/**
Armazena as funções de uma SimbolLine

@author Murilo Marques Marinho
@version 1.3
*/

#include<stdlib.h>
#include"simbolline.h"
/**
Funcao de inicializacao de uma SimbolLine.

@param SimbolLine a SimbolLine que se deseja inicializar.
@param nome A string com o nome da Label.
*/
void newSimbolLine(struct SimbolLine **sl, char* nome){
	(*sl) = (struct SimbolLine*)malloc(sizeof(struct SimbolLine));
	(*sl)->label = nome;
	(*sl)->nextSimbolLine = NULL;
	(*sl)->valor = 0;
	(*sl)->externo = 0;
	(*sl)->istextsim = 0;
	(*sl)->name = 0;
	(*sl)->publico = 0;
}


