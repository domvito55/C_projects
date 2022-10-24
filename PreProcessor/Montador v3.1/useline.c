/**
Armazena as funções de uma UseLine

@author Murilo Marques Marinho
@version 1.2
*/

#include<stdlib.h>
#include"useline.h"
/**
Funcao de inicializacao de uma UseLine.

@param UseLine a UseLine que se deseja inicializar.
@param nome A string com o nome da Label.
*/
void newUseLine(UseLine **ul, char* nome){

	(*ul) = (UseLine*)malloc(sizeof(UseLine));
	(*ul)->label = nome;
	(*ul)->nextUseLine = NULL;
	(*ul)->valor = 0;
	(*ul)->name = 0;

}


