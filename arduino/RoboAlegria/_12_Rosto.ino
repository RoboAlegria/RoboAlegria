//********************
//Definição dos rostos
//********************

//alterar exibição dos olhos
void display_olhos(byte olho[], int posicao) {
  for(int i=0;i<8;i++) {
   lc.setRow(posicao,i,olho[i]); //a função setRow roda mais rápido que a setColumn. Por isso, as faces são alteradas usando o setRow
  } 
}

//alterar exibição da boca
void display_boca(byte boca[]) {
  for(int i=0;i<8;i++) {
    lc.setRow(0,i,boca[i]); //a função setRow roda mais rápido que a setColumn. Por isso, as faces são alteradas usando o setRow
    lc.setRow(3,i,boca[i+8]); //a função setRow roda mais rápido que a setColumn. Por isso, as faces são alteradas usando o setRow
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
  display_olhos(olho_neutro_d, 1);
  display_olhos(olho_neutro_e, 2);
  display_boca(boca_alegre);
}

//rosto muito feliz
void fac2()
{
  face = 2;
  piscar = true;
  olho_direito = 1;
  olho_esquerdo = 1;
  boca = 2;
  display_olhos(olho_neutro_d, 1);
  display_olhos(olho_neutro_e, 2);
  display_boca(boca_muito_feliz);
}

//rosto triste
void fac3()
{
  face = 3;
  piscar = true;
  olho_direito = 6;
  olho_esquerdo = 6;
  boca = 3;
  display_olhos(olho_triste_d, 1);
  display_olhos(olho_triste_e, 2);  
  display_boca(boca_triste);
}

//rosto muito triste
void fac4()
{
  face = 4;
  piscar = true;
  olho_direito = 6;
  olho_esquerdo = 6;
  boca = 4;
  display_olhos(olho_triste_d, 1);
  display_olhos(olho_triste_e, 2);  
  display_boca(boca_muito_triste);
}

//rosto com língua para fora
void fac5()
{
  face = 5;
  piscar = false;
  olho_direito = 3;
  olho_esquerdo = 3;  
  boca = 5;
  display_olhos(olho_fechado_cima_d, 1);  
  display_olhos(olho_fechado_cima_e, 2);  
  display_boca(boca_lingua);
}

//rosto morto
void fac6()
{
  face = 6;
  piscar = false;
  olho_direito = 5;
  olho_esquerdo = 5;
  boca = 7;
  display_olhos(olho_morto_d, 1);  
  display_olhos(olho_morto_e, 2);  
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
  display_olhos(olho_arregalado_d, 1);  
  display_olhos(olho_arregalado_e, 2);  
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
  display_olhos(olho_fechado_baixo_d, 1);  
  display_olhos(olho_fechado_baixo_e, 2);  
  display_boca(boca_aberta);
}


//rosto confuso
void fac9()
{
  face = 9;
  piscar = true;
  olho_direito = 2;
  olho_esquerdo = 1;  
  boca = 7;
  display_olhos(olho_arregalado_d, 1);  
  display_olhos(olho_neutro_e, 2);
  display_boca(boca_neutra);
}

//rosto entediado
void fac10()
{
  face = 10;
  piscar = true;
  olho_direito = 7;
  olho_esquerdo = 7;  
  boca = 7;
  display_olhos(olho_entediado_d, 1);  
  display_olhos(olho_entediado_e, 2);
  display_boca(boca_neutra);
}

//rosto apaixonado
void fac11()
{
  face = 11;
  piscar = true;
  olho_direito = 9;
  olho_esquerdo = 9;  
  boca = 1;
  display_olhos(olho_apaixonado_d, 1);  
  display_olhos(olho_apaixonado_e, 2);
  display_boca(boca_alegre);
}

//rosto nojo
void fac12()
{
  face = 12;
  piscar = true;
  olho_direito = 1;
  olho_esquerdo = 1; 
  boca = 8;
  display_olhos(olho_neutro_d, 1);  
  display_olhos(olho_neutro_e, 2);
  display_boca(boca_nojo);
}

//rosto raiva
void fac13()
{
  face = 13;
  piscar = true;
  olho_direito = 8;
  olho_esquerdo = 8;  
  boca = 3;
  display_olhos(olho_raiva_d, 1);  
  display_olhos(olho_raiva_e, 2);
  display_boca(boca_triste);
}


//falando
void fac14()
{
  if ((boca==1) || (boca==2) || (boca==5) || (boca==7)) {
    display_boca(boca_alegre);
    delay(100);
    display_boca(boca_muito_feliz);
    delay(100);
    display_boca(boca_alegre);
    delay(100);
    display_boca(boca_neutra);
    delay(100);
    display_boca(boca_alegre);
    delay(100);
    display_boca(boca_muito_feliz);
    delay(100);
    restore();
  }
  else {
    display_boca(boca_triste);
    delay(100);
    display_boca(boca_muito_triste);
    delay(100);
    display_boca(boca_triste);
    delay(100);
    display_boca(boca_neutra);
    delay(100);
    display_boca(boca_triste);
    delay(100);
    display_boca(boca_muito_triste);
    delay(100);
    restore();    
  }
}

void restore()
{
        switch (olho_esquerdo){
          case 1:
            display_olhos(olho_neutro_e, 2);
            break;
          case 2:
            display_olhos(olho_arregalado_e, 2);
            break;
          case 3:
            display_olhos(olho_fechado_cima_e, 2);
            break;        
          case 4:
            display_olhos(olho_fechado_baixo_e, 2);
            break;
          case 5:
            display_olhos(olho_morto_e, 2);
            break;
          case 6:
            display_olhos(olho_triste_e, 2);
            break;
          case 7:
            display_olhos(olho_entediado_e, 2);
            break;
          case 8:
            display_olhos(olho_raiva_e, 2);
            break;
          case 9:
            display_olhos(olho_apaixonado_e, 2);
            break;
        }
          
        switch (olho_direito){
          case 1:
            display_olhos(olho_neutro_d, 1);
            break;
          case 2:
            display_olhos(olho_arregalado_d, 1);
            break;
          case 3:
            display_olhos(olho_fechado_cima_d, 1);
            break;
          case 4:
            display_olhos(olho_fechado_baixo_d, 1);
            break;
          case 5:
            display_olhos(olho_morto_d, 1);
            break;
          case 6:
            display_olhos(olho_triste_d, 1);
            break;
          case 7:
            display_olhos(olho_entediado_d, 1);
            break;
          case 8:
            display_olhos(olho_raiva_d, 1);
            break;           
          case 9:
            display_olhos(olho_apaixonado_d, 1);
            break;
        }
      switch (boca){
        case 1:
          display_boca(boca_alegre);
          break;
        case 2:
          display_boca(boca_muito_feliz);
          break;
        case 3:
          display_boca(boca_triste);
          break;
        case 4:
          display_boca(boca_muito_triste);
          break;
        case 5:
          display_boca(boca_lingua);
          break;
        case 6:
          display_boca(boca_aberta);
          break;
        case 7:
          display_boca(boca_neutra);
          break;
        case 8:
          display_boca(boca_nojo);
          break;          
          
        }
}
