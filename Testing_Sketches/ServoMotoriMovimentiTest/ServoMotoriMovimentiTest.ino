#include <Servo.h>

Servo ServoR;
Servo ServoL;

void Avanti() {
  //ServoR.write(); 
  //ServoL.write(0);
  // Impostazione posizione minima servo-motori
  ServoR.writeMicroseconds(1500); 
  ServoL.writeMicroseconds(1700);
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
  //ServoR.attach(12);
  ServoL.attach(13);

  ServoR.writeMicroseconds(1500); 
  ServoL.writeMicroseconds(1500);

}

void loop() {
  //Inserisci le funzioni da testare all'interno del for. Default -> nulla.
  for (int timer=1; timer <= 3; timer++) {
    Avanti();
  }
  
  //ServoR.detach();
  //ServoL.detach();
}
