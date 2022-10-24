/**
Armazenas as funções de uma DirLine

@author Murilo Marques Marinho
@version 1.0
*/


#include"dirline.h"
#include<stdlib.h>
#include<stdio.h>

/**
Aloca a nova DirLine na memória

@param dirLine o pointeiro para a Dirline que será alocada.
*/
void newDirLine(DirLine** dirLine){
	DirLine* newDirLine;

	newDirLine = (DirLine *)malloc(sizeof(DirLine));

	newDirLine->nextLine = NULL;
	newDirLine->directive = NULL;

	(*dirLine) = newDirLine;

	return;
}
