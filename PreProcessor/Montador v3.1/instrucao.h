/**
Armazena as flags de tipo e a estrutura de uma instrução.

@author Murilo Marques Marinho
*/



/**
Flag que identifica se o operando pode ser um Registrador.
@see addReg()
*/
#define R_FLAG 0x01
/**
Flag que identifica se o operando pode ser um Par de Registradores.
@see addRegPair()
*/
#define RP_FLAG 0x04
/**
Flag que identifica se o operando pode ser uma Label.
@see addLabel()
*/
#define L_FLAG 0x08
/**
Flag que identifica se o operando pode ser um Imediato.
@see addIm()
*/
#define I_FLAG 0x10

/**
EXCECOES
*/

/**
Flag que identifica se a ordem de construcao da Instrucao deve ser invertida. Necessario para algumas instrucoes.
O tipo do operando PRECISA ter um OR com R_FLAG

*/
#define INV_FLAG 0x20
/**
Flag que indentica que so os registradores B e D sao possiveis na instrucao. Para STAX e LDAX.
O tipo do operando PRECISA ter um OR com RP_FLAG.

@see RP_FLAG
*/
#define BD_FLAG 0x40
/**
Flag que identifica que a instrucao usa PSW no lugar do SP. Para PUSH e POP
O tipo da instrucao PRECISA ter um OR com RP_FLAG.

@see RP_FLAG
*/
#define PSW_FLAG 0x80
/**
Flag que identifica a peculiar funcao RST
O tipo da instrucao PRECISA ter um OR com I_FLAG

@see I_FLAG
*/
#define RST_FLAG 0x02
/**
Flag que identifica que a função aceita registradores mas seu opcode não é alterado.
O tipo da instrucao PRECISA ter um OR com R_FLAG

@see R_FLAG
*/
#define RNC_FLAG 0x100
/**
Flag que identifica que a funcao MOV ja recebeu M como seu primeiro operando.
Nao deve ser atribuido inicialmente a nada.

*/
#define MMOV_FLAG 0x200


#ifndef DEBUG
#define DEBUG 0
#endif




/**
A estrutura de uma Instrucao

@see newInst()
*/
typedef struct Inst{
	/**
	Bem... o opcode
	*/
	unsigned int opcode;
	/**
	O tamanho da instrucao, em bytes	
	*/
	int size;
	/**
	Numero de operandos
	*/
	int nop;

		/**
		Tipos possiveis para o operando 1. 
		@see R_FLAG
		@see I_FLAG
		@see RP_FLAG
		@see L_FLAG
                */
		unsigned int tipo1;
		/**
		Tipos possiveis para o operando 2.
		@see R_FLAG
		@see I_FLAG
		@see RP_FLAG
		@see L_FLAG
                */
		unsigned int tipo2;
		/**
		O char* que armazena o nome da label, caso seja um operando.
		*/
		char* label;
		/**
		Int que avisa que a label ja foi codificada, para casos que o usuario inserir o endereco.
		*/
		int labelcoded;
} Inst;

extern int newInst(Inst** inst, char* nome);

	extern int addReg(char* nome,Inst** inst, int opNumber);

	extern int addRegPair(char* nome,Inst** inst);

	extern int addIm(char* nome,Inst** inst, int opnumber);

	extern int addLabel(char* nome,Inst** inst, int opnumber);

extern int isLabel(char *nome);

extern void labelClear(char **nome);

extern int isNumericalLabel(char *nome);

extern int isDecimalNumber(char *nome);

extern int numericalLabelClear(char *nome);

extern int getStringSize(char* string);

extern char* stolower(char* s);

extern int strToPosInt(char* n);



