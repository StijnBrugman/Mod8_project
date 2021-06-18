/*
  The Arduino file for the Hybrid Worlds Project of Creative Technolgy.

  The Arduino collects data from flow sensors, water level sensors, distance sensors, and from rotary encoders.
  It sends this data to a Raspberry Pi.
  The Raspberry Pi sends commands to the Arduino.
  The Arduino controls water valves that work together with pumps to fill several tubes with water.

  For a complete overview of the project and all code, you can check our repository on GitHub.
  https://github.com/StijnBrugman/Mod8_project

  Bas van der Steenhoven
  Stijn Brugman
  David Lammers

  2021

*/
//----------------------------General_Communication----------------------------//
// Communcation headers
char rotaryHeaders[] = {'A', 'B', 'C', 'D'};          // Headers for the rotary encoders and the button
char distanceHeaders[5] = {'E', 'F', 'G', 'H', 'I'};  // Headers for the distance sensors
char flowHeaders[] = {'J', 'K'};                      // Headers for the flow sensors


//--------------------------------Water_Valves---------------------------------//
// Water Valve Pins
//#define valvePin_1_Out 22
//#define valvePin_1_In 23
//#define valvePin_2_Out 24
//#define valvePin_2_In 25
//#define valvePin_3_Out 26
//#define valvePin_3_In 27
//#define valvePin_4_Out 28
//#define valvePin_4_In 29
//#define valvePin_5_Out 30
//#define valvePin_5_In 31
//#define valvePin_6_Out 32
//#define valvePin_6_In 33

#define valvePin_1_Out 22 // TEMP
#define valvePin_1_In 23  // TEMP
#define valvePin_2_Out 24 // TEMP
#define valvePin_2_In 25  // TEMP


//--------------------------------Distance_Sensor------------------------------//
// Distance Sensor Pins
//#define trigPin_A 44
//#define echoPin_A 45
//#define trigPin_B 46
//#define echoPin_B 47
//#define trigPin_C 48
//#define echoPin_C 49
//#define trigPin_D 50
//#define echoPin_D 51
//#define trigPin_E 52
//#define echoPin_E 53

#define trigPin_A 5 // TEMP
#define echoPin_A 6 // TEMP
#define trigPin_B 7 // TEMP
#define echoPin_B 8 // TEMP

int oldDistanceA;
int oldDistanceB;

//int newDistance[5];
//int oldDistance[5];

unsigned long distanceTimer;


//--------------------------------Rotary_Encoder-------------------------------//
// Rotary Encoder Pins
#define ROT_ENC_CLK_D 2
#define ROT_ENC_DT_D 3
#define ROT_ENC_SW_D 4

int counter_D = 0;
int currentStateCLK_D;
int lastStateCLK_D;

#define ROT_ENC_CLK_M 14
#define ROT_ENC_DT_M 15
#define ROT_ENC_SW_M 16

int counter_M = 0;
int currentStateCLK_M;
int lastStateCLK_M;

#define ROT_ENC_CLK_Y 19
#define ROT_ENC_DT_Y 20
#define ROT_ENC_SW_Y 21

int counter_Y = 0;
int currentStateCLK_Y;
int lastStateCLK_Y;


unsigned long lastButtonPress = 0;

int buttonState = 0;
boolean pressed = false;


//--------------------------------Water_Level_Sensors--------------------------//
// Water Level Sensor Pins
//#define sensorPin_A A0
//#define sensorPin_B A1
//#define sensorPin_C A2
//#define sensorPin_D A3
//#define sensorPin_E A4

// Water Level Sensor Power Pins
//#define sensorPowerPin_A 8
//#define sensorPowerPin_B 9
//#define sensorPowerPin_C 10
//#define sensorPowerPin_D 11
//#define sensorPowerPin_E 12


//--------------------------------Flow_Sensors---------------------------------//
#define flowSensorPin_A 6
#define flowSensorPin_B 7

volatile float flow_frequency_A; // Measures flow sensor pulsesunsigned
volatile float flow_frequency_B; // Measures flow sensor pulsesunsigned

float l_second_A; // Calculated litres/hour
float l_second_B; // Calculated litres/hour
unsigned long currentTime;
unsigned long cloopTime;

unsigned long volume_Old_A = 0;
unsigned long volume_New_A = 0;
unsigned long volume_Old_B = 0;
unsigned long volume_New_B = 0;

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
  //  pinMode(trigPin_C, OUTPUT);
  //  pinMode(echoPin_C, INPUT);
  //  pinMode(trigPin_D, OUTPUT);
  //  pinMode(echoPin_D, INPUT);
  //  pinMode(trigPin_E, OUTPUT);
  //  pinMode(echoPin_E, INPUT);

  // Set the valve pins to output
  pinMode(valvePin_1_Out, OUTPUT);
  pinMode(valvePin_1_In, OUTPUT);
  pinMode(valvePin_2_Out, OUTPUT);
  pinMode(valvePin_2_In, OUTPUT);
  //  pinMode(valvePin_3_Out, OUTPUT);
  //  pinMode(valvePin_3_In, OUTPUT);
  //  pinMode(valvePin_4_Out, OUTPUT);
  //  pinMode(valvePin_4_In, OUTPUT);
  //  pinMode(valvePin_5_Out, OUTPUT);
  //  pinMode(valvePin_5_In, OUTPUT);
  //  pinMode(valvePin_6_Out, OUTPUT);
  //  pinMode(valvePin_6_In, OUTPUT);

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

  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of CLK
  lastStateCLK_D = digitalRead(ROT_ENC_CLK_D);
  lastStateCLK_M = digitalRead(ROT_ENC_CLK_M);
  lastStateCLK_Y = digitalRead(ROT_ENC_CLK_Y);

}

