/**
Armazena as funções de uma SimbolTable

@author Murilo Marques Marinho
@version 1.1
*/

#include"simbolline.h"
#include"simboltable.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>


/**
Inicializa uma SimbolTable

@param SimbolTable a SimbolTable que se deseja inicializar.
*/
void newSimbolTable(struct SimbolTable **st){

	(*st) = (struct SimbolTable*)malloc(sizeof(struct SimbolTable));
	(*st)->firstSimbolLine = NULL;

}

/**
Adiciona uma SimbolLine a uma SimbolTable.
Adiciona automaticamente a primeira SimbolLine cujo nextSimbolLine e NULL, ou a firstSimbolLine.
Verifica automaticamente se esta se tentando adicionar uma label repetida.
Há diferenciação entre maiúsculas e minúsculas na verificação, então PSW: e psw: seriam labels diferentes.

@param SimbolTable a SimbolTable na qual se deseja adicionar a SimbolLine
@param SimbolLine a SimbolLine que se deseja adicionar.
@return 0 Adicao sem problemas.
@return 1 Simbolo Repetido.
*/
int addSimbolLineToSimbolTable(struct SimbolLine **sl, struct SimbolTable **st){


	/*Verifica se a primeira linha eh NULL*/
	if((*st)->firstSimbolLine == NULL){
		(*st)->firstSimbolLine = (*sl);
		return 0;
	}
	/*Se nao for null...*/
	else{
		struct SimbolLine *d_sl;/*Dummy Simbol Line*/
		/*Anda por todas as linhas ate que a proxima seja NULL*/
		for(d_sl = (*st)->firstSimbolLine; d_sl->nextSimbolLine != NULL; d_sl = d_sl->nextSimbolLine){

			/*Verifica igualdade*/
			if(!strcmp((*sl)->label,d_sl->label) ){
					return 1;
			}
		}
		/*Verifica se a Linha atual, cujo proximo eh NULL, eh igual a que se quer adicionar*/
		if(!strcmp((*sl)->label,d_sl->label) ){
				return 1;
		}

		/*Adiciona e retorna*/
		d_sl->nextSimbolLine = (*sl);
		return 0;
	}

}

/**
Verifica se uma determinada label e EXTERN.

@param st Ponteiro para a SimbolTable.
@param label A String que representa essa label.
@return 1 Se for EXTERN.
	0 Se nao for EXTERN.
*/
int isExtern(SimbolTable **st, char* label){
	SimbolLine* sl;


	if((*st)->firstSimbolLine == NULL){
		return 0;
	}
	for(sl = (*st)->firstSimbolLine; sl != NULL; sl = sl->nextSimbolLine){
		if(!strcmp(sl->label, label)){
			if(sl->externo){
				return 1;
			}
			return 0;
		}
	}
	return 0;


}

/**
Libera a SimbolTable da memoria

@param SimbolTable a SimbolTable que sera liberada
*/
void freeSimbolTable(SimbolTable** st){
	SimbolLine *sl;
  
	if((*st)->firstSimbolLine != NULL){
		for(;;){
			sl = (*st)->firstSimbolLine;
			if((*st)->firstSimbolLine->nextSimbolLine == NULL){
				free((*st)->firstSimbolLine);
				free(*st);
				*st = NULL;
				return;
			}
			(*st)->firstSimbolLine = (*st)->firstSimbolLine->nextSimbolLine;
			sl->nextSimbolLine = NULL;
			free(sl);
		}

	}
	else{
		free(*st);
		*st = NULL;
	}
}


