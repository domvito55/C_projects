/**
Armazena as funções de uma MCLine

@author Murilo Marques Marinho
@version 1.0
*/

#include<stdlib.h>
#include"mcline.h"
/**
Amazena o espaco em memoria e inicializa os componentes de uma MCLine.

@param mcLine Um MCLine que sera inicializado.
*/
void newMCLine(MCLine** mcLine){
	MCLine* newMCLine;

	#if DEBUG
	printf("\n\tNewline malloc...\n");
	#endif
	newMCLine = (MCLine *)malloc(sizeof(MCLine ) );
	#if DEBUG
	printf("\n\tNewline malloced.\n");
	#endif


	newMCLine->nextLine = NULL;
	newMCLine->inst = NULL;

	(*mcLine) = newMCLine;

	#if DEBUG
	printf("\n\tNew MCLine created.\n");
	#endif

	return;
}


