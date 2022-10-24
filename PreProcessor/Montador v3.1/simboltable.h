/**
Armazena a estrutura de uma SimbolTable

@author Murilo Marques Marinho
@version 1.1
*/

#ifndef SIMBOL_TABLE_HEADER_GUARD
#define SIMBOL_TABLE_HEADER_GUARD
/**
A raiz de uma lista encadeada de SimbolLine.
*/
typedef struct SimbolTable{
	/**
	A primeira SimbolLine
	*/
	struct SimbolLine *firstSimbolLine;
}SimbolTable;

extern void newSimbolTable(struct SimbolTable **SimbolTable);

extern int addSimbolLineToSimbolTable(struct SimbolLine **SimbolLine, struct SimbolTable **SimbolTable);

extern void freeSimbolTable(SimbolTable** simboltable);

extern int isExtern(SimbolTable **st, char* label);


#endif
