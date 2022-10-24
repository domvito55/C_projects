/**
Armazena as funções de uma UseTable

@author Murilo Marques Marinho
@version 1.1
*/

#include"useline.h"
#include"usetable.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>


/**
Inicializa uma UseTable

@param UseTable a UseTable que se deseja inicializar.
*/
void newUseTable(UseTable **ut){

	(*ut) = (UseTable*)malloc(sizeof(UseTable));

	(*ut)->firstUseLine = NULL;
}

/**
Adiciona uma UseLine a uma UseTable.
Adiciona automaticamente a primeira UseLine cujo nextUseLine e NULL, ou a firstUseLine.

@param UseTable a UseTable na qual se deseja adicionar a UseLine
@param UseLine a UseLine que se deseja adicionar.
*/
void addUseLineToUseTable(UseLine **ul ,UseTable **ut){

	/*Verifica se a primeira linha eh NULL*/
	if((*ut)->firstUseLine == NULL){
		(*ut)->firstUseLine = (*ul);
		return;
	}
	/*Se nao for null...*/
	else{
		UseLine *d_ul;/*Dummy UseLine*/
		/*Anda por todas as linhas ate que a proxima seja NULL*/
		for(d_ul = (*ut)->firstUseLine; d_ul->nextUseLine != NULL; d_ul = d_ul->nextUseLine);
		/*Adiciona e retorna*/
		d_ul->nextUseLine = (*ul);
		return;
	}

}

/**
Libera a UseTable da memoria

@param UseTable a UseTable que sera liberada
*/
void freeUseTable(UseTable** st){
	UseLine *sl;
  
	if((*st)->firstUseLine != NULL){
		for(;;){
			sl = (*st)->firstUseLine;
			if((*st)->firstUseLine->nextUseLine == NULL){
				free((*st)->firstUseLine);
				free(*st);
				*st = NULL;
				return;
			}
			(*st)->firstUseLine = (*st)->firstUseLine->nextUseLine;
			sl->nextUseLine = NULL;
			free(sl);
		}

	}
	else{
		free(*st);
		*st = NULL;
	}
}


