//*******************************
//Definição das imagens dos olhos
//*******************************

//olho morto
byte olho_x[8] = { B00000000,
                   B01000010,
                   B01100110,
                   B00011100,
                   B00011000,
                   B01100110,
                   B01000010,
                   B00000000};

//olho interrogação (obsoleto)
byte olho_int[8] = {B00011000,
                    B00100100,
                    B00000100,
                    B00000100,
                    B00001000,
                    B00010000,
                    B00000000,
                    B00010000};

//olho neutro                   
byte olho_neutro[8] = {B00000000,
                       B00000000,
                       B00111100,
                       B01111110,
                       B01111110,
                       B00111100,
                       B00000000,
                       B00000000};

//olho arregalado
byte olho_arregalado[8] = {B00000000,
                           B00000000,
                           B01111110,
                           B11111111,
                           B11111111,
                           B01111110,
                           B00000000,
                           B00000000};

//olho fechado (para cima)
byte olho_fechado[8] = {B00000000,
                        B00001100,
                        B00011100,
                        B00011000,
                        B00011000,
                        B00011100,
                        B00001100,
                        B00000000};
                        
//olho fechado (para baixo)
byte olho_dormindo[8] = {B00000000,
                         B00011000,
                         B00011000,
                         B00001100,
                         B00001100,
                         B00011000,
                         B00011000,
                         B00000000};