void loop() {
  encoderReaderDay();                                             // Run the rotary encoder for the day selector
  encoderReaderMonth();                                           // Run the rotary encoder for the month selector
  encoderReaderYear();                                            // Run the rotary encoder for the year selector
  buttonDetection();                                              // Check if the button is pressed
  flowSendData();

  if (millis() > distanceTimer + 333) {                           // 1/3th of a second after the timer
    distanceRead();                                               // Read the distance
    distanceTimer = millis();                                     // Reset the timer
    //Serial.print('Z');
    //Serial.println("Sukkel");
  }

  if (Serial.available() > 0) {                                   // If serial data is available for reading
    readData();                                                   // Execute the method to read the data
  }
  delay(1);                                                       // Wait 1 millisecond
}

// Read the data
void readData() {                                                 // Read the data
  String recievedData = Serial.readStringUntil('\n');             // Save the string until the break
  char recieveHeader = recievedData.charAt(0);                    // Check the header
  recievedData.remove(0, 1);                                      // Remove the header
  int data = recievedData.toInt();                                // Transate the remaining string to an int

  //  switch (recieveHeader) {                                      // Go into the switch with the header
  //    case 'A':                                                   // If the header matches the case
  //      if (data == 1) {                                          // And the int is 1
  //        digitalWrite(valvePin_1_Out, HIGH);                     // Write HIGH to the valve
  //      } else {                                                  // If other data was send
  //        digitalWrite(valvePin_1_Out, LOW);                      // Else write LOW
  //      }
  //      break;                                                    // Break out of the switch
  //    case 'B':
  //      if (data == 1) {
  //        digitalWrite(valvePin_1_In, HIGH);
  //      } else {
  //        digitalWrite(valvePin_1_In, LOW);
  //      }      break;
  //    case 'C':
  //      if (data == 1) {
  //        digitalWrite(valvePin_2_Out, HIGH);
  //      } else {
  //        digitalWrite(valvePin_2_Out, LOW);
  //      }      break;
  //    case 'D':
  //      if (data == 1) {
  //        digitalWrite(valvePin_2_In, HIGH);
  //      } else {
  //        digitalWrite(valvePin_2_In, LOW);
  //      }
  //      break;
  //    case 'E':
  //      if (data == 1) {
  //        digitalWrite(valvePin_3_Out, HIGH);
  //      } else {
  //        digitalWrite(valvePin_3_Out, LOW);
  //      }      break;
  //    case 'F':
  //      if (data == 1) {
  //        digitalWrite(valvePin_3_In, HIGH);
  //      } else {
  //        digitalWrite(valvePin_3_In, LOW);
  //      }      break;
  //    case 'G':
  //      if (data == 1) {
  //        digitalWrite(valvePin_4_Out, HIGH);
  //      } else {
  //        digitalWrite(valvePin_4_Out, LOW);
  //      }
  //      break;
  //    case 'H':
  //      if (data == 1) {
  //        digitalWrite(valvePin_4_In, HIGH);
  //      } else {
  //        digitalWrite(valvePin_4_In, LOW);
  //      }      break;
  //    case 'I':
  //      if (data == 1) {
  //        digitalWrite(valvePin_5_Out, HIGH);
  //      } else {
  //        digitalWrite(valvePin_5_Out, LOW);
  //      }      break;
  //    case 'J':
  //      if (data == 1) {
  //        digitalWrite(valvePin_5_In, HIGH);
  //      } else {
  //        digitalWrite(valvePin_5_In, LOW);
  //      }
  //      break;
  //    case 'K':
  //      if (data == 1) {
  //        digitalWrite(valvePin_6_Out, HIGH);
  //      } else {
  //        digitalWrite(valvePin_6_Out, LOW);
  //      }      break;
  //    case 'L':
  //      if (data == 1) {
  //        digitalWrite(valvePin_6_In, HIGH);
  //      } else {
  //        digitalWrite(valvePin_6_In, LOW);
  //      }      break;
  //  }

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

  int tempDistance = distance(echoPin_A, trigPin_A);  // Calculate the distance from the distancesensor
  if (tempDistance != oldDistanceA) {                 // Check if that distance has changed. If it has
    Serial.print(distanceHeaders[0]);                 // Print the header
    Serial.println(tempDistance);                     // And the distance
  }
  oldDistanceA = tempDistance;                        // Save the new distance

  tempDistance = distance(echoPin_B, trigPin_B);
  if (tempDistance != oldDistanceB) {
    Serial.print(distanceHeaders[1]);
    Serial.println(tempDistance);
  }
  oldDistanceB = tempDistance;

  // For loop for use with 5 sensors
  //  int j;                                                     // Declare int 'j'
  //  for (int i = 0; i < 10; i += 2) {                          // For all 5 sensors
  //  // It goes from 0 to 10 and increases by 2. This makes sure that i + pinnumber is correct.
  //    newDistance[j] = distance(i + trigPinA, i + echoPinA);   // newDistance is the measured distance from the sensor
  //
  //    if (newDistance[j] != oldDistance[j]) {                  // If the new distance is different
  //      Serial.print(distanceHeaders[i]);                      // Print the according header
  //      Serial.println(newDistance[j]);                        // And the measured value
  //      newDistance[j] = oldDistance[j];                       // Save the measured value
  //    }
  //    j++;                                                     // Increment J
  //  }
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


void flow_A () {                                               // Interrupt function

  flow_frequency_A++;
}
void flow_B () {                                               // Interrupt function

  flow_frequency_B++;
}

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
