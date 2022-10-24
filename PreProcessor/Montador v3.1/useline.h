/**
Armazena a estrutura de uma UseLine

@author Murilo Marques Marinho
@version 1.1
*/


#ifndef USE_LINE_HEADER_GUARD
#define USE_LINE_HEADER_GUARD


/**
Estrutura de uma UseLine.
As linhas de uma UseTable.
*/
typedef struct UseLine{
	/**
	O valor em string que representa a label	
	*/
	char *label;
	/**
	O valor que representa o endereco
	*/
	int valor;
	/**
	O indice na StrTab que representa esse simbolo
	*/
	int name;
	/**
	Proxima UseLine	
	*/
	struct UseLine *nextUseLine;
}UseLine;

extern void newUseLine(struct UseLine **UseLine, char* nome);

#endif
