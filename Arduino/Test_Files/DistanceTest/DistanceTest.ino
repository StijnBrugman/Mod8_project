#define trigPin_A 2
#define echoPin_A 3
#define trigPin_B 4
#define echoPin_B 5
#define trigPin_C 6
#define echoPin_C 7
#define trigPin_D 8
#define echoPin_D 9
#define trigPin_E 10
#define echoPin_E 11

int newDistance[5] = {0, 0, 0, 0, 0};
int oldDistance[5] = {0, 0, 0, 0, 0};

int oldDistanceA;
int oldDistanceB;

int newDistanceA;
int newDistanceB;

unsigned long distanceTimer;

char distanceHeaders[5] = {'E', 'F', 'G', 'H', 'I'};

void setup() {
  Serial.begin (9600);
  pinMode(trigPin_A, OUTPUT);
  pinMode(echoPin_A, INPUT);
  pinMode(trigPin_B, OUTPUT);
  pinMode(echoPin_B, INPUT);
  pinMode(trigPin_C, OUTPUT);
  pinMode(echoPin_C, INPUT);
  pinMode(trigPin_D, OUTPUT);
  pinMode(echoPin_D, INPUT);
  pinMode(trigPin_E, OUTPUT);
  pinMode(echoPin_E, INPUT);
}

void loop() {

  //if (millis() > distanceTimer + 333) {
  distanceRead();
  //  distanceTimer = millis();
  //}
}
void distanceRead() {
  int j;
  for (int i = 0; i < 10; i += 2) {

    newDistance[j] = distance(i + trigPin_A, i + echoPin_A);

    if (newDistance[j] != oldDistance[j]) {
      Serial.print(distanceHeaders[j]);
      Serial.println(newDistance[j]);
    }
    newDistance[j] = oldDistance[j];
    j++;

    //  newDistanceA = distance(trigPin_A, echoPin_A);
    //
    //  Serial.print('E');
    //  Serial.println(newDistanceA);
    //
    //  newDistanceB = distance(trigPin_B, echoPin_B);
    //
    ////  Serial.print('E');
    ////  Serial.println(newDistanceA);
    //  Serial.print('F');
    //  Serial.println(newDistanceB);

    //  }
  }
}

int distance(int trigPin, int echoPin) {
  int duration, distance;
  digitalWrite (trigPin, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPin, LOW);
  duration = pulseIn (echoPin, HIGH);
  distance =  (duration / 2) / 29.1;
  return distance;
}
