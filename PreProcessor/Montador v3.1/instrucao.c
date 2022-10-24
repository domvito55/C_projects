/**
Armazena todas as funcoes relativas a construcao de instrucoes.
Em seu codigo esta escrita toda a tabela de instrucoes necessaria para a 
construcao.

Lida com a construcao e ajuste de Labels.
Lida com a construcao e ajuste de Imediatos.
Lida com a construcao e ajuste de Registradores, Pares de Registradores.
Lida com as excessoes.


@version 1.2
@author Murilo Marques Marinho
*/


#include"instrucao.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<ctype.h>

/**
Inicializa uma instrucao dada uma string com seu mnemonico.
Dentro dessa funcao ele verifica se a funcao existe, e inicializa com todos seus valores especificos.

@param inst A instrucao que se quer inicializar.
@param nome O mnemonico da funcao.
@return 0 se o mnemonico nao foi encontrado
@return 1 se o mnemonico foi encontrado
*/
int newInst(Inst** inst, char* nome){

	Inst* newInst = (Inst*)malloc(sizeof(Inst));
	newInst->tipo1 = 0;
	newInst->tipo2 = 0;
	newInst->opcode = 0;
	newInst->label = NULL;
	newInst->labelcoded = 0;
	
	/*#1*/
	if(!strcmp(nome, "add")){
		newInst->opcode = 0x80;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (R_FLAG);

	}
	else if(!strcmp(nome, "mov")){
		newInst->opcode = 0x40;
		newInst->size = 1;
		newInst->nop = 2;
		newInst->tipo1 = (R_FLAG);
		newInst->tipo2 = (R_FLAG);
	}
	else if(!strcmp(nome, "sub")){
		newInst->opcode = 0x90;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (R_FLAG);

	}
	else if(!strcmp(nome, "inx")){
		newInst->opcode = 0x03;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (RP_FLAG);

	}
	else if(!strcmp(nome, "adi")){
		newInst->opcode = 0xC6;
		newInst->size = 2;
		newInst->nop = 1;
		newInst->tipo1 = (I_FLAG);

	}
	else if(!strcmp(nome, "jmp")){
		newInst->opcode = 0xC3;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = (L_FLAG);

	}
	else if(!strcmp(nome, "lxi")){
		newInst->opcode = 0x01;
		newInst->size = 3;
		newInst->nop = 2;
		newInst->tipo1 = (RP_FLAG);
		newInst->tipo2 = (L_FLAG);

	}
	else if(!strcmp(nome, "ana")){
		newInst->opcode = 0xA0;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (R_FLAG);

	}
	else if(!strcmp(nome, "ora")){
		newInst->opcode = 0xB0;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (R_FLAG);

	}
	/*#10*/
	else if(!strcmp(nome, "adc")){
		newInst->opcode = 0x88;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (R_FLAG);

	}
	else if(!strcmp(nome, "sbb")){
		newInst->opcode = 0x98;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (R_FLAG);

	}
	else if(!strcmp(nome, "xra")){
		newInst->opcode = 0xA8;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (R_FLAG);

	}
	else if(!strcmp(nome, "cmp")){
		newInst->opcode = 0xB8;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (R_FLAG);

	}
	else if(!strcmp(nome, "mvi")){
		newInst->opcode = 0x06;
		newInst->size = 2;
		newInst->nop = 2;
		newInst->tipo1 = (R_FLAG) | (INV_FLAG);
		newInst->tipo2 = (I_FLAG);
	}					
	else if(!strcmp(nome, "inr")){
		newInst->opcode = 0x04;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (R_FLAG) | (INV_FLAG);
	}
	else if(!strcmp(nome, "dcr")){
		newInst->opcode = 0x05;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (R_FLAG) | (INV_FLAG);
	}
	else if(!strcmp(nome, "dad")){
		newInst->opcode = 0x09;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (RP_FLAG);
	}
	else if(!strcmp(nome, "dcx")){
		newInst->opcode = 0x0B;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (RP_FLAG);
	}
	else if(!strcmp(nome, "lxi")){
		newInst->opcode = 0x01;
		newInst->size = 3;
		newInst->nop = 2;
		newInst->tipo1 = (RP_FLAG);
		newInst->tipo2 = (L_FLAG);
	}
	/*#20*/
	else if(!strcmp(nome, "nop")){
		newInst->opcode = 0x00;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "arhl")){
		newInst->opcode = 0x10;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "rim")){
		newInst->opcode = 0x20;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "sim")){
		newInst->opcode = 0x30;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "rlc")){
		newInst->opcode = 0x07;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "ral")){
		newInst->opcode = 0x17;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "daa")){
		newInst->opcode = 0x27;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "stc")){
		newInst->opcode = 0x37;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "shld")){
		newInst->opcode = 0x22;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "sta")){
		newInst->opcode = 0x32;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	/*#30*/
	else if(!strcmp(nome, "lhld")){
		newInst->opcode = 0x2A;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "lda")){
		newInst->opcode = 0x3A;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "jz")){
		newInst->opcode = 0xCA;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "jc")){
		newInst->opcode = 0xDA;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "jpe")){
		newInst->opcode = 0xEA;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "jm")){
		newInst->opcode = 0xFA;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "stax")){
		newInst->opcode = 0x02;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (RP_FLAG | BD_FLAG);
	}
	else if(!strcmp(nome, "ldax")){
		newInst->opcode = 0x0A;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (RP_FLAG | BD_FLAG);
	}
	else if(!strcmp(nome, "pop")){
		newInst->opcode = 0xC1;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (RP_FLAG | PSW_FLAG);
	}
	else if(!strcmp(nome, "push")){
		newInst->opcode = 0xC5;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = (RP_FLAG | PSW_FLAG);
	}
	/*#40*/
	else if(!strcmp(nome, "rnz")){
		newInst->opcode = 0xC0;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "rnc")){
		newInst->opcode = 0xD0;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "rpo")){
		newInst->opcode = 0xE0;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "rp")){
		newInst->opcode = 0xF0;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "xthl")){
		newInst->opcode = 0xE3;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "di")){
		newInst->opcode = 0x37;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "rz")){
		newInst->opcode = 0xC8;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "rc")){
		newInst->opcode = 0xD8;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "rpe")){
		newInst->opcode = 0xE8;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "rm")){
		newInst->opcode = 0xF8;
		newInst->size = 1;
		newInst->nop = 0;
	}
	/*#50*/
	else if(!strcmp(nome, "ret")){
		newInst->opcode = 0xC9;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "shlx")){
		newInst->opcode = 0xD9;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "pchl")){
		newInst->opcode = 0xE9;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "sphl")){
		newInst->opcode = 0xF9;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "rstv")){
		newInst->opcode = 0xCB;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "xchg")){
		newInst->opcode = 0xEB;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "ei")){
		newInst->opcode = 0xFB;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "dsub")){
		newInst->opcode = 0x08;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "rdel")){
		newInst->opcode = 0x18;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "rrc")){
		newInst->opcode = 0x0F;
		newInst->size = 1;
		newInst->nop = 0;
	}
	/*#60*/
	else if(!strcmp(nome, "rar")){
		newInst->opcode = 0x1F;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "cma")){
		newInst->opcode = 0x2F;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "cmc")){
		newInst->opcode = 0x3F;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "ldhi")){
		newInst->opcode = 0x28;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = R_FLAG | RNC_FLAG;
	}
	else if(!strcmp(nome, "ldsi")){
		newInst->opcode = 0x38;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = R_FLAG | RNC_FLAG;
	}
	else if(!strcmp(nome, "jnz")){
		newInst->opcode = 0xC2;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "jnc")){
		newInst->opcode = 0xD2;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "jpo")){
		newInst->opcode = 0xE2;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "jp")){
		newInst->opcode = 0xF2;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "cnz")){
		newInst->opcode = 0xC4;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	/*#70*/
	else if(!strcmp(nome, "cnc")){
		newInst->opcode = 0xD4;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "cpo")){
		newInst->opcode = 0xE4;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "cp")){
		newInst->opcode = 0xF4;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "cz")){
		newInst->opcode = 0xCC;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "cc")){
		newInst->opcode = 0xDC;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "cpe")){
		newInst->opcode = 0xEC;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "cm")){
		newInst->opcode = 0xFC;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "call")){
		newInst->opcode = 0xCD;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "jnk")){
		newInst->opcode = 0xDD;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "lhlx")){
		newInst->opcode = 0xED;
		newInst->size = 1;
		newInst->nop = 0;
	}
	/*#80*/
	else if(!strcmp(nome, "jk")){
		newInst->opcode = 0xFD;
		newInst->size = 3;
		newInst->nop = 1;
		newInst->tipo1 = L_FLAG;
	}
	else if(!strcmp(nome, "out")){
		newInst->opcode = 0xD3;
		newInst->size = 2;
		newInst->nop = 1;
		newInst->tipo1 = (I_FLAG);
	}
	else if(!strcmp(nome, "sui")){
		newInst->opcode = 0xD6;
		newInst->size = 2;
		newInst->nop = 1;
		newInst->tipo1 = (I_FLAG);
	}
	else if(!strcmp(nome, "ani")){
		newInst->opcode = 0xE6;
		newInst->size = 2;
		newInst->nop = 1;
		newInst->tipo1 = (I_FLAG);
	}
	else if(!strcmp(nome, "ori")){
		newInst->opcode = 0xF6;
		newInst->size = 2;
		newInst->nop = 1;
		newInst->tipo1 = (I_FLAG);
	}
	else if(!strcmp(nome, "in")){
		newInst->opcode = 0xDB;
		newInst->size = 2;
		newInst->nop = 1;
		newInst->tipo1 = (I_FLAG);
	}
	else if(!strcmp(nome, "adi")){
		newInst->opcode = 0xC6;
		newInst->size = 2;
		newInst->nop = 1;
		newInst->tipo1 = (I_FLAG);
	}
	else if(!strcmp(nome, "aci")){
		newInst->opcode = 0xCE;
		newInst->size = 2;
		newInst->nop = 1;
		newInst->tipo1 = (I_FLAG);
	}
	else if(!strcmp(nome, "sbi")){
		newInst->opcode = 0xDE;
		newInst->size = 2;
		newInst->nop = 1;
		newInst->tipo1 = (I_FLAG);
	}
	else if(!strcmp(nome, "xri")){
		newInst->opcode = 0xEE;
		newInst->size = 2;
		newInst->nop = 1;
		newInst->tipo1 = (I_FLAG);
	}
	/*#90*/
	else if(!strcmp(nome, "cpi")){
		newInst->opcode = 0xFE;
		newInst->size = 2;
		newInst->nop = 1;
		newInst->tipo1 = (I_FLAG);
	}
	else if(!strcmp(nome, "hlt")){
		newInst->opcode = 0x76;
		newInst->size = 1;
		newInst->nop = 0;
	}
	else if(!strcmp(nome, "rst")){
		newInst->opcode = 0xC7;
		newInst->size = 1;
		newInst->nop = 1;
		newInst->tipo1 = I_FLAG | RST_FLAG;
	}
	/*INSIRA NOVAS INSTRUCOES AQUI*/
	else if(!newInst->opcode)
		return 0;
	
	(*inst) = newInst;
	#if DEBUG
	printf("\n\tInstruction created =  %s.\n", nome);
	#endif

	return 1;
}

