
/*
  Communication Test for M8 Project

  Bas van der Steenhoven
  Stijn Brugman
*/


int pins[] = {A0, A1};
int lastRead = 0;
/*
    Pin A0 is the x-coordinate with the header 'X'
    Pin A1 is the y-coordinate with the header 'Y'
*/
char headers[] = {'X', 'Y'};

void setup () {

  Serial.begin(9600);

}


void loop() {
  for (int i = 0; i < 1; i++) {
    if (abs(analogRead(pins[i]) - lastRead) > 50) {
        Serial.print(headers[i]);
        Serial.println(analogRead(pins[i]));
        lastRead = analogRead(pins[i]);
      }
    }
}
