#include <IRremote.hpp>

#define IR_RECEIVE_PIN 8

void setup()
{
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
  Serial.begin(9600);
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData); // Print "old" raw data

    if (IrReceiver.decodedIRData.decodedRawData == 3877175040) {
     Serial.println("Comando");
    }
      
    IrReceiver.resume(); // Enable receiving of the next value
  }
}