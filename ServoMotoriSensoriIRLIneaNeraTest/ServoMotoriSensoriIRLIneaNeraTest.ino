#include <Servo.h>

#define SensoreR A2
#define SensoreC A0
#define SensoreL A1

Servo ServoR;
Servo ServoL;

int DefaultR = 1491;
int DefaultL = 1509;

int Soglia1 = 1020;
int Soglia2 = 1000;

int LetturaR, LetturaC, LetturaL;

int Q = 0;

void Lettura() {
  LetturaR = analogRead(SensoreR);
  LetturaC = analogRead(SensoreC);
  LetturaL = analogRead(SensoreL);
}

void Avanti() {
  ServoR.writeMicroseconds(1470);
  ServoL.writeMicroseconds(1530);
}

void LeggermenteDestra() {
  ServoR.writeMicroseconds(1500);
  ServoL.writeMicroseconds(1530);
  delay(500);
  Q = 1;
}

void LeggermenteSinistra() {
  ServoR.writeMicroseconds(1470);
  ServoL.writeMicroseconds(1500);
  delay(500);
  Q = 2;
}

void Stop() {
  ServoR.writeMicroseconds(1500);
  ServoL.writeMicroseconds(1500);
  ServoR.detach();
  ServoL.detach();
}

void Ctrl_Q() {

}

void Codifica() {
  //Casi Definiti

  while(LetturaL >= Soglia1 && LetturaC >= Soglia2 && LetturaR < Soglia1) {
    LeggermenteSinistra();
    Lettura();
  }
    
  while(LetturaL >= Soglia1 && LetturaC < Soglia2 && LetturaR < Soglia1) {
    LeggermenteSinistra();
    Lettura();
  }

  while(LetturaL < Soglia1 && LetturaC >= Soglia2 && LetturaR >= Soglia1) {
    LeggermenteDestra();
    Lettura();
  }

  while(LetturaL < Soglia1 && LetturaC >= Soglia2 && LetturaR < Soglia1) {
    Avanti();
    Lettura();
  }
 
  while(LetturaL < Soglia1 && LetturaC < Soglia2 && LetturaR >= Soglia1) {
    LeggermenteDestra();
    Lettura();
  }

  if (LetturaL >= Soglia1 && LetturaC >= Soglia2 && LetturaR >= Soglia1) {
    Stop();
  } 
  
  if (LetturaL < Soglia1 && LetturaC < Soglia2 && LetturaR < Soglia1) {
    if (Q == 0) {
      ServoR.writeMicroseconds(1500);
      ServoL.writeMicroseconds(1500);
    } 
  } 

  //Default
  ServoR.writeMicroseconds(DefaultR);
  ServoL.writeMicroseconds(DefaultL);
}

void setup() {
  ServoR.attach(12);
  ServoL.attach(13);
  
} 

void loop() {
  Lettura();
  Codifica();
}
