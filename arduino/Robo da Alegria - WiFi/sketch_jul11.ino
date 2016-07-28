// Robô da Alegria v1.0 By Igor Fonseca Albuquerque
// Faces por Thiago Farauche e Diego Augustus

//incluir bibliotecas
#include <SoftwareSerial.h>
#include <Servo.h>
#include "LedControl.h"

LedControl lc = LedControl(13,12,11,5); //Pinos 13 (DIN), 12 (CLK), 11 (CS), 5 displays a serem controlados
SoftwareSerial esp8266(5, 4); //RX pino 5, TX pino 4

//definição de variáveis 
#define DEBUG true //exibir mensagens trocadas entre o ESP8266 e o arduino na porta Serial
#define SERV1 9 //porta digital 9 PWM
#define SERV2 10 //porta digital 10 PWM
#define SERV3 8 //porta digital 8 PWM
#define SERV4 7 //porta digital 7 PWM

Servo s1; //servo 1
Servo s2; //servo 2
Servo s3; //servo 3
Servo s4; //servo 4
int pos1 = 170; //ângulo atual do servo 1
int pos2 = 170; //ângulo atual do servo 2
int pos3 = 15; //ângulo atual do servo 3
int pos4 = 15; //ângulo atual do servo 4
int vel = 10; //velocidade dos servos (100 -> 90º em 1 s)(1 -> 90º em 9 s)
int pos1min = 20; //ângulo mínimo do servo 1
int pos2min = 20; //ângulo mínimo do servo 2
int pos3min = 40; //ângulo mínimo do servo 3
int pos4min = 40; //ângulo mínimo do servo 4
int pos1max = 160; //ângulo máximo do servo 1
int pos2max = 160; //ângulo máximo do servo 2
int pos3max = 160; //ângulo máximo do servo 3
int pos4max = 160; //ângulo máximo do servo 4
int face; //número da face atual
boolean piscar; //definir se deve ou não piscar os olhos
byte olho_atual[8];
unsigned long tempo0; //tempo para piscar os olhos


//*******************
//definição dos olhos
//*******************

//olho morto
byte olho_x[8] = { B00000000,
                   B01100110,
                   B00100100,
                   B00011000,
                   B00011000,
                   B00100100,
                   B01100110,
                   B00000000};

//olho interrogação
byte olho_int[8] = {B00011000,
                    B00100100,
                    B00000100,
                    B00000100,
                    B00001000,
                    B00010000,
                    B00000000,
                    B00010000};

//olho neutro                   
byte olho_neutro[8] = {B00000000,
                       B00011000,
                       B00111100,
                       B00111100,
                       B00111100,
                       B00111100,
                       B00011000,
                       B00000000};

//olho arregalado
byte olho_arregalado[8] = {B00011000,
                           B00111100,
                           B00111100,
                           B00111100,
                           B00111100,
                           B00111100,
                           B00111100,
                           B00011000};

//olho fechado (para cima)
byte olho_fechado[8] = {B00000000,
                        B00000000,
                        B00000000,
                        B00111100,
                        B01111110,
                        B01100110,
                        B00000000,
                        B00000000};

//olho fechado (para baixo)
byte olho_dormindo[8] = {B00000000,
                          B00000000,
                          B00000000,
                          B01100110,
                          B01111110,
                          B00011000,
                          B00000000,
                          B00000000};                        
                        
//*****************
//definição da boca
//*****************

//boca alegre fechada                        
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


//boca triste fechada
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

//boca triste aberta                         
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

//boca alegre aberta                         
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

//boca do nojo                         
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

//boca com língua para fora
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

//boca dormindo (sorriso pequeno)
byte boca_dormindo[24] = { B00000000,
                         B00000000,
                         B00000001,
                         B00000001,
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000000,
                         // parte1
                         B00000000,
                         B00000000,
                         B10000001,
                         B11111111,
                         B01111110,
                         B00000000,
                         B00000000,
                         B00000000,
                         // parte2
                         B00000000,
                         B00000000,
                         B10000000,
                         B10000000,
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000000 };

