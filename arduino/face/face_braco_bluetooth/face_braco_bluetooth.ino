#include "LedControl.h"
#include <Servo.h>

//Pinos 12 (DIN), 11 (CLK), 10 (CS)
//Ultimo parametro do construtor eh a quantidade de displays a serem controlados
LedControl lc = LedControl(12,11,10,5);

// Braço Esquerdo
Servo servoE;

// Braço Direito
Servo servoD;

unsigned long tempo = 1500;

byte olho_x[8] = { B00000000,
                   B01100110,
                   B00100100,
                   B00011000,
                   B00011000,
                   B00100100,
                   B01100110,
                   B00000000};

byte olho_int[8] = {B00011000,
                    B00100100,
                    B00000100,
                    B00000100,
                    B00001000,
                    B00010000,
                    B00000000,
                    B00010000};
                   
byte olho_neutro[8] = {B00000000,
                       B00011000,
                       B00111100,
                       B00111100,
                       B00111100,
                       B00111100,
                       B00011000,
                       B00000000};
                  
byte olho_arregalado[8] = {B00011000,
                           B00111100,
                           B00111100,
                           B00111100,
                           B00111100,
                           B00111100,
                           B00111100,
                           B00011000};

byte olho_fechado[8] = {B00000000,
                        B00000000,
                        B00000000,
                        B00111100,
                        B01111110,
                        B01100110,
                        B00000000,
                        B00000000};
                        
byte boca_alegre[24] = { B00000000,
                         B00001000,
                         B00011100,
                         B00011110,
                         B00001111,
                         B00000011,
                         B00000000,
                         B00000000,
                         // parte1
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000000,
                         B10000001,
                         B11111111,
                         B11111111,
                         B01111110,
                         // parte2
                         B00000000,
                         B00010000,
                         B00111000,
                         B01111000,
                         B11110000,
                         B11000000,
                         B00000000,
                         B00000000 };

byte boca_triste[24] = { B00000000,
                         B00000000,
                         B00000000,
                         B00000011,
                         B00001111,
                         B00011000,
                         B00010000,
                         B00000000,
                         // parte1
                         B00000000,
                         B00111100,
                         B11111111,
                         B11000011,
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000000,
                         // parte2
                         B00000000,
                         B00000000,
                         B00000000,
                         B11000000,
                         B11100000,
                         B00110000,
                         B00010000,
                         B00000000 };
                         
byte aberta_triste[24] = { B00000000,
                           B00000011,
                           B00001100,
                           B00010000,
                           B00100000,
                           B00100000,
                           B00011100,
                           B00000011,
                         // parte1
                         B01111110,
                         B10000001,
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000000,
                         B11111111,
                         // parte2
                         B00000000,
                         B11000000,
                         B00110000,
                         B00001000,
                         B00000100,
                         B00000100,
                         B00111000,
                         B11000000 };
                         
byte aberta_alegre[24] = { B00000000,
                           B00011000,
                           B00100111,
                           B00100000,
                           B00010000,
                           B00001100,
                           B00000011,
                           B00000000,
                         // parte1
                         B00000000,
                         B00000000,
                         B00000011,
                         B11111100,
                         B00000000,
                         B00000000,
                         B00000011,
                         B11111100,
                         // parte2
                         B00000000,
                         B00110000,
                         B11001000,
                         B00001000,
                         B00010000,
                         B01100000,
                         B10000000,
                         B00000000 };                         
                         
byte boca_nojo[24] = { B00000000,
                       B00000000,
                       B00001000,
                       B01010101,
                       B00100010,
                       B00000000,
                       B00000000,
                       B00000000,
                         // parte1
                         B00000000,
                         B00000000,
                         B10001000,
                         B01010101,
                         B00100010,
                         B00000000,
                         B00000000,
                         B00000000,
                         // parte2
                         B00000000,
                         B00000000,
                         B01000100,
                         B10101010,
                         B00010001,
                         B00000000,
                         B00000000,
                         B00000000 };                          

byte boca_lingua[24] = { B00000000,
                         B00011000,
                         B00001110,
                         B00000111,
                         B00000001,
                         B00000000,
                         B00000000,
                         B00000000,
                         // parte1
                         B00000000,
                         B00000000,
                         B00000000,
                         B11000011,
                         B11111111,
                         B00111100,
                         B00000000,
                         B00000000,
                         // parte2
                         B00000000,
                         B00011000,
                         B01110000,
                         B11111000,
                         B11111100,
                         B01111100,
                         B00111000,
                         B00000000 };
                   
void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,1);
  lc.clearDisplay(0);
  lc.shutdown(1,false);
  lc.setIntensity(1,1);
  lc.clearDisplay(1);
  lc.shutdown(2,false);
  lc.setIntensity(2,1);
  lc.clearDisplay(2);
  lc.shutdown(3,false);
  lc.setIntensity(3,1);
  lc.clearDisplay(3);
  lc.shutdown(4,false);
  lc.setIntensity(4,1);
  lc.clearDisplay(4);
  
  // Define o braço esquerdo para porta 7
  servoE.attach(7);
  
  // Definie o braço direiro para porta 9
  servoD.attach(9);
  
  // Inicia o Serial para receber os dados via bluetooh
  Serial.begin(9600);
}

void display_olhos(byte olhos[]) {
  for(int i=0;i<8;i++) {
   lc.setColumn(0,i,olhos[i]);
   lc.setColumn(1,i,olhos[i]);
  } 
}

void display_boca(byte boca[]) {
  for(int i=0;i<8;i++) {
    lc.setColumn(2,i,boca[i]);
    lc.setColumn(3,i,boca[i+8]);
    lc.setColumn(4,i,boca[i+16]);
  }
}

void loop() {
  
  char serial = Serial.read();

  
  // Triste
  if ( serial == '0' ) {
    display_olhos(olho_x);
    display_boca(boca_triste);
  }

  // Duvida
  if ( serial == '1' ) {
    display_olhos(olho_int);
    display_boca(boca_nojo);
  }

  // Alegre
  if ( serial == '2' ) {
    display_olhos(olho_neutro);
    display_boca(boca_alegre);
  }
  
  // Susto
  if ( serial == '3' ) { 
    display_olhos(olho_arregalado);
    display_boca(aberta_triste);
  }
  
  // Feliz boca aberta
  if ( serial == '4' ) {
    display_olhos(olho_neutro);
    display_boca(aberta_alegre);
  }
  
  // Mostrar lingua
  if ( serial == '5' ) {
    display_olhos(olho_fechado);
    display_boca(boca_lingua);
  }

  /*  Ações dos braços */
  //Dois braços para baixo
  if ( serial == '6' ) {
    servoE.write(0);
    servoD.write(0);
  }

  //Braço Esquerdo para cima
  if ( serial == '7' ) {
    servoE.write(160);
  }

  //Braço Direito para cima
  if ( serial == '8' ) {
    servoD.write(160);
  }

  //Dois braços para cima
  if ( serial == '9' ) {
    servoE.write(160);
    servoD.write(160);
  }

  //Braço esquerto reto
  if ( serial == 'A' ) {
    servoE.write(90);
  }

  //Braço direito reto
  if ( serial == 'B' ) {
    servoD.write(90);
  }
 
}
