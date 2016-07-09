/* Projeto de código aberto, com o objetivo de compartilhar conhecimentos sobre eletrônica, robótica e programação de computadores.

O objetivo geral do projeto é criar um Robô para ser utilizado no trabalho de ONGs como o Doutores da Alegria. */

#include <Servo.h>
#include "LedControl.h"
#include <SoftwareSerial.h>

//Pinos 12 (DIN), 11 (CLK), 10 (CS)
//Ultimo parametro do construtor eh a quantidade de displays a serem controlados
LedControl lc = LedControl(12,11,10,5);

//Defino os pino Rx pino 2 e Tx pino 3
SoftwareSerial bluetooth(2, 3);

// Braço Esquerdo
Servo servoE;

// Braço Direito
Servo servoD;

// unsigned long tempo = 1500; - não vi aplicação no código upado no github por isso comentei

byte olho_x[8] = { B00000000,
                   B01100110,
                   B00100100,
                   B00011000,
                   B00011000,
                   B00100100,
                   B01100110,
                   B00000000};

byte olho_interrogacao[8] = {B00011000,
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


void setup(){
  bluetooth.begin(115200); //inicio comunicação bluetooth baud-rate 115200
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
 // Define o braço esquerdo para porta 4 e direito porta 6
  servoE.attach(4);
  servoD.attach(5);
}

void display_olhos(byte olhos[]) {
	for (int i = 0; i < 8; i++) {
		lc.setColumn(0, i, olhos[i]);
		lc.setColumn(1, i, olhos[i]);
	}
}
        
void display_boca(byte boca[]) {
  for(int i = 0; i < 8; i++) {
    lc.setColumn(2, i, boca[i]);
    lc.setColumn(3, i, boca[i + 8]);
    lc.setColumn(4, i ,boca[i + 16]);
  }
}                   

void loop()
{
  char recebe_bluetooth = bluetooth.read();
	switch (recebe_bluetooth) {
		// triste
	    case '1':
	      display_olhos(olho_x);
    	  display_boca(boca_triste);
	      break;
	    // alegre
	    case '2':
	      display_olhos(olho_neutro);
   		  display_boca(boca_alegre);
	      break;
	    // alegre boca aberta
	    case '3':
	      display_olhos(olho_neutro);
        display_boca(aberta_alegre);
	      break;
	   // mostrar língua 
	    case '4':
   		  display_olhos(olho_fechado);
    	  display_boca(boca_lingua);
    	  break;
    	// ponto de interrogação ?.?
 	    case '5':
   		  display_olhos(olho_interrogacao);
    	  display_boca(boca_nojo);
    	  break;
    	// triste boca abeerta
 	    case '6':
    	  display_olhos(olho_arregalado);
        display_boca(aberta_triste);
    	  break;
     	// feliz aberto olho arregalado
 	    case '7':
    	  display_olhos(olho_arregalado);
        display_boca(aberta_alegre);
    	  break;   	
    	// braços para baixo  
    	case 'A':
   		  servoE.write(0);
        servoD.write(0);
    	  break;   	
    	// braços para cima 
    	case 'B':
   		  servoE.write(160);
        servoD.write(160);
    	  break;  
    	// braço direito cima
    	case 'C':
        servoD.write(160);
        servoE.write(0);
    	  break; 
    	// braço esquerdo cima
    	case 'D':
        servoE.write(160);
        servoD.write(0);
    	  break;  
	}
}
