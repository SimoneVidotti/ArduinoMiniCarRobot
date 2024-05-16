// Collegamenti:
// Buzzer: GND -> GND, + -> Pin 9
// LED: GND -> GND, + -> Pin 11

void setup() {
  pinMode(6, OUTPUT); // Imposta il pin 9 come OUTPUT per il buzzer
  pinMode(7, OUTPUT); // Imposta il pin 11 come OUTPUT per il LED
}

void loop() {
  // Suona il buzzer per 500 ms
  tone(6, 3000); // Send 1KHz sound signal...
  delay(200);        // ...for 1 sec
  digitalWrite(7, HIGH);
  delay(200);        // ...for 1 sec

  noTone(6);     // Stop sound...
  delay(100);   
  digitalWrite(7, LOW);
  delay(100);
}
