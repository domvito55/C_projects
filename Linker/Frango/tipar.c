#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"estruturas.h"
/*utilizou-se da sguinte conveção para tipar
codigo	tipo
0		0 (especial)
1		.shstrtab
2		.text
3		.data
4		.rela.text
5		.strtab
6		.symtab
7		.stab
********************************************/

/*=========================tiparsh()============================
retorna o tipo de Section Header
É chamda por:
	-preenceSH (preenche.c)
@parametros:
	- codigo: código obejto fonte
	- SHeader: Endereço da section header
	- posicaostr: posicao da String Table
==============================================================*/
int tiparSH (FILE *codigo, Elf32_Shdr *SHeader, int posicaostr)
{
	/*========Variáveis Locais===========*/
	int j;		/*contador*/
	char charaux[20];	/*buffer de string*/
	char byteatual;		/*variavel para fazer leitura byte a byte do arquivo*/

	/*====Fim Variáveis Locais===========*/

	/*Ir na String Table e ler o nome da seção.*/	
	if(SHeader->sh_name!=0){
		fseek(codigo, (posicaostr+SHeader->sh_name), SEEK_SET);
		j = 0;
		do{
			fread(&byteatual,1,1,codigo);
			charaux[j] = byteatual;
			j++;
		}while(byteatual != '\0');
		
		#ifdef DEBUGstring
		printf("%s\n\n", charaux);
		#endif
	}
	if(strcmp(charaux, "")==0)
		return 0;
	if(strcmp(charaux, ".shstrtab")==0)
		return 1;
	if(strcmp(charaux, ".text")==0)
		return 2;
	if(strcmp(charaux, ".data")==0)
		return 3;
	if(strcmp(charaux, ".rela.text")==0)
		return 4;
	if(strcmp(charaux, ".strtab")==0)
		return 5;
	if(strcmp(charaux, ".symtab")==0)
		return 6;
	if(strcmp(charaux, ".stab")==0)
		return 7;

return -1;
}