/****************************************
**********[001]OPERANDOS*****************
****************************************/


	/**
	Funcao que adiciona um registrador ao opcode da instrucao.

	Verifica se o tipo do operando pode ser um Registrador e altera devidamente a codificacao caso INV_FLAG seja verdadeiro.
	Tambem cuida de nao modificar o opcode caso RNC_FLAG seja verdadeiro.

	@param nome A string que representa esse registrador.
	@param inst A estrutura que representa essa instrucao. Ja inicializada.
	@param opNumber O numero do operando. 1 para primeiro, 2 para segundo.
	
	@return 1 Se nome era um registrador valido e a funcao aceita registradores no operando opNumber.
	@return 0 Se nome nao era um registrador valido ou se a funcao nao aceita registradores como aquele operando.
	*/
	int addReg(char* nome,Inst** inst, int opNumber){
		/*Passa a entrada para minusculo*/		
		
		/*Verifica se a instrucao aceita registradores simples*/
		if((!((*inst)->tipo1 & R_FLAG)) && (opNumber == 1)){
			return 0;
		}
		if(!((*inst)->tipo2 & R_FLAG) && (opNumber == 2)){
			return 0;
		}


		if(((*inst)->tipo1 & R_FLAG)&&((*inst)->tipo2 & R_FLAG)){
			if(opNumber == 1)
				opNumber = 1;
			else if(opNumber == 2)
				opNumber = 0;
		}
		/*Verifica se a instrução requer inversão na adição de opcode*/
		else{
			if((*inst)->tipo1 & INV_FLAG){
				opNumber = 1;
			}
			else{
				opNumber = 0;
			}
		}

		/*Verifica se a instrução requer que o opcode permaneça inalterado. Armazena o opcode para ser devolvido posteriormente.
		Isso permite que ainda haja a verificacao mas que o opcode se mantenha o mesmo.	*/
		int holder;
		if((*inst)->tipo1 & RNC_FLAG){
			holder = (*inst)->opcode;
		}


		/*Compara e ajusta o opcode para o registrador. Senao encontrar na lista, houve problema.*/
		#if DEBUG
			printf("\n\tInstruction opcode:%x \n", (*inst)->opcode);
		#endif
		if(!strcmp(nome, "a")){
			(*inst)->opcode |= ((0x07)<<(opNumber*3));
		}
		else if(!strcmp(nome, "b")){
		}
		else if(!strcmp(nome, "c")){
			(*inst)->opcode |= ((0x01)<<(opNumber*3));
		} 
		else if(!strcmp(nome, "d")){
			(*inst)->opcode |= ((0x02)<<(opNumber*3));
		}
		else if(!strcmp(nome, "e")){
			(*inst)->opcode |= ((0x03)<<(opNumber*3));
		}
		else if(!strcmp(nome, "h")){
			(*inst)->opcode |= ((0x04)<<(opNumber*3));
		}
		else if(!strcmp(nome, "l")){
			(*inst)->opcode |= ((0x05)<<(opNumber*3));
		}
		else if(!strcmp(nome, "m")){
			(*inst)->opcode |= ((0x06)<<(opNumber*3));

			/*Adiciona aqui uma comparacao caso M seja usado como os dois operandos da funcao MOV*/
			if((*inst)->nop == 2 && opNumber == 1){
				(*inst)->tipo1 |= MMOV_FLAG;
			}
			else if(((*inst)->tipo1 & MMOV_FLAG) && (opNumber == 0)){
				return 0;
			}
		}
		else
			return 0;
		#if DEBUG
			printf("\n\tInstruction opcode after newReg:%x \n", (*inst)->opcode);
		#endif

		/*Devolve o opcode original da funcao, caso ela se enquadra na excessao RNC_FLAG*/
		if((*inst)->tipo1 & RNC_FLAG){
			(*inst)->opcode = holder;
		}
		
		return 1;	
	}



	/**
	Funcao que adiciona par de registradores ao opcode da instrucao.

	Verifica se o tipo do operando verifica tambem as excecoes de BD_FLAG e PSW_FLAG

	@param nome A string que representa esse registrador.
	@param inst A estrutura que representa essa instrucao. Ja inicializada.
	
	@return 1 Se nome era um par de registradores valido para a instrucao.
	@return 0 Se nome nao era um registrador valido ou se a funcao nao aceita par de registradores.
	*/	
	int addRegPair(char* nome,Inst** inst){

		/*Verifica se a instrucao aceita Par de Registradores*/
		if(!((*inst)->tipo1 & RP_FLAG)){
			return 0;
		}

		/*Compara e ajusta o opcode para o registrador. Senao encontrar na lista, houve problema.*/
		else if(!strcmp(nome, "b")){
			(*inst)->opcode |= (0x00);
		}
		else if(!strcmp(nome, "d")){
			(*inst)->opcode |= ((0x01)<<(4));
		}
		else if((!strcmp(nome, "h")) && (((*inst)->tipo1 & BD_FLAG)==0)){
			(*inst)->opcode |= ((0x02)<<(4));
		}
		else if(!strcmp(nome, "sp") && (((*inst)->tipo1 & BD_FLAG)==0) && (((*inst)->tipo1 & PSW_FLAG)==0)){
			(*inst)->opcode |= ((0x03)<<(4));
		}
		else if(!strcmp(nome, "psw") && (((*inst)->tipo1) & PSW_FLAG)){
			(*inst)->opcode |= ((0x03)<<(4));
		}
		else
			return 0;

		/*Avisa para o programa que o tipo do operando eh registrador duplo*/
		(*inst)->tipo1 = RP_FLAG;


		return 1;	
	}

	/**
	Tenta adicionar um imediato a instrucao.

	Verifica se o operando definido por opnumber aceita Imediatos.
	Verifica se a entrada e decimal (numero cru) ou hexadecimal (numero seguido de H)
	Tenta converter a String de entrada para um Inteiro de 1 byte.
	Modifica o opcode da funcao.
	Responsavel tambem pela funcao RST

	@param nome A String que representa esse argumento
	@inst A Inst na qual se tenta adicionar esse argumento
	@opnumber O numero do operando. 1 para primeiro, 2 para segundo.

	@return 0 Se a Inst aceitava Imediados, conseguiu fazer a conversao sem overflow ou underflow.
	@return 4 Se a Inst nao aceita Imediados.
	@return 1 Overflow, apesar de a instrução aceitar imediatos.
	@return 2 Underflow, apesar de a instrução aceitar imediatos.
	@return 3 Erro na funcao de conversao => nao é numero, quaaaase era um número, etc... Apesar de a instrução aceitar imediatos.

	*/
	int addIm(char* nome,Inst** inst, int opnumber){
		/*Verifica se a instrucao aceita Imediatos*/
		if(!((*inst)->tipo1 & I_FLAG) && (opnumber == 1)){
			return 4;
		}
		if(!((*inst)->tipo2 & I_FLAG) && (opnumber == 2)){
			return 4;
		}

		/*Verifica se é um número hexadecimal ou decimal válido*/
		int imd = strToPosInt(nome);
		if(imd < 0){
			return (-1*imd);
		}

		/*Parte especial da funcao RST*/
		if((*inst)->tipo1 & RST_FLAG){
			/*Verifica se o opnumber e 1*/			
			if(opnumber != 1)
				return 4;
			/*Verifica se o 0 <= inteiro <= 7*/
			if(imd < 0 || imd > 7)
				return 4;
			/*Adiciona o opcode*/
			(*inst)->opcode |= (imd << 3);
			return 0;
		}

		(*inst)->opcode = ((*inst)->opcode << 8);
		(*inst)->opcode |= imd;

		#if DEBUG
		printf("\n\tOpcode com imediato %x \n", (*inst)->opcode);
		#endif

		return 0;	
	}



	/**
	Tenta adicionar uma label a uma Inst

	Verifica se uma label e um argumento valido.
	Adiciona a label valida ao opcode da instrucao sem fazer a modificacao para little endian.

	@param nome A String que representa essa possivel label.
	@param opnumber O numero do operando 1 se for o primeiro, 2 se for o segundo.

	@return 0 Se a Inst aceitava Labels, ou conseguiu fazer a conversao sem overflow ou underflow do endereço.
	@return 4 Se a Inst nao aceita Labels.
	@return 1 Overflow do endereço, apesar de a instrução aceitar endereços.
	@return 2 Underflow do endereço, apesar de a instrução aceitar endereços.
	@return 3 Erro na funcao de conversao => nao é numero hexa, quaaaase era um número hexa, etc...
	*/
	int addLabel(char* nome,Inst** inst, int opnumber){

		/*Verifica se a instrucao aceita Labels*/
		if(!((*inst)->tipo1 & L_FLAG) && opnumber == 1){
			return 4;
		}
		if(!((*inst)->tipo2 & L_FLAG) && opnumber == 2){
			return 4;
		}

		if(getStringSize(nome) < 1)
			return 4;

		/*Verifica se a label eh um valor numerico*/
		if(isNumericalLabel(nome)){
			(*inst)->labelcoded = 1;
			(*inst)->opcode = (*inst)->opcode << 16;
		    int labeltemp = numericalLabelClear(nome);
			if (labeltemp < 0){
				return ((-1)*labeltemp);
			}
		    int labeltemp2 = labeltemp;
			labeltemp = labeltemp << 8;
			labeltemp &= 0xFF00;
			labeltemp2 = labeltemp2 >> 8;
			labeltemp2 &= 0xFF;
			(*inst)->opcode |= labeltemp;
			(*inst)->opcode |= labeltemp2;
			return 0;
		}


		(*inst)->label = (char*) malloc (sizeof(char)*getStringSize(nome));
		strcpy((*inst)->label, nome);

		#if DEBUG
		printf("\n\tLabel added but not yet coded %s \n", (*inst)->label);
		#endif

		/*Avisa para o programa que o tipo do operando eh Imediato*/
		if(opnumber == 1){		
			(*inst)->tipo1 = L_FLAG;
		}
		if(opnumber == 2){		
			(*inst)->tipo2 = L_FLAG;
		}
	
		return 0;	
	}


