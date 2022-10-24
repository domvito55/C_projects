/**
Armazenas a estrutura de uma DefinitionLine

@author Murilo Marques Marinho
@version 1.1
*/


#ifndef definition_LINE_HEADER_GUARD
#define definition_LINE_HEADER_GUARD


/**
Estrutura de uma definitionLine.
As linhas de uma definitionTable.
*/
typedef struct DefinitionLine{
	/**
	O valor em string que representa a label	
	*/
	char *label;
	/**
	Proxima definitionLine	
	*/
	struct DefinitionLine *nextDefLine;
}DefinitionLine;

extern void newDefinitionLine(struct DefinitionLine **definitionLine, char* nome);

#endif
