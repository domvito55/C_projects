/*Matheus Vinicius Ferreira de Figueiredo Teixeira
Turma C
Matricula 0913511
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/*structs*/
typedef struct adjacente adjacente;


typedef struct filme{
int              flag;
char        nome[150];
struct adjacente *nos;
}filme;


typedef struct arcos{
filme         *filme1;
struct arcos *proximo;
}arcos;


typedef struct no{
int          flag;
char     ator[70];
struct no   *prox;
arcos      *parco;
arcos      *uarco;
}no;


struct adjacente{
no              *ator;
struct adjacente *adj;
};


typedef struct table{
struct no   *primeiro;
struct no     *ultimo;
}table;


typedef struct fila{
struct fila     *proximo;
struct filme *antecessor;
struct no   *antecessor2;
struct fila *antecessor3;
struct arcos      *lista;
}fila;


/*declaracao de funcoes*/

int                          menu(void);
char letexto(FILE *arq, char palavra[]);
int                       ial(char p[]);
int                       ial(char p[]);
int              grafo(table *tabela[]);
int              busca(table *tabela[]);
int              teste(table *tabela[]);


int main(void)
{
table *tabela[104701];
grafo(tabela);

for(;;) 
   {
    switch(menu())
          {
          case 1: fflush(stdin); teste(tabela);
            break;
          case 2: fflush(stdin); busca(tabela);
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

printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tbem-vindo a este programa\n\t\t\tescolha a op��o\n\t\t\t1.testar se dois atores trabalharam juntos\n\t\t\t2.descobrir graus de separacao\n\t\t\t3.sair\n\n\n\n\n\n\n\n\n\n\n");

do {
   scanf("%s",s);
   c = atoi(s);
   } while(c<0 || c>3);
usleep(1000000);


return c;
}


/*funcao que constroi grafo*/

int grafo(table *tabela[])
{
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t  Carregando...\n\t\t\tEsse processo pode demorar ateh um minuto e meio\n\n\n\n\n\n\n\n\n\n\n\n");

/*declaracao de variaveis*/
int        b = 0;
int            c;
int        d = 1;
int        e = 0;

char           a;
char    ator[70];
char filme2[150];

no         *raiz;
no         **nax;
no         *nax2;

adjacente *raiz2;
adjacente **adax;

arcos       *cax;

filme       *fax;

while(b<104701)
{
tabela[b] = NULL;
b++;
}

raiz = (no*)malloc(sizeof(no));

FILE *arq;

arq = fopen("input-all.txt", "r");


/*construindo grafo*/
nax = &raiz;
while(!feof(arq))
     {
     raiz2      = (adjacente*)malloc(sizeof(adjacente));
     adax       =                                &raiz2;
     a          =                  letexto(arq, filme2);
     fax        =         (filme*)malloc(sizeof(filme));
     fax->flag  =                                     0;
     strcpy((fax->nome), filme2);
     (fax->nos) =                                 raiz2;

     while(a != '\n')
          {
          if(feof(arq))
            break;
          a              = letexto(arq, ator);
          strcpy(((*nax)->ator), ator);
          ((*nax)->prox) =               NULL;
          ((*nax)->flag) =                  0;

          ((*nax)->parco)          = (arcos*)malloc(sizeof(arcos));
          ((*nax)->parco->filme1)  =                           fax;
          ((*nax)->parco->proximo) =                          NULL;
          ((*nax)->uarco)          =               ((*nax)->parco);

          ((*adax)->ator)          =                        (*nax);

          c = ial(ator);
          if(tabela[c] == NULL)
            {
            tabela[c] = (table*)malloc(sizeof(table));
            (tabela[c]->primeiro) = (*nax);
            (tabela[c]->ultimo) = (tabela[c]->primeiro);
            }
          else
              {
              nax2 = tabela[c]->primeiro;
              while(1)
                   {
                   d =                                  1;
                   d = strcmp(((*nax)->ator), nax2->ator);
                   if(d == 0)
                     {
                     nax2->uarco->proximo         = (arcos*)malloc(sizeof(arcos));
                     nax2->uarco->proximo->filme1 =                           fax;
                     (*adax)->ator                =                          nax2;
                     nax2->uarco                  =          nax2->uarco->proximo;
                     nax2->uarco->proximo         =                          NULL;
                     e = 1;
                     }
                   if(nax2 == tabela[c]->ultimo)
                     break;
                   nax2 = nax2->prox;
                   }
              if(e == 0)
                {
                (tabela[c]->ultimo->prox) =                    (*nax);
                (tabela[c]->ultimo)       = (tabela[c]->ultimo->prox);
                }
              e = 0;
              }
          raiz = (no*)malloc(sizeof(no));
          nax = (&(raiz));
          ((*adax)->adj) = (adjacente*)malloc(sizeof(adjacente));
          adax = (&((*adax)->adj));
          ((*adax)->adj) = NULL;
          }
     }

fclose(arq);


return 0;
}


/*funcao que le arquivo de entrada*/

char letexto(FILE *arq, char palavra[])
{
/*declaracao de variaveis*/
char k     =  'a';
int  i     =    0;

palavra[0] = '\0';

while((k!='/') && (k!='\n'))
     {
     k = fgetc(arq);
     if(feof(arq))
       {
       return k;
       }
     if((k!='/') && (k!='\n'))
       {
       palavra[i]=k;
       i++;
       palavra[i]='\0';
       }
     }

return k;
}


/*funcao transformacao da hashtable*/

int ial(char p[])
{
/*declaracao de variaveis*/
int a;

/*transformacao*/
a = (((p[0]+95)*307)+((p[1]+95)*229)+((p[2]+95)*563)+((p[3]+95)*709)+((p[4]+95)*1013))%104701;

//printf("a: %d", a); /////////////////////////////////////
return a;
}


/*funcao que acha o numero de bacon*/

int busca(table *tabela[])
{
/*declaracao de variaveis*/
char a =   'a';
char ator1[70];
char ator2[70];
int  i =     0;
int  b =     0;
int  c =     0;
int  d =     1;
int  e =     1;
int  k =     1;
char         f;
no        *nax;

no         *nax2;
fila      *fila1;
fila      *fila2;
fila      *fila3;
filme       *fax;
adjacente **adax;
arcos       *cax;

printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tdigite o nome do primeiro ator\n\t\t\texemplo: Bacon, Kevin\n\n\n\n\n\n\n\n\n\n\n\n\n");
//f = fgetc(stdin);
while(a != '\n')
     {
     a = fgetc(stdin);
     if(a != '\t' && a != '\n')
     ator1[i] =    a;
     i++;
     ator1[i] = '\0';
     }
usleep(1000000);

b = ial(ator1);

printf("\nator1: %s", ator1);/////////////////////////
//printf("\nial: %d", b);//////////////////////////////

if(tabela[b] == NULL)
  {
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tator 1 nao encontrado\n\n\n\n\n\n\n\n\n\n\n\n");
  usleep(1000000);
  return 0;
  }

a ='a';
i =  0;
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tdigite o nome do segundo ator\n\t\t\texemplo: Bacon, Kevin\n\n\n\n\n\n\n\n\n\n\n\n\n");
while(a != '\n')
{
a = fgetc(stdin);
if(a != '\t' && a != '\n')
ator2[i] =    a;
i++;
ator2[i] = '\0';
}
usleep(1000000);

c = ial(ator2);
d = strcmp(ator1, ator2);
if(d == 0)
  {
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\tdistancia entre %s e %s eh 0\n\n\n\n\n\n\n\n\n\n\n", ator1, ator2);
  usleep(2000000);
  return 0;
  }
if(tabela[c] == NULL)
  {
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tator 2 nao encontrado\n\n\n\n\n\n\n\n\n\n\n\n");
  usleep(1000000);
  return 0;
  }
nax = tabela[b]->primeiro;

while(1)
     {
     d = strcmp(ator1, nax->ator);
     if(d == 0)
       break;
     if(nax == (tabela[b]->ultimo))
       break;
     nax = (nax->prox);
     }
if(d != 0)
  {
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tator 1 nao encontrado\n\n\n\n\n\n\n\n\n\n\n\n");
  usleep(1000000);
  return 0;
  }

nax->flag = 1;
fila1              =  (fila*)malloc(sizeof(fila));
fila1->proximo     =                         NULL;
fila1->antecessor  =                         NULL;
fila1->antecessor2 =                         NULL;
fila1->antecessor3 =                         NULL;
fila1->lista       =                   nax->parco;

fila2              =                        fila1;
fila3              =                        fila1;
cax                =                 fila1->lista;
fax                =         fila1->lista->filme1;
adax               = &(fila1->lista->filme1->nos);
fax->flag          =                            1;

while(1)
     {
     while(1)
          {
          while(1)
               {
               fax->flag = 1;
               if((*adax)->ator->flag == 0)
                 {
                 (*adax)->ator->flag = 1;
                 e = strcmp(ator2, (*adax)->ator->ator);
                 if(e == 0)
                   break;
                 (*adax)->ator->flag =                           1;
                 fila2->proximo      = (fila*)malloc(sizeof(fila));
                 fila2               =              fila2->proximo;
                 fila2->proximo      =                        NULL;
                 fila2->antecessor   =                         fax;
                 fila2->antecessor2  =               (*adax)->ator;
                 fila2->antecessor3  =                       fila3;
                 fila2->lista        =        (*adax)->ator->parco;
                 }
               if((*adax)->adj->adj == NULL)
                 break;
                 adax = &((*adax)->adj);
               }
          if(e == 0)
            break;
          if(cax->proximo == NULL)
            break;

           while(1)
                {
                if(cax->proximo == NULL)
                  break;
                cax = cax->proximo;
                if(cax->filme1->flag == 0)
                  break;
                }
          fax  = cax->filme1;
          adax = &(fax->nos);
          }
     if(e == 0)
       break;

     while(1)
          {
          if(fila3->proximo == NULL)
            break;
          fila3 = fila3->proximo;
          cax   =   fila3->lista;
          while(1)
               {
               if(cax->filme1->flag == 0)
                 break;
               if(cax->proximo == NULL)
                 break;
               cax = cax->proximo;
               }
          if(cax->filme1->flag == 0)
            break;
          }
     fax = cax->filme1;
     if(fax->flag == 1)
       break;
     adax = &fax->nos;
     }

printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
if(e == 0)
  {
  printf("\t\t\t\t%s\n\t\t\t\t     |\n\t\t\t\t     V\n", ator2);
  printf("\t\t\t%s\n\t\t\t\t     |\n\t\t\t\t     V\n", fax->nome);
  fax = fila3->antecessor;
  nax2 = fila3->antecessor2;
  fila2 = fila3;
  while(1)
       {
       if(fila2->antecessor == NULL)
         break;
       k++;
       printf("\t\t\t\t%s\n\t\t\t\t     |\n\t\t\t\t     V\n", nax2->ator);
       printf("\t\t\t%s\n\t\t\t\t     |\n\t\t\t\t     V\n", fax->nome);
       if(fila2->antecessor3 == NULL)
         break;
       fila2 = fila2->antecessor3;
       fax = fila2->antecessor;
       nax2 = fila2->antecessor2;
        }
  printf("\t\t\t\t%s\n\n", ator1);
  printf("Numero de Bacon: %d", k);
  }
else
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tNumero de Bacon: infinito\n\n\n\n\n\n\n\n\n\n\n");


c = 0;
while(1)
     {
     if(tabela[c] != NULL)
       {
       nax = tabela[c]->primeiro;
       while(1)
            {
            cax = nax->parco;
            while(1)
                 {
                 cax->filme1->flag = 0;
                 if(cax == nax->uarco)
                   break;
                 cax = cax->proximo;
                 }
            nax->flag = 0;
            if(nax->prox == NULL)
              break;
            nax = nax->prox;
            }
       }
     if(c == 104700)
       break;
     c++;
     }
printf("\n\nPrecione enter para retornar");
a = fgetc(stdin);


return 0;
}


/*que testa se dois atores trabalharam juntos*/

int teste(table *tabela[])
{
/*declaracao de variaveis*/
char a =   'a';
char ator1[70];
char ator2[70];
int  i =     0;
int  b =     0;
int  c =     0;
int  d =     1;
int  e =     1;
int  k =     0;
char         f;
no        *nax;

filme        *fax;
adjacente   *adax;
arcos        *cax;
arcos       *cax2;
arcos       *cax3;
arcos       *cax4;

printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tdigite o nome do primeiro ator\n\t\t\texemplo: Bacon, Kevin\n\n\n\n\n\n\n\n\n\n\n\n\n");
f = fgetc(stdin);
while(a != '\n')
     {
     a = fgetc(stdin);
     if(a != '\t' && a != '\n')
     ator1[i] =    a;
     i++;
     ator1[i] = '\0';
     }
usleep(1000000);

b = ial(ator1);
if(tabela[b] == NULL)
  {
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tator 1 nao encontrado\n\n\n\n\n\n\n\n\n\n\n\n");
  usleep(1000000);
  return 0;
  }

a ='a';
i =  0;
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tdigite o nome do segundo ator\n\t\t\texemplo: Bacon, Kevin\n\n\n\n\n\n\n\n\n\n\n\n\n");
while(a != '\n')
     {
     a = fgetc(stdin);
     if(a != '\t' && a != '\n')
     ator2[i] =    a;
     i++;
     ator2[i] = '\0';
     }
usleep(1000000);

c = ial(ator2);
d = strcmp(ator1, ator2);
if(d == 0)
  {
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\tdistancia entre %s e %s eh 0\n\n\n\n\n\n\n\n\n\n\n", ator1, ator2);
  usleep(2000000);
  return 0;
  }
if(tabela[c] == NULL)
  {
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tator 2 nao encontrado\n\n\n\n\n\n\n\n\n\n\n\n");
  usleep(1000000);
  return 0;
  }
nax = tabela[b]->primeiro;

while(1)
     {
     d = strcmp(ator1, nax->ator);
     if(d == 0)
       break;
     if(nax == (tabela[b]->ultimo))
       break;
     nax = (nax->prox);
     }
if(d != 0)
  {
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tator 1 nao encontrado\n\n\n\n\n\n\n\n\n\n\n\n");
  usleep(1000000);
  return 0;
  }

cax           =                    nax->parco;
cax2          = (arcos*)malloc(sizeof(arcos));
(*cax2)       =                        (*cax);
cax2->proximo =                          NULL;
cax3          =                          cax2;
cax4          =                          cax3;
fax           =                   cax->filme1;
adax          =                      fax->nos;


while(1)
     {
     while(1)
          {
          e =                               1;
          e = strcmp(ator2, adax->ator->ator);
          if(e == 0)
            {
            k++;
            (*(cax2->filme1)) = (*fax);
            cax2->proximo = (arcos*)malloc(sizeof(arcos));
            cax2 = cax2->proximo;
            cax2->proximo = NULL;
            }
         if(adax->adj->adj == NULL)
            break;
         adax = adax->adj;
         }
     if(cax->proximo == NULL)
       break;
     cax     = cax->proximo;
     (*cax2) =       (*cax);
     fax     =  cax->filme1;
     adax    =     fax->nos;
     }
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");



if(k != 0)
  {
  fax = cax3->filme1;
  printf("%s trabalhou com %s em:\n\n", ator2, ator1);
  printf("%s\n", fax->nome);
  while(1)
       {
       if(cax3->proximo == NULL)
         break;
       cax3 = cax3->proximo;
       fax  =  cax3->filme1;
       if(cax3->proximo == NULL)
         break;
       printf("%s\n", fax->nome);
        }
  }

else
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t%s e %s n�o trabalharam juntos\n\n\n\n\n\n\n\n\n\n\n", ator1, ator2);

printf("\n\nPrecione enter para retornar");
a = fgetc(stdin);


return 0;
}


