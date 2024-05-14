#include <Servo.h>

Servo ServoR;
Servo ServoL;

#define echoPin 3 // pin D2 Arduino Echo dell'HC-SR04
#define trigPin 2 // pin D3 Arduino Trig dell'HC-SR04

long t; // tempo impiegato segnale ultrasuoni
int d;  // distanza rilevata
bool Superamento = false;

void Ctrl_Ostacolo() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // Genera un impulso ultrasonico
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  t = pulseIn(echoPin, HIGH); // tempo di ritorno del segnale
  d = t * 0.0344 / 2; //  distanza in cm

  if (d <= 10 || d <= 3 || d <= 5 || d <= 8) {
    Superamento = true;
  } else {
    Superamento = false;
  }
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  ServoR.attach(12);
  ServoL.attach(13);
}

void loop() {
  ServoR.writeMicroseconds(1300); 
  ServoL.writeMicroseconds(1800);

  Ctrl_Ostacolo();

  while (Superamento) {
    ServoR.writeMicroseconds(1700); 
    ServoL.writeMicroseconds(1300);
    delay(1100);

    ServoR.writeMicroseconds(1300); 
   ServoL.writeMicroseconds(1300);
   delay(600);

    Ctrl_Ostacolo();
  }

  delay(100);
}