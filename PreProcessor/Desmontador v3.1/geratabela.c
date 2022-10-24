#include<stdio.h>
#include<stdlib.h>
#include"desmontador.h"

#define DEBUGG

/*
**	___________________geratabela.c___________________
**		
**	Gera a estrutura de dados com os dados da tabela a partir do arquivo “tabela.txt”.
**	
**	___________________geratabela.c___________________
**/


void geratabela(tabelaS **p_inicio, FILE *tabela){
	int byteatual=0;
	int tipoatual=0, i=0;
	char nomeatual=0;
	tabelaS *p1, *p2;

	/*Inicio da Geração da tabela.*/
	*p_inicio=NULL;
	/*Posicionando no inicio*/
	fseek(tabela, 0, SEEK_SET);

/*============================================================
====================Enquanto não for fim de arquivo===========
============================================================*/

	while ( fscanf(tabela, "%x", &byteatual) != EOF){

		/*============================================================
		====================Cria novo elemento========================
		============================================================*/
		p1=malloc(sizeof(tabelaS));

		/*============================================================
		====================Escreve o opcode==========================
		============================================================*/
		p1->opcode=byteatual;

		/*============================================================
		====================Escreve o tipo da instrução===============
		============================================================*/
		fscanf(tabela, "%x", &tipoatual);
		p1->tipo=tipoatual;

		/*============================================================
		====================Escreve a instrução=======================
		============================================================*/
		nomeatual=getc(tabela);
		i=0;
		while( (nomeatual=getc(tabela)) != '\n'){
			p1->nome[i]=nomeatual;
			i++;
		}
		p1->nome[i]=nomeatual;


		if(*p_inicio==NULL)
			*p_inicio=p1;
		else
			p2->next=p1;
		p2=p1;

	}

	#ifdef DEBUG
	p1=*p_inicio;
	if (p_inicio == NULL)
		printf ("lista vazia \n");
	else {          
		p1=*p_inicio;   
		while (p1 != NULL) {
			printf("%.2x %d ", p1->opcode, p1->tipo);
			i=0;
			while( (p1->nome[i]) != '\n'){
				printf("%c", p1->nome[i]);
				i++;
			}
			printf("\n");
			p1 = p1->next;
		}
	}
	#endif

	printf("...Tabela de instruções gerada com sucesso.\n");
}
