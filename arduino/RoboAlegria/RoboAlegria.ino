// Robô da Alegria v1.0 By Igor Fonseca Albuquerque

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
int pos1 = 180; //ângulo atual do servo 1
int pos2 = 170; //ângulo atual do servo 2
int pos3 = 15; //ângulo atual do servo 3
int pos4 = 15; //ângulo atual do servo 4
int vel = 10; //velocidade dos servos (100 -> 90º em 1 s)(1 -> 90º em 9 s)
int pos1min = 60; //ângulo mínimo do servo 1
int pos2min = 00; //ângulo mínimo do servo 2
int pos3min = 00; //ângulo mínimo do servo 3
int pos4min = 00; //ângulo mínimo do servo 4
int pos1max = 180; //ângulo máximo do servo 1
int pos2max = 170; //ângulo máximo do servo 2
int pos3max = 120; //ângulo máximo do servo 3
int pos4max = 170; //ângulo máximo do servo 4
int face; //número da face atual
int olho_direito; //número do olho direito atual
int olho_esquerdo; //número do olho esquerdo atual
int boca; //número da boca atual
boolean piscar; //definir se deve ou não piscar os olhos
byte olho_atual[8];
unsigned long tempo0; //tempo para piscar os olhos


//*******************
//definição dos olhos
//*******************

//olho morto
byte olho_x[8] = { B00000000,
                   B01000010,
                   B01100110,
                   B00011100,
                   B00011000,
                   B01100110,
                   B01000010,
                   B00000000};

//olho interrogação (obsoleto)
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
                       B00000000,
                       B00111100,
                       B01111110,
                       B01111110,
                       B00111100,
                       B00000000,
                       B00000000};

//olho arregalado
byte olho_arregalado[8] = {B00000000,
                           B00000000,
                           B01111110,
                           B11111111,
                           B11111111,
                           B01111110,
                           B00000000,
                           B00000000};

//olho fechado (para cima)
byte olho_fechado[8] = {B00000000,
                        B00001100,
                        B00011100,
                        B00011000,
                        B00011000,
                        B00011100,
                        B00001100,
                        B00000000};
                        
//olho fechado (para baixo)
byte olho_dormindo[8] = {B00000000,
                         B00011000,
                         B00011000,
                         B00001100,
                         B00001100,
                         B00011000,
                         B00011000,
                         B00000000};                        
                         
                        
//*****************
//definição da boca
//*****************

//boca alegre fechada                        
byte boca_alegre[24] = { B00000000,
                         B00000000,
                         B00000000,
                         B00110000,
                         B01111000,
                         B00111000,
                         B00011100,
                         B00001100,    
                         // parte1
                         B00001110,
                         B00000111,
                         B00000111,
                         B00000111,
                         B00000111,
                         B00000111,
                         B00000111,
                         B00001110,
                         // parte2 
                         B00001100,
                         B00011100,
                         B00111000,
                         B01111000,
                         B00110000,
                         B00000000,
                         B00000000,
                         B00000000 };
                         
                                                  
//boca triste fechada
byte boca_triste[24] = { B00000000,
                         B00000000,
                         B00000000,
                         B00000110,
                         B00001100,
                         B00001000,
                         B00011000,
                         B00011000,
                         // parte1
                         B00110000,
                         B00110000,
                         B01100000,
                         B01100000,
                         B01100000,
                         B01100000,
                         B00110000,
                         B00110000,
                         // parte2
                         B00011000,
                         B00011000,
                         B00001100,
                         B00000110,
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000000 };

//boca triste aberta
byte aberta_triste[24] = { B00000000,
                           B00000000,
                           B00001100,
                           B00010010,
                           B00100010,
                           B00100010,
                           B01000010,
                           B01000100,                           
                         // parte1
                         B01000100,
                         B10000100,
                         B10000100,
                         B10000100,
                         B10000100,
                         B10000100,
                         B10000100,
                         B01000100,                         
                         // parte2
                         B01000100,
                         B01000010,
                         B00100010,
                         B00100010,
                         B00010010,
                         B00001100,
                         B00000000,
                         B00000000 };

//boca alegre aberta                         
byte aberta_alegre[24] = { B00000000,
                           B00000000,
                           B00110000,
                           B01001000,
                           B01000100,
                           B00100100,
                           B00100010,
                           B00100010,
                         // parte1
                         B00010001,
                         B00010001,
                         B00010001,
                         B00010001,
                         B00010001,
                         B00010001,
                         B00010001,
                         B00010001,                        
                         // parte2
                         B00100010,
                         B00100010,
                         B00100100,
                         B01000100,
                         B01001000,
                         B00110000,
                         B00000000,
                         B00000000, };                         

