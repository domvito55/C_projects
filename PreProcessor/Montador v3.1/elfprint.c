/**
Instrucoes relevantes para impressao de secoes de um arquivo ELF relocavel.

@version 1.2
@author Murilo M. Marinho

*/


#include<stdio.h>
#include<stdlib.h>
#include"lexicAnaliser.h"
#include"instrucao.h"
#include"mcline.h"
#include"mctable.h"
#include"simboltable.h"
#include"simbolline.h"
#include<string.h>
#include"dirline.h"
#include"dirtable.h"
#include"directives.h"
#include"definitionline.h"
#include"definitiontable.h"
#include"useline.h"
#include"usetable.h"
#include"ce.h"
#include"elfprint.h"



/**
Imprime a secao .strtab, a partir da SimbolTable.

@param fp O arquivo no qual se quer imprimir.
@param A simboltable cujas strings se deseja imprimir.
*/
void elfPrintStrTab(FILE* fp, Elf32_Str** strr){

	char snbuffer[MAX_TOKEN_BUFFER_SIZE];
	
	strcpy(snbuffer,"\0");	
	fwrite(snbuffer,1,1,fp);
	
	Elf32_Str* s;


	if((*strr) == NULL){
		return;
	}
	if((*strr)->next == NULL){
		return;
	}

	for(s = (*strr)->next; s!= NULL; s = s->next){
		strcpy(snbuffer, s->str);
		snbuffer[getStringSize(s->str)] = '\0';
		fwrite(snbuffer,getStringSize(s->str),1,fp);
	}

}

/**
Imprime a SimbolTable no arquivo fp, conforme a estrutura elf:

@param fp O arquivo no qual se quer imprimir.
@param st A SimbolTable que se deseja imprimir.

*/
void elfPrintSimbolTable(FILE* fp, SimbolTable** st, UseTable** ut, Stab** s, char* start_label){

	SimbolLine* sl;
	Elf32_Sym* sym = (Elf32_Sym*)malloc(sizeof(Elf32_Sym));
	changeSym(&sym, 0, 0, 0, 0);
	sym->st_info = 0;
	sym->st_shndx = 0;
	int shndx = 0;


	if((*st)->firstSimbolLine == NULL){
		return;
	}

	/*Imprime um simbolo vazio*/
	fwrite(sym, sizeof(Elf32_Sym), 1, fp);
	
	for(sl = (*st)->firstSimbolLine; sl!= NULL; sl = sl->nextSimbolLine){
			if(!(sl->externo)){
				/*Ajusta os valores no ponteiro e imprime*/
				if(sl->istextsim) shndx = 3;
				else shndx = 2;
				changeSym(&sym,  sl->name, sl->valor, !sl->publico, shndx);
				fwrite(sym, sizeof(Elf32_Sym), 1, fp);
			}
			int type = 0;
			if(sl->externo || sl->publico){
				type = N_GSYM;
			}
			else if(sl->istextsim){
				type = N_FUN;
			}
			else{
				type = N_STSYM;
			}
			if(start_label != NULL){
				if(!strcmp(sl->label, start_label)){
					type = N_MAIN;
				}
			}
			addStab(s,sl->name,type,0,sl->valor);
	}

	UseLine* ul;
		
	if((*ut)->firstUseLine == NULL){
		return;
	}

	for(ul = (*ut)->firstUseLine; ul!= NULL; ul = ul->nextUseLine){
			/*Ajusta os valores no ponteiro e imprime*/
			changeSym(&sym,  ul->name, ul->valor, 0, 0);
			fwrite(sym, sizeof(Elf32_Sym), 1, fp);
	}

	free(sym);

}

/**
Imprime a Stab List no arquivo fp:

@param fp O arquivo no qual se quer imprimir
@param s A Stab List
*/
void elfPrintStab(FILE* fp, Stab** s){

	Stab* sp;

	if((*s)->next == NULL){
		return;
	}
	
	for(sp = (*s); sp != NULL; sp = sp->next){
			fwrite(sp, STAB_SIZE, 1, fp);
	}

}


