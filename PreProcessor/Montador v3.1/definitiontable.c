/**
Armazenas as funções de uma DefinitionTable

@author Murilo Marques Marinho
@version 1.1
*/


#include"definitionline.h"
#include"definitiontable.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>


/**
Inicializa uma definitionTable

@param definitionTable a definitionTable que se deseja inicializar.
*/
void newDefinitionTable(struct DefinitionTable **definitionTable){
	struct DefinitionTable *newdefinitionTable;
	newdefinitionTable = (struct DefinitionTable*)malloc(sizeof(struct DefinitionTable));
	newdefinitionTable->firstDefLine = NULL;

	(*definitionTable) = newdefinitionTable;

	return;
}

/**
Adiciona uma definitionLine a uma definitionTable.
Adiciona automaticamente a primeira definitionLine cujo nextDefLine e NULL, ou a firstDefLine.
Verifica automaticamente se esta se tentando adicionar uma label repetida.

@param definitionTable a definitionTable na qual se deseja adicionar a definitionLine
@param definitionLine a definitionLine que se deseja adicionar.
@return 1 Se tudo ocorrer de maneira correta.
	0 Se a label for repetida. 
*/
int addDefinitionLineToDefinitionTable(struct DefinitionLine **definitionLine, struct DefinitionTable **definitionTable){

	/*Verifica se a primeira linha eh NULL*/
	if((*definitionTable)->firstDefLine == NULL){
		(*definitionTable)->firstDefLine = (*definitionLine);
		return 1;
	}
	/*Se nao for null...*/
	else{
		struct DefinitionLine *dummydefinitionLine;
		/*Anda por todas as linhas ate que a proxima seja NULL*/
		for(dummydefinitionLine = (*definitionTable)->firstDefLine; dummydefinitionLine->nextDefLine != NULL; dummydefinitionLine = dummydefinitionLine->nextDefLine){

			/*Verifica igualdade*/
			if(!strcmp((*definitionLine)->label,dummydefinitionLine->label) ){
					return 0;
			}
		}
		/*Verifica se a Linha atual, cujo proximo eh NULL, eh igual a que se quer adicionar*/
		if(!strcmp((*definitionLine)->label,dummydefinitionLine->label) ){
				return 0;
		}

		/*Adiciona e retorna*/
		dummydefinitionLine->nextDefLine = (*definitionLine);
		return 1;
	}

}

/**
Libera a definitionTable da memoria

@param definitionTable a definitionTable que sera liberada
*/
void freeDefinitionTable(DefinitionTable** st){
	DefinitionLine *sl;
  
	if((*st)->firstDefLine != NULL){
		for(;;){
			sl = (*st)->firstDefLine;
			if((*st)->firstDefLine->nextDefLine == NULL){
				free((*st)->firstDefLine);
				free(*st);
				*st = NULL;
				return;
			}
			(*st)->firstDefLine = (*st)->firstDefLine->nextDefLine;
			sl->nextDefLine = NULL;
			free(sl);
		}

	}
	else{
		free(*st);
		*st = NULL;
	}
}


