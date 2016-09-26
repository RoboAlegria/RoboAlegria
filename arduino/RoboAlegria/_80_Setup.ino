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
  sendData("AT+CWJAP=\"Connectify-me\",\"12345678\"\r\n", 2000, DEBUG);   //conectar com a rede wifi
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
