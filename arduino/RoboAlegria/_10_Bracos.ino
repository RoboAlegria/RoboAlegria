//***********************************
//Definição dos movimentos dos braços
//***********************************

//movimento1 = levantar braço esquerdo
void mov1()
{
  //realizar movimento
  while(pos3 != pos3min) {
    pos3 -= 1;
    pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos3 < pos3min) {
      pos3 = pos3min;
    }
  }
  delay(100);
  while(pos3 != pos3max) {
    pos3 += 1;
    pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos3 > pos3max) {
      pos3 = pos3max;
    }
  }
}


//movimento2 = levantar braço direito
void mov2()
{
  //realizar movimento
  while(pos1 != pos1max) {
    pos1 += 1;
    pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos1 > pos1max) {
      pos1 = pos1max;
    }
  }
  delay(100);
  while(pos1 != pos1min) {
    pos1 -= 1;
    pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos1 < pos1min) {
      pos1 = pos1min;
    }
  }
}


//movimento3 = levantar os dois braços
void mov3()
{
  //realizar movimento
  while((pos1 != pos1max)||(pos3 != pos3min)) {
    pos3 -= 1;
    pos1 += 1;
    pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));
    pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos3 < pos3min) {
      pos3 = pos3min;
    }
    if (pos1 > pos1max) {
      pos1 = pos1max;
    }
  }
  delay(100);
  while((pos1 != pos1min)||(pos3 != pos3max)) {
    pos3 += 1;
    pos1 -= 1;
    pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));;
    pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos3 > pos3max) {
      pos3 = pos3max;
    }
    if (pos1 < pos1min) {
      pos1 = pos1min;
    }
  }
}


//movimento4 = não
void mov4()
{  
  for(int k = 0; k < 3 ; k++) {
  //realizar movimento
  while((pos5 != pos5min + 40)) {
    pos5 -= 1;
    pwm.setPWM(4, 0, map(pos5, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos5 < pos5min + 40) {
      pos5 = pos5min + 40;
    }
  }
  while((pos5 != pos5max - 40)) {
    pos5 += 1;
    pwm.setPWM(4, 0, map(pos5, 0, 180, SERVOMIN, SERVOMAX));;
    delay(100/vel);
    if (pos5 > pos5max - 40) {
      pos5 = pos5max - 40;
    }
  }
  }

  while((pos5 != 77)) {
    pos5 -= 1;
    pwm.setPWM(4, 0, map(pos5, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos5 < 77) {
      pos5 = 77;
    }
  }  
}


//movimento5 = balançar os dois braços abertos
void mov5()
{
    for(int k = 0; k < 3 ; k++) {
  //realizar movimento
  while((pos1 != pos1max)||(pos3 != pos3min)) {
    pos3 -= 1;
    pos1 += 1;
    pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));
    pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos3 < pos3min) {
      pos3 = pos3min;
    }
    if (pos1 > pos1max) {
      pos1 = pos1max;
    }
  }
  delay(100);
  while((pos1 != pos1min)||(pos3 != pos3max)) {
    pos3 += 1;
    pos1 -= 1;
    pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));;
    pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos3 > pos3max) {
      pos3 = pos3max;
    }
    if (pos1 < pos1min) {
      pos1 = pos1min;
    }
  }
}
}


//movimento6 = balançar os dois braços na frente
void mov6()
{
    //realizar os movimentos    
    for(int k = 0; k < 3 ; k++) {
      while((pos2 != pos2min)&& (pos4!= pos4max)) {
        pos2 -= 1;
        pos4 += 1;
        pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
        pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
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
        pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
        pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
        if (pos2 > pos2max) {
          pos2 = pos2max;
        }
        if (pos4 < pos4min) {
          pos4 = pos4min;
        }
      }
    }
      while((pos2 != 40) && (pos4!= 130)) {
        pos2 -= 1;
        pos4 += 1;
        pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
        pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
        if (pos2 < pos2min) {
          pos2 = pos2min;
        }
        if (pos4 > pos4max) {
          pos4 = pos4max;
        }
      }
}


//movimento7 = balançar os dois braços na frente
void mov7()
{
    //realizar os movimentos    
    for(int k = 0; k < 3 ; k++) {
      while((pos2 != pos2min)&& (pos4!= pos4min)) {
        pos2 -= 1;
        pos4 -= 1;
        pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
        pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
        if (pos2 < pos2min) {
          pos2 = pos2min;
        }
        if (pos4 < pos4min) {
          pos4 = pos4min;
        }
      }
      while((pos2 != pos2max)&& (pos4!= pos4max)) {
        pos2 += 1;
        pos4 += 1;
        pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
        pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
        if (pos2 > pos2max) {
          pos2 = pos2max;
        }
        if (pos4 > pos4max) {
          pos4 = pos4max;
        }
      }
    }
      while((pos2 != 40) && (pos4!= 130)) {
        pos2 -= 1;
        pos4 -= 1;
        pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
        pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
        if (pos2 < pos2min) {
          pos2 = pos2min;
        }
        if (pos4 < pos4min) {
          pos4 = pos4max;
        }
      }
}


//movimento8 = girar os braços
void mov8()
{
 for(int k = 0; k < 3 ; k++) {
  //realizar movimento
  while((pos6 != pos6min)) {
    pos6 -= 1;
    pwm.setPWM(5, 0, map(pos6, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos6 < pos6min) {
      pos6 = pos6min;
    }
  }
  while((pos6 != pos6max)) {
    pos6 += 1;
    pwm.setPWM(5, 0, map(pos6, 0, 180, SERVOMIN, SERVOMAX));;
    delay(100/vel);
    if (pos6 > pos6max) {
      pos6 = pos6max;
    }
  }
  }

  while((pos6 != 40)) {
    pos6 -= 1;
    pwm.setPWM(5, 0, map(pos6, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos6 < 40) {
      pos6 = 40;
    }
  }
  
}


//movimento 9 = aceno
void mov9()
{  
    //realizar movimento
    //levantar o braço
    while(pos2!= pos2max) {
        pos2 += 1;
        pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
        if (pos2 > pos2max) {
          pos2 = pos2max;
        }
      }
    //acenar
    for(int k = 1; k < 5 ; k++) {
      while(pos1 != (pos1max - 50)) {
        pos1 += 1;
        pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
      }
      while(pos1 != pos1min) {
        pos1 -= 1;
        pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
      }
    }
    while(pos2 != 40) {
        pos2 -= 1;
        pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
        if (pos2 < pos2min) {
          pos2 = pos2min;
        }
    }  
}
