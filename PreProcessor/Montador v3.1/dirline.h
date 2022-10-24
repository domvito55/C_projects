/**
Armazenas a estrutura de uma DirLine

@author Murilo Marques Marinho
@version 1.0
*/


#ifndef DIRLINE_HEADER_GUARD
#define DIRLINE_HEADER_GUARD

/**
Linha da estrutura DirTable, que formará a estrutura de dados que armazena as diretivas.

*/
typedef struct DirLine{
	/**
	Próxima linha
	*/
	struct DirLine* nextLine;

	/**
	Avisa para o programa o tipo da diretiva, para que ele possa fazer corretamente o casting do void* directive
	1 == DB
	2 == DS
	*/
	int dirType;
	/**
	Ponteiro flexível para a diretiva
	*/
	void * directive;
} DirLine;

extern void newDirLine(DirLine** dirLine);

#endif
