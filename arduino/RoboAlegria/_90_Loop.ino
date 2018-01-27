//*************************
//Loop principal do Arduino
//*************************
void loop()
{
  int delta = millis() - tempo0;
  if(delta > 3000) {              //se o tempo for superior a 10 segundos
    if(piscar == true) {
//    display_olhos(olho_dormindo, olho_dormindo);  //piscar olhos
      display_olhos(olho_fechado_baixo_e, 2);  //piscar olhos
      display_olhos(olho_fechado_baixo_d, 1);  //piscar olhos
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
         //avançar até o ângulo desejado
         while(pos1 != valor) {
           if (pos1 > valor) {
             pos1 -= 1;
             pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
           if (pos1 < valor) {
             pos1 += 1;
             pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
         }
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
         while(pos2 != valor) {
           if (pos2 > valor) {
             pos2 -= 1;
             pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
           if (pos2 < valor) {
             pos2 += 1;
             pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
         }   
      }
      
      //mover o servo3 no angulo recebido em valor
      if(comando == "sr3") {
         //limitar o angulo de entrada
         valor = 180 - valor;
         if (valor >= pos3max) {
           valor = pos3max;
         }
         if (valor <= pos3min) {
           valor = pos3min;
         }
         while(pos3 != valor) {
           if (pos3 > valor) {
             pos3 -= 1;
             pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
           if (pos3 < valor) {
             pos3 += 1;
             pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
         }   
      }
      
      //mover o servo4 no angulo recebido em valor
      if(comando == "sr4") {
         valor = 180 - valor;
         //limitar o angulo de entrada
         if (valor >= pos4max) {
           valor = pos4max;
         }
         if (valor <= pos4min) {
           valor = pos4min;
         }        
         while(pos4 != valor) {
           if (pos4 > valor) {
             pos4 -= 1;
             pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
           if (pos4 < valor) {
             pos4 += 1;
             pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
         }       
      }

      //mover o servo5 no angulo recebido em valor
      if(comando == "sr5") {
         //limitar o angulo de entrada
         if (valor >= pos5max) {
           valor = pos5max;
         }
         if (valor <= pos5min) {
           valor = pos5min;
         }        
         while(pos5 != valor) {
           if (pos5 > valor) {
             pos5 -= 1;
             pwm.setPWM(4, 0, map(pos5, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
           if (pos5 < valor) {
             pos5 += 1;
             pwm.setPWM(4, 0, map(pos5, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
         }       
      }

      //mover o servo6 no angulo recebido em valor
      if(comando == "sr6") {
         valor = 180 - valor;
         //limitar o angulo de entrada
         if (valor >= pos6max) {
           valor = pos6max;
         }
         if (valor <= pos6min) {
           valor = pos6min;
         }        
         while(pos6 != valor) {
           if (pos6 > valor) {
             pos6 -= 1;
             pwm.setPWM(5, 0, map(pos6, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
           if (pos6 < valor) {
             pos6 += 1;
             pwm.setPWM(5, 0, map(pos6, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
         }       
      }


      //**************************************
      //realizar ações: movimentos programados
      //**************************************

      if(comando == "mov") {

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

      }
      
      //**********************************
      //realizar ações: expressões da face
      //**********************************

      if(comando == "fac") {
        if(valor == 10) {
          fac1(); //feliz
        }
        if(valor == 20) {
          fac2(); //muito feliz
        }
        if(valor == 30) {
          fac3(); //triste
        }
        if(valor == 40) {
          fac4(); //muito triste
        }
        if(valor == 50) {
          fac5(); //língua para fora
        }
        if(valor == 60) {
          fac6(); //morto
        }
        if(valor == 70) {
          fac7(); //assustado
        }
        if(valor == 80) {
          fac8(); //dormindo
        }
        if(valor == 90) {
          fac9(); //confuso
        }
        if(valor == 100) {
          fac10(); //entediado
        }  
        if(valor == 110) {
          fac11(); //apaixonado
        }  
        if(valor == 120) {
          fac12(); //nojo
        }  
        if(valor == 130) {
          fac13(); //raiva
        }
        if(valor == 140) {
          fac14(); //falando
        } 
      }

      if(comando == "old") {
        if(valor == 10) {
          display_olhos(olho_neutro_d, 1);
          olho_direito = 1;
        }
        if(valor == 20) {
          display_olhos(olho_arregalado_d, 1);
          olho_direito = 2;
        }
        if(valor == 30) {
          display_olhos(olho_fechado_cima_d, 1);
          olho_direito = 3;
        }
        if(valor == 40) {
          display_olhos(olho_fechado_baixo_d, 1);
          olho_direito = 4;
        }
        if(valor == 50) {
          display_olhos(olho_morto_d, 1);
          olho_direito = 5;
        }
        if(valor == 60) {
          display_olhos(olho_triste_d, 1);
          olho_direito = 6;
        }
        if(valor == 70) {
          display_olhos(olho_entediado_d, 1);
          olho_direito = 7;
        }
        if(valor == 80) {
          display_olhos(olho_raiva_d, 1);
          olho_direito = 8;
        }
        if(valor == 90) {
          display_olhos(olho_apaixonado_d, 1);
          olho_direito = 9;
        }
      }
      
      if(comando == "ole") {
        if(valor == 10) {
          display_olhos(olho_neutro_e, 2);
          olho_esquerdo = 1;
        }
        if(valor == 20) {
          display_olhos(olho_arregalado_e, 2);
          olho_esquerdo = 2;
        }
        if(valor == 30) {
          display_olhos(olho_fechado_cima_e, 2);
          olho_esquerdo = 3;          
        }
        if(valor == 40) {
          display_olhos(olho_fechado_baixo_e, 2);
          olho_esquerdo = 4;          
        }
        if(valor == 50) {
          display_olhos(olho_morto_e, 2);
          olho_esquerdo = 5;          
        }
        if(valor == 60) {
          display_olhos(olho_triste_e, 2);
          olho_esquerdo = 6;          
        }
        if(valor == 70) {
          display_olhos(olho_entediado_e, 2);
          olho_esquerdo = 7;          
        }
        if(valor == 80) {
          display_olhos(olho_raiva_e, 2);
          olho_esquerdo = 8;          
        }                        
        if(valor == 90) {
          display_olhos(olho_apaixonado_e, 2);
          olho_esquerdo = 9;          
        }
      }
      
      if(comando == "boc") {
        if(valor == 10) {
          display_boca(boca_alegre);
          boca = 1;
        }
        if(valor == 20) {
          display_boca(boca_muito_feliz);
          boca = 2;
        }
        if(valor == 30) {
          display_boca(boca_triste);
          boca = 3;          
        }
        if(valor == 40) {
          display_boca(boca_muito_triste);
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
          display_boca(boca_neutra);
          boca = 7;          
        }
        if(valor == 80) {
          display_boca(boca_neutra);
          boca = 8;          
        }
        if(valor == 90) {
          display_boca(boca_nojo);
          boca = 9;          
        }

        
      }
      //***************************************
      //realizar ações: alteração de velocidade
      //***************************************

      if(comando == "vel") {
        vel = valor;
      }


      //**********************************
      //movimentar os motores DC
      //**********************************

      if(comando == "mot") {
        if(valor == 10) {
          mot1(); //movimentar para a frente
        }
        if(valor == 20) {
          mot2(); //movimentar para a direita
        }
        if(valor == 30) {
          mot3(); //movimentar para a esquerda
        }
        if(valor == 40) {
          mot4(); //movimentar para tras
        }
      }

      
    }
  }
}