/**
Verifica se a String de entrada e uma Label valida.

Percorre toda a String ate achar um : seguido de um /0.

@return -1 Se achou dois ':' seguidos
@return 1 Se e uma Label valida
@return 0 Se o ultimo caractere nao era ':'
*/
int isLabel(char *nome){

	char a = 'x';
	char b = 'x';	
	a = (*nome);
		
	while(a != '\0'){
		b = a;
		nome += sizeof(char);
		a = (*nome);
		if(a == ':' && b == ':'){
			#if DEBUG
			printf("\n\ta and b == :\n");
			#endif
			return -1;
		}
	}
	if(b == ':'){
		#if DEBUG
		printf("\n\tb == : && a == /0\n");
		printf("\n\tLabel recognized %s", nome);
		#endif
		return 1;
	}
	else{
		#if DEBUG
		printf("\n\ta == %c && b == %c\n", a, b);
		#endif
		return 0;
	}
}


/**
Verifica se a String de entrada e uma Label Numerica valida.
Numero em hexa obrigatoriamente escrito em minúsculo.

Percorre toda a String ate achar um H seguido de um /0.

@return 1 Se e uma Label Numerica valida
@return 0 Se o ultimo caractere nao era 'H' ou era invalida de alguma forma.
*/
int isNumericalLabel(char *nome){

	char a = 'x';
	char b = 'x';	
	a = (*nome);
	/*Verifica se o primeiro caracter e um numero. Se nao for, nao e um endereco numerico*/
	if(!isdigit(a)){
		return 0;
	}
	while(a != '\0'){
		b = a;
		if(!isdigit(a) && a != 'h' && a != 'a' && a != 'b' && a != 'c' && a != 'd' && a != 'e' && a != 'f'){
			return 0;
		}
		nome += sizeof(char);
		a = (*nome);
		if(a == 'h' && b == 'h'){
			#if DEBUG
			printf("\n\ta and b == h\n");
			#endif
			return 0;
		}
	}
	if(b == 'h'){
		#if DEBUG
		printf("\n\tb == h && a == /0\n");
		printf("\n\tLabel recognized %s", nome);
		#endif
		return 1;
	}
	else{
		#if DEBUG
		printf("\n\ta == %c && b == %c\n", a, b);
		#endif
		return 0;
	}
}

