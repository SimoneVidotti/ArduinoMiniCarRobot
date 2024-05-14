#include <Servo.h>

Servo ServoR;
Servo ServoL;

void Avanti() {
  // Impostazione posizione minima servo-motori
  ServoR.writeMicroseconds(1100); 
  ServoL.writeMicroseconds(1100);
  delay(1000); // Attendi 1 secondo
}

void Destra() {
  // Impostazione posizione minima servo-motori
  ServoR.writeMicroseconds(1100); 
  ServoL.writeMicroseconds(1100);
  delay(1000); // Attendi 1 secondo
}

void Sinistra() {
  // Impostazione posizione minima servo-motori
  ServoR.writeMicroseconds(1100); 
  ServoL.writeMicroseconds(1100);
  delay(1000); // Attendi 1 secondo
}

void LeggermenteDestra() {
  // Impostazione posizione minima servo-motori
  ServoR.writeMicroseconds(1100); 
  ServoL.writeMicroseconds(1100);
  delay(1000); // Attendi 1 secondo
}

void LeggermenteSinistra() {
  // Impostazione posizione minima servo-motori
  ServoR.writeMicroseconds(1100); 
  ServoL.writeMicroseconds(1100);
  delay(1000); // Attendi 1 secondo
}

void setup() {
  ServoR.attach(12);
  ServoL.attach(13);

  // Imposto i servo-motori al centro
  ServoR.writeMicroseconds(1500);
  ServoR.writeMicroseconds(1500);

}

void loop() {
  //Inserisci le funzioni da testare all'interno del for. Default -> nulla.
  for (int timer=0; timer <= 10; timer++) {

    delay(1000);
  }
  
  ServoR.detach();
  ServoL.detach();
}