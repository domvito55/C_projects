#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*tamanho inicial da cobra*/
#define TAM_INICIAL 3

typedef struct tipocoordenada
{
int x;
int y;
}tipocoordenada;

typedef struct tipocelula
{
tipocoordenada coordenada;
struct tipocelula *anterior;
struct tipocelula *proximo;
}tipocelula;

typedef struct tipocobra
{
struct tipocelula *cabeca;
struct tipocelula *rabo;
}tipocobra;

// sorteia um inteiro entre minimo e maximo (inclusive)
int sorteio(int minimo,int maximo)
{
int val;
val = minimo + (rand() % (maximo-minimo+1));
return val;
}

int fim_de_jogo(void)
{
int pontos, i,y;

clear();
y = (LINES/2) - 2;
move(y++,(COLS-15)/2); for(i=0;i<15;i++) addch('*');
move(y++,(COLS-15)/2); addstr("* FIM DE JOGO *");
move(y++,(COLS-15)/2); printw("* %4d pontos *",pontos);
move(y,(COLS-15)/2); for(i=0;i<15;i++) addch('*');
move(y+2,(COLS-11)/2); addstr("Tecle  Algo");
move(LINES-1,COLS-1);
refresh();

// espera uma tecla ser pressionada
do y = getch(); while(y==ERR);
return 0;
}



/*================================insere nova celula na cobra================================================*/
int insere(int *tam_cobra, tipocobra *cobra, tipocoordenada cnc/*coordenada da nova celula*/)
{
cobra->rabo->proximo = (tipocelula*) malloc(sizeof(tipocelula));
cobra->rabo->proximo->anterior = (tipocelula*) malloc(sizeof(tipocelula));

cobra->rabo->proximo->anterior = cobra->rabo;
cobra->rabo = cobra->rabo->proximo;
cobra->rabo->anterior->proximo = cobra->rabo;
cobra->rabo->proximo = (tipocelula*) malloc(sizeof(tipocelula));

cobra->rabo->coordenada = cnc;

(*tam_cobra)++;

return 0;
}

int cria(tipocobra *cobra)
{
int i;
int tam_cobra = 1;
tipocoordenada cci/*coordenadas das celulas iniciais*/;

cobra->cabeca = (tipocelula*) malloc(sizeof(tipocelula));
cobra->rabo = cobra->cabeca;

cobra->cabeca->coordenada.x = (COLS/2);
cobra->cabeca->coordenada.y = (LINES/2);
cobra->cabeca->proximo = NULL;
cobra->cabeca->anterior = (tipocelula*) malloc(sizeof(tipocelula));


for(i=1; i<TAM_INICIAL; i++)
   {
   cci.x = (cobra->rabo->coordenada.x)-1;
   cci.y = cobra->rabo->coordenada.y;
   insere(&tam_cobra, cobra, cci);
   }

return tam_cobra;
}

/*====================================direciona a cobrinha===================================================*/
int direciona(int tecla, int a, tipocoordenada *direcao)
{
     //o if impede que a cobrina passe por cima de si mesma caso o usuario aperte a tecla com o sentido contrario ao movimento da cobra
     if((!(((a==4)&&(tecla==5))||((a==5)&&(tecla==4))||((a==2)&&(tecla==3))||((a==3)&&(tecla==2)))) && (a!=tecla))
       {
         switch(tecla)
               {
               case 4:    direcao->x =-1; direcao->y = 0; break;/*esquerda*/
               case 5:    direcao->x = 1; direcao->y = 0; break;/*direita*/
               case 3:    direcao->x = 0; direcao->y =-1; break;/*pra cima*/
               case 2:    direcao->x = 0; direcao->y = 1; break;/*pra baixo*/
               }
       }

return 0;
}
/*====================================movimenta a cobrinha==================================================*/
tipocoordenada movimenta(tipocobra *cobra, tipocoordenada direcao)
{
tipocoordenada ultima_rabo;

ultima_rabo.x = cobra->rabo->coordenada.x;
ultima_rabo.y = cobra->rabo->coordenada.y;



cobra->rabo->coordenada.x = (cobra->cabeca->coordenada.x) + direcao.x;
cobra->rabo->coordenada.y = (cobra->cabeca->coordenada.y) + direcao.y;
cobra->rabo->proximo = cobra->cabeca;
cobra->cabeca->anterior = cobra->rabo;
cobra->cabeca = cobra->rabo;
cobra->rabo = cobra->rabo->anterior;

return ultima_rabo;
}
/*===================================================gera fruta==================================================*/
int gerafruta(tipocoordenada *pos_fruta)
{
pos_fruta->x = sorteio(1,COLS-3);
pos_fruta->y = sorteio(1,LINES-3);

return 0;
}
/*===========================================imprimi quadrado====================================================*/
int imprimiquadrado(int pontos)
{
int i;

for(i=0;i<COLS;i++)
   {
   move(0,i); addch('_');
   move(LINES-2,i); addch('_');
   }

for(i=1;i<LINES-1;i++)
   {
   move(i,0); addch('|');
   move(i,COLS-1); addch('|');
   }
move(LINES-1,2); 
printw("Pontos: %8d",pontos);
move(LINES,COLS); 

return 0;
}

