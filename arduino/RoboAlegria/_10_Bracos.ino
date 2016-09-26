//***********************************
//Definição dos movimentos dos braços
//***********************************

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
