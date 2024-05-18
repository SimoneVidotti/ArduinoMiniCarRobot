// Vidotti Simone, Zhou Luigi 4 TEL A Progetto LineFollower, Robottino Arduino
#include <IRremote.hpp> // Libreria per telecomando IR
#include <Servo.h> // Libreria per gestire i servo-motori

// pin Sensori
#define SensoreR A2
#define SensoreC A0
#define SensoreL A1

// pin Ultrasuoni
#define echoPin 3 // pin D2 Arduino Echo dell'HC-SR04
#define trigPin 2 // pin D3 Arduino Trig dell'HC-SR04

// pin ricevitore
#define IR_RECEIVE_PIN 12

// pin Servo-motori
Servo ServoR;
Servo ServoL;

// Velocita per fixing line
int DefaultR = 1460;
int DefaultL = 1540;

// Soglia sensori
int Soglia = 1000;

// Valori di lettura
int LetturaR, LetturaC, LetturaL;

// variabili di distanza e tempo per Ultrasuoni
long t; // tempo impiegato segnale ultrasuoni
int d;  // distanza rilevata

// Stato iniziale
bool start = false; // Controllo quando partire

// Controllo Ostacolo, guida manuale.
bool Superamento = false; // Ctrl superamento

// Controllo partenza
Ctrl_Start() {
    if (IrReceiver.decode()) {
        uint16_t command = IrReceiver.decodedIRData.command;

        if (command == 69) {
            start = true;
        }

    }

    IrReceiver.resume();
}

// --- Seguire Linea nera ---
void Lettura() { //Lettura sensori IR
    LetturaR = analogRead(SensoreR);
    LetturaC = analogRead(SensoreC);
    LetturaL = analogRead(SensoreL);
}

void Avanti() { // Andare avanti
    ServoR.writeMicroseconds(1450);
    ServoL.writeMicroseconds(1550);
}

void LeggermenteDestra() { // Svoltare a destra
    ServoR.writeMicroseconds(1500);
    ServoL.writeMicroseconds(1530);
    delay(500);
}

void LeggermenteSinistra() { // Svoltare a sinistra
    ServoR.writeMicroseconds(1470);
    ServoL.writeMicroseconds(1500);
    delay(500);
}

void Fermo() { // Stato di quiete, il robot sta fermo
    ServoR.writeMicroseconds(1500);
    ServoL.writeMicroseconds(1500);
}

void Stop() { // Stop quando arriva al traguardo
    ServoR.writeMicroseconds(1500);
    ServoL.writeMicroseconds(1500);
    ServoR.detach();
    ServoL.detach();
    start = false;
}

void Traguardo() {
    // Allarme per circa 8s e dopo led accesso quando è arrivato al Traguardo
    for (int i=0; i < 5; i++) {
        tone(6, 3000); // frequenza
        delay(200);        //
        digitalWrite(7, HIGH);
        delay(200);        //

        noTone(6);     // buzzer off
        delay(100);
        digitalWrite(7, LOW);
    }

    while (start == false) {
        noTone(6);     // buzzer off

        digitalWrite(7, HIGH);
    }
}

// --- Codifica lettura soglie --- distinguere nero e bianco
void Codifica() {
    //Casi Definiti
    while(LetturaL >= Soglia && LetturaC >= Soglia && LetturaR < Soglia) {
        LeggermenteSinistra();
        Lettura();
    }

    while(LetturaL >= Soglia && LetturaC < Soglia && LetturaR < Soglia) {
        LeggermenteSinistra();
        Lettura();
    }

    while(LetturaL < Soglia && LetturaC >= Soglia && LetturaR >= Soglia) {
        LeggermenteDestra();
        Lettura();
    }

    while(LetturaL < Soglia && LetturaC >= Soglia && LetturaR < Soglia) {
        Avanti();
        Lettura();
    }

    while(LetturaL < Soglia && LetturaC < Soglia && LetturaR >= Soglia) {
        LeggermenteDestra();
        Lettura();
    }

    if (LetturaL >= Soglia && LetturaC >= Soglia && LetturaR >= Soglia) {
        Stop();
    }

    if (LetturaL < Soglia && LetturaC < Soglia && LetturaR < Soglia) {
            ServoR.writeMicroseconds(1500);
            ServoL.writeMicroseconds(1500);
    }

    //Default
    ServoR.writeMicroseconds(DefaultR);
    ServoL.writeMicroseconds(DefaultL);
}

