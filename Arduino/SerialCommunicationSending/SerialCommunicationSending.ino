/*
  Communication for M8 Project

  Bas van der Steenhoven
  Stijn Brugman
  
*/
//----------------------------General_Communication----------------------------//
// Communcation headers
char header[] = {'A', 'B', 'C', 'D'};


//--------------------------------Water Valves---------------------------------//
// Water valve Pins
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



//--------------------------------Distance Sensor------------------------------//
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

unsigned long distanceTimer;


//--------------------------------Rotary_Encoder-------------------------------//
// Rotary Encoder Inputs
#define ROT_ENC_CLK 2
#define ROT_ENC_DT 3
#define ROT_ENC_SW 4

int counter = 0;
int currentStateCLK;
int lastStateCLK;
unsigned long lastButtonPress = 0;

int buttonState = 0;
boolean pressed = false;
//----------------------------------------------------------------------------//

void setup() {

  // Set encoder pins as inputs
  pinMode(ROT_ENC_CLK, INPUT);
  pinMode(ROT_ENC_DT, INPUT);
  pinMode(ROT_ENC_SW, INPUT_PULLUP);

  // Set distancesensor pins to input and output
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

  // Set the valve pins to input
//  pinMode(valvePin_1_Out, OUTPUT);
//  pinMode(valvePin_1_In, OUTPUT);
//  pinMode(valvePin_2_Out, OUTPUT);
//  pinMode(valvePin_2_In, OUTPUT);
//  pinMode(valvePin_3_Out, OUTPUT);
//  pinMode(valvePin_3_In, OUTPUT);
//  pinMode(valvePin_4_Out, OUTPUT);
//  pinMode(valvePin_4_In, OUTPUT);
//  pinMode(valvePin_5_Out, OUTPUT);
//  pinMode(valvePin_5_In, OUTPUT);
//  pinMode(valvePin_6_Out, OUTPUT);
//  pinMode(valvePin_6_In, OUTPUT);


  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(ROT_ENC_CLK);
}

void loop() {
  encoderReader();
  buttonDetection();

  if (millis() > distanceTimer + 333) {
    distanceRead();
    distanceTimer = millis();
    //Serial.print('Z');
    //Serial.println("ukkel");
  }

  if (Serial.available() > 0) {
    readData();
  }
  delay(1);
}

// Read the data
void readData() {                                              // Read the data
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
  int btnState = digitalRead(ROT_ENC_SW);

  //If we detect LOW signal, button is pressed
  if (btnState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress > 50 && !pressed) {
      buttonState++;
      Serial.print(header[3]);
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
void encoderReader() {
  // Read the current state of CLK
  currentStateCLK = digitalRead(ROT_ENC_CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(ROT_ENC_DT) != currentStateCLK) {
      counter ++;
    } else { // Encoder is rotating CW so increment
      counter --;
    }
    Serial.print(header[0]);
    Serial.println(counter);
  }
  // Remember last CLK state
  lastStateCLK = currentStateCLK;
}


// Reads the distance sensors and outputs their data to the Pi
void distanceRead() {

  int tempDistance = distance(echoPin_A, trigPin_A);  // Calculate the distance from the distancesensor
  if (tempDistance != oldDistanceA) {                 // Check if that distance has changed. If it has
    Serial.print("E");                                // Print the header
    Serial.println(tempDistance);                     // And the distance
  }
  oldDistanceA = tempDistance;                        // Save the new distance

  tempDistance = distance(echoPin_B, trigPin_B);
  if (tempDistance != oldDistanceB) {
    Serial.print("F");
    Serial.println(tempDistance);
  }
  oldDistanceB = tempDistance;
}

// Calculates the distance for the distance sensors
int distance(int echoPin, int trigPin) {
  int duration, distance;
  digitalWrite (trigPin, HIGH);
  delay(10);
  digitalWrite (trigPin, LOW);
  duration = pulseIn (echoPin, HIGH);
  distance =  (duration / 2) / 2.91;
  return distance;
}
