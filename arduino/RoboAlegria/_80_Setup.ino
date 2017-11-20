//************************
//inicialização do Arduino
//************************
void setup()
{
  //inicialização dos displays (configurar intensidade e zerar os displays)
  lc.shutdown(0, false);
  lc.setIntensity(0, 1);
  lc.clearDisplay(0);
  lc.shutdown(1, false);
  lc.setIntensity(1, 1);
  lc.clearDisplay(1);
  lc.shutdown(2, false);
  lc.setIntensity(2, 1);
  lc.clearDisplay(2);
  lc.shutdown(3, false);
  lc.setIntensity(3, 1);
  lc.clearDisplay(3);
  lc.shutdown(4, false);
  lc.setIntensity(4, 1);
  lc.clearDisplay(4);

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  //manter o rosto dormindo durante a inicialização (até conectar com o wifi)
  fac8();

  //inicialização dos braços
  pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
  pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
  pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));
  pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
  pwm.setPWM(4, 0, map(pos5, 0, 180, SERVOMIN, SERVOMAX));
  pwm.setPWM(5, 0, map(pos6, 0, 180, SERVOMIN, SERVOMAX));
  
  //inicialização da comunicação serial
  Serial.begin(9600);
  esp8266.begin(19200);

  sendData("AT+RST\r\n", 2000, DEBUG); //resetar módulo
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); //setar modo station
  sendData("AT+CWJAP=\"Connectify-me\",\"12345678\"\r\n", 2000, DEBUG);   //conectar com a rede wifi
  while (!esp8266.find("OK")) { //aguardar estabelecer conexão
  }
  
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG); //configura para multiplas conexões
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // Inicia o web server na porta 80
  sendData("AT+CIFSR\r\n", 1000, DEBUG); //mostrar endereco IP

  //ativar rosto alegre após conexão com o wifi
  fac1();

  //inicializar timer
  tempo0 = millis();
}
