#define valvePin_6_In 6  // TEMP

#define ROT_ENC_CLK_D 2
#define ROT_ENC_DT_D 3
#define ROT_ENC_SW_D 4

bool flow = false;

int counter_D = 0;
int currentStateCLK_D;
int lastStateCLK_D;

unsigned long lastButtonPress = 0;

int buttonState = 0;
boolean pressed = false;

char rotaryHeaders[] = {'A', 'B', 'C', 'D'};          // Headers for the rotary encoders and the button
char flowHeaders[] = {'J', 'K'};                      // Headers for the flow sensors

unsigned long volume_Old_A = 0;

unsigned long loopTimer;
unsigned long loopTimer2;

void setup()
{
  pinMode(valvePin_6_In, OUTPUT);
  digitalWrite(valvePin_6_In, LOW);

  // Set encoder pins as inputs and calibrate the last state
  pinMode(ROT_ENC_CLK_D, INPUT);
  pinMode(ROT_ENC_DT_D, INPUT);
  pinMode(ROT_ENC_SW_D, INPUT_PULLUP);

  lastStateCLK_D = digitalRead(ROT_ENC_CLK_D);

  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of CLK
  lastStateCLK_D = digitalRead(ROT_ENC_CLK_D);

  loopTimer = millis();
  loopTimer2 = millis();
}

void loop ()
{
  encoderReaderDay();                                             // Run the rotary encoder for the day selector
  buttonDetection();                                              // Check if the button is pressed
  flowSendData();

  if (Serial.available() > 0) {                                   // If serial data is available for reading
    String recievedData = Serial.readStringUntil('\n');             // Save the string until the break
    readData(recievedData);                                                   // Execute the method to read the data
  }
  delay(1);
}

void readData(String passedData) {                                                 // Read the data
  String recievedData = passedData;             // Save the string until the break
  char recieveHeader = recievedData.charAt(0);                    // Check the header
  recievedData.remove(0, 1);                                      // Remove the header
  int data = recievedData.toInt();                                // Transate the remaining string to an int
  //Serial.println("Header Onbekend");
  switch (recieveHeader) {
    case 'L':
      Serial.print('Z');
      Serial.println(data);
      if (data == 1) {
        digitalWrite(valvePin_6_In, HIGH);
        digitalWrite(8, LOW);
        flow = true;
      }
      if (data == 0) {
        digitalWrite(valvePin_6_In, LOW);
        digitalWrite(8, HIGH);
        flow = false;
        Serial.print('Z');
        Serial.println("wut");
      }
      break;
  }
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


void flowSendData () {

  if (flow == true) {
    if (loopTimer2 + 10 < millis()) {
      volume_Old_A++;
      loopTimer2 = millis();
    }
    if (loopTimer + 200 < millis()) {
      Serial.print('J');
      Serial.println(volume_Old_A);
      loopTimer = millis();
    }
  }
}
