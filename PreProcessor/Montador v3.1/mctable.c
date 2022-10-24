/**
Armazena as funções de uma MCTable

@author Murilo Marques Marinho
@version 1.1
*/


#include<stdlib.h>
#include<stdio.h>
#include"mcline.h"
#include"mctable.h"

/**
Aloca espaco na memoria e inicializa os componentes de uma MCTable

@param mt A MCTable que se deseja inicializar.
*/
void newMCTable(MCTable** mt){

	(*mt) = (MCTable*) malloc(sizeof(MCTable));

	(*mt)->firstLine = NULL;

	#if DEBUG
	printf("\n\tNew MCTable created.\n");
	#endif
	return;
}

/**
Adiciona uma MCLine a uma MCTable.
Automaticamente insere na primeira MCLine cujo nextLine seja NULL.

@param mt A MCTable na qual se deseja adicionar a MCLine.
@param ml A MCLine a ser adicionada.
*/
void addMCLineToMCTable(MCTable** mt, MCLine** ml){

	MCLine* l;

	if((*mt)->firstLine == NULL){
		(*mt)->firstLine = (*ml);
	
		#if DEBUG
		printf("\n\tNew Code Machine Line added to MCTable.\n");
		#endif

		return;
	}


	for(l = (* mt)->firstLine; l->nextLine != NULL; l = l->nextLine);
	l->nextLine = (*ml);

	#if DEBUG
	printf("\n\tNew Code Machine Line added to MCTable\n");
	#endif
	
	return;
}


/**
Libera a MCTable da memoria

@param mt a MCTable que sera liberada
*/
void freeMCTable(MCTable** mt){
	MCLine *ml;
  
	if((*mt)->firstLine != NULL){
		for(;;){
			ml = (*mt)->firstLine;
			if((*mt)->firstLine->nextLine == NULL){
				free((*mt)->firstLine);
				free(*mt);
				*mt = NULL;
				return;
			}
			(*mt)->firstLine = (*mt)->firstLine->nextLine;
			ml->nextLine = NULL;
			free(ml->inst);
			free(ml);
		}

	}
	else{
		free(*mt);
		*mt = NULL;
	}
}


