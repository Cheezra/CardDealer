//www.elegoo.com
//2016.12.9

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin 4 to 74hc595 pin 1
 * LCD Enable pin 6 to 74hc595 pin 3
 * LCD D4 pin 11 to 74hc595 pin 4
 * LCD D5 pin 12 to 74hc595 pin 5
 * LCD D6 pin 13 to 74hc595 pin 6
 * LCD D7 pin 14 to 74hc595 pin 7
 * LCD R/W pin 5 to ground
 * LCD VSS pin 1 to ground
 * LCD VCC pin 2 to 5V
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Following tutorial from https://www.instructables.com/LCD-Screen-With-74HC595-and-Keypad-Module/
 Library used: https://github.com/An7orAhmed/LiquidCrystalSerial

vv original library vv
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal


 74HC595 Connections:
 Q0 pin 15 -> none
 Q1 pin 1 -> lcd pin 4
 Q2 pin 2 -> none
 Q3 pin 3 -> lcd pin 6
 Q4 pin 4 -> lcd pin 11
 Q5 pin 5 -> lcd pin 12
 Q6 pin 6 -> lcd pin 13
 Q7 pin 7 -> lcd pin 14
 Q7' pin 9 -> none
 GND pin 8 -> ground
 MR pin 10 -> 5V power
 SH_CP pin 11 -> arduino pin 13
 ST_CP pin 12 -> arduino pin 10
 OE pin 13 -> ground
 DS pin 14 -> arduino pin 11
 VCC pin 16 -> 5V power
 */

// include the library code:
#include <LiquidCrystalSerial.h>
#include <Stepper.h>

#define KEY_NOT_PRESSED '-'

#define ENABLE 4
#define DIRA 2
#define DIRB 3

using namespace std;

// define arduino pins connected to the 74HC595
int SHCP = 13;
int STCP = 10;
int DS = 11;

int keyPressDelay = 250;
int analogPin = 0;
int raw = 0;
int Vin = 5;
float Vout = 0;
float R1 = 10000;
float R2 = 0;
float buffer = 0;

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int gearRatio = 4;              // number of teeth in big gear / number of teeth in small gear
const int rotateTime = 125;          // milliseconds needed for the motor to shoot out only 1 card

// initialize the library with the numbers of the interface pins
LiquidCrystalSerial lcd(SHCP, DS, STCP);

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 6, 8, 7, 9);

// resistance measuring code taken from https://www.circuitbasics.com/arduino-ohm-meter/
// known resistor should be 10k

// keypad measuring breadboard setup taken from https://www.youtube.com/watch?v=kVw6kPSJJfw
// resistors should be 1k and 220

char readKeypadPress() {
  char key = KEY_NOT_PRESSED;
  // get the value from the analog pin and determine the key that was pressed
  raw = analogRead(analogPin);
  // Serial.print("Raw: ");
  // Serial.println(raw);
  // delay(1000);
  // make sure the key was pressed and it wasn't too soon after the last press
  if (raw > 500) {
    buffer = raw * Vin;
    Vout = (buffer) / 1024.0;
    buffer = (Vin / Vout) - 1;
    R2 = R1 * buffer;
    // Serial.print("Vout: ");
    // Serial.println(Vout);
    // Serial.print("R2: ");
    // Serial.println(R2);

    // determine the key based on the resistance value R2
    // key = (R2 < 1000 + 110 && R2 > 1000 - 110) ? '1' : KEY_NOT_PRESSED;
    // key = (R2 < 1220 + 110 && R2 > 1220 - 110) ? '2' : KEY_NOT_PRESSED;
    // key = (R2 < 1440 + 110 && R2 > 1440 - 110) ? '3' : KEY_NOT_PRESSED;
    // key = (R2 < 1660 + 110 && R2 > 1660 - 110) ? 'A' : KEY_NOT_PRESSED;
    // key = (R2 < 2000 + 110 && R2 > 2000 - 110) ? '4' : KEY_NOT_PRESSED;
    // key = (R2 < 2220 + 110 && R2 > 2220 - 110) ? '5' : KEY_NOT_PRESSED;
    // key = (R2 < 2440 + 110 && R2 > 2440 - 110) ? '6' : KEY_NOT_PRESSED;
    // key = (R2 < 2660 + 110 && R2 > 2660 - 110) ? 'B' : KEY_NOT_PRESSED;
    // key = (R2 < 3000 + 110 && R2 > 3000 - 110) ? '7' : KEY_NOT_PRESSED;
    // key = (R2 < 3220 + 110 && R2 > 3220 - 110) ? '8' : KEY_NOT_PRESSED;
    // key = (R2 < 3440 + 110 && R2 > 3440 - 110) ? '9' : KEY_NOT_PRESSED;
    // key = (R2 < 3660 + 110 && R2 > 3660 - 110) ? 'C' : KEY_NOT_PRESSED;
    // key = (R2 < 4000 + 110 && R2 > 4000 - 110) ? '*' : KEY_NOT_PRESSED;
    // key = (R2 < 4220 + 110 && R2 > 4220 - 110) ? '0' : KEY_NOT_PRESSED;
    // key = (R2 < 4440 + 110 && R2 > 4440 - 110) ? '#' : KEY_NOT_PRESSED;
    // key = (R2 < 4660 + 110 && R2 > 4660 - 110) ? 'D' : KEY_NOT_PRESSED;

    if (R2 < 1000 + 110) key = '1';
    else if (R2 < 1220 + 110) key = '2';
    else if (R2 < 1440 + 110) key = '3';
    else if (R2 < 1660 + 110) key = 'A';
    else if (R2 < 2000 + 110) key = '4';
    else if (R2 < 2220 + 110) key = '5';
    else if (R2 < 2440 + 110) key = '6';
    else if (R2 < 2660 + 110) key = 'B';
    else if (R2 < 3000 + 110) key = '7';
    else if (R2 < 3220 + 110) key = '8';
    else if (R2 < 3440 + 110) key = '9';
    else if (R2 < 3660 + 110) key = 'C';
    else if (R2 < 4000 + 110) key = '*';
    else if (R2 < 4220 + 110) key = '0';
    else if (R2 < 4440 + 110) key = '#';
    else if (R2 < 4660 + 110) key = 'D';
    else key = KEY_NOT_PRESSED; 
    // Serial.println(key);
  }

  return key;

}

