/*

  The Arduino file for the Hybrid Worlds Project of Creative Technolgy.

  The Arduino collects data from flow sensors, water level sensors, distance sensors, and from rotary encoders.
  It sends this data to a Raspberry Pi.
  The Raspberry Pi sends commands to the Arduino.
  The Arduino controls water valves that work together with pumps to fill several tubes with water. 
  It also lights LED strips to show the water height and the temperature of the water.

  For a complete overview of the project and all code, you can check our repository on GitHub.
  https://github.com/StijnBrugman/Mod8_project

  Bas van der Steenhoven
  Stijn Brugman
  David Lammers

  2021


  The following pins are used:
    Pins A0 to A4 are for the Water Level Sensors
    Pins 5 to 9 are for LED strips
    Pins 14 and 19 are for the Screen
    Pins 22 to 31 are for the Valves
    Pins 32 to 41 are for the Distance Sensors
    Pins 42, 43 and 47 to 53 are for Rotary Encoders

  For sending data, the following headers are used:
    A to C for the Rotary Encoders
    D for the Button
    E to I for the Distance Sensors
    J and K for th Flow Sensors
    L for the city selector with the Water Level Sensors

  For recieving data, the following headers are used:
    A to L for the Water Valves. K and L are for the river, the rest is for the tubes in pairs of 2
    M for the City that the display should show
    N for the Date that the display should show
    O to P for the LED strips that display temperature


*/


//----------------------------General_Communication----------------------------//
// Communcation headers
char rotaryHeaders[] = {'A', 'B', 'C', 'D'};                                   // Headers for the rotary encoders and the button
char distanceHeaders[5] = {'E', 'F', 'G', 'H', 'I'};                           // Headers for the distance sensors
char flowHeaders[] = {'J', 'K'};                                               // Headers for the flow sensors
char cityHeader = 'L';                                                         // Header for the city selector
char LEDHeaders[5] = {'O', 'P', 'Q', 'R', 'S'};                                // Headers for the LED strips
char failedHeader = 'Z';

char receivedCityHeader = 'M';
char receivedDateHeader = 'N';

String receivedCity = "";
String receivedDate = "";


//--------------------------------Water_Valves---------------------------------//
// Water Valve Pins
#define valvePin_1_Out 22
#define valvePin_1_In 23
#define valvePin_2_Out 24
#define valvePin_2_In 25
#define valvePin_3_Out 26
#define valvePin_3_In 27
#define valvePin_4_Out 28
#define valvePin_4_In 29
#define valvePin_5_Out 30
#define valvePin_5_In 31
#define valvePin_6_Out 32
#define valvePin_6_In 33


//--------------------------------Distance_Sensor------------------------------//
// Distance Sensor Pins
#define trigPin_A 32
#define echoPin_A 33
#define trigPin_B 34
#define echoPin_B 35
#define trigPin_C 36
#define echoPin_C 37
#define trigPin_D 38
#define echoPin_D 39
#define trigPin_E 40
#define echoPin_E 41

int newDistance[5];
int oldDistance[5];

unsigned long distanceTimer;


//--------------------------------Rotary_Encoder-------------------------------//
// Rotary Encoder Pins
#define ROT_ENC_CLK_D 42
#define ROT_ENC_DT_D 43
#define ROT_ENC_SW_D 47

int counter_D = 0;
int currentStateCLK_D;
int lastStateCLK_D;

#define ROT_ENC_CLK_M 48
#define ROT_ENC_DT_M 49
#define ROT_ENC_SW_M 50

int counter_M = 0;
int currentStateCLK_M;
int lastStateCLK_M;

#define ROT_ENC_CLK_Y 51
#define ROT_ENC_DT_Y 52
#define ROT_ENC_SW_Y 53

int counter_Y = 0;
int currentStateCLK_Y;
int lastStateCLK_Y;

unsigned long lastButtonPress = 0;

