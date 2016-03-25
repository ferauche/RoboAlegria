#include "LedControl.h"

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
  display(neutral);
  delay(tempo);
  display(triste);
  delay(tempo);
  display(susto);
  delay(tempo);
  display(fechado);
  delay(tempo);
  piscada();
  delay(tempo);
}
