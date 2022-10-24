/*Matheus Vinicius Ferreira de Figueiredo Teixeira
Turma C
Matricula 0913511
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define PONTO (ispunct(k) || isspace(k))

typedef struct no
{
int frequencia;
char palavra[30];
struct no *esq;
struct no *dir;
}no;

int menu(void);
int bancodedados(void);
int armazena(no **raiz, int m, char arq1[]);
int letexto(FILE *arq, char palavra[]);
int arvore(no **p, char palavra[], int *m);
int preordem2(no **raiz, int m);
int frequencia(no **raiz, int m);
int balanciamento(no **raiz, int *h, int *k, int m);
int backbone(no **raiz, int a);
int rotacao(no **raiz, int a);
int balanceiain(no **raiz, int m, int *h, int *k);
int balanceia(no **raiz, int *h, int *k);
int salvar(no *raiz, int m,char autor[]);
int descobrir(void);
int carregar(no **raiz, int a, FILE *fp);
int arvore2(no **p, no *x);
int preordem3(no *raiz, no *raiz2, long int *st);
int busca(no *raiz, no *raiz2, long int *e);
long int erro(long int a, long int b);


/*========================funcao principal===================================*/

int main (void)
{
int m, h, k;
no    *raiz;
FILE *fp;

m = 0;
h = 0;
raiz = NULL;

for(;;) 
   {
    switch(menu())
          {
          case 1: bancodedados();
            break;
          case 2: descobrir();
            break;
          case 3: exit(0);
          }
    }


return 0;
}


/*=========================================menu========================================*/

int menu(void)
{
char s[80];
int      c;

printf("\n\tbem-vindo ao programa de indentificacao de autores");
printf("\n\tescolha operacao\n\n");
printf("1.Armazenar novo autor/texto em banco de dados\n");
printf("2.Descobrir autor de texto\n");
printf("3.Sair\n");
do {
   scanf("%s",s);
   c = atoi(s);
   } while(c<0 || c>3);


return c;
}


/*========================insere novo autor em banco de dados=============================*/

int bancodedados(void)
{
char a = 'a';
char autor[80];
char texto[80];
int i, m/*quantidade de nos*/, h/*altura de arvore atual*/, k/*altura de arvore completa*/;
no    *raiz;
i=1;
m = 0;
h = 0;


printf("\n\n\n\tentre com o nome do autor\n");
scanf("%c", autor);
while(a != '\n')
{
a = fgetc(stdin);
if(a != '\t' && a != '\n')
autor[i] = a;
i++;
autor[i] = '\0';
}

i = 1;
a = 'a';

printf("\tentre com o nome do arqivo texto\n");
scanf("%c", texto);
while(a != '\n')
{
a = fgetc(stdin);
if(a != '\t' && a != '\n')
texto[i] = a;
i++;
texto[i] = '\0';
}
m = armazena(&raiz, m, texto);
preordem2(&raiz, m);
/*balanciamento(&raiz, &h, &k, m);*/
salvar(raiz, m, autor);


return 0;
}


/*=============armazena cada palavra do texto em uma arvore de strings====================*/

int armazena(no **raiz, int m, char arq1[])
{
int      a;
char x[30];
FILE  *arq;

*raiz = NULL;
a     =    0;
arq = fopen(arq1, "r");
if(!arq)
  {
  printf("\nnome do arqivo de texto errado ou não esta salvo nesse diretorio\n\n");
  exit(1);
  }

while(a==0)
     {
     a = letexto(arq, x);
     if(x[0] != '\0')
     arvore(raiz, x, &m);
     }


return m;
}


/*=======================le cada palavra do texto======================================*/

int letexto(FILE *arq, char palavra[])
{
char k = 'a';
int  i =   0;

palavra[0] = '\0';

while(!PONTO)
     {
     k = fgetc(arq);
     if(k==EOF)
       {
       return 1;
       }
     if(!PONTO)
       {
       palavra[i]=k;
       i++;
       palavra[i]='\0';
       }
     }



return 0;
}


/*=============================cria arvore de strings================================*/