//boca de nojo                         
byte boca_nojo[24] = { B00000000,
                       B00010000,
                       B00001000,
                       B00010000,
                       B00100000,
                       B00010000,
                       B00001000,
                       B00010000,
                         // parte1
                         B00100000,
                         B00010000,
                         B00001000,
                         B00010000,
                         B00100000,
                         B00010000,
                         B00001000,
                         B00010000,
                         // parte2
                         B00100000,
                         B00010000,
                         B00001000,
                         B00010000,
                         B00100000,
                         B00010000,
                         B00001000,
                         B00000000 };

//boca falando                         
byte boca_falando[24] = { B00000000,
                       B00000000,
                       B00001000,
                       B00010000,
                       B00100000,
                       B00010000,
                       B00001000,
                       B00010000,
                         // parte1
                         B00100000,
                         B00010000,
                         B00001000,
                         B00010000,
                         B00100000,
                         B00010000,
                         B00001000,
                         B00010000,
                         // parte2
                         B00010000,
                         B00100000,
                         B00010000,
                         B00001000,
                         B00010000,
                         B00100000,
                         B00000000,
                         B00000000 };

//boca falando 1                         
byte boca_neutra[24] = { B00000000,
                        B00000000,
                        B00010000,
                        B00010000,
                        B00010000,
                        B00010000,
                        B00010000,
                        B00010000,
                         // parte1
                         B00010000,
                         B00010000,
                         B00010000,
                         B00010000,
                         B00010000,
                         B00010000,
                         B00010000,
                         B00010000,
                         // parte2
                         B00010000,
                         B00010000,
                         B00010000,
                         B00010000,
                         B00010000,
                         B00010000,
                         B00000000,
                         B00000000 };
                         
//boca falando 2
byte boca_falando2[24] = { B00000000,
                        B00000000,
                        B00001000,
                        B00010000,
                        B00100000,
                        B00010000,
                        B00001000,
                        B00010000,
                         // parte1
                         B00010000,
                         B00001000,
                         B00010000,
                         B00100000,
                         B00010000,
                         B00001000,
                         B00010000,
                         B00100000,
                         // parte2
                         B00010000,
                         B00001000,
                         B00010000,
                         B00100000,
                         B00010000,
                         B00001000, 
                         B00000000,
                         B00000000 };                       

//boca com língua para fora
byte boca_lingua[24] = { B00000000,
                         B00000000,
                         B00000000,
                         B01000000,
                         B01100000,
                         B00110000,
                         B00110000,
                         B00011000,
                         // parte1
                         B00011000,
                         B00011000,
                         B00001100,
                         B00001100,
                         B00001100,
                         B00001100,
                         B00011000,
                         B00011000,
                         // parte2
                         B00011000,
                         B00111100,
                         B00111110,
                         B01111110,
                         B01011110,
                         B00001100,
                         B00000000,
                         B00000000 };


//boca com a língua para fora (frente)                         
byte boca_lingua_1[24] = { B00000000,
                           B00000000,
                           B00000000,
                           B00000000,
                           B00000000,
                           B00110000,
                           B00101000,
                           B00101000,
                         // parte1
                         B00101000,
                         B00101000,
                         B00111110,
                         B00111111,
                         B00111111,
                         B00111110,
                         B00101000,
                         B00101000,                        
                         // parte2
                         B00101000,
                         B00101000,
                         B00110000,
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000000, };                         



//boca dormindo (sorriso pequeno)
byte boca_dormindo[24] = { B00000000,
                           B00000000,
                           B00000000,
                           B00000000,
                           B00000000,
                           B00000000,
                           B00000000,
                           B00110000,
                         // parte1
                         B00110000,
                         B00010000,
                         B00011000,
                         B00011000,
                         B00011000,
                         B00011000,
                         B00010000,
                         B00110000,
                         // parte2
                         B00110000,
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000000,
                         B00000000 };

