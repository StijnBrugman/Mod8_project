#define yellow_LED 10
#define red_LED 9
#define green_LED 8


void setup() {

  Serial.begin(9600);
}


void loop() {

  if (Serial.available() > 0) {

    readDataTesting();
  }
}


void readDataTesting() {

  String recievedData = Serial.readStringUntil('\n');
  char recieveHeader = recievedData.charAt(0);
  recievedData.remove(0, 1);
  int data = recievedData.toInt();

  switch (recieveHeader) {
    case 'A':
      if (data == 1) {
        digitalWrite(yellow_LED, HIGH);
      } else {
        digitalWrite(yellow_LED, LOW);
      }
      break;
    case 'B':
      if (data == 1) {
        digitalWrite(red_LED, HIGH);
      } else {
        digitalWrite(red_LED, LOW);
      }      break;
    case 'C':
      if (data == 1) {
        digitalWrite(green_LED, HIGH);
      } else {
        digitalWrite(green_LED, LOW);
      }      break;
  }
}
