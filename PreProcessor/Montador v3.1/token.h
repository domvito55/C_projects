/**
Armazena a estrutura de uma Token

@author Murilo Marques Marinho
@version 1.1
*/

#ifndef TOKEN_HEADER_GUARD
#define TOKEN_HEADER_GUARD
/**
Estrutura de uma Token

@see TokenTable
@see Line
*/
typedef struct Token{
	/**
	String que representa a token
	*/
	char *nome;
	/**
	Ponteiro para a proxima Token
	*/
	struct Token *nextToken;
} Token;

extern void newToken(struct Token **token, char *nome);
#endif