int buttonState = 0;
boolean pressed = false;


//--------------------------------Water_Level_Sensors--------------------------//
// Water Level Sensor Pins
#define sensorPin_A A0
#define sensorPin_B A1
#define sensorPin_C A2
#define sensorPin_D A3
#define sensorPin_E A4

// Water Level Sensor Power Pins
#define sensorPowerPin_A 4
#define sensorPowerPin_B 10
#define sensorPowerPin_C 11
#define sensorPowerPin_D 12
#define sensorPowerPin_E 13

// Value for storing water level
int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;

unsigned long waterTimer = 0;

//--------------------------------Flow_Sensors---------------------------------//
#define flowSensorPin_A 6
#define flowSensorPin_B 7

volatile float flow_frequency_A;                                               // Measures flow sensor pulsesunsigned
volatile float flow_frequency_B;                                               // Measures flow sensor pulsesunsigned

float l_second_A;                                                              // Calculated litres/hour
float l_second_B;                                                              // Calculated litres/hour
unsigned long currentTime;
unsigned long cloopTime;

unsigned long volume_Old_A = 0;
unsigned long volume_New_A = 0;
unsigned long volume_Old_B = 0;
unsigned long volume_New_B = 0;


//--------------------------------Screen---------------------------------------//
// include the library code:
#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 19, en = 18, d4 = 17, d5 = 16, d6 = 15, d7 = 14;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//--------------------------------LEDs-----------------------------------------//
#include <Adafruit_NeoPixel.h>