int arvore(no **p, char palavra[], int *m)
{
int x;

if(*p == NULL) 
  {
  *p = (no*)malloc(sizeof(no));
  strcpy((*p)->palavra, palavra);
  (*m)++;
  (*p)->frequencia = 1;
  (*p)->esq = NULL;
  (*p)->dir = NULL;
  return 0;
  }

x = strcmp(palavra, (*p)->palavra);
if(x<0)
  {
  arvore(&(*p)->esq, palavra, m);
  return 0;
  }
if(x>0)
  {
  arvore(&(*p)->dir, palavra, m);
  return 0;
  }
if(x==0)
  (*p)->frequencia++;
}


/*=============percorre arvore em preordem, atualizndo frequencias==================================*/

int preordem2(no **raiz, int m)
{
frequencia(raiz, m);
if (((*raiz)->esq) != NULL)
   preordem2(&((*raiz)->esq), m);
if (((*raiz)->dir) !=NULL)
   preordem2(&((*raiz)->dir), m);


return 0;
}


/*=============calcula e armazena frequencia percentual: subrotina de preordem 2====================*/

int frequencia(no **raiz, int m)
{
int a, b;
a = (*raiz)->frequencia;
b = 100*a/m;
(*raiz)->frequencia =b;
} 


/*=======================================balanceia arvores=========================================*/

int balanciamento(no **raiz, int *h, int *k, int m)
{
int a = 0;
backbone(raiz, 1);
balanceiain(raiz, m, h, k);
balanceia(raiz, h, k);

a = ((*h) - (*k));
while(a>0)
     {
     balanceia(raiz, h, k);
     a = ((*h) - (*k));
     }


}


/*===============cria backbone a direita: subrotina de balanciamento=================================*/

int backbone(no **raiz, int a)
{
if(((*raiz)->esq) != NULL)
  {
  rotacao(raiz, 1);
  backbone((raiz), 1);
  }
if(((*raiz)->esq) == NULL)
{
if(((*raiz)->dir) != NULL)
  {
  backbone(&((*raiz)->dir), 1);
  }
}


return 0;
}


/*==========================rotaciona nos em arvores=================================*/

int rotacao(no **raiz, int a)
{
no    *aux;
aux = NULL;

if(a==1)
  {
  aux = (*raiz)->esq;
  (*raiz)->esq = (*raiz)->esq->dir;
  aux->dir = (*raiz);
  (*raiz) = aux;
  }

if(a==2)
  {
  aux = (*raiz)->dir;
  (*raiz)->dir = (*raiz)->dir->esq;
  aux->esq = (*raiz);
  (*raiz) = aux;
  }


return 0;
}


/*==balanciamento inicial de arvores comfolhas insuficientes para completar um nivel: subrotina de balanciamento==*/

int balanceiain(no **raiz, int m, int *h, int *k)
{
double a, b, c;
int i, x;

a = log(m+1);
b =   log(2);
c =      a/b;
i =        0;
(*h) =     m;

(*k) = (int)c;
x = (m - ((pow(2, (*k))-1)));

while(i<x)
     {
     rotacao(raiz, 2);
     raiz = &((*raiz)->dir);
     i++;
     (*h)--;
     }
}


/*================================balanciamento a partir do backbone==========================================*/

int balanceia(no **raiz, int *h, int *k)
{
int a;

if((*raiz)->dir!=NULL)
  {
  rotacao(raiz, 2);
  (*h)--;
  a = ((*h) - (*k));
  if(a <= 1) return 0;
  balanceia(&((*raiz)->dir), h, k);
  }


}


/*=======================================abri arquivo e salva arvore==================================*/

int salvar(no *raiz, int m,char autor[])
{
FILE *fp;
no *primeiro;
primeiro = (no *)malloc(sizeof(no));

(primeiro->frequencia) = m;
strcpy((primeiro->palavra), autor);
primeiro->dir = NULL;
primeiro->esq = NULL;

fp = fopen("banco de dados", "ab");
fwrite(primeiro, sizeof(no), 1, fp);

if(!fp)
  {
  printf("nao pode abrir arquivo.\n");
  exit(1);
  }
preordem(raiz, fp);
fclose(fp);
}


/*========percorre arvore em preordem, escrevendo-a em arquivo: subrotina de salvar==============*/

