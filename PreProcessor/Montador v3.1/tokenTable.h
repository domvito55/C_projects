/**
Armazena a estrutura de uma TokenTable

@author Murilo Marques Marinho
@version 1.1
*/

#ifndef TOKENTABLE_HEADER_GUARD
#define TOKENTABLE_HEADER_GUARD

/**
Raiz da tabela de Token.
E basicamente uma lista encadeada de listas encadeadas.

@see Line
@see Token
*/
typedef struct TokenTable{
	/**
	Primeira linha da tabela
	*/
	struct Line *firstLine;
}TokenTable;

extern void newTokenTable(struct TokenTable **tokenTable);
extern void addLineToTokenTable(struct Line **line, struct TokenTable **tokenTable);
extern void printTokenTable(struct TokenTable *tokenTable);
extern void freeTokenTable(struct TokenTable** tt);

#endif
