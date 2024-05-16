#include <Servo.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 8

Servo ServoR;
Servo ServoL;

void Ctl_Telecomando() {
  if (IrReceiver.decode()) {
    uint16_t command = IrReceiver.decodedIRData.command;

    Serial.println(command);

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
    }

    IrReceiver.resume();
  } else {
    ServoR.writeMicroseconds(1500);
    ServoL.writeMicroseconds(1500);
  }
}

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  pinMode(IR_RECEIVE_PIN, INPUT);
  ServoR.attach(10);
  ServoL.attach(11);
}

void loop() {
  Ctl_Telecomando();
}
