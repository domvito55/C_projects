/**
Armazena as funções de uma Line

@author Murilo Marques Marinho
@version 1.1
*/
#include"token.h"
#include"line.h"
#include<stdlib.h>

/**
Aloca espaco na memoria para uma nova linha e inicializa seus componentes.

@param l O ponteiro para essa nova Line
*/
void newLine( Line **l){

	(*l) = ( Line*)malloc(sizeof( Line));
	(*l)->firstToken = NULL;
	(*l)->nextLine = NULL;

}

/**
Adiciona uma Token a uma Line

@param l A Line na qual se deseja adicionar a Token
@param t A Token que se deseja adicionar
*/
void addTokenToLine(Line **l,Token **t){
	Token *d_t;

	if((*l)->firstToken == NULL){
		(*l)->firstToken = (*t);
		return;
	}
	for(d_t = (*l)->firstToken; d_t->nextToken != NULL; d_t = d_t->nextToken);
	d_t->nextToken = (*t);

	return;
}

/**
Adiciona uma nova Token a Line

@param l A Line na qual se deseja inserir a Token
@param nome A string que define a token
@see newToken()
@see addTokenToLine()
*/
void addNewTokenToLine(Line **l, char *nome){
	Token *t;

	newToken(&t, nome);

	addTokenToLine(l, &t);
}


/**
Libera a Line da memoria

@param l a Line que sera liberada
*/
void freeLine( Line** l){
	 Token *t;
  
	if((*l)->firstToken != NULL){
		for(;;){
			t = (*l)->firstToken;
			if((*l)->firstToken->nextToken == NULL){
				free((*l)->firstToken);
				free(*l);
				*l = NULL;
				return;
			}
			(*l)->firstToken = (*l)->firstToken->nextToken;
			t->nextToken = NULL;
			free(t->nome);
			t->nome = NULL;
			free(t);
		}

	}
	else{
		free(*l);
		*l = NULL;
	}
}
