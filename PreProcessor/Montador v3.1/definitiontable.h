/**
Armazenas a estrutura de uma DefinitionTable

@author Murilo Marques Marinho
@version 1.0
*/


#ifndef definition_TABLE_HEADER_GUARD
#define definition_TABLE_HEADER_GUARD
/**
A raiz de uma lista encadeada de definitionLine.
*/
typedef struct DefinitionTable{
	/**
	A primeira definitionLine
	*/
	struct DefinitionLine *firstDefLine;
}DefinitionTable;

extern void newDefinitionTable(struct DefinitionTable **definitionTable);

extern int addDefinitionLineToDefinitionTable(struct DefinitionLine **definitionLine, struct DefinitionTable **definitionTable);

extern void freeDefinitionTable(DefinitionTable** definitiontable);


#endif