int preordem(no *raiz, FILE *fp)
{
fwrite(raiz, sizeof(no), 1, fp);
if ((raiz->esq) != NULL)
   preordem(raiz->esq, fp);
if ((raiz->dir) !=NULL)
   preordem(raiz->dir, fp);

return 0;
}


/*============================sugere autor para texto de autoria===============================*/

int descobrir(void)
{
FILE *fp;
no *raiz2;/*raiz volatil*/
no *raiz;/*raiz em banco*/
no *parcial;/*resultado parcial*/
no *resultado;/*autor*/
char texto[80]={'a','r','q','.','t','x','t'};/*texto desconhecido*/
char a;
int  b, h, i, k, m;
long int st, sr;

parcial =  (no *)malloc(sizeof(no));/*resultado parcial*/
resultado = (no *)malloc(sizeof(no));/*autor sugerido*/
raiz = (no *)malloc(sizeof(no));
raiz2 = (no *)malloc(sizeof(no));

a = 'a';
b = 1;
h = 0;
k = 0;
m = 0;
i = 0;
st = 0;
sr = 0;
printf("\tentre com o nome do arquivo\n");
scanf("%c", texto);

while(a != '\n')
{
a = fgetc(stdin);
if(a != '\t' && a != '\n')
texto[i] = a;
i++;
texto[i] = '\0';
}


m = armazena(&raiz2, m, texto);
preordem2(&raiz2, m);
/*balanciamento(&raiz2, &h, &k, m);*/

fp = fopen("banco de dados", "rb");

fread(resultado, sizeof(no), 1, fp);
carregar(&raiz, resultado->frequencia, fp);
preordem3(raiz, raiz2, &sr);
while(b != 0)
     {
     b = fread(parcial, sizeof(no), 1, fp);
     if(b == 0)
       break;
     st = 0;
     carregar(&raiz, parcial->frequencia, fp);
     preordem3(raiz, raiz2, &st);
     if(st<sr)
       {
       sr = st;
       strcpy((resultado->palavra),(parcial->palavra));
       }
     }
printf("%s eh o provavel autor desse texto\n",(resultado->palavra));

fclose(fp);

}


/*=========================================carregar=======================================*/

int carregar(no **raiz, int a, FILE *fp)
{
no *p;
(*raiz) = NULL;
p = (no*)malloc(sizeof(no));
while(a>0)
{
fread(p, sizeof(no), 1, fp);
arvore2(raiz, p);
a--;
}

free(p);

return 0;
}


/*===========================subrotina da funcao carregar================================*/

int arvore2(no **p, no *x)
{
int a;

if(*p == NULL) 
  {
  *p = (no*)malloc(sizeof(no));
  strcpy((*p)->palavra, x->palavra);
  (*p)->frequencia = x->frequencia;
  (*p)->esq = NULL;
  (*p)->dir = NULL;
  return 0;
  }

a = strcmp(x->palavra, (*p)->palavra);
if(a<0)
  {
  arvore2(&(*p)->esq, x);
  }
if(a>0)
  {
  arvore2(&(*p)->dir, x);
  }
}



/*============================compara frequencias===============================*/

int preordem3(no *raiz, no *raiz2, long int *st)
{

long int s = 0;
busca(raiz, raiz2 , &s);
(*st) = (*st) + s;

if ((raiz2->esq) != NULL)
   preordem3(raiz, (raiz2->esq), st);
if ((raiz2->dir) !=NULL)
   preordem3(raiz, raiz2->dir, st);


return 0;
}


/*========================busca: subrotina de preordem3===============================*/

int busca(no *raiz, no *raiz2, long int *e)
{
int a;
a = 0;


if(raiz == NULL)
  {
  (*e) = erro((raiz2->frequencia), 0);
  return 0;
  }
a = strcmp((raiz2->palavra), (raiz->palavra));
if(a<0)
  {
  busca(raiz->esq, raiz2, e);
  return 0;
  }
if(a>0)
  {
  busca(raiz->dir, raiz2, e);
  return 0;
  }
if(a==0)
  {
  (*e) = erro((raiz->frequencia), (raiz2->frequencia));
  return 0;
  }
}


/*====================soma dos erros quadrdos: subrotina de busca============================*/

long int erro(long int a, long int b)
{
long int c, d;
c = a - b;
d = pow(c, 2);


return d;
}