void clearLcdLine(int row) {
  lcd.setCursor(0, row);
  lcd.print("                ");
}

int readNumberEntered(String prompt) {

  String number_str = "";
  int number = 0;

  // display the prompt
  lcd.setCursor(0, 0);
  lcd.print(prompt);

  // * = enter
  // # = clear
  // A - D = nothing

  char key = KEY_NOT_PRESSED;
  while (key != '*') {
    // check for a keypress repeatedly
    key = readKeypadPress();
    // make sure the key is a valid number
    if (key != KEY_NOT_PRESSED && key != 'A' && key != 'B' && key != 'C' && key != 'D' && key != '*' && key != '#') {
      // Serial.println(key);

      // add the number to a string
      number_str += key;

      // convert the number to an int
      number = number_str.toInt();

      // check if the number is too large
      if (number > 10000) {
        number = 0;
        number_str = "";
        // print an error message
        clearLcdLine(0);
        clearLcdLine(1);
        lcd.setCursor(0, 0);
        lcd.print("The number is");
        lcd.setCursor(0, 1);
        lcd.print("too big!");
        delay(1000);

        // restore prompt
        clearLcdLine(0);
        clearLcdLine(1);
        lcd.setCursor(0, 0);
        lcd.print(prompt);
      }

      // show the number on the screen
      lcd.setCursor(0, 1);
      lcd.print(number);
    }

    // clear the number if the user presses #
    else if (key == '#') {
      number_str = "";
      number = 0;
      clearLcdLine(1);
    }

    // delay to prevent double clicking
    delay(keyPressDelay);
  }

  // clear the display once done
  clearLcdLine(0);
  clearLcdLine(1);

  return number;
}

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hello, World!");
  
  myStepper.setSpeed(rolePerMinute);
  // initialize the serial port:
  Serial.begin(9600);
  // set pin directions
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // set the motor direction
  digitalWrite(ENABLE, LOW);
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  // lcd.print(millis() / 1000);

  // clear the line
  clearLcdLine(0);
  clearLcdLine(1);
  // prompt the user to enter the number of players
  int numPlayers = readNumberEntered("# of players?");//# of players?
  // prompt the user to enter the number of cards each
  int numCards = readNumberEntered("# of cards each?");//# of cards each?

  Serial.print("Number of Players: ");
  Serial.println(numPlayers);
  Serial.print("Number of Cards: ");
  Serial.println(numCards);

  // Dealing...
  lcd.setCursor(0, 0);
  lcd.print("Dealing...");// Dealing
  // delay(5000);


  // deal cards
      
  // figure out how much is needed to rotate to aim at the next player
  // stepsPerRevolution * gearRatio = 360 degrees
  // 360 / numplayers = amount needed
  // amount needed = stepsPerRevolution * gearRatio / numPlayers
  int stepsPerAngle = stepsPerRevolution * gearRatio / numPlayers; // will result in integer answer

  // loop through for each card dealt
  for (int card = 0; card < numCards; card++) {
    // loop through each player and deal a card to them
    for (int player = 0; player < numPlayers; player++) {
      // rotate to the next player
      myStepper.step(stepsPerAngle);
      // shoot the card
      digitalWrite(DIRA, HIGH);
      digitalWrite(DIRB, LOW);
      digitalWrite(ENABLE, HIGH);
      delay(rotateTime);
      digitalWrite(ENABLE, LOW);

      // bring back extra card
      digitalWrite(DIRA, LOW);
      digitalWrite(DIRB, HIGH);
      digitalWrite(ENABLE, HIGH);
      delay(rotateTime);
      digitalWrite(ENABLE, LOW);

    }
    // rotate back to forward at the end
    myStepper.step(-numPlayers * stepsPerAngle);

    // wait
    delay(1000);
  }

}