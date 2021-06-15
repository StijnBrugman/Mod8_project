/*
  Communication for M8 Project

  Bas van der Steenhoven
  Stijn Brugman
*/
//----------------------------General_Communication----------------------------//
// Communcation headers
char header[] = {'A', 'B', 'C', 'D'};

//TEST
int dataRecieved = 3;
int dataValues[] = {0, 0, 0};
int currentValue;

#define yellow_LED_Pin 10
int yellow_LED = 0;
#define red_LED_Pin 9
int red_LED = 0;
#define green_LED_Pin 8
int green_LED = 0;


//-----------------------------------------------------------------------------//


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

  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(ROT_ENC_CLK);
}

void loop() {
  encoderReader();
  buttonDetection();

  ledReadTest();

  delay(1);
}


void ledReadTest() {                                              // Read the data

  // Find the original code here:
  //https://gist.github.com/atduskgreg/1349176

  int incomingValue = Serial.read();                           // Read the incoming data

  dataValues[currentValue] = incomingValue;                    // Assign that spot in the array with the value from the data

  currentValue++;                                              // Add to the current value
  if (currentValue > dataRecieved - 1) {                       // If the counter is larger than the amount of variables being send
    currentValue = 0;                                          // Set the counter to 0
  }

  yellow_LED = dataValues[0];
  red_LED = dataValues[1];
  green_LED = dataValues[2];

  if (yellow_LED) {
    digitalWrite(yellow_LED_Pin, HIGH);
  } else if (!yellow_LED) {
    digitalWrite(yellow_LED_Pin, LOW);
  }

  if (red_LED) {
    digitalWrite(red_LED_Pin, HIGH);
  } else if (!red_LED) {
    digitalWrite(red_LED_Pin, LOW);
  }

  if (green_LED) {
    digitalWrite(green_LED_Pin, HIGH);
  } else if (!green_LED) {
    digitalWrite(green_LED_Pin, LOW);
  }

}


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
