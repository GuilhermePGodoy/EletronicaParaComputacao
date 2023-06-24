/* 
  Projeto criado para a disciplina Eletrônica para Computação
  Nome dos integrantes:
    Gabriel de Andrade Abreu - NUMUSP: 14571362
    Guilherme Pascoale Godoy - NUMUSP: 14576277 
    Isabela Beatriz Souza Nunes Farias - NUMUSP: 
*/
#include <LiquidCrystal.h>

#define botaoCima 8
#define botaoBaixo 9
#define botaoTiro 10

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
//display

int velocidadeJogo = 100;
int pontos, pxNave, pyNave, pxAsteroide, pyAsteroide, pxEnergia, pyEnergia, pxTiro, pyTiro;
bool game, temTiro, temPilha;
// game - esta pausado ou não
double venergia;
int vtela;
int maxpontos = 50;

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
  vtela = 0;

  lcd.createChar(1, nave);
  lcd.createChar(2, asteroide);
  lcd.createChar(3, explosao);
  lcd.createChar(4, energia);
  lcd.createChar(5, tiro);
  lcd.begin(16, 2);
  lcd.clear();
  game = false;
  temPilha = temPilha = false;
}

void loop() {
  //Verifica se o jogo está rodando ou não
  if(game){
    venergia -= 0.25;
    //Verifica se a energia acabou
    if(venergia <= 0){
      game = false;
      desenhaExplosaoNave(pxNave, pyNave);
      vtela = 2;
    }
    lcd.clear();
    painel(13);

    if(digitalRead(botaoCima) == 1){
      pyNave = 0;
    }
    if(digitalRead(botaoBaixo) == 1){
      pyNave = 1;
    }
    if(digitalRead(botaoTiro) == 1){
      pxTiro = 1;
      temTiro = true;
      pyTiro = pyNave;
    }
    //Altera a posição do asteroide a cada loop, para que ele se movimente para a esquerda;
    pxAsteroide -= 1;
    //Desenha a nave
    desenhaNave(pxNave, pyNave);
    //Desenha o asteroide
    desenhaAsteroide(pxAsteroide, pyAsteroide);]
    //Desenha o tiro, se houver algum na tela, e define seu movimento para a direita
    if(temTiro){
      desenhaTiro(pxTiro, pyTiro);
      pxTiro += 1;
    }
    //Define a nova posição do asteroide, quando este chega no limite do display
    if(pxAsteroide < 0){
      pxAsteroide = 12;
      pyAsteroide = random(0, 2);
    }
    //Faz o mesmo com a posição do tiro
    if(pxTiro > 16){
      temTiro = false;
      pxTiro = -1;
    }
    //Implementa as colisões dos tiros com os asteroides
    if(((pxTiro == pxAsteroide) && (pyTiro == pyAsteroide)) || ((pxTiro == pxAsteroide + 1)&&(pyTiro == pyAsteroide))){
      temTiro = false;
      pxTiro = -1;
      desenhaExplosaoAsteroide(pxAsteroide, pyAsteroide);
      pyAsteroide = random(0, 2);
      pxAsteroide = 12;
      pontos += 2;
      //Verifica se o jogador atingiu a posição máxima
      if(pontos >= maxpontos){
        game = false;
        vtela = 1;
      }
    }
    //Implementa a colisão de asteroide com a nave
    if((pxNave == pxAsteroide) && (pyNave == pyAsteroide)){
      game = false;
      desenhaExplosaoNave(pxNave, pyNave);
      vtela = 2;
    }
    //Sorteia o aparecimento ou não de uma pilha
    if(temPilha == false){
      if(random(0, 60) > 58){
        pxEnergia = 12;
        temPilha = true;
        pyEnergia = random(0, 2);
      }
    }
    else{
      pxEnergia -= 1;
      desenhaEnergia(pxEnergia, pyEnergia);
      //Verifica a colisão da pilha com a nave
      if(((pxNave == pxEnergia + 1) && (pyNave == pyEnergia)) || ((pxNave == pxEnergia) && (pyNave == pyEnergia))){
        temPilha = false;
        pxEnergia = -1;
        venergia = 100;
      }
    }
    delay(velocidadeJogo);
  }
  else{
    tela(vtela);
    if(digitalRead(botaoTiro)==1){
      reset();
    }
  }
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
  vtela = 0;
}

void painel(int px){
  lcd.setCursor(px, 0);
  lcd.print(pontos);
  lcd.setCursor(px, 1);
  lcd.print(venergia);
}

void tela(int condicao){
  // 0 = tela inicial | 1 = ganhou | 2 = perdeu
  if(condicao < 1){
    lcd.setCursor(4,0);
    lcd.print("BCC  023");
    lcd.setCursor(0, 1);
    lcd.print("Pressione Tiro");
  }
  else{
  char texto[6];
  if(condicao > 1){
    texto[6] = "PERDEU";
  } else{
    texto[6] = "GANHOU";
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
}
