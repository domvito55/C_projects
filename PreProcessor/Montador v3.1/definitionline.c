/**
Armazenas as funções de uma DefinitionLine

@author Murilo Marques Marinho
@version 1.1
*/

#include<stdlib.h>
#include"definitionline.h"
/**
Funcao de inicializacao de uma definitionLine.

@param definitionLine a definitionLine que se deseja inicializar.
@param nome A string com o nome da Label.
*/
void newDefinitionLine(struct DefinitionLine **definitionLine, char* nome){
	struct DefinitionLine *newdefinitionLine;
	newdefinitionLine = (struct DefinitionLine*)malloc(sizeof(struct DefinitionLine));
	newdefinitionLine->label = nome;
	newdefinitionLine->nextDefLine = NULL;

	(*definitionLine) = newdefinitionLine;
}