//************************
//inicialização do Arduino
//************************
void setup()
{
  //inicialização dos displays (configurar intensidade e zerar os displays)
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

  //manter o rosto dormindo durante a inicialização (até conectar com o wifi)
  fac8();

  //inicialização dos braços
  //associar os servomotores
  s1.attach(SERV1);
  s2.attach(SERV2);
  s3.attach(SERV3);
  s4.attach(SERV4);
  //posicionar os braços na posição neutra
  s1.write(pos1max);
  s2.write(pos2max);
  s3.write(pos3min);
  s4.write(pos4min);
  //desassociar os servomotores
  s1.detach();
  s2.detach();
  s3.detach();
  s4.detach();
  
  //inicialização da comunicação serial
  Serial.begin(9600);
  esp8266.begin(19200);
  
  sendData("AT+RST\r\n", 2000, DEBUG); //resetar módulo
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); //setar modo station
//  sendData("AT+CWJAP=\"Connectify-me\",\"12345678\"\r\n", 2000, DEBUG);   //conectar com a rede wifi
  sendData("AT+CWJAP=\"Thaiane\",\"1391162683\"\r\n", 2000, DEBUG);   //conectar com a rede wifi
  while(!esp8266.find("OK")) { //aguardar estabelecer conexão
  } 
  sendData("AT+CIFSR\r\n", 1000, DEBUG); //mostrar endereco IP
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG); //configura para multiplas conexões
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // Inicia o web server na porta 80
  
  //ativar rosto alegre após conexão com o wifi
  fac1();

  //inicializar timer
  tempo0 = millis();
}

