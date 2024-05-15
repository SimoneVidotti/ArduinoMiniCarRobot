#define sensorPin A0

int value;

int Soglia1 = 1020;
int Soglia2 = 1000;

void Test1() {
  if (value > Soglia) {
    Serial.println("Nero");
  } else if (value < Soglia) {
    Serial.println("Bianco");
  }
}

void Test2() {
  Serial.println(value);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  value = analogRead(sensorPin);

  Test2();

  delay(100);
}