// --- Rivelamento ricevitore IR per Telecomando ---
void Ctrl_Telecomando() {
    if (IrReceiver.decode()) {
        if (command == 24) {
            ServoR.writeMicroseconds(1400);
            ServoL.writeMicroseconds(1600);
        } else if (command == 82) {
            ServoR.writeMicroseconds(1600);
            ServoL.writeMicroseconds(1400);
        } else if (command == 90) {
            ServoR.writeMicroseconds(1500);
            ServoL.writeMicroseconds(1600);

        } else if (command == 8) {
            ServoR.writeMicroseconds(1400);
            ServoL.writeMicroseconds(1500);
            delay(500);
        } else if (command == 70){
          Superamento = false;
        }
    } else {
        Fermo();
    }
    
    IrReceiver.resume();
}

// --- Supera Ostacolo ---
void SuperaOstacolo() {
   // Leggermente indietro
   ServoR.writeMicroseconds(1550);
   ServoL.writeMicroseconds(1450);
   delay(300);

    // Destra su se stesso
   ServoR.writeMicroseconds(1550);
   ServoL.writeMicroseconds(1550);
   delay(700);

   // Avanti
   Avanti();
   delay(1600);

   // Sinistra su se stesso
   ServoR.writeMicroseconds(1450);
   ServoL.writeMicroseconds(1450);
   delay(700);

   // Avanti
   Avanti();
   delay(1600);

   // Sinistra su se stesso
   ServoR.writeMicroseconds(1450);
   ServoL.writeMicroseconds(1450);
   delay(450);

   bool Linea = false;

   while(Linea == false) {
    Lettura();

    //Default
    ServoR.writeMicroseconds(DefaultR);
    ServoL.writeMicroseconds(DefaultL);

    if (LetturaC >= Soglia) { // Controllo rivelamento linea sensore centrale
      ServoR.writeMicroseconds(1550);
      ServoL.writeMicroseconds(1550);
      delay(700);

      Linea = true;

      break;
    }
   }
}

// --- Controllo Ostacolo ---
void Ctrl_Ostacolo() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); // Genera un impulso ultrasonico
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    t = pulseIn(echoPin, HIGH); // tempo di ritorno del segnale
    d = t * 0.0344 / 2; //  distanza in cm

    if (d <= 10) {
        Fermo();

        Superamento = true;

        for (int i=0; i < 5; i++) {
            // Suona il buzzer per circa 8s
            tone(6, 3000); // 
            delay(200);        //
            digitalWrite(7, HIGH);
            delay(200);        //

            noTone(6);     // Stop sound...
            delay(100);
            digitalWrite(7, LOW);
        }

        noTone(6);     // Stop sound...

        digitalWrite(7, HIGH);

        /*
          // Dovrebbe andare in guida manuale, ma non va:
          while(Superamento) {
            Ctrl_Telecomando();
          }
        */
      
        SuperaOstacolo();

        // Superamento = false;
    } 
}

//Setup
void setup() {
    // Setup Led & Buzzer
    pinMode(6, OUTPUT); // Imposta il pin 6 come OUTPUT per il buzzer
    pinMode(7, OUTPUT); // Imposta il pin 7 come OUTPUT per il LED

    // Setup Ultrasuoni
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Setup Ricevitore
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    //pinMode(IR_RECEIVE_PIN, INPUT);

    // Setup Servo-motori
    ServoR.attach(10);
    ServoL.attach(11);
}

//main loop
void loop() {
 Ctrl_Start();

 while (start) {
     Ctrl_Ostacolo();
     Lettura();
     Codifica();
 }

 Traguardo();
}
