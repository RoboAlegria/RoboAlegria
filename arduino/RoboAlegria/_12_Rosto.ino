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
    lc.setRow(2,i,boca[i]); //a função setRow roda mais rápido que a setColumn. Por isso, as faces são alteradas usando o setRow
    lc.setRow(3,i,boca[i+8]); //a função setRow roda mais rápido que a setColumn. Por isso, as faces são alteradas usando o setRow
    lc.setRow(4,i,boca[i+16]); //a função setRow roda mais rápido que a setColumn. Por isso, as faces são alteradas usando o setRow
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
