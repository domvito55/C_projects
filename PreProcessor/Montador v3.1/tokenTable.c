/**
Armazena as funções de uma TokenTable

@author Murilo Marques Marinho
@version 1.1
*/

#include"tokenTable.h"
#include"line.h"
#include"token.h"
#include<stdlib.h>
#include<stdio.h>

/**
Aloca espaco na memoria para uma nova TokenTable.

@param tt O ** para a nova TokenTable
*/
void newTokenTable(TokenTable **tt){

	(*tt) = (TokenTable*)malloc(sizeof(TokenTable));

	(*tt)->firstLine = NULL;
}

/**
Adiciona uma Line na TokenTable

Adiciona na primeira linha cuja proxima linha e NULL

@param l A Line a ser adicionada
@param tt A TokenTable a ter essa Line adicionada
*/
void addLineToTokenTable( Line **l,  TokenTable **tt){
	if((*tt)->firstLine == NULL){
		(*tt)->firstLine = (*l);
		return;
	}
	else{
		 Line *d_l;/*Dummy Line*/
		for(d_l = (*tt)->firstLine; d_l->nextLine != NULL; d_l = d_l->nextLine);
		d_l->nextLine = (*l);
		return;
	}

}

/**
Libera a TokenTable da memoria

@param tt a TokenTable que sera liberada
*/
void freeTokenTable( TokenTable** tt){
	 Line *l;
  
	if((*tt)->firstLine != NULL){
		for(;;){
			l = (*tt)->firstLine;
			if((*tt)->firstLine->nextLine == NULL){
				freeLine(&(*tt)->firstLine);
				free(*tt);
				*tt = NULL;
				return;
			}
			(*tt)->firstLine = (*tt)->firstLine->nextLine;
			l->nextLine = NULL;
			freeLine(&l);
		}

	}
	else{
		free(*tt);
		*tt = NULL;
	}
}
