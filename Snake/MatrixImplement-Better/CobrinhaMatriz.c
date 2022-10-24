/*
Matheus Vin&iacute;cius Ferreira de Figueiredo Teixeira
Matricula: 0913511
turma:c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

int inicializa(void);
int entrada(void);
int jogo(void);
int sorteio(int minimo,int maximo);
int fim_de_jogo(void);

// variaveis globais
int sair=0, pontos=0;

// funcao main
int main(void)
{

//inicializa ncurses
inicializa();
while(sair==0)
     {

     //leta de entrada do jogo
     entrada();

     //o jogo
     if (!sair) jogo();

     //tela de fim de jogo
     if (!sair) fim_de_jogo();
     }

//finaliza ncurses
endwin();
return 0;
}

//inicializa ncurses
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

// tela de entrada do jogo
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
       sair = 1;
       return 0;
       }
     }
return 0;
}

// o jogo
int jogo(void)
{
int tam_cobra; // tamanho da cobra
int pos_cobra[COLS*LINES][2]; // posicoes (x,y) da cobra
int num_frutas; // numero de frutas
int pos_fruta[2]; // posicoes (x,y) das frutas
int V_cobra[2] = { 0, 1 }; // direcao da cobra (x,y)
int i, fim, j, k, lx, ly, tecla, a;
char quadrado[LINES][COLS];

/* valores iniciais */
pos_cobra[0][0] = 5;
pos_cobra[0][1] = 5;
tam_cobra = 3;
num_frutas = 0;
fim = 0;
pontos = 0;
tecla=0;
a=261;

while(!fim)
     {
     tecla = getch();

     //direciona a cobrinha; toda a primeira parte do if(antes do ultimo && impede que a cobrina passe por cima de si mesma caso o usuario aperte a tecla com o sentido contrario ao movimento da cobra
     if((!(((a==259)&&(tecla==258))||((a==258)&&(tecla==259))||((a==260)&&(tecla==261))||((a==261)&&(tecla==260)))) && (a!=tecla))
       {
         switch(tecla)
               {
               case KEY_LEFT:  V_cobra[0]= 0; V_cobra[1]=-1; break;
               case KEY_RIGHT: V_cobra[0]= 0; V_cobra[1]= 1; break;
               case KEY_UP:    V_cobra[0]=-1; V_cobra[1]= 0; break;
               case KEY_DOWN:  V_cobra[0]= 1; V_cobra[1]= 0; break;
               case 's': 
               case 'S': fim=1; break;
               }
       }

     //movimenta a cobrinha
     for(i=tam_cobra-1;i>0;i--)
        {
        pos_cobra[i][0] = pos_cobra[i-1][0];
        pos_cobra[i][1] = pos_cobra[i-1][1];
        }

     //atualiza a direcao da cobra
     pos_cobra[0][0] += V_cobra[0];
     pos_cobra[0][1] += V_cobra[1];

     // limpa a tela
     clear();

     //gera novas frutas
     if (num_frutas == 0)
       {
       pos_fruta[0] = sorteio(1,LINES-3);
       pos_fruta[1] = sorteio(1,COLS-3);
       num_frutas=1;
       }

     //preenche a matriz
     for(j=0;j<COLS-3;j++)
        {
        quadrado[0][j]='_';
        }

     for(i=1;i<LINES-1;i++)
        {
        quadrado[i][0]='|';
        quadrado[i][COLS-1]='|';
        }

     for(i=1;i<LINES-1;i++)
        {
        for(j=1;j<COLS-3;j++)
           {
           quadrado[i][j]=' ';
           if((i==pos_cobra[0][0])&&(j==pos_cobra[0][1]))
             {
             quadrado[i][j]='@';
             } 
           if((i==pos_fruta[0])&&(j==pos_fruta[1]))
             {
             quadrado[i][j]='o';
             }
          for(k=1;k<tam_cobra;k++)
             {
             if((i==pos_cobra[k][0])&&(j==pos_cobra[k][1]))
               {
               quadrado[i][j]='*';
               }
             }
          if(i==LINES-2)
            {
            quadrado[LINES-2][j]='_';
            if((LINES-2==pos_cobra[0][0])&&(j==pos_cobra[0][1]))
              {
              quadrado[i][j]='@';
              }
            for(k=1;k<tam_cobra;k++)
               {
               if((LINES-2==pos_cobra[k][0])&&(j==pos_cobra[k][1]))
                 {
                 quadrado[i][j]='*';
                 }
               }
            }
           }
        }

     //Imprimi a Matriz: desenha o jogo
     for(i=0;i<LINES-1;i++)
        {
        for(j=0;j<COLS;j++)
           {
           printw("%c",quadrado[i][j]);
           }
        printw("\n");
        }
        printw("pontos%8d", pontos);

     //termina o jogo caso a cobra atinja a parede
     if((pos_cobra[0][0]==0 || pos_cobra[0][0]==LINES-1 ||  pos_cobra[0][1]==0 || pos_cobra[0][1]==COLS-3))
       {
       fim = 1;
       }

     //termina o jogo casa a cobra bata em si mesma: tudo que usa a variavel a no if serve para impedir que a cobra morra
     // caso o usuario tecle a seta da direcao contraria ao movimento da cobra
     if(a!=tecla)
       {
       for(i=1;i<tam_cobra;i++)
          {
          if((!(((a==259)&&(tecla==258))||((a==258)&&(tecla==259))||((a==260)&&(tecla==261))||((a==261)&&(tecla==260)))) &&((pos_cobra[i][0]==pos_cobra[0][0])&&(pos_cobra[i][1]==pos_cobra[0][1])))
            {
            fim = 1;
            break;
            }
          }
       }

     //quebra o while levando a tela ao fim de jogo
     if(fim!=0)
       {
       break;
       }

     //aumenta o tamanho da cobra caso ela passe sobre um fruto
     lx = pos_cobra[tam_cobra-1][0];
     ly = pos_cobra[tam_cobra-1][1];
     for(i=0;i<num_frutas;i++)
        {
        if(pos_fruta[0]==pos_cobra[0][0] && pos_fruta[1]==pos_cobra[0][1])
          {
	  pos_cobra[tam_cobra][0]=lx;
	  pos_cobra[tam_cobra][1]=ly;
	  tam_cobra++;
	  pontos += 1;
	  num_frutas=0;
	  break;
          }
       }

     //a guarda o ultimo valor de tecla
     if(tecla!=-1)
       {
       a=tecla;
       }

     //o cursor vai pro canto da tela pra nao atrapalhar o jogo
     move(LINES-1,COLS-1);

     //faz com que tudo seja impresso de uma vez na tela
     refresh();

     //atraza as impress&otilde;es em 1,5 segundos: regula a velocidade da cobra
     usleep(150000);
     }

//impedi que a volte ao jogo com um valor diferente do seta para direita evitando problemas no direcionamento da cobra
a=261;

return 0;
}


// sorteia um inteiro entre minimo e maximo (inclusive)
int sorteio(int minimo,int maximo)
{
int val;
val = minimo + (rand() % (maximo-minimo+1));
return val;
}

int fim_de_jogo(void)
{
int i,y;

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
