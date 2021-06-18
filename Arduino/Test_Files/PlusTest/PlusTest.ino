void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(11, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(11, HIGH);
  Serial.println("HIGH");
  delay(500);
  digitalWrite(11, LOW);
  Serial.println("LOW");
  delay(500);
}
