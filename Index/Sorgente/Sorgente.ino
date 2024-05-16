// Vidotti Simone, Zhou Luigi 4 TEL A Progetto LineFollower, Robottino Arduino
#include <Servo.h>
#include <IRremote.hpp>

// pin Sensori
#define SensoreR A2
#define SensoreC A0
#define SensoreL A1

// pin Ultrasuoni
#define echoPin 3 // pin D2 Arduino Echo dell'HC-SR04
#define trigPin 2 // pin D3 Arduino Trig dell'HC-SR04

// pin ricevitore
#define IR_RECEIVE_PIN 8

// pin Servo-motori
Servo ServoR;
Servo ServoL;

// Velocita per fixing line
int DefaultR = 1491;
int DefaultL = 1509;

// Soglie, Sensore centrale ha una soglia diversa
int Soglia1 = 1020;
int Soglia2 = 1000;

// Valori di lettura
int LetturaR, LetturaC, LetturaL;

// variabili di distanza e tempo per Ultrasuoni
long t; // tempo impiegato segnale ultrasuoni
int d;  // distanza rilevata

// Stato iniziale
bool start = false; // Controllo quando partire

// Controllo Ostacolo, guida manuale.
bool Superamento = false; // Ctrl superamento

// --- Seguire Linea nera ---
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
}

void LeggermenteSinistra() {
    ServoR.writeMicroseconds(1470);
    ServoL.writeMicroseconds(1500);
    delay(500);
}

void Fermo() {
    
    ServoR.writeMicroseconds(1500);
    ServoL.writeMicroseconds(1500);
}

void Stop() {
    ServoR.writeMicroseconds(1500);
    ServoL.writeMicroseconds(1500);
    ServoR.detach();
    ServoL.detach();
    digitalWrite(7, HIGH);
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
            ServoR.writeMicroseconds(1500);
            ServoL.writeMicroseconds(1500);
    }

    //Default
    ServoR.writeMicroseconds(DefaultR);
    ServoL.writeMicroseconds(DefaultL);
}

// Rivelamento ricevitore IR per Telecomando
void Ctrl_Telecomando() {
    if (IrReceiver.decode()) {
        uint16_t command = IrReceiver.decodedIRData.command;

        if (command == 69) {
            start = true;
        }

        if (command == 24) {
            ServoR.writeMicroseconds(1400);
            ServoL.writeMicroseconds(1600);
            delay(300);
        } else if (command == 82) {
            ServoR.writeMicroseconds(1600);
            ServoL.writeMicroseconds(1400);
            delay(300);
        } else if (command == 90) {
            ServoR.writeMicroseconds(1500);
            ServoL.writeMicroseconds(1600);
            delay(500);
        } else if (command == 8) {
            ServoR.writeMicroseconds(1400);
            ServoL.writeMicroseconds(1500);
            delay(500);
        } else if (command == 70){
          Superamento = false;
        }
    }
    
    IrReceiver.resume();
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

    if (d <= 10 || d <= 5) {
        Fermo();

        Superamento = true;

        for (int i=0; i < 3; i++) {
            // Suona il buzzer per 500 ms
            tone(6, 3000); // Send 1KHz sound signal...
            delay(200);        //
            digitalWrite(7, HIGH);
            delay(200);        //

            noTone(6);     // Stop sound...
            delay(100);
            digitalWrite(7, LOW);
        }

        noTone(6);     // Stop sound...

        //Lampeggio led mentre è telecomandato
        while (Superamento) {
            digitalWrite(7, HIGH);
            delay(50);
            digitalWrite(7, LOW);
            delay(50);

            Ctrl_Telecomando();
        }
    } 

    Superamento = false;
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
    pinMode(IR_RECEIVE_PIN, INPUT);

    // Setup Servo-motori
    ServoR.attach(10);
    ServoL.attach(11);
}

//main loop
void loop() {
 Ctrl_Telecomando();

 while (start) {
     Ctrl_Ostacolo();
     Lettura();
     Codifica();
 }
}