//*************************
//Loop principal do Arduino
//*************************
void loop()
{
  int delta = millis() - tempo0;
  if(delta > 3000) {              //se o tempo for superior a 10 segundos
    if(piscar == true) {
      display_olhos(olho_dormindo);  //piscar olhos
      delay(200);
      switch (face){
        case 1:
          fac1();
          break;
        case 2:
          fac2();
          break;
        case 3:
          fac3();
          break;
        case 4:
          fac4();
          break;
        case 5:
          fac5();
          break;
        case 6:
          fac6();
          break;
        case 7:
          fac7();
          break;
        case 8:
          fac8();
          break;
        case 9:
          fac9();
          break;          
      }  
      tempo0 = millis();
    }
  }
  
  if (esp8266.available())  //verifica se o ESP8266 está recebendo dados
  {
    if (esp8266.find("+IPD,")) //se tiver recebido um dado
    {
      String msg;
      esp8266.find("?"); //corre o cursor até encontrar o comando na mensagem recebida     
      msg = esp8266.readStringUntil(' '); //ler string até o fim da mensagem
      String comando = msg.substring(0, 3); //primeiros 3 caracteres da mensagem = comando
      String valorStr = msg.substring(4);   //3 caracteres seguintes = valor associado ao comando
      int valor = valorStr.toInt();         //conversão de valor para inteiro
      if (DEBUG) {
        Serial.println(comando);
        Serial.println(valor);
      }
      delay(100);
      
      //*********************************************************
      //realizar ações: movimentar servos para ângulos informados
      //*********************************************************
      
      //mover o servo1 no angulo recebido em valor
      if(comando == "sr1") {
         //limitar o angulo de entrada
         if (valor >= pos1max) {
           valor = pos1max;
         }
         if (valor <= pos1min) {
           valor = pos1min;
         }
         s1.attach(SERV1); //associar servo
         //avançar até o ângulo desejado
         while(pos1 != valor) {
           if (pos1 > valor) {
             pos1 -= 1;
             s1.write(pos1);
             delay(100/vel);
           }
           if (pos1 < valor) {
             pos1 += 1;
             s1.write(pos1);
             delay(100/vel);
           }
         }
         s1.detach(); //desassociar servo
      }

      //mover o servo2 no angulo recebido em valor
      if(comando == "sr2") {
         //limitar o angulo de entrada
         if (valor >= pos2max) {
           valor = pos2max;
         }
         if (valor <= pos2min) {
           valor = pos2min;
         }
         s2.attach(SERV2);
         while(pos2 != valor) {
           if (pos2 > valor) {
             pos2 -= 1;
             s2.write(pos2);
             delay(100/vel);
           }
           if (pos2 < valor) {
             pos2 += 1;
             s2.write(pos2);
             delay(100/vel);
           }
         }   
         s2.detach();     
      }
      
      //mover o servo3 no angulo recebido em valor
      if(comando == "sr3") {
         //limitar o angulo de entrada
         if (valor >= pos3max) {
           valor = pos3max;
         }
         if (valor <= pos3min) {
           valor = pos3min;
         }
         s3.attach(SERV3);
         while(pos3 != valor) {
           if (pos3 > valor) {
             pos3 -= 1;
             s3.write(pos3);
             delay(100/vel);
           }
           if (pos3 < valor) {
             pos3 += 1;
             s3.write(pos3);
             delay(100/vel);
           }
         }   
         s3.detach();     
      }
      
      //mover o servo4 no angulo recebido em valor
      if(comando == "sr4") {
         //limitar o angulo de entrada
         if (valor >= pos4max) {
           valor = pos4max;
         }
         if (valor <= pos4min) {
           valor = pos4min;
         }        
         s4.attach(SERV4);
         while(pos4 != valor) {
           if (pos4 > valor) {
             pos4 -= 1;
             s4.write(pos4);
             delay(100/vel);
           }
           if (pos4 < valor) {
             pos4 += 1;
             s4.write(pos4);
             delay(100/vel);
           }
         }   
         s4.detach();     
      }


      //**************************************
      //realizar ações: movimentos programados
      //**************************************

      if(comando == "mov") {
         //associar servos
        s1.attach(SERV1);
        s2.attach(SERV2);
        s3.attach(SERV3);
        s4.attach(SERV4);

        if(valor == 10) {
            mov1(); //movimento1 = levantar braço esquerdo
        }
        if(valor == 20) {
            mov2(); //movimento2 = levantar braço direito
        }
        if(valor == 30) {
            mov3(); //movimento3 = levantar os dois braços
        }
        if(valor == 40) {
            mov4(); //movimento4 = abaixar os dois braços
        }
        if(valor == 50) {
            mov5(); //movimento5 = balançar os dois braços abertos
        }
        if(valor == 60) {
            mov6(); //movimento6 = balançar os dois braços na frente
        }
        if(valor == 70) {
            mov7(); //movimento7 = balançar os dois braços na frente
        }
        if(valor == 80) {
            mov8(); //movimento8 = girar os braços
        }        
        if(valor == 90) {
            mov9(); //movimento 9 = aceno
        }
 
        //desassociar servos
        s1.detach();
        s2.detach();
        s3.detach();
        s4.detach();
      }
      
      //**********************************
      //realizar ações: movimentos da face
      //**********************************

      if(comando == "fac") {
        if(valor == 10) {
          fac1();
        }
        if(valor == 20) {
          fac2();
        }
        if(valor == 30) {
          fac3();
        }
        if(valor == 40) {
          fac4();
        }
        if(valor == 50) {
          fac5();
        }
        if(valor == 60) {
          fac6();
        }
        if(valor == 70) {
          fac7();
        }
        if(valor == 80) {
          fac8();
        }
        if(valor == 90) {
          fac9();
        }  
      }

      //procurar comando para acionar algum pino   
      /*if(comando=="pin"){ // corre o cursor até encontrar "pin=" na mensagem recebida     
          digitalWrite(valor, !digitalRead(valor)); // toggle
      } */      
    }
  }
}


//******************
//Funções auxiliares
//******************


//enviar dados para o ESP8266
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available()) //enquanto o ESP8266 tiver dados disponíveis na sua saída
    {
      char c = esp8266.read(); //ler e armazenar os caracteres recebidos
      response += c;
    }
  }
  if (debug) //se estiver em modo DEBUG, imprimir a resposta
  {
    Serial.print(response);
  }
  return response;
}


