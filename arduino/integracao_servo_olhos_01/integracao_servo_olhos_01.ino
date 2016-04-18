#include "LedControl.h"
#include<Servo.h>

// Braço Esquerdo
Servo servoE;

// Braço Direito
Servo servoD;

//Pinos 12 (DIN), 11 (CLK), 10 (CS)
//Ultimo parametro do construtor eh a quantidade de displays a serem controlados
LedControl lc = LedControl(12,11,10,2);

unsigned long tempo = 2000;

byte neutral[8] = {B01111110,
                   B11111111,
                   B11111111,
                   B11100111,
                   B11100111,
                   B11111111,
                   B11111111,
                   B01111110};

byte susto[8] = {B01111110,
                 B11111111,
                 B11100111,
                 B11000011,
                 B11000011,
                 B11100111,
                 B11111111,
                 B01111110};
                   
byte triste[8] = {B00000000,
                  B00000000,
                  B11111111,
                  B11111111,
                  B11100111,
                  B01111110,
                  B00000000,
                  B00000000};
                  
byte fechado[8] = {B00000000,
                   B00000000,
                   B00000000,
                   B11111111,
                   B01111110,
                   B00000000,
                   B00000000,
                   B00000000};

void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,1);
  lc.clearDisplay(0);
  lc.shutdown(1,false);
  lc.setIntensity(1,1);
  lc.clearDisplay(1);
  
  // Define o braço esquerdo para porta 7
  servoE.attach(7);
  
  // Definie o braço direiro para porta 9
  servoD.attach(9);
  
  // Inicia o Serial para receber os dados via bluetooh
  Serial.begin(9600);

  pinMode(13, OUTPUT);
}

void display(byte data[]) {
  for(int i=0;i<8;i++) {
   lc.setColumn(0,i,data[i]);
   lc.setColumn(1,i,data[i]);
  } 
}

void piscada() {
  for(int i=0;i<8;i++) {
    lc.setColumn(1,i,neutral[i]);
    lc.setColumn(0,i,fechado[i]);
  }
}

void loop() {
  // Inicia a leitora do Bluetooh
  char serial = Serial.read();

  
  // Neutral
  if ( serial == '0' ) {
    display(neutral);
  }

  // Susto
  if ( serial == '1' ) {
    display(susto);
  }

  // Triste
  if ( serial == '2' ) {
    display(triste);
  }
  
  // Neutral
  if ( serial == '3' ) {
    display(neutral);
  }
  
  // Fechado
  if ( serial == '4' ) {
    display(fechado);
  }
  
  // Piscada
  if ( serial == '5' ) {
    display(fechado);
  }



  /*  Ações dos braços */

  Dois braços para baixo
  if ( serial == '6' ) {
    servoE.write(0);
    servoD.write(0);
  }

  Braço Esquerdo para cima
  if ( serial == '7' ) {
    servoE.write(180);
  }

  Braço Direito para cima
  if ( serial == '8' ) {
    servoD.write(180);
  }

  Dois braços para cima
  if ( serial == '9' ) {
    servoE.write(180);
    servoD.write(180);
  }

  Braço esquerto reto
  if ( serial == '10' ) {
    servoE.write(90);
  }

  Braço direito reto
  if ( serial == '11' ) {
    servoD.write(90);
  }
  
  //piscada();
  delay(tempo);
}