/**
Verifica se a String de entrada e um numero decimal valido.
Numero deve ser positivo!

Percorre toda a String ate achar um /0.

@return 1 Se e um numero decimal valido
@return 0 Se nao era um numero decimal valido
*/
int isDecimalNumber(char *nome){

	char a = 'x';
	a = (*nome);

	while(a != '\0'){
		if(!isdigit(a)){
			return 0;
		}
		nome += sizeof(char);
		a = (*nome);
}
	return 1;
}
/**
Percorre uma String e retorna seu tamanho.

@param string A String cujo tamanho se deseja saber.
@return Um inteiro com o tamanho da String.
	0 se for NULL
*/
int getStringSize(char* string){
	if(string == NULL) return 0;

	char a = 'a';
	int i = 0;
	a = (*string);
	i++;
	while(a != '\0'){
		i++;
		string += sizeof(char);
		a = (*string);
	}
	return i;
}

/**
Percorre uma String e retorna uma equivalente com todos seus caracteres
em lowercase.

@param s A string que se deseja passar para lowercase
@return Um ponteiro para a string modificada.
@deprecated
*/
char* stolower(char* s){
	char a = 'x';
	char* h = (char*)malloc(sizeof(char)*(1 + getStringSize(s)));

	/*Para retornar o ponteiro para a posicao correta*/
	int i = 0;
	while(a != '\0'){
		a = (*s);
		i++;
		if(isalpha(a)){
			(*h) = tolower(a);
		}
		(s) += sizeof(char);
		(h) += sizeof(char);
	}
	(h) -= sizeof(char);
	(*h) = 0;
	(s) = (s) - i*sizeof(char);
	(h) = (h) - (i-1)*sizeof(char);

	return h;
}


