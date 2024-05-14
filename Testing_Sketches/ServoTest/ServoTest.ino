#include <Servo.h>

Servo ServoX;

void testA() {
  for(int i=1000; i <= 2000; i+=100) {
    ServoX.writeMicroseconds(i);
    Serial.println(i);
    delay(3000);
  }
}

void testB() {
  //Calibrazione, in questo punto la ruota dovrebbe essere completamente ferma.
  ServoX.writeMicroseconds(1500);
  delay(3000);
}

void testC() {
  ServoX.writeMicroseconds(1700);
  delay(3000);
  ServoX.writeMicroseconds(1500);
  delay(3000);
  ServoX.writeMicroseconds(1300);
  delay(3000);
}

void setup() {
  ServoX.attach(8);
  ServoX.writeMicroseconds(1500);
  Serial.begin(9600);
}

void loop() {
  testA();
}
