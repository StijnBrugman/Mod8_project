/*
  LiquidCrystal Library - Hello World

  Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
  library works with all LCD displays that are compatible with the
  Hitachi HD44780 driver. There are many of them out there, and you
  can usually tell them by the 16-pin interface.

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe
  modified 7 Nov 2016
  by Arturo Guadalupi

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

#define ROT_ENC_CLK_D 8
#define ROT_ENC_DT_D 9
#define ROT_ENC_SW_D 10

int counter_D = 0;
int currentStateCLK_D;
int lastStateCLK_D;

char rotaryHeaders[] = {'A', 'B', 'C', 'D'};                                   // Headers for the rotary encoders and the button


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String recievedCity = "";
String recievedDate = "";


unsigned long lastButtonPress = 0;

int buttonState = 0;
boolean pressed = false;

void setup() {

  Serial.begin(9600);

  // Set encoder pins as inputs and calibrate the last state
  pinMode(ROT_ENC_CLK_D, INPUT);
  pinMode(ROT_ENC_DT_D, INPUT);
  pinMode(ROT_ENC_SW_D, INPUT_PULLUP);

  lastStateCLK_D = digitalRead(ROT_ENC_CLK_D);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {

  if (Serial.available() > 0) {
    readData();
  }
  button();
  rotary();

}

void readData() {
  String recievedData = Serial.readStringUntil('\n');             // Save the string until the break

  char recieveHeader = recievedData.charAt(0);                    // Check the header
  recievedData.remove(0, 1);                                      // Remove the header

  if (recieveHeader == 'M') {
    recievedCity = recievedData;
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(recievedCity);
  } else if (recieveHeader == 'N') {
    recievedDate = recievedData;
    lcd.setCursor(0, 1);
    lcd.print(recievedDate);
  } else {

    int data = recievedData.toInt();                                // Transate the remaining string to an int

    //    switch (recieveHeader) {                                        // Go into the switch with the header
    //      case 'A':                                                     // If the header matches the case
    //        if (data == 1) {                                            // And the int is 1
    //          digitalWrite(valvePin_1_Out, HIGH);                       // Write HIGH to the valve
    //        } else {                                                    // If other data was send
    //          digitalWrite(valvePin_1_Out, LOW);                        // Else write LOW
    //        }
    //        break;                                                      // Break out of the switch
    //      case 'B':
    //        if (data == 1) {
    //          digitalWrite(valvePin_1_In, HIGH);
    //        } else {
    //          digitalWrite(valvePin_1_In, LOW);
    //        }      break;
    //      case 'C':
    //        if (data == 1) {
    //          digitalWrite(valvePin_2_Out, HIGH);
    //        } else {
    //          digitalWrite(valvePin_2_Out, LOW);
    //        }      break;
    //      case 'D':
    //        if (data == 1) {
    //          digitalWrite(valvePin_2_In, HIGH);
    //        } else {
    //          digitalWrite(valvePin_2_In, LOW);
    //        }
    //        break;
    //      case 'E':
    //        if (data == 1) {
    //          digitalWrite(valvePin_3_Out, HIGH);
    //        } else {
    //          digitalWrite(valvePin_3_Out, LOW);
    //        }      break;
    //      case 'F':
    //        if (data == 1) {
    //          digitalWrite(valvePin_3_In, HIGH);
    //        } else {
    //          digitalWrite(valvePin_3_In, LOW);
    //        }      break;
    //      case 'G':
    //        if (data == 1) {
    //          digitalWrite(valvePin_4_Out, HIGH);
    //        } else {
    //          digitalWrite(valvePin_4_Out, LOW);
    //        }
    //        break;
    //      case 'H':
    //        if (data == 1) {
    //          digitalWrite(valvePin_4_In, HIGH);
    //        } else {
    //          digitalWrite(valvePin_4_In, LOW);
    //        }      break;
    //      case 'I':
    //        if (data == 1) {
    //          digitalWrite(valvePin_5_Out, HIGH);
    //        } else {
    //          digitalWrite(valvePin_5_Out, LOW);
    //        }      break;
    //      case 'J':
    //        if (data == 1) {
    //          digitalWrite(valvePin_5_In, HIGH);
    //        } else {
    //          digitalWrite(valvePin_5_In, LOW);
    //        }
    //        break;
    //      case 'K':
    //        if (data == 1) {
    //          digitalWrite(valvePin_6_Out, HIGH);
    //        } else {
    //          digitalWrite(valvePin_6_Out, LOW);
    //        }      break;
    //      case 'L':
    //        if (data == 1) {
    //          digitalWrite(valvePin_6_In, HIGH);
    //        } else {
    //          digitalWrite(valvePin_6_In, LOW);
    //        }      break;
    //    }
  }
}

void button() {

  // Read the button state
  int btnState = digitalRead(ROT_ENC_SW_D);

  //If we detect LOW signal, button is pressed
  if (btnState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress > 50 && !pressed) {
      buttonState++;
      Serial.print(rotaryHeaders[3]);
      Serial.println(buttonState);
      pressed = true;
    }
    // Remember last button press event
    lastButtonPress = millis();
  } else {
    pressed = false;

  }
}

void rotary() {

  // Reads the encoder and outputs that value to the Pi
  // Read the current state of CLK
  currentStateCLK_D = digitalRead(ROT_ENC_CLK_D);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK_D != lastStateCLK_D  && currentStateCLK_D == 1) {
    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(ROT_ENC_DT_D) != currentStateCLK_D) {
      counter_D ++;
    } else { // Encoder is rotating CW so increment
      counter_D --;
    }
    Serial.print(rotaryHeaders[0]);
    Serial.println(counter_D);
  }
  // Remember last CLK state
  lastStateCLK_D = currentStateCLK_D;

}
