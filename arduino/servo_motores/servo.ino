#include<Servo.h>

Servo servoE;
Servo servoD;

void setup() {
  servoE.attach(7);
  servoD.attach(9);
  
  Serial.begin(9600);

  pinMode(13, OUTPUT);
}

void loop() {
  char serial = Serial.read();

  if ( serial == '0' ) {
    digitalWrite(13, HIGH);
    servoE.write(0);
    servoD.write(180);
  }

  if ( serial == '1' ) {
    digitalWrite(13, LOW);
    servoE.write(90);
    servoD.write(0);
  }

  if ( serial == '2' ) {
    digitalWrite(13, HIGH);
    servoE.write(180);
    servoD.write(90);
  }


  delay(10);
}
