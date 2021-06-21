#define greenLED 11
#define redLED 10
#define blueLED 9

char LEDHeaders[5] = {'O', 'P', 'Q', 'R', 'S'};

String recievedColourArray;

String redLEDColourString;
String greenLEDColourString;
String blueLEDColourString;
int redLEDColour;
int greenLEDColour;
int blueLEDColour;

int ind1, ind2, ind3;

char recievedCityHeader = 'M';
char recievedDateHeader = 'N';

String recievedCity = "";
String recievedDate = "";

char rotaryHeaders[4] = {'A', 'B', 'C', 'D'};                                   // Headers for the rotary encoders and the button

// Rotary Encoder Pins
#define ROT_ENC_CLK_D 2
#define ROT_ENC_DT_D 3
#define ROT_ENC_SW_D 4

int counter_D = 0;
int currentStateCLK_D;
int lastStateCLK_D;

unsigned long lastButtonPress = 0;

int buttonState = 0;
boolean pressed = false;

void setup() {
  // put your setup code here, to run once:

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  // Set encoder pins as inputs and calibrate the last state
  pinMode(ROT_ENC_CLK_D, INPUT);
  pinMode(ROT_ENC_DT_D, INPUT);
  pinMode(ROT_ENC_SW_D, INPUT_PULLUP);

  lastStateCLK_D = digitalRead(ROT_ENC_CLK_D);

  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0) {
    readData();
  }
  rotary();
  button();
}

void readData() {
  String recievedData = Serial.readStringUntil('\n');             // Save the string until the break

  char recieveHeader = recievedData.charAt(0);                    // Check the header
  recievedData.remove(0, 1);                                      // Remove the header

  //  if (recieveHeader == 'M') {
  //    recievedCity = recievedData;
  //    lcd.setCursor(0, 0);
  //    lcd.print("                ");
  //    lcd.setCursor(0, 0);
  //    lcd.print(recievedCity);
  //  } else if (recieveHeader == 'N') {
  //    recievedDate = recievedData;
  //    lcd.setCursor(0, 1);
  //    lcd.print(recievedDate);
  //  } else if (recieveHeader == 'O') {
  if (recieveHeader == 'O') {
    recievedColourArray = recievedData;

    ind1 = recievedColourArray.indexOf(',');  //finds location of first ,
    redLEDColourString = recievedColourArray.substring(0, ind1);   //captures first data String
    ind2 = recievedColourArray.indexOf(',', ind1 + 1 ); //finds location of second ,
    greenLEDColourString = recievedColourArray.substring(ind1 + 1, ind2 + 1); //captures second data String
    ind3 = recievedColourArray.indexOf(',', ind2 + 1 );
    blueLEDColourString = recievedColourArray.substring(ind2 + 1); //captures remain part of data after last ,

    redLEDColour = redLEDColourString.toInt();

    analogWrite(redLED, redLEDColour);
    analogWrite(greenLED, greenLEDColour);
    analogWrite(blueLED, blueLEDColour);

  } else if (recieveHeader == 'P') {
  } else if (recieveHeader == 'Q') {
  } else if (recieveHeader == 'R') {
  } else if (recieveHeader == 'S') {
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