//alterar exibição dos olhos
void display_olhos(byte olhos[]) {
  for(int i=0;i<8;i++) {
   lc.setColumn(0,i,olhos[i]);
   lc.setColumn(1,i,olhos[i]);
  } 
}


//alterar exibição da boca
void display_boca(byte boca[]) {
  for(int i=0;i<8;i++) {
    lc.setColumn(2,i,boca[i]);
    lc.setColumn(3,i,boca[i+8]);
    lc.setColumn(4,i,boca[i+16]);
  }
}


//movimento1 = levantar braço esquerdo
void mov1()
{
  pos1 = pos1max;
  s1.write(pos1);        
  while(pos2 != pos2min) {
    pos2 -= 1;
    s2.write(pos2);
    delay(100/vel);
    if (pos2 < pos2min) {
      pos2 = pos2min;
    }
  }  
}


//movimento2 = levantar braço direito
void mov2()
{
  pos3 = pos3min;
  s3.write(pos3);        
  while(pos4 != pos4max) {
    pos4 += 1;
    s4.write(pos4);
    delay(100/vel);
    if (pos4 > pos4max) {
      pos4 = pos4max;
    }
  }  
}


//movimento3 = levantar os dois braços
void mov3()
{
  pos1 = pos1max;
  pos3 = pos3min;
  s1.write(pos1);        
  s3.write(pos3);        
  while((pos2 != pos2min) || (pos4!= pos4max)) {
    pos2 -= 1;
    pos4 += 1;
    s2.write(pos2);
    s4.write(pos4);
    delay(100/vel);
    if (pos2 < pos2min) {
      pos2 = pos2min;
    }
    if (pos4 > pos4max) {
      pos4 = pos4max;
    }
  }  
}


//movimento4 = abaixar os dois braços
void mov4()
{  
  pos1 = pos1max;
  pos3 = pos3min;
  s1.write(pos1);        
  s3.write(pos3);        
  while((pos2 != pos2max) || (pos4!= pos4min)) {
    pos2 += 1;
    pos4 -= 1;
    s2.write(pos2);
    s4.write(pos4);
    delay(100/vel);
    if (pos2 > pos2max) {
      pos2 = pos2max;
    }
    if (pos4 < pos4min) {
      pos4 = pos4min;
    }
  }  
}


//movimento5 = balançar os dois braços abertos
void mov5()
{
    s1.write(pos1max);
    s2.write(pos2max);
    s3.write(pos3min);    
    s4.write(pos4min);    
    delay(500);
    for(int k = 1; k < 3 ; k++) {
      while((pos1 != pos1min)&& (pos3!= pos3max)) {
        pos1 -= 1;
        pos3 += 1;
        s1.write(pos1);
        s3.write(pos3);
        delay(100/vel);
        if (pos1 < pos1min) {
          pos1 = pos1min;
        }
        if (pos3 > pos3max) {
          pos3 = pos3max;
        }
      }
      while((pos1 != pos1max)&& (pos3!= pos3min)) {
        pos1 += 1;
        pos3 -= 1;
        s1.write(pos1);
        s3.write(pos3);
        delay(100/vel);
        if (pos1 > pos1max) {
          pos1 = pos1max;
        }
        if (pos3 < pos3min) {
          pos3 = pos3min;
        }
      }
    }
}


//movimento6 = balançar os dois braços na frente
void mov6()
{
    s1.write(pos1max);
    s2.write(pos2max);
    s3.write(pos3min);
    s4.write(pos4min);
    delay(500);
    
    for(int k = 1; k < 3 ; k++) {
      while((pos2 != pos2min)&& (pos4!= pos4max)) {
        pos2 -= 1;
        pos4 += 1;
        s2.write(pos2);
        s4.write(pos4);
        delay(100/vel);
        if (pos2 < pos2min) {
          pos2 = pos2min;
        }
        if (pos4 > pos4max) {
          pos4 = pos4max;
        }
      }
      while((pos2 != pos2max)&& (pos4!= pos4min)) {
        pos2 += 1;
        pos4 -= 1;
        s2.write(pos2);
        s4.write(pos4);
        delay(100/vel);
        if (pos2 > pos2max) {
          pos2 = pos2max;
        }
        if (pos4 < pos4min) {
          pos4 = pos4min;
        }
      }
    }
}