/**
Retira o : final das labels. O resultado para uma String que nao passou pelo 
teste isLabel() e indefinido.

@param nome A String que se quer tirar o :
*/
void labelClear(char **nome){
	/*Esquecer de inicializar variaveis doi muito.*/	
	char a = 'x';
	int i = 0;
	/***********************Variaveis adicionadas por Mathes****************/
	/*j = Variavel para detectar se a label eh constituida soh de pontuacao*/
	int j = 0;
	/*******************fim Variaveis adicionadas por Mathes****************/
	while(a != ':'){
		a = (**nome);
		i++;
		(*nome) += sizeof(char);
		if(ispunct(a))
			j++;
	}
	(*nome) -= sizeof(char);
	(**nome) = '\0'	;
	j--;
	i--;
	(*nome) = (*nome) - i*sizeof(char);
	/******************************************************************codigo incluido por Matheus**************************************************************/
	/*ifs para verificacao de validade da label*/
	if(i==j){
		printf("\n\n\n\tlabel invalida: %s. constituida apenas por pontuacao\n\n\n\n", (*nome));
		exit(100);
	}
	if((!strcmp((*nome), "add"))||(!strcmp((*nome), "mov"))||(!strcmp((*nome), "sub"))||(!strcmp((*nome), "inx"))||(!strcmp((*nome), "adi"))||(!strcmp((*nome), "jmp"))||(!strcmp((*nome), "lxi"))||(!strcmp((*nome), "ana"))||(!strcmp((*nome), "ora"))||(!strcmp((*nome), "adc"))||(!strcmp((*nome), "sbb"))||(!strcmp((*nome), "xra"))||(!strcmp((*nome), "cmp"))||(!strcmp((*nome), "mvi"))||(!strcmp((*nome), "inr"))||(!strcmp((*nome), "dcr"))||(!strcmp((*nome), "dad"))||(!strcmp((*nome), "dcx"))||(!strcmp((*nome), "lxi"))||(!strcmp((*nome), "nop"))||(!strcmp((*nome), "arhl"))||(!strcmp((*nome), "rim"))||(!strcmp((*nome), "sim"))||(!strcmp((*nome), "rlc"))||(!strcmp((*nome), "ral"))||(!strcmp((*nome), "daa"))||(!strcmp((*nome), "stc"))||(!strcmp((*nome), "shld"))||(!strcmp((*nome), "sta"))||(!strcmp((*nome), "lhld"))||(!strcmp((*nome), "lda"))||(!strcmp((*nome), "jz"))||(!strcmp((*nome), "jc"))||(!strcmp((*nome), "jpe"))||(!strcmp((*nome), "jm"))||(!strcmp((*nome), "stax"))||(!strcmp((*nome), "ldax"))||(!strcmp((*nome), "pop"))||(!strcmp((*nome), "push"))||(!strcmp((*nome), "rnz"))||(!strcmp((*nome), "rnc"))||(!strcmp((*nome), "rpo"))||(!strcmp((*nome), "rp"))||(!strcmp((*nome), "xthl"))||(!strcmp((*nome), "di"))||(!strcmp((*nome), "rz"))||(!strcmp((*nome), "rc"))||(!strcmp((*nome), "rpe"))||(!strcmp((*nome), "rm"))||(!strcmp((*nome), "ret"))||(!strcmp((*nome), "shlx"))||(!strcmp((*nome), "pchl"))||(!strcmp((*nome), "sphl"))||(!strcmp((*nome), "rstv"))||(!strcmp((*nome), "xchg"))||(!strcmp((*nome), "ei"))||(!strcmp((*nome), "dsub"))||(!strcmp((*nome), "rdel"))||(!strcmp((*nome), "rrc"))||(!strcmp((*nome), "rar"))||(!strcmp((*nome), "cma"))||(!strcmp((*nome), "cmc"))||(!strcmp((*nome), "ldhi"))||(!strcmp((*nome), "ldsi"))||(!strcmp((*nome), "jnz"))||(!strcmp((*nome), "jnc"))||(!strcmp((*nome), "jpo"))||(!strcmp((*nome), "jp"))||(!strcmp((*nome), "cnz"))||(!strcmp((*nome), "cnc"))||(!strcmp((*nome), "cpo"))||(!strcmp((*nome), "cp"))||(!strcmp((*nome), "cz"))||(!strcmp((*nome), "cc"))||(!strcmp((*nome), "cpe"))||(!strcmp((*nome), "cm"))||(!strcmp((*nome), "call"))||(!strcmp((*nome), "jnk"))||(!strcmp((*nome), "lhlx"))||(!strcmp((*nome), "jk"))||(!strcmp((*nome), "out"))||(!strcmp((*nome), "sui"))||(!strcmp((*nome), "ani"))||(!strcmp((*nome), "ori"))||(!strcmp((*nome), "in"))||(!strcmp((*nome), "adi"))||(!strcmp((*nome), "aci"))||(!strcmp((*nome), "sbi"))||(!strcmp((*nome), "xri"))||(!strcmp((*nome), "cpi"))||(!strcmp((*nome), "hlt"))||(!strcmp((*nome), "rst"))||(!strcmp((*nome), "db"))||(!strcmp((*nome), "ds"))||(!strcmp((*nome), "dw"))||(!strcmp((*nome), "public"))||(!strcmp((*nome), "extern"))||(!strcmp((*nome), ".start"))||(!strcmp((*nome), ".begin"))||(!strcmp((*nome), ".text"))||(!strcmp((*nome), ".data"))||(!strcmp((*nome), ".end"))){
		printf("\n\n\n\tlabel invalida: %s. nome de palavra chave\n\n\n\n", (*nome));
		exit(100);
	}
	/***********************************************************fim de codigo incluido por Matheus**************************************************************/

}