/*================================================imprimi coordenadas===================================================*/
int imprmicoordenada(int num_fruta, tipocoordenada pos_fruta)
{
int i;

for(i=0;i<=num_fruta;i++)
   {
   mvaddch(pos_fruta.y, pos_fruta.x, 'o');
   }
}

/*================================================imprimi lista===================================================*/
int imprmilista(int *fim, int tam_cobra, tipocobra *cobra)
{
int i;
tipocelula *aux;

mvaddch(cobra->cabeca->coordenada.y , cobra->cabeca->coordenada.x, '@');
aux = cobra->cabeca;

for(i=1;i<tam_cobra;i++)
   {
   mvaddch(aux->proximo->coordenada.y, aux->proximo->coordenada.x, '*');
   aux = aux->proximo;
   if((cobra->cabeca->coordenada.x == aux->coordenada.x)&&(cobra->cabeca->coordenada.y == aux->coordenada.y))
   (*fim) = 1;
   }

move(0, 0);
}


/*==================================================inicializa ncurses============================================*/
int inicializa(void)
{
initscr();
cbreak();
noecho();
intrflush(stdscr,FALSE);
keypad(stdscr,TRUE);
nodelay(stdscr,TRUE);
return 0;
}

/*============================================ tela de entrada do jogo=============================================*/
int entrada(void)
{
char k;
clear();
move(LINES/2, (COLS/2)-13); printw("Pressione espaco para jogar.");
move((LINES/2)+1, (COLS/2)-13); printw("Pressione S para sair.");
refresh();
while(1)
     {
     k = getch();
     if(k==' ')
     return 0;
     if(k=='S' || k=='s')
       {
       return 0;
       }
     }
return 0;
}



int jogo(void)
{
char a;
char tecla;
int num_fruta = 0;
int pontos = 0;
tipocobra *cobra =  (tipocobra*) malloc(sizeof(tipocobra));
tipocoordenada direcao;
tipocoordenada pos_fruta;
tipocoordenada ultima_rabo;
int i, tam_cobra;
int fim=0;
direcao.x = 1;
direcao.y = 0;

clear();
tam_cobra = cria(cobra);

while(!fim)
     {
     tecla = getch();
     if(tecla == 's')
      { 
      fim =1;
      }

     if(num_fruta == 0)
       {
       gerafruta(&pos_fruta);
       num_fruta = 1;
       }

     imprimiquadrado(pontos);
     imprmicoordenada(num_fruta, pos_fruta);
     if((cobra->cabeca->coordenada.x == pos_fruta.x)&&(cobra->cabeca->coordenada.y == pos_fruta.y))
       {
       insere(&tam_cobra, cobra, ultima_rabo);
       num_fruta = 0;
       pontos++;
       }
     imprmilista(&fim, tam_cobra, cobra);

     if(((cobra->cabeca->coordenada.x) == 0)||((cobra->cabeca->coordenada.x) == (COLS-1))||((cobra->cabeca->coordenada.y) == 0)||((cobra->cabeca->coordenada.y) == (LINES-2)))
       {
       fim = 1;
       }
     direciona(tecla, a, &direcao);
     ultima_rabo = movimenta(cobra, direcao);


     if((tecla == 2)||(tecla == 3)||(tecla == 4)||(tecla == 5))
     a=tecla;


     refresh();
     usleep(100000);
     clear();

     }
}

/*=================================================funcao main====================================================*/
int main(void)
{
int sair =0;

/*inicializa ncurses*/
inicializa();

while(sair==0)
     {

     /*tela de entrada do jogo*/
     entrada();

     /*o jogo*/
     if (sair==0)
     {
     jogo();
     }
     /*tela de fim de jogo*/
     if (!sair) fim_de_jogo();
     }

/*finaliza ncurses*/
endwin();

return 0;
}







/*




int main(void)
{
tipocoordenada a, b, c;

a.x = 3;
a.y = 2;
b.x = 3;
b.y = 2;
c.y=0;
c.x = 5;
a.x = 8;
a.y = 9;

printf("\n%8d%8d\n\n", c.x, c.y);
}*/