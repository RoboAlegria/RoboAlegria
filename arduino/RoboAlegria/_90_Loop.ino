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
    }
  }
}
