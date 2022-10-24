/*
**	___________________estruturas.c___________________
**		
**	Todas as estruturas utilizadas no programa (exceto as do elf).
**	
**	___________________estruturas.c___________________
**/

typedef struct elementotabela{		/*Estrutura da tabela*/
	int opcode;
	int tipo;
	char nome[9];
	struct elementotabela *next;
} tabelaS;

typedef struct elementolabel{		/*Estrutura das labels*/
	char *label;
	int endereco;
	struct elementolabel *next;
} labelS;

typedef struct code{ 			/*Estrutura do código*/
	int *codigocompleto;
	int endereco;
} codeS;

typedef struct data{ 			/*Estrutura do data new*/
	int *datacompleto;
	int endereco;
} dataS;

typedef struct undados{			/*Estrutura dos dados (.bss)*/
	int quantidade;
	int endereco;
} undadosS;

typedef struct listaend{		/*Estrutura dos dados (.bss)*/
	int *endereco;
} listaendS;
