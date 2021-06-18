#define valvePin_6_In 6  // TEMP

#define ROT_ENC_CLK_D 2
#define ROT_ENC_DT_D 3
#define ROT_ENC_SW_D 4

int counter_D = 0;
int currentStateCLK_D;
int lastStateCLK_D;

unsigned long lastButtonPress = 0;

int buttonState = 0;
boolean pressed = false;

#define flowSensorPin_A 7

volatile float flow_frequency_A; // Measures flow sensor pulsesunsigned

float l_second_A; // Calculated litres/hour
unsigned long currentTime;
unsigned long cloopTime;

unsigned long volume_Old_A = 0;
unsigned long volume_New_A = 0;

char rotaryHeaders[] = {'A', 'B', 'C', 'D'};          // Headers for the rotary encoders and the button
char flowHeaders[] = {'J', 'K'};                      // Headers for the flow sensors


void setup() {
  // put your setup code here, to run once:

  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);

  pinMode(valvePin_6_In, OUTPUT);

  // Set encoder pins as inputs and calibrate the last state
  pinMode(ROT_ENC_CLK_D, INPUT);
  pinMode(ROT_ENC_DT_D, INPUT);
  pinMode(ROT_ENC_SW_D, INPUT_PULLUP);

  lastStateCLK_D = digitalRead(ROT_ENC_CLK_D);

  // Set the flow sensor pins to input and calibrate the timer
  pinMode(flowSensorPin_A, INPUT);
  sei(); // Enable interrupts

  digitalWrite(flowSensorPin_A, HIGH); // Optional Internal Pull-Up
  attachInterrupt(0, flow_A, RISING); // Setup Interrupt


  currentTime = millis();
  cloopTime = currentTime;


  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of CLK
  lastStateCLK_D = digitalRead(ROT_ENC_CLK_D);

}

void loop() {
  // put your main code here, to run repeatedly:
  encoderReaderDay();                                             // Run the rotary encoder for the day selector
  buttonDetection();                                              // Check if the button is pressed
  flowSendData();

  if (Serial.available() > 0) {                                   // If serial data is available for reading
    readData();                                                   // Execute the method to read the data
  }
  delay(1);
}

void readData() {                                                 // Read the data
  String recievedData = Serial.readStringUntil('\n');             // Save the string until the break
  char recieveHeader = recievedData.charAt(0);                    // Check the header
  recievedData.remove(0, 1);                                      // Remove the header
  int data = recievedData.toInt();                                // Transate the remaining string to an int

  switch (recieveHeader) {
    case 'L':
      if (data == 1) {
        digitalWrite(valvePin_6_In, HIGH);
      } else {
        digitalWrite(valvePin_6_In, LOW);
      }      break;
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

void flow_A () {                                               // Interrupt function

  flow_frequency_A++;
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
    if (volume_New_A != volume_Old_A) {
      Serial.print(flowHeaders[0]);
      Serial.println(volume_New_A);
      volume_Old_A = volume_New_A;
    }
  }
}
