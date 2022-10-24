/**
Armazena as funções de uma DirTable

@author Murilo Marques Marinho
@version 1.0
*/



#include"dirline.h"
#include"dirtable.h"
#include"directives.h"
#include<stdlib.h>
#include<stdio.h>


/**
Aloca uma nova DirTable na memória e inicializa seus valores.

@param dirTable O ponteiro para essa nova região alocada.
*/
void newDirTable(DirTable** dirTable){

	DirTable* newDirTable;

	newDirTable = (DirTable*)malloc(sizeof(DirTable));
	newDirTable->firstLine = NULL;

	(*dirTable) = newDirTable;
	#if DEBUG
	printf("\n\tNew DirTable created.\n");
	#endif
	return;
}


/**
Adiciona uma DirLine já alocada a uma DirTable já alocada.

@param dirTable a DirTable na qual se quer adicionar a DirLine
@param dirLine a DirLine que se deseja adicionar
*/
void addDirLineToDirTable(DirTable** dirTable, DirLine** dirLine){

	DirLine* dummyLine;

	if((*dirTable)->firstLine == NULL){
		(*dirTable)->firstLine = (*dirLine);
	
		#if DEBUG
		printf("\n\tNew Code Machine Line added to DirTable.\n");
		#endif

		return;
	}


	for(dummyLine = (* dirTable)->firstLine; dummyLine->nextLine != NULL; dummyLine = dummyLine->nextLine);
	dummyLine->nextLine = (*dirLine);

	#if DEBUG
	printf("\n\tNew Code Machine Line added to DirTable\n");
	#endif
	
	return;
}

/**
Libera a DirTable da memória.

@param dt A DirTable que se deseja liberar.
*/
void freeDirTable(DirTable** dt){
	DirLine *dl;
  
	if((*dt)->firstLine != NULL){
		for(;;){
			dl = (*dt)->firstLine;
			if((*dt)->firstLine->nextLine == NULL){
				free((*dt)->firstLine);
				free(*dt);
				*dt = NULL;
				return;
			}
			(*dt)->firstLine = (*dt)->firstLine->nextLine;
			dl->nextLine = NULL;
			if(dl->dirType == 1){
				DirDB* dd = ((DirDB*)dl->directive);
				freeDirDB(&dd);
			}
			if(dl->dirType == 2){
				free(dl->directive);
			}
			free(dl);
		}

	}
	else{
		free(*dt);
		*dt = NULL;
	}
}

