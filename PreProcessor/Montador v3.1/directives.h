/**
Armazena estruturas relativas a diretivas.

@author Murilo Marques Marinho
*/


#ifndef DIRECTIVES_HEADER_GUARD
#define DIRECTIVES_HEADER_GUARD
#include"token.h"
#include"dirline.h"

/**
A estrutura de uma DirDB, relativa a uma diretiva DB.

*/
typedef struct DirDB{
	/**
	Numero de bytes que essa diretiva ocupará na memória
	*/
	int size;
	/**
	Ponteiro para a primeira DirDBPart, ou seja, o primeiro valor dessa DirDB
	*/
	struct DirDBPart* firstValue;
} DirDB;

/**
A estrutura de uma DirDBPart que permite alocação dinâmica dos bytes da diretiva DB.
*/
typedef struct DirDBPart{
	/**
	O valor armazenado por essa DirDBPart
	*/
	int value;
	/**
	O próximo valor
	*/
	struct DirDBPart* nextValue;
} DirDBPart;

/**
A estrutura de uma diretiva DirDS, relativa a uma diretiva DS
*/
typedef struct DirDS{
	/**
	A quantidade de bytes a serem reservados na memória
	*/
	int size;
} DirDS;

extern int addDirective(DirLine **dirline, struct Token* token);

extern int newDirDS(DirDS** dirds , char* nome);

extern void newDirDBPart(DirDBPart** dirdbpart , int value);

extern int addDirDBPart(DirDB** dirdb , char* nome);

extern int newDirDB(DirDB** dirdb , struct Token* token);

extern void freeDirDB(DirDB** dd);


#endif
