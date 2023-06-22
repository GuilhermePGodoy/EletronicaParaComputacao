/* 
  Projeto criado para a disciplina eletrônica para computação
  Nome dos integrantes:
    Gabriel de Andrade Abreu - NUMUSP: 14571362
    Guilherme - NUMUSP: 
    Isabela Beatriz Souza Nunes Farias - NUMUSP: 
*/
#include <LiquidCrystal.h>

#define botaoCima 8
#define botaobaixo 9
#define botaoTiro 10

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
//display

int velocidadeJogo = 100;
int pontos, pxNave, pyNave, pxAsteroide, pyAsteroide, pxEnergia, pyEnergia, pxTiro, pyTiro;
bool game, temTiro, temPilha;
// game - esta pausado ou não
double venergia;

/* definicao da imagem dos objetos: */

byte nave[8] = {
  B11000, B01100, B01110, B01111, B01111, B01110, B01100, B11000
};

byte asteroide[8] = {
  B00000, B00100, B01110, B10111, B11101, B01110, B00000, B00000
};

byte explosao[8] = {
  B10001, B10101, B01010, B10100, B00101, B01010, B10101, B10001
};

byte energia[8] = {
  B01110, B11011, B10001, B10001, B10001, B10001, B10001, B11111
};

byte tiro[8] = {
  B00000, B00000, B00000, B00111, B00111, B00000, B00000, B00000
};

void setup() {
  //definição da posição e do valor inicial de cada variavel
  pontos = pxNave = pyNave = pyAsteroide = pxEnergia = pyEnergia = pyTiro = 0;
  pxTiro = -1;
  pxAsteroide = 12;
  venergia = 100;

  lcd.createChar(1, nave);
  lcd.createChar(2, asteroide);
  lcd.createChar(3, explosao);
  lcd.createChar(4, energia);
  lcd.createChar(5, tiro);
  lcd.begin(16, 2);
  lcd.clear();
  game = true;
  temPilha = temPilha = false;
}

void loop() {
  
}

void desenhaNave(int px, int py){
  lcd.setCursor(px, py);
  lcd.write(1);
}

void desenhaAsteroide(int px, int py){
  lcd.setCursor(px, py);
  lcd.write(2);
}

void desenhaEnergia(int px, int py){
  lcd.setCursor(px, py);
  lcd.write(4);
}

void desenhaTiro(int px, int py){
  lcd.setCursor(px, py);
  lcd.write(5);
}

void desenhaExplosaoNave(int px, int py){
  lcd.clear();
  lcd.setCursor(px, py);
  lcd.write(3);
  delay(1000);
  lcd.clear();
}

void desenhaExplosaoAsteroide(int px, int py){
  lcd.setCursor(px, py);
  lcd.write(3);
  delay(1000);
  lcd.clear();
}

void reset(){
  pontos = 0;
  venergia = 100;
  game = true;
}

void painel(int px){
  lcd.setCursor(px, 0);
  lcd.print(pontos);
  lcd.setCursor(px, 1);
  lcd.print(venergia);
}

void tela(int condicao){
  // ganhou = 1, oerdeu = 0
  char texto[6];
  if(condicao > 0){
    texto[6] = "GANHOU";
  } else{
    texto[6] = "PERDEU";
  }
  
  lcd.setCursor(9, 0);
  lcd.print("pts: ");
  lcd.setCursor(13, 0);
  lcd.print(pontos);
  lcd.setCursor(1, 0);
  lcd.print(texto);
  lcd.setCursor(0, 1);
  lcd.print("Pressione Tiro");
}