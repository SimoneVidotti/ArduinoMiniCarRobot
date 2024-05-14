#include <Servo.h>

Servo ServoR;
Servo ServoL;

void Avanti() {
  ServoR.writeMicroseconds(1300); 
  ServoL.writeMicroseconds(1700);
  delay(1000);
}

void Destra() {
  ServoR.writeMicroseconds(1700); 
  ServoL.writeMicroseconds(1700);
  delay(600);
}

void Sinistra() {
  ServoR.writeMicroseconds(1300); 
  ServoL.writeMicroseconds(1300);
  delay(600);
}

void LeggermenteDestra() {
  ServoR.writeMicroseconds(1550); 
  ServoL.writeMicroseconds(1550);
  delay(200);

  ServoR.writeMicroseconds(1300); 
  ServoL.writeMicroseconds(1700);
  delay(200);

  ServoR.writeMicroseconds(1450); 
  ServoL.writeMicroseconds(1450);
  delay(200);
}

void LeggermenteSinistra() {
  ServoR.writeMicroseconds(1450); 
  ServoL.writeMicroseconds(1450);
  delay(200);

  ServoR.writeMicroseconds(1300); 
  ServoL.writeMicroseconds(1700);
  delay(200);

  ServoR.writeMicroseconds(1550); 
  ServoL.writeMicroseconds(1550);
  delay(200);
}

void setup() {
  ServoR.attach(12);
  ServoL.attach(13);
}

void loop() {
  //Inserisci le funzioni da testare. Default -> nulla.
  
  ServoR.detach();
  ServoL.detach();
}
