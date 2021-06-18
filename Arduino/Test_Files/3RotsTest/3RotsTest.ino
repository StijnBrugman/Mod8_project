char rotaryHeaders[] = {'A', 'B', 'C', 'D'};          // Headers for the rotary encoders and the button

#define ROT_ENC_CLK_D 2
#define ROT_ENC_DT_D 3
#define ROT_ENC_SW_D 4

int counter_D = 0;
int currentStateCLK_D;
int lastStateCLK_D;

#define ROT_ENC_CLK_M 5
#define ROT_ENC_DT_M 6
#define ROT_ENC_SW_M 7

int counter_M = 0;
int currentStateCLK_M;
int lastStateCLK_M;

#define ROT_ENC_CLK_Y 8
#define ROT_ENC_DT_Y 9
#define ROT_ENC_SW_Y 10

int counter_Y = 0;
int currentStateCLK_Y;
int lastStateCLK_Y;

unsigned long lastButtonPress = 0;

int buttonState = 0;
boolean pressed = false;



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
  buttonDetection();
}


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
    
    //Serial.println("Test D: " + counter_D);

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

  //Serial.println("Test M: " + counter_M);

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

  //Serial.println("Test Y: " + counter_Y);

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
