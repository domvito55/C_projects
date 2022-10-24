/**
Armazena as funções de uma Token

@author Murilo Marques Marinho
@version 1.2
*/

#include"token.h"
#include<stdlib.h>

/**
Aloca espaco na memoria para uma nova Token e inicializa seus valores.

@param token Ponteiro para essa nova Token alocada
@param nome String que representa essa Token
*/
void newToken(Token **t, char *nome){

	(*t) = (Token*)malloc(sizeof(Token));

	(*t)->nome = nome;

	(*t)->nextToken = NULL;

}