/**
Retira o H final das labels em HEXA e retorna seu valor em inteiro. O resultado
para uma String que nao passou por isNumericalLabel() anteriormente e indefinido.
Faz automaticamente a verificacao para o teto de 16bits.
Faz automaticamente a verificacao do chao de 16bits.
Faz automaticamente a verificacao de impossibilidade de conversao.

@param nome A String que representa essa label
@return O valor numerico que representa essa label
@return -1 Overflow
@return -2 Underflow
@return -3 Falha na conversao
*/
int numericalLabelClear(char *nome){
	/*Esquecer de inicializar variaveis doi muito.*/	
	char a = 'x';
	int i = 0;
	while(a != 'h'){
		a = (*nome);
		i++;
		(nome) += sizeof(char);
	}
	(nome) -= sizeof(char);
	i--;
	(*nome) = '\0'	;
	(nome) -= (i*sizeof(char));

	/*Como addIm com ajuste para 16 bits*/
	long int im = strtol(nome,NULL,16);
	unsigned int imd = 0;
	if(im > 65535){
		return -1;
	}
	else if(im < 0){
		return -2;
	}
	else if(im == 0 && errno == EINVAL){
		return -3;
	}
	imd = (unsigned int)im;

	return imd;
}

/**
Transforma uma String em um valor numerico equivalente (hex ou decimal) 8 bits.
Nao aceita numeros com sinal.
Faz verificacao de overflow

@param n A String a ser convertida

@return O valor convertido
@return -1 Se houve overflow
@return -3 Se houve erro na conversao
*/
int strToPosInt(char* n){
	/*Verifica se é um número hexadecimal ou decimal válido*/
	int isHex = isNumericalLabel(n);
	if(!isHex){
		if(!isDecimalNumber(n))
			return -3;
	}
	long int im;
	if(!isHex){
		 /*Como descrito em http://en.wikipedia.org/wiki/Atoi*/
		 im = strtol(n,NULL,10);
	}
	else{
		 im = numericalLabelClear(n);
	}		
		int imd = 0;
	if(im > 255){
		return -1;
	}
	else if(im == 0 && errno == EINVAL){
		return -3;
	}
	imd = (int)im;
	return imd;
}

