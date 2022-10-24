/**
Armazena a estrutura de uma MCTable

@author Murilo Marques Marinho
@version 1.1
*/

#ifndef MACHINE_CODE_TABLE
#define MACHINE_CODE_TABLE

/**
Estrutura de uma Machine Code Table.
A raiz da tabela, que aponta para a primeira MCLine.

Estrutura de uma lista encadeada.
*/
typedef struct MCTable{
	/**
	Ponteiro para a primeira linha (MCLine) da tabela.		
	*/
	MCLine* firstLine;
} MCTable;

extern void newMCTable(MCTable** mcTable);

extern void addMCLineToMCTable(MCTable** mcTable, MCLine** mcLine);

extern void freeMCTable(MCTable** mt);




#endif