#define Strip_1_Pin 5
#define Strip_2_Pin 6
#define Strip_3_Pin 7
#define Strip_4_Pin 8
#define Strip_5_Pin 9
#define N_LEDS 8

Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(N_LEDS, Strip_1_Pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_2 = Adafruit_NeoPixel(N_LEDS, Strip_2_Pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_3 = Adafruit_NeoPixel(N_LEDS, Strip_3_Pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_4 = Adafruit_NeoPixel(N_LEDS, Strip_4_Pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_5 = Adafruit_NeoPixel(N_LEDS, Strip_5_Pin, NEO_GRB + NEO_KHZ800);

String receivedColourArray;

String redLEDColourString;
String greenLEDColourString;
String blueLEDColourString;
int redLEDColour;
int greenLEDColour;
int blueLEDColour;

String amountOfLEDsString;
int amountOfLEDs;
int city;

int ind1, ind2, ind3;

int data = 0;




//-----------------------------------------------------------------------------//

void setup() {

  // Set encoder pins as inputs and calibrate the last state
  pinMode(ROT_ENC_CLK_D, INPUT);
  pinMode(ROT_ENC_DT_D, INPUT);
  pinMode(ROT_ENC_SW_D, INPUT_PULLUP);

  lastStateCLK_D = digitalRead(ROT_ENC_CLK_D);

  pinMode(ROT_ENC_CLK_M, INPUT);
  pinMode(ROT_ENC_DT_M, INPUT);
  pinMode(ROT_ENC_SW_M, INPUT_PULLUP);

  lastStateCLK_M = digitalRead(ROT_ENC_CLK_M);

  pinMode(ROT_ENC_CLK_Y, INPUT);
  pinMode(ROT_ENC_DT_Y, INPUT);
  pinMode(ROT_ENC_SW_Y, INPUT_PULLUP);

  lastStateCLK_M = digitalRead(ROT_ENC_CLK_Y);

  // Set distance sensor pins to input and output
  pinMode(trigPin_A, OUTPUT);
  pinMode(echoPin_A, INPUT);
  pinMode(trigPin_B, OUTPUT);
  pinMode(echoPin_B, INPUT);
  pinMode(trigPin_C, OUTPUT);
  pinMode(echoPin_C, INPUT);
  pinMode(trigPin_D, OUTPUT);
  pinMode(echoPin_D, INPUT);
  pinMode(trigPin_E, OUTPUT);
  pinMode(echoPin_E, INPUT);

  // Set the valve pins to output
  pinMode(valvePin_1_Out, OUTPUT);
  pinMode(valvePin_1_In, OUTPUT);
  pinMode(valvePin_2_Out, OUTPUT);
  pinMode(valvePin_2_In, OUTPUT);
  pinMode(valvePin_3_Out, OUTPUT);
  pinMode(valvePin_3_In, OUTPUT);
  pinMode(valvePin_4_Out, OUTPUT);
  pinMode(valvePin_4_In, OUTPUT);
  pinMode(valvePin_5_Out, OUTPUT);
  pinMode(valvePin_5_In, OUTPUT);
  pinMode(valvePin_6_Out, OUTPUT);
  pinMode(valvePin_6_In, OUTPUT);

  // Set the flow sensor pins to input and calibrate the timer
  pinMode(flowSensorPin_A, INPUT);
  pinMode(flowSensorPin_B, INPUT);
  sei(); // Enable interrupts

  digitalWrite(flowSensorPin_A, HIGH); // Optional Internal Pull-Up
  attachInterrupt(0, flow_A, RISING); // Setup Interrupt
  digitalWrite(flowSensorPin_B, HIGH); // Optional Internal Pull-Up
  attachInterrupt(0, flow_B, RISING); // Setup Interrupt

  currentTime = millis();
  cloopTime = currentTime;

  // Set D7 as an OUTPUT
  pinMode(sensorPowerPin_A, OUTPUT);
  pinMode(sensorPowerPin_B, OUTPUT);
  pinMode(sensorPowerPin_C, OUTPUT);
  pinMode(sensorPowerPin_D, OUTPUT);
  pinMode(sensorPowerPin_E, OUTPUT);


  // Set to LOW so no power flows through the sensor
  digitalWrite(sensorPowerPin_A, LOW);
  digitalWrite(sensorPowerPin_B, LOW);
  digitalWrite(sensorPowerPin_C, LOW);
  digitalWrite(sensorPowerPin_D, LOW);
  digitalWrite(sensorPowerPin_E, LOW);


  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  strip_1.begin();
  strip_2.begin();
  strip_3.begin();
  strip_4.begin();
  strip_5.begin();

  // Setup Serial Monitor
  Serial.begin(9600);


}

void loop() {
  encoderReaderDay();                                             // Run the rotary encoder for the day selector
  encoderReaderMonth();                                           // Run the rotary encoder for the month selector
  encoderReaderYear();                                            // Run the rotary encoder for the year selector
  buttonDetection();                                              // Check if the button is pressed
  flowSendData();

  if (millis() > waterTimer + 300) {
    waterTimer = millis();// 1/3th of a second after the timer
    waterSensor();
  }
  // Send data from the flow sensors

  if (millis() > distanceTimer + 20) {                            // 1/3th of a second after the timer
    distanceRead();                                               // Read the distance
    distanceTimer = millis();                                     // Reset the timer
  }

  if (Serial.available() > 0) {                                   // If serial data is available for reading
    readData();                                                   // Execute the method to read the data
  }
  delay(1);                                                       // Wait 1 millisecond
}

// Read the data
void readData() {                                                 // Read the data
  String receivedData = Serial.readStringUntil('\n');             // Save the string until the break
  char receiveHeader = receivedData.charAt(0);                    // Check the header
  receivedData.remove(0, 1);                                      // Remove the header
  data = 0;
  if (receiveHeader == 'M') {
    receivedCity = receivedData;
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(receivedCity);
  } else if (receiveHeader == 'N') {
    receivedDate = receivedData;
    lcd.setCursor(0, 1);
    lcd.print(receivedDate);
  } else {
    switch (receiveHeader) {                                        // Go into the switch with the header
      case 'A':                                                     // If the header matches the case
        data = receivedData.toInt();
        if (data == 1) {                                            // And the int is 1
          digitalWrite(valvePin_1_Out, HIGH);                       // Write HIGH to the valve
        } else {                                                    // If other data was send
          digitalWrite(valvePin_1_Out, LOW);                        // Else write LOW
        }
        break;                                                      // Break out of the switch
      case 'B':
        data = receivedData.toInt();
        if (data == 1) {
          digitalWrite(valvePin_1_In, HIGH);
        } else {
          digitalWrite(valvePin_1_In, LOW);
        }      break;
      case 'C':
        data = receivedData.toInt();
        if (data == 1) {
          digitalWrite(valvePin_2_Out, HIGH);
        } else {
          digitalWrite(valvePin_2_Out, LOW);
        }      break;
      case 'D':
        data = receivedData.toInt();
        if (data == 1) {
          digitalWrite(valvePin_2_In, HIGH);
        } else {
          digitalWrite(valvePin_2_In, LOW);
        }
        break;
      case 'E':
        data = receivedData.toInt();
        if (data == 1) {
          digitalWrite(valvePin_3_Out, HIGH);
        } else {
          digitalWrite(valvePin_3_Out, LOW);
        }      break;
      case 'F':
        data = receivedData.toInt();
        if (data == 1) {
          digitalWrite(valvePin_3_In, HIGH);
        } else {
          digitalWrite(valvePin_3_In, LOW);
        }      break;
      case 'G':
        data = receivedData.toInt();
        if (data == 1) {
          digitalWrite(valvePin_4_Out, HIGH);
        } else {
          digitalWrite(valvePin_4_Out, LOW);
        }
        break;
      case 'H':
        data = receivedData.toInt();
        if (data == 1) {
          digitalWrite(valvePin_4_In, HIGH);
        } else {
          digitalWrite(valvePin_4_In, LOW);
        }      break;
      case 'I':
        data = receivedData.toInt();
        if (data == 1) {
          digitalWrite(valvePin_5_Out, HIGH);
        } else {
          digitalWrite(valvePin_5_Out, LOW);
        }      break;
      case 'J':
        data = receivedData.toInt();
        if (data == 1) {
          digitalWrite(valvePin_5_In, HIGH);
        } else {
          digitalWrite(valvePin_5_In, LOW);
        }
        break;
      case 'K':
        data = receivedData.toInt();
        if (data == 1) {
          digitalWrite(valvePin_6_Out, HIGH);
        } else {
          digitalWrite(valvePin_6_Out, LOW);
        }      break;
      case 'L':
        data = receivedData.toInt();
        if (data == 1) {
          digitalWrite(valvePin_6_In, HIGH);
        } else {
          digitalWrite(valvePin_6_In, LOW);
        }
        break;
      case 'O':                                                   // If an 'O' is recieved

        city = 1;                                                 // Select the corresponding city

        receivedColourArray = receivedData;                       // Put the data in a String

        ind1 = receivedColourArray.indexOf(',');                  // Finds thelocation of first ,
        ind2 = receivedColourArray.indexOf(',', ind1 + 1 );       // Finds the location of second ,
        ind3 = receivedColourArray.indexOf(',', ind2 + 1 );       // Finds the location of the third ,

        amountOfLEDsString = receivedColourArray.substring(0, ind1);              // Captures the
        redLEDColourString = receivedColourArray.substring(ind1 + 1, ind2 + 1);   // captures second data String, which is the redness of the total colour
        greenLEDColourString = receivedColourArray.substring(ind2 + 1, ind3 + 1); // captures third data String, which is the greenness of the total colour
        blueLEDColourString = receivedColourArray.substring(ind3 + 1);            // captures remain part of the full String, which is the blueness

        amountOfLEDs = amountOfLEDsString.toInt();                                // Translates the String to the integer of the String
        redLEDColour = redLEDColourString.toInt();                                // Translates the String to the integer of the String
        greenLEDColour = greenLEDColourString.toInt();                            // Translates the String to the integer of the String
        blueLEDColour = blueLEDColourString.toInt();                              // Translates the String to the integer of the String



        lightLEDs(strip_1.Color(redLEDColour, blueLEDColour, greenLEDColour), amountOfLEDs, city); // Lights the LEDstrip
        break;
      case 'P':

        city = 2;

        receivedColourArray = receivedData;

        ind1 = receivedColourArray.indexOf(',');
        ind2 = receivedColourArray.indexOf(',', ind1 + 1 );
        ind3 = receivedColourArray.indexOf(',', ind2 + 1 );

        amountOfLEDsString = receivedColourArray.substring(0, ind1);
        redLEDColourString = receivedColourArray.substring(ind1 + 1, ind2 + 1);
        greenLEDColourString = receivedColourArray.substring(ind2 + 1, ind3 + 1);
        blueLEDColourString = receivedColourArray.substring(ind3 + 1);

        amountOfLEDs = amountOfLEDsString.toInt();
        redLEDColour = redLEDColourString.toInt();
        greenLEDColour = greenLEDColourString.toInt();
        blueLEDColour = blueLEDColourString.toInt();

        lightLEDs(strip_2.Color(redLEDColour, blueLEDColour, greenLEDColour), amountOfLEDs, city);
        break;
      case 'Q':

        city = 3;

        receivedColourArray = receivedData;

        ind1 = receivedColourArray.indexOf(',');
        ind2 = receivedColourArray.indexOf(',', ind1 + 1 );
        ind3 = receivedColourArray.indexOf(',', ind2 + 1 );

        amountOfLEDsString = receivedColourArray.substring(0, ind1);
        redLEDColourString = receivedColourArray.substring(ind1 + 1, ind2 + 1);
        greenLEDColourString = receivedColourArray.substring(ind2 + 1, ind3 + 1);
        blueLEDColourString = receivedColourArray.substring(ind3 + 1);

        amountOfLEDs = amountOfLEDsString.toInt();
        redLEDColour = redLEDColourString.toInt();
        greenLEDColour = greenLEDColourString.toInt();
        blueLEDColour = blueLEDColourString.toInt();

        lightLEDs(strip_3.Color(redLEDColour, blueLEDColour, greenLEDColour), amountOfLEDs, city);
        break;
      case 'R':

        city = 4;

        receivedColourArray = receivedData;

        ind1 = receivedColourArray.indexOf(',');
        ind2 = receivedColourArray.indexOf(',', ind1 + 1 );
        ind3 = receivedColourArray.indexOf(',', ind2 + 1 );

        amountOfLEDsString = receivedColourArray.substring(0, ind1);
        redLEDColourString = receivedColourArray.substring(ind1 + 1, ind2 + 1);
        greenLEDColourString = receivedColourArray.substring(ind2 + 1, ind3 + 1);
        blueLEDColourString = receivedColourArray.substring(ind3 + 1);

        amountOfLEDs = amountOfLEDsString.toInt();
        redLEDColour = redLEDColourString.toInt();
        greenLEDColour = greenLEDColourString.toInt();
        blueLEDColour = blueLEDColourString.toInt();

        lightLEDs(strip_4.Color(redLEDColour, blueLEDColour, greenLEDColour), amountOfLEDs, city);
        break;
      case 'S':

        city = 5;

        receivedColourArray = receivedData;

        ind1 = receivedColourArray.indexOf(',');
        ind2 = receivedColourArray.indexOf(',', ind1 + 1 );
        ind3 = receivedColourArray.indexOf(',', ind2 + 1 );

        amountOfLEDsString = receivedColourArray.substring(0, ind1);
        redLEDColourString = receivedColourArray.substring(ind1 + 1, ind2 + 1);
        greenLEDColourString = receivedColourArray.substring(ind2 + 1, ind3 + 1);
        blueLEDColourString = receivedColourArray.substring(ind3 + 1);

        amountOfLEDs = amountOfLEDsString.toInt();
        redLEDColour = redLEDColourString.toInt();
        greenLEDColour = greenLEDColourString.toInt();
        blueLEDColour = blueLEDColourString.toInt();

        lightLEDs(strip_5.Color(redLEDColour, blueLEDColour, greenLEDColour), amountOfLEDs, city);
        break;
      default:
        Serial.print(failedHeader);
        Serial.print("  Letter was not recognised");
        Serial.print("  I received: ");
        Serial.print(receiveHeader);
        Serial.print("  ");
        Serial.println(receivedData);
        break;
    }
  }
}

// Detects the button of the rotary encoder
void buttonDetection() {
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


// Reads the encoder and outputs that value to the Pi
void encoderReaderDay() {
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


void encoderReaderMonth() {
  // Read the current state of CLK
  currentStateCLK_M = digitalRead(ROT_ENC_CLK_M);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK_M != lastStateCLK_M  && currentStateCLK_M == 1) {
    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(ROT_ENC_DT_M) != currentStateCLK_M) {
      counter_M ++;
    } else { // Encoder is rotating CW so increment
      counter_M --;
    }
    Serial.print(rotaryHeaders[1]);
    Serial.println(counter_M);
  }
  // Remember last CLK state
  lastStateCLK_M = currentStateCLK_M;
}


void encoderReaderYear() {
  // Read the current state of CLK
  currentStateCLK_Y = digitalRead(ROT_ENC_CLK_Y);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK_Y != lastStateCLK_Y  && currentStateCLK_Y == 1) {
    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(ROT_ENC_DT_Y) != currentStateCLK_Y) {
      counter_Y ++;
    } else { // Encoder is rotating CW so increment
      counter_Y --;
    }
    Serial.print(rotaryHeaders[2]);
    Serial.println(counter_Y);
  }
  // Remember last CLK state
  lastStateCLK_Y = currentStateCLK_Y;
}


// Reads the distance sensors and outputs their data to the Pi
void distanceRead() {

  // For loop for use with 5 sensors
  int j = 0;                                                     // Declare int 'j'
  for (int i = 0; i < 10; i += 2) {                          // For all 5 sensors
    // It goes from 0 to 10 and increases by 2. This makes sure that i + pinnumber is correct.
    newDistance[j] = distance(i + trigPin_A, i + echoPin_A);   // newDistance is the measured distance from the sensor

    if (newDistance[j] != oldDistance[j]) {                  // If the new distance is different
      Serial.print(distanceHeaders[i]);                      // Print the according header
      Serial.println(newDistance[j]);                        // And the measured value
      newDistance[j] = oldDistance[j];                       // Save the measured value
    }
    j++;                                                     // Increment J
  }
}

// Calculates the distance for the distance sensors
int distance(int trigPin, int echoPin) {                       // Take the echo pin and trigger pin of the distance sensor
  int duration, distance;                                      // Declare duration and distance
  digitalWrite (trigPin, HIGH);                                // Set the trigger pin to HIGH
  delayMicroseconds(10);                                       // Wait for 10 microseconds
  digitalWrite (trigPin, LOW);                                 // Set it back to low
  duration = pulseIn (echoPin, HIGH);                          // Wait for the pulse to arrive and measure that time
  distance =  (duration / 2) / 2.91;                           // Calculate the distance based on time travelled and the speed of light
  return distance;                                             // Return the distance
}

void lightLEDs(uint32_t c, int height, int caseCity) {

  switch (caseCity) {
    case 1:
      for (int i = 0; i < height; i++) {
        strip_1.setPixelColor(i , c);
      }
      for (int i = height; i < N_LEDS - 1; i++) {
        strip_1.setPixelColor(i, 0);
      }
      strip_1.show();
      break;
    case 2:
      for (int i = 0; i < height; i++) {
        strip_2.setPixelColor(i , c);
      }
      for (int i = height; i < N_LEDS - 1; i++) {
        strip_2.setPixelColor(i, 0);
      }
      strip_2.show();
      break;
    case 3:
      for (int i = 0; i < height; i++) {
        strip_3.setPixelColor(i , c);
      }
      for (int i = height; i < N_LEDS - 1; i++) {
        strip_3.setPixelColor(i, 0);
      }
      strip_3.show();
      break;
    case 4:
      for (int i = 0; i < height; i++) {
        strip_4.setPixelColor(i , c);
      }
      for (int i = height; i < N_LEDS - 1; i++) {
        strip_4.setPixelColor(i, 0);
      }
      strip_4.show();
      break;
    case 5:
      for (int i = 0; i < height; i++) {
        strip_5.setPixelColor(i , c);
      }
      for (int i = height; i < N_LEDS - 1; i++) {
        strip_5.setPixelColor(i, 0);
      }
      strip_5.show();
      break;
  }

}

void waterSensor() {
  //get the reading from the function below and print it
  int level1 = readSensor(sensorPowerPin_A, sensorPin_A, val1);
  int level2 = readSensor(sensorPowerPin_B, sensorPin_B, val2);
  int level3 = readSensor(sensorPowerPin_C, sensorPin_C, val3);
  int level4 = readSensor(sensorPowerPin_D, sensorPin_D, val4);
  int level5 = readSensor(sensorPowerPin_E, sensorPin_E, val5);

  if (level1 > 280) {
    Serial.print(cityHeader);
    Serial.println("1");
  }

  if (level2 > 280) {
    Serial.print(cityHeader);
    Serial.println("2");
  }

  if (level3 > 280) {
    Serial.print(cityHeader);
    Serial.println("3");
  }

  if (level4 > 280) {
    Serial.print(cityHeader);
    Serial.println("4");
  }

  if (level5 > 280) {
    Serial.print(cityHeader);
    Serial.println("5");
  }

}

//This is a function used to get the reading
int readSensor(int power, int pin, int val) {
  digitalWrite(power, HIGH);  // Turn the sensor ON
  val = analogRead(pin);    // Read the analog value form sensor
  digitalWrite(power, LOW);   // Turn the sensor OFF
  return val;             // send current reading
}


void flow_A () {                                               // Interrupt function for 1 flow sensor

  flow_frequency_A++;
}
void flow_B () {                                               // Interrupt function for the other flow sensor

  flow_frequency_B++;
}

// This function calculates the volume of water that has passed the flow sensor and sends it to the Pi
void flowSendData () {

  currentTime = millis();
  // Every second, calculate and print millilitres/hour
  if (currentTime >= (cloopTime + 10))
  {
    unsigned long dt = currentTime - cloopTime;
    cloopTime = currentTime; // Updates cloopTime

    // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
    l_second_A = 1000.0 * (flow_frequency_A / 4380.0); // (Pulse frequency x 60 min) / 7.5Q = flowrate in mL/second
    volume_New_A += 1.34 * dt * l_second_A / 1000.0; //ml
    flow_frequency_A = 0; // Reset Counter

    l_second_B = 1000.0 * (flow_frequency_B / 4380.0); // (Pulse frequency x 60 min) / 7.5Q = flowrate in mL/second
    volume_New_B += 1.34 * dt * l_second_B / 1000.0; //ml
    flow_frequency_B = 0; // Reset Counter

    if (volume_New_A != volume_Old_A) {
      Serial.print(flowHeaders[0]);
      Serial.println(volume_New_A);
      volume_Old_A = volume_New_A;
    }
    if (volume_New_B != volume_Old_B) {
      Serial.print(flowHeaders[1]);
      Serial.println(volume_New_B);
      volume_Old_B = volume_New_B;
    }
  }
}
