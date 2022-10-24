/**
Armazena a estrutura de uma UseTable

@author Murilo Marques Marinho
@version 1.0
*/


#ifndef USE_TABLE_HEADER_GUARD
#define USE_TABLE_HEADER_GUARD
/**
A raiz de uma lista encadeada de UseLine.
*/
typedef struct UseTable{
	/**
	A primeira UseLine
	*/
	struct UseLine *firstUseLine;
}UseTable;

extern void newUseTable(struct UseTable **UseTable);

extern void addUseLineToUseTable(struct UseLine **UseLine, struct UseTable **UseTable);

extern void freeUseTable(UseTable** Usetable);


#endif
