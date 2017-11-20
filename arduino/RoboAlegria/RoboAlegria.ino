// Robô da Alegria v2.0
//By Igor Fonseca Albuquerque
//   Thiago Ferrauche
//   Yhan Christian
//   Paulo de Azevedo Jr.

//**********************************
//Inicialização de variávies globais
//**********************************

//incluir bibliotecas
#include <SoftwareSerial.h>
#include <Servo.h>
#include "LedControl.h"

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

LedControl lc = LedControl(9,10,11,4); //Pinos 9 (DIN), 10 (CLK), 11 (CS), 4 displays a serem controlados
SoftwareSerial esp8266(5, 4); //RX pino 5, TX pino 4

//definição de variáveis 
#define DEBUG true //exibir mensagens trocadas entre o ESP8266 e o arduino na porta Serial

int pos1 = 30; //ângulo atual do servo 1
int pos2 = 40; //ângulo atual do servo 2
int pos3 = 135; //ângulo atual do servo 3
int pos4 = 130; //ângulo atual do servo 4
int pos5 = 77; //ângulo atual do servo 5
int pos6 = 40; //ângulo atual do servo 6
int vel = 10; //velocidade dos servos (100 -> 90º em 1 s)(1 -> 90º em 9 s)
int pos1min = 20; //ângulo mínimo do servo 1
int pos2min = 10; //ângulo mínimo do servo 2
int pos3min = 42; //ângulo mínimo do servo 3
int pos4min = 10; //ângulo mínimo do servo 4
int pos5min = 30; //ângulo mínimo do servo 5
int pos6min = 26; //ângulo mínimo do servo 6
int pos1max = 115; //ângulo máximo do servo 1
int pos2max = 170; //ângulo máximo do servo 2
int pos3max = 136; //ângulo máximo do servo 3
int pos4max = 170; //ângulo máximo do servo 4
int pos5max = 150; //ângulo máximo do servo 5
int pos6max = 50; //ângulo máximo do servo 6
int face; //número da face atual
int olho_direito; //número do olho direito atual
int olho_esquerdo; //número do olho esquerdo atual
int boca; //número da boca atual
boolean piscar; //definir se deve ou não piscar os olhos
unsigned long tempo0; //tempo para piscar os olhos
