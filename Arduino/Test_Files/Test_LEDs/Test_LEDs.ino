#define GREEN_LED 9;
#define RED_LED 6;
#define BLUE_LED 5;

int greenBrightness = 0;
int redBrightness = 0;
int blueBrightness = 0;


void setup() {
  // put your setup code here, to run once:

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < 256; i++) {
    analogWrite(GREEN_LED, greenBrightness);
    greenBrightness += 1;
    delay(10);
  }

  for (int i = 0; i < 256; i++) {
    analogWrite(RED_LED, redBrightness);
    redBrightness += 1;
    delay(10);
  }

  for (int i = 0; i < 256; i++) {
    analogWrite(BLUE_LED, blueBrightness);
    blueBrightness += 1;
    delay(10);
  }

  for (int i = 255; i > 0; i--) {
    analogWrite(GREEN_LED, greenBrightness);
    greenBrightness += 1;
    delay(10);
  }

  for (int i = 255; i > 0; i--) {
    analogWrite(RED_LED, redBrightness);
    redBrightness += 1;
    delay(10);
  }

  for (int i = 255; i > 0; i--) {
    analogWrite(BLUE_LED, blueBrightness);
    blueBrightness += 1;
    delay(10);
  }
}
