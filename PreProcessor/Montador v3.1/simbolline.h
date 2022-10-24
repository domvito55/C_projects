/**
Armazena a estrutura de uma SimbolLine.

@author Murilo Marques Marinho
@version 1.2
*/

#ifndef SIMBOL_LINE_HEADER_GUARD
#define SIMBOL_LINE_HEADER_GUARD


/**
Estrutura de uma SimbolLine.
As linhas de uma SimbolTable.
*/
typedef struct SimbolLine{
	/**
	O valor em string que representa a label	
	*/
	char *label;
	/**
	O valor que representa o endereco
	*/
	int valor;
	/**
	Basicamente um booleano que indica se a funcao e externa ou interna
	*/
	int externo;
	/**
	Indica se o simbolo aponta para .text (istextsim == 1) ou .data (istextsim == 0)
	*/
	int istextsim;
	/**
	Indica o indice na StrTab desse simbolo
	*/
	int name;
	/**
	Indica se o simbolo e publico
	*/
	int publico;
	/**
	Proxima SimbolLine	
	*/
	struct SimbolLine *nextSimbolLine;
}SimbolLine;

extern void newSimbolLine(struct SimbolLine **SimbolLine, char* nome);

#endif