/**
Decodifica as Labels do programa.
Imprime no arquivo a tabela de instrucoes, equivalente a regiao .text do programa.


@param fp O arquivo no qual se quer imprimir.
@param mcTable A MCTable que armazena as instrucoes codificadas.
@param simbolTable A SimbolTable que armazena as labels a serem decodificadas.
@param end O endereco atual no programa.
@return 0 Sem erros 
	1 Se uma label foi usada mas nao foi declarada.

*/
int elfPrintText(FILE* fp, MCTable* mcTable, SimbolTable* simbolTable,int* end){
	int labeltemp = 0;
	int labeltemp2 = 0;
	MCLine* mcLine;
	SimbolLine* simbolLine;

	int labelfound = 0;

	/*Armazena as informações de relocação*/
	Elf32_Rela* relaroot;
	newRela(&relaroot,0,0);

	for(mcLine = mcTable->firstLine; mcLine != NULL; mcLine = mcLine->nextLine){
		if(mcLine->inst == NULL)
			break;


		if((mcLine->inst->tipo1 & L_FLAG || mcLine->inst->tipo2 & L_FLAG) && !mcLine->inst->labelcoded){
			labelfound = 0;
			for(simbolLine = simbolTable->firstSimbolLine; simbolLine != NULL; simbolLine = simbolLine->nextSimbolLine){

			#if DEBUG
			printf("\n\t %s != %s \n", simbolLine->label, mcLine->inst->label);
			#endif

				if(simbolLine->label != NULL && mcLine->inst->label != NULL){
	
					
					if(!strcmp(simbolLine->label, mcLine->inst->label)){
						labelfound = 1;
						mcLine->inst->opcode = mcLine->inst->opcode << 16;
						labeltemp = simbolLine->valor;
						labeltemp2 = simbolLine->valor;
						labeltemp = labeltemp << 8;
						labeltemp &= 0xFF00;
						labeltemp2 = labeltemp2 >> 8;
						labeltemp2 &= 0xFF;
						mcLine->inst->opcode |= labeltemp;
						mcLine->inst->opcode |= labeltemp2;
						
	
						break;
					}
				
				}		
			}
			if(!labelfound){
				return 1;
			} 
		}
	}
	int* loveme = (int*)malloc(sizeof(int));
	for(mcLine = mcTable->firstLine; mcLine != NULL; mcLine = mcLine->nextLine){
		if(mcLine->inst == NULL)
			break;

		if(mcLine->inst->size == 1){
			(*loveme) = mcLine->inst->opcode; 
			fwrite(loveme, 1, 1, fp);
		}
		else if (mcLine->inst->size == 2){
			(*loveme) = ((mcLine->inst->opcode >> 8) & 0xFF);
			fwrite(loveme, 1, 1, fp);
			(*loveme) = (mcLine->inst->opcode & 0xFF);
			fwrite(loveme, 1, 1, fp);
		}
		else if(mcLine->inst->size == 3){
			(*loveme) = ((mcLine->inst->opcode >> 16) & 0xFF);
			fwrite(loveme, 1, 1, fp);
			(*loveme) = ((mcLine->inst->opcode >> 8) & 0xFF);
			fwrite(loveme, 1, 1, fp);
			(*loveme) = (mcLine->inst->opcode & 0xFF);
			fwrite(loveme, 1, 1, fp);
			addNewRela(&relaroot,(*(end)+1),((mcLine->inst->opcode & 0xFFFF)));
		}
		*end += mcLine->inst->size;
		
	}
	free(loveme);
	printRelaList(&relaroot, fp);

	return 0;
}

/**
Imprime os dados, regiao .data do programa.

@param fp O arquivo no qual se quer imprimir
@param dirTable A DirTable que se pretente imprimir no arquivo
*/
void elfPrintData(FILE *fp, DirTable* dirtable){
	DirLine* dirline;
	int* loveme = (int*)malloc(sizeof(int));

	for(dirline = dirtable->firstLine; dirline != NULL; dirline = dirline->nextLine){
		if(dirline->directive == NULL)
			break;
		
		if(dirline->dirType == 1){
			DirDBPart* part;		
			for(part = ((DirDB*)dirline->directive)->firstValue; part != NULL; part = part->nextValue){
				(*loveme) = (part->value & 0xFF);
				fwrite(loveme, 1, 1, fp);
			}
		}
		else if(dirline->dirType == 2){
			int i = 0;
			for(i = 0; i < ((DirDS*)dirline->directive)->size; i++){
				(*loveme) = 0;
				fwrite(loveme, 1, 1, fp);
			}		
		}

	}
	free(loveme);

}

