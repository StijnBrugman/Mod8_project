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
//#define trigPinA 44
//#define echoPinA 45
//#define trigPinB 46
//#define echoPinB 47
//#define trigPinC 48
//#define echoPinC 49
//#define trigPinD 50
//#define echoPinD 51
//#define trigPinE 52
//#define echoPinE 53

#define trigPinA 5 // TEMP
#define echoPinA 6 // TEMP
#define trigPinB 7 // TEMP
#define echoPinB 8 // TEMP

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
  pinMode(trigPinA, OUTPUT);
  pinMode(echoPinA, INPUT);
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);

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
    ledReadTest();
  }
  delay(1);
}

// Communication Test
void ledReadTest() {                                              // Read the data
  String recievedData = Serial.readStringUntil('\n');
  Serial.print("E");
  Serial.println(recievedData);
  char recieveHeader = recievedData.charAt(0);
  recievedData.remove(0, 1);
  int data = recievedData.toInt();

//  switch (recieveHeader) {
//    case 'A':
//      if (data == 1) {
//        digitalWrite(valvePin_1_Out, HIGH);
//      } else {
//        digitalWrite(valvePin_1_Out, LOW);
//      }
//      break;
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

  int tempDistance = distance(echoPinA, trigPinA);
  if (tempDistance != oldDistanceA) {
    Serial.print("E");
    Serial.println(tempDistance);
  }
  oldDistanceA = tempDistance;

  tempDistance = distance(echoPinB, trigPinB);
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
  delayMicroseconds(10);
  digitalWrite (trigPin, LOW);
  duration = pulseIn (echoPin, HIGH);
  distance =  (duration / 2) / 29.1;
  return distance;
}
