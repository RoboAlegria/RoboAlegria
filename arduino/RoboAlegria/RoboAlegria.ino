// Robô da Alegria v1.0 By Igor Fonseca Albuquerque

//**********************************
//Inicialização de variávies globais
//**********************************


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