// boca aberta            //part 1
byte boca_aberta[24] = {   B00000000,
                           B00000000,
                           B00000000,
                           B00000000,
                           B00000000,
                           B00000000,
                           B00000000,
                           B00000000,
                           // part 2
                           B00000000,
                           B00011100,
                           B00100010,
                           B01000001,
                           B01000001,
                           B00100010,
                           B00011100,
                           B00000000,
                           // part 3
                           B00000000,
                           B00000000,
                           B00000000,
                           B00000000,
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
//      display_olhos(olho_dormindo, olho_dormindo);  //piscar olhos
      display_olhos(olho_dormindo, 0);  //piscar olhos
      display_olhos(olho_dormindo, 1);  //piscar olhos
      delay(200);
      restore();
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
      //realizar ações: expressões da face
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
        if(valor == 100) {
          fac10();
        }  
      }

      if(comando == "old") {
        if(valor == 10) {
          display_olhos(olho_neutro, 0);
          olho_direito = 1;
        }
        if(valor == 20) {
          display_olhos(olho_arregalado, 0);
          olho_direito = 2;
        }
        if(valor == 30) {
          display_olhos(olho_fechado, 0);
          olho_direito = 3;
        }
        if(valor == 40) {
          display_olhos(olho_dormindo, 0);
          olho_direito = 4;
        }
        if(valor == 50) {
          display_olhos(olho_x, 0);
          olho_direito = 5;
        }
      }
      
      if(comando == "ole") {
        if(valor == 10) {
          display_olhos(olho_neutro, 1);
          olho_esquerdo = 1;
        }
        if(valor == 20) {
          display_olhos(olho_arregalado, 1);
          olho_esquerdo = 2;
        }
        if(valor == 30) {
          display_olhos(olho_fechado, 1);
          olho_esquerdo = 3;          
        }
        if(valor == 40) {
          display_olhos(olho_dormindo, 1);
          olho_esquerdo = 4;          
        }
        if(valor == 50) {
          display_olhos(olho_x, 1);
          olho_esquerdo = 5;          
        }
      }
      
      if(comando == "boc") {
        if(valor == 10) {
          display_boca(boca_alegre);
          boca = 1;
        }
        if(valor == 20) {
          display_boca(aberta_alegre);
          boca = 2;
        }
        if(valor == 30) {
          display_boca(boca_triste);
          boca = 3;          
        }
        if(valor == 40) {
          display_boca(aberta_triste);
          boca = 4;          
        }
        if(valor == 50) {
          display_boca(boca_lingua);
          boca = 5;          
        }
        if(valor == 60) {
          display_boca(boca_aberta);
          boca = 6;          
        }
        if(valor == 70) {
          display_boca(boca_nojo);
          boca = 7;          
        }
        
      }
      //***************************************
      //realizar ações: alteração de velocidade
      //***************************************

      if(comando == "vel") {
        vel = valor;
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
/*void display_olhos(byte olho_direito[], byte olho_esquerdo[]) {
  for(int i=0;i<8;i++) {
   lc.setRow(0,i,olho_esquerdo[i]); //a função setRow roda mais rápido que a setColumn. Por isso, as faces são alteradas usando o setRow
   lc.setRow(1,i,olho_direito[i]); //a função setRow roda mais rápido que a setColumn. Por isso, as faces são alteradas usando o setRow
  } 
}*/

//alterar exibição dos olhos
void display_olhos(byte olho[], int posicao) {
  for(int i=0;i<8;i++) {
   lc.setRow(posicao,i,olho[i]); //a função setRow roda mais rápido que a setColumn. Por isso, as faces são alteradas usando o setRow
  } 
}


//alterar exibição da boca
void display_boca(byte boca[]) {
  for(int i=0;i<8;i++) {
    lc.setRow(2,i,boca[i]); //a função setRow roda mais rápido que a setColumn. Por isso, as faces são alteradas usando o setRow
    lc.setRow(3,i,boca[i+8]); //a função setRow roda mais rápido que a setColumn. Por isso, as faces são alteradas usando o setRow
    lc.setRow(4,i,boca[i+16]); //a função setRow roda mais rápido que a setColumn. Por isso, as faces são alteradas usando o setRow
  }
}


//movimento1 = levantar braço esquerdo
void mov1()
{
  pos2 = pos2max;
  s2.write(pos2);
  //realizar movimento
  while(pos1 != pos1min) {
    pos1 -= 1;
    s1.write(pos1);
    delay(100/vel);
    if (pos1 < pos1min) {
      pos1 = pos1min;
    }
  }
  //retornar para posição neutra
  pos_neutra();
}


//movimento2 = levantar braço direito
void mov2()
{
  pos4 = pos4min;
  s4.write(pos4);
  //realizar movimento
  while(pos3 != pos3max) {
    pos3 += 1;
    s3.write(pos3);
    delay(100/vel);
    if (pos3 > pos3max) {
      pos3 = pos3max;
    }
  }
  //retornar para posição neutra
  pos_neutra();
}


//movimento3 = levantar os dois braços
void mov3()
{
  pos2 = pos2max;
  pos4 = pos4min;
  s2.write(pos2);        
  s4.write(pos4);
  //realizar o movimento  
  while((pos1 != pos1min) || (pos3!= pos3max)) {
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
  //retornar para posição neutra
  pos_neutra();
}


//movimento4 = abaixar os dois braços
void mov4()
{  
  pos_neutra();  
}


//movimento5 = balançar os dois braços abertos
void mov5()
{
    //realizar movimento
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
    //retornar para posição neutra
    pos_neutra();
}


//movimento6 = balançar os dois braços na frente
void mov6()
{
    s1.write(pos1max);
    s2.write(pos2max);
    s3.write(pos3min);
    s4.write(pos4min);
    delay(500);

    //realizar os movimentos    
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
    //retornar para posiçao neutra
    pos_neutra();
}


//movimento7 = balançar os dois braços na frente
void mov7()
{
    while ((pos1 != 130) || (pos3 != 60))
    {
      pos1 -= 1;
      pos3 += 1;
      s1.write(pos1);
      s3.write(pos3);
      delay(100/vel);
      if (pos1 < 130) {
          pos1 = 130;
      }
      if (pos3 > 60) {
          pos3 = 60;
      }
    }
    while ((pos2 != 70) || (pos4 != 110))
    {
      pos2 -= 1;
      pos4 += 1;
      s2.write(pos2);
      s4.write(pos4);
      delay(100/vel);
      if (pos2 < 70) {
          pos2 = 70;
      }
      if (pos4 > 110) {
          pos4 = 110;
      }
    }
    delay(1000);
    while ((pos2 != pos2max) || (pos4 != pos4min))
    {
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
    //retornar para posição neutra
    pos_neutra();  
}


//movimento8 = girar os braços
void mov8()
{
    //abrir os braços
    while ((pos1 != 130) || (pos3 != 60))
    {
      pos1 -= 1;
      pos3 += 1;
      s1.write(pos1);
      s3.write(pos3);
      delay(100/vel);
      if (pos1 < 130) {
          pos1 = 130;
      }
      if (pos3 > 60) {
          pos3 = 60;
      }
    }
    pos2 = 140;
    pos4 = 40;
    s2.write(pos2);
    s4.write(pos4);
    float theta = 0;
    float thetar = 0;
    for (theta; theta < 720; theta++) {
      thetar = theta*3.14/180;
      s1.write(pos1 + 40*sin(thetar));
      s2.write(pos2 + 40*cos(thetar));
      s3.write(pos3 - 40*sin(thetar));
      s4.write(pos4 - 40*cos(thetar));
      delay(100/vel);
    }
    //retornar para posição neutra
    pos_neutra();
}


//movimento 9 = aceno
void mov9()
{  
    //realizar movimento
    //levantar o braço
    while(pos1!= pos1min) {
        pos1 -= 1;
        s1.write(pos1);
        delay(100/vel);
        if (pos1 < pos1min) {
          pos1 = pos1min;
        }
      }
    while(pos2 != (pos2max - 20)) {
        pos2 -= 1;
        s2.write(pos2);
        delay(100/vel);
    }  
    //acenar
    for(int k = 1; k < 5 ; k++) {
      while(pos1 != (pos1min + 30)) {
        pos1 += 1;
        s1.write(pos1);
        delay(100/vel);
      }
      while(pos1 != pos1min) {
        pos1 -= 1;
        s1.write(pos1);
        delay(100/vel);
      }
    }
    while(pos2 != pos2max) {
        pos2 += 1;
        s2.write(pos2);
        delay(100/vel);
    }  
    //retornar para posição neutra
    pos_neutra();  
}

//retornar para posição neutra dos braços
void pos_neutra()
{

  while((pos1 != pos1max)||(pos3 != pos3min)) {
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
  
  while((pos4 != pos4min)||(pos2 != pos2max)) {
    pos4 -= 1;
    pos2 += 1;
    s4.write(pos4);
    s2.write(pos2);
    delay(100/vel);
    if (pos4 < pos4min) {
      pos4 = pos4min;
    }
    if (pos2 > pos2max) {
      pos2 = pos2max;
    }
  }
}

//rosto feliz
void fac1()
{
  face = 1;
  olho_direito = 1;
  olho_esquerdo = 1;
  boca = 1;
  piscar = true;
  display_olhos(olho_neutro, 0);
  display_olhos(olho_neutro, 1);
  display_boca(boca_alegre);
}

//rosto muito feliz
void fac2()
{
  face = 2;
  piscar = true;
  olho_direito = 2;
  olho_esquerdo = 2;
  boca = 2;
  display_olhos(olho_arregalado, 0);
  display_olhos(olho_arregalado, 1);
  display_boca(aberta_alegre);
}

//rosto triste
void fac3()
{
  face = 3;
  piscar = true;
  olho_direito = 1;
  olho_esquerdo = 1;
  boca = 3;
  display_olhos(olho_neutro, 0);
  display_olhos(olho_neutro, 1);  
  display_boca(boca_triste);
}

//rosto muito triste
void fac4()
{
  face = 4;
  piscar = true;
  olho_direito = 2;
  olho_esquerdo = 2;
  boca = 4;
  display_olhos(olho_arregalado, 0);
  display_olhos(olho_arregalado, 1);  
  display_boca(aberta_triste);
}

//rosto com língua para fora
void fac5()
{
  face = 5;
  piscar = false;
  olho_direito = 3;
  olho_esquerdo = 3;  
  boca = 5;
  display_olhos(olho_fechado, 0);  
  display_olhos(olho_fechado, 1);  
  display_boca(boca_lingua);
}

//rosto morto
void fac6()
{
  face = 6;
  piscar = false;
  olho_direito = 5;
  olho_esquerdo = 5;
  boca = 3;
  display_olhos(olho_x, 0);  
  display_olhos(olho_x, 1);  
  display_boca(boca_triste);
}

//rosto assustado
void fac7()
{
  face = 7;
  piscar = true;
  olho_direito = 2;
  olho_esquerdo = 2;
  boca = 6;
  display_olhos(olho_arregalado, 0);  
  display_olhos(olho_arregalado, 1);  
  display_boca(boca_aberta);
}

//rosto dormindo
void fac8()
{
  face = 8;
  piscar = false;
  olho_direito = 4;
  olho_esquerdo = 4;  
  boca = 6;
  display_olhos(olho_dormindo, 0);  
  display_olhos(olho_dormindo, 1);  
  display_boca(boca_aberta);
}


//rosto nojo
void fac9()
{
  face = 9;
  piscar = true;
  olho_direito = 2;
  olho_esquerdo = 1;  
  boca = 7;
  display_olhos(olho_arregalado, 0);  
  display_olhos(olho_neutro, 1);
  display_boca(boca_nojo);
}

//falando
void fac10()
{
  display_boca(boca_falando);
  delay(100);
  display_boca(boca_neutra);
  delay(50);
  display_boca(boca_falando2);
  delay(100);
  display_boca(boca_neutra);
  delay(50);
  display_boca(boca_falando);
  delay(100);
  display_boca(boca_neutra);
  restore();
}

void restore()
{
        switch (olho_esquerdo){
        case 1:
          display_olhos(olho_neutro, 1);
          break;
        case 2:
          display_olhos(olho_arregalado, 1);
          break;
        case 3:
          display_olhos(olho_fechado, 1);
          break;
        case 4:
          display_olhos(olho_dormindo, 1);
          break;
        case 5:
          display_olhos(olho_x, 1);
          break;
        }  
        switch (olho_direito){
        case 1:
          display_olhos(olho_neutro, 0);
          break;
        case 2:
          display_olhos(olho_arregalado, 0);
          break;
        case 3:
          display_olhos(olho_fechado, 0);
          break;
        case 4:
          display_olhos(olho_dormindo, 0);
          break;
        case 5:
          display_olhos(olho_x, 0);
          break;
        }
      switch (boca){
        case 1:
          display_boca(boca_alegre);
          break;
        case 2:
          display_boca(aberta_alegre);
          break;
        case 3:
          display_boca(boca_triste);
          break;
        case 4:
          display_boca(aberta_triste);
          break;
        case 5:
          display_boca(boca_lingua);
          break;
        case 6:
          display_boca(boca_aberta);
          break;
        case 7:
          display_boca(boca_nojo);
          break;
        }
}