//movimento7 = balançar os dois braços na frente
void mov7()
{
    s2.write(90);
    s1.write(pos1max);
    s4.write(90);
    s3.write(pos3min);
    delay(500);
    s1.write(90);
    s3.write(90);
    delay(500);
    for(int k = 1; k < 3 ; k++) {
      while((pos2 != pos2max)&& (pos4!= pos4min)) {
        pos2 += 1;
        pos4 -= 1;
        s2.write(pos2);
        s4.write(pos4);
        delay(100/vel);
        if (pos2 > pos2max) {
          pos2 = pos2max;
        }
        if (pos4 < pos4min) {
          pos4 = pos4min;
        }
      }
      while((pos2 != 90)&& (pos4!= 90)) {
        pos2 -= 1;
        pos4 += 1;
        s2.write(pos2);
        s4.write(pos4);
        delay(100/vel);
        if (pos2 < 90) {
          pos2 = 90;
        }
        if (pos4 > 90) {
          pos4 = 90;
        }
      }
    }
    while((pos2 != pos2max)&& (pos4!= pos4min)) {
        pos2 += 1;
        pos4 -= 1;
        s2.write(pos2);
        s4.write(pos4);
        delay(100/vel);
        if (pos2 > pos2max) {
          pos2 = pos2max;
        }
        if (pos4 < pos4min) {
          pos4 = pos4min;
        }
      }
    s1.write(pos1max);
    s3.write(pos3min);
    delay(500);    
}


//movimento8 = girar os braços
void mov8()
{
  s1.write(170);
  s2.write(90);
  delay(500);
  s2.write(90);
  delay(500);
  s1.write(170);
  delay(500);
  //incompleto...  

}


//movimento 9 = aceno
void mov9()
{
    s1.write(170);
    s2.write(20);
    delay(500);
    s1.write(150);
    s2.write(20);
    delay(500);
    s1.write(175);
    s2.write(20);
    delay(500);
    s1.write(150);
    s2.write(20);
    delay(500);
    s1.write(175);
    s2.write(20);
    delay(500);
    s1.write(150);
    s2.write(20);
    delay(500);
    s1.write(175);
    s2.write(20);
    delay(500);
    s1.write(170);
    s2.write(170);
    delay(500);
}


//rosto feliz
void fac1()
{
  face = 1;
  piscar = true;
  display_olhos(olho_neutro);
  display_boca(boca_alegre);
}


//rosto feliz com olhos arregalados
void fac2()
{
  face = 2;
  piscar = true;
  display_olhos(olho_arregalado);
  display_boca(boca_alegre);
}


//rosto feliz com boca aberta
void fac3()
{
  face = 3;
  piscar = true;
  display_olhos(olho_neutro);
  display_boca(aberta_alegre);
}


//rosto triste
void fac4()
{
  face = 4;
  piscar = true;
  display_olhos(olho_neutro);
  display_boca(boca_triste);
}


//rosto triste com olhos arregalados
void fac5()
{
  face = 5;
  piscar = true;
  display_olhos(olho_arregalado);
  display_boca(boca_triste);
}


//rosto morto
void fac6()
{
  face = 6;
  piscar = false;
  display_olhos(olho_x);
  display_boca(boca_triste);
}


//rosto com língua para fora
void fac7()
{
  face = 7;
  piscar = false;
  display_olhos(olho_fechado);
  display_boca(boca_lingua);
}


//rosto dormindo
void fac8()
{
  face = 8;
  piscar = false;
  display_olhos(olho_dormindo);
  display_boca(boca_dormindo);
}


//rosto nojo
void fac9()
{
  face = 9;
  piscar = true;
  display_olhos(olho_arregalado);
  display_boca(boca_nojo);
}
