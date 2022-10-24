/**
Armazena o tamanho dos buffers de entrada. Tamanho máximo de linhas e tokens são modificados aqui.

@author Murilo Marques Marinho
@version 1.2
*/

#ifndef LEXIC_ANALISER_HEADER_GUARD
#define LEXIC_ANALISER_HEADER_GUARD
/**
@brief Tamanho maximo de uma linha.
*/
#define MAX_LINE_BUFFER_SIZE 100
/**
@brief Tamanho maximo de uma token.
*/
#define MAX_TOKEN_BUFFER_SIZE 30

#include"line.h"
#include"tokenTable.h"

extern int tokenMaker(char line[], int lineSize, struct Line **lineStruct);

extern int lexicAnalise(struct TokenTable **tokenTable, FILE *fp);

#endif
