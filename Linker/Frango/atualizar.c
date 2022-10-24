#include"estruturas.h"
#include"constantes.h"
#include<stdio.h>
#include<stdlib.h>

extern int leinf(Elf32_Ehdr *EHentrada, Elf32_Shdr *SHentrada, int *e, int tipos, int inf);
extern int inverte(int addr);

/*====================atualizarelaadd()====================================
atualiza adendo de uma variavel relocavel
é chamada por:
	- rela (rela.c)
@parametros:
	- rela: estrutura rela a ser atualizada
	- EHentrada: elf header de um arquivo objeto especifico
	- SHentrada: lista com section header de um arquivo objeto especifico
	- e: lista que armazena o tipo das sections de um arquivo objeto especifico
	- deslocatext: deslocamento da section .text de um arquivo objeto especifico
	em relação ao inicio do segment .text
	- deslocadata: deslocamento da section .data de um arquivo objeto especifico
	em relação ao inicio do segment .data
	- tamtext: tamanho do segment .text
================================================================*/
int atualizarelaadd (Elf32_Rela *rela, Elf32_Ehdr *EHentrada, Elf32_Shdr *SHentrada, int *e, int deslocatext, int deslocadata, int tamtext){

/*===================variaveis locais=========================*/
	int addrtext;	/*recebe endereço de memórida de section .text*/
	int addrdata;	/*recebe endereço de memórida de section .data*/
/*===============fim variaveis locais=========================*/

	addrtext = leinf(EHentrada, SHentrada, e, TEXT, SHADDR);
	addrdata = leinf(EHentrada, SHentrada, e, DATA, SHADDR);

	/*desfazendo o little ending*/
	rela->r_addend= inverte (rela->r_addend);

/*os if's são usados para definir se a symbol foi definida na section
.data ou na .text. Definido isso escolhe-se o aloritmo adequado
	se tiver na .data
		valor = tamanho do segment .text + deslocamento da symbol dentro do segment data
	se tiver na .data
		valor = deslocamento da symbol dentro do segment .text
*/
	if(addrtext > addrdata){

		if((rela->r_addend) >= addrtext){
			(rela->r_addend) = ((rela->r_addend)-addrtext)+deslocatext;

		} else if((rela->r_addend) >= addrdata){
			(rela->r_addend) = ((rela->r_addend)-addrdata)+tamtext+deslocadata;	

		} else {
		printf("erro indesperado1\n");
		exit (0);
		}

	}else if (addrdata > addrtext){

		if((rela->r_addend) >= addrdata){
			(rela->r_addend) = ((rela->r_addend)-addrdata)+tamtext+deslocadata;
		} else if((rela->r_addend) >= addrtext){
			(rela->r_addend) = ((rela->r_addend)-addrtext)+deslocatext;	

		} else {
		printf("erro indesperado2\n");
		exit (0);
		}
	}

return 0;
}

/*====================atualizarelaoff()====================================
atualiza offset de uma estrutura rela
é chamada por:
	- rela (rela.c)
@parametros:
	- rela: estrutura rela a ser atualizada
	- EHentrada: elf header de um arquivo objeto especifico
	- SHentrada: lista com section header de um arquivo objeto especifico
	- e: lista que armazena o tipo das sections de um arquivo objeto especifico
	- deslocatext: deslocamento da section .text de um arquivo objeto especifico
	em relação ao inicio do segment .text
	- deslocadata: deslocamento da section .data de um arquivo objeto especifico
	em relação ao inicio do segment .data
	- tamtext: tamanho do segment .text
================================================================*/
int atualizarelaoff (Elf32_Rela *rela, Elf32_Ehdr *EHentrada, Elf32_Shdr *SHentrada, int *e, int deslocatext, int deslocadata, int tamtext){

/*===================variaveis locais=========================*/
	int addrtext;	/*recebe endereço de memórida de section .text*/
	int addrdata;	/*recebe endereço de memórida de section .data*/
/*===============fim variaveis locais=========================*/

	addrtext = leinf(EHentrada, SHentrada, e, TEXT, SHADDR);
	addrdata = leinf(EHentrada, SHentrada, e, DATA, SHADDR);

/*os if's são usados para definir se a symbol foi definida na section
.data ou na .text. Definido isso escolhe-se o aloritmo adequado
	se tiver na .data
		valor = tamanho do segment .text + deslocamento da symbol dentro do segment data
	se tiver na .data
		valor = deslocamento da symbol dentro do segment .text
*/
	if(addrtext > addrdata){

		if((rela->r_offset) >= addrtext){
			(rela->r_offset) = ((rela->r_offset)-addrtext)+deslocatext;

		} else if((rela->r_offset) >= addrdata){
			(rela->r_offset) = ((rela->r_offset)-addrdata)+tamtext+deslocadata;	

		} else {
		printf("erro indesperado1\n");
		exit (0);
		}

	}else if (addrdata > addrtext){

		if((rela->r_offset) >= addrdata){
			(rela->r_offset) = ((rela->r_offset)-addrdata)+tamtext+deslocadata;
		} else if((rela->r_offset) >= addrtext){
			(rela->r_offset) = ((rela->r_offset)-addrtext)+deslocatext;	

		} else {
		printf("erro indesperado2\n");
		exit (0);
		}
	}

return 0;
}

/*====================atualizavalor()====================================
atualiza valor de um symbol
é chamada por:
	- criatdg (cria.c)
@parametros:
	- Tgd: endereço de armazenamento da tabela de definições de um arquivo objeto fonte
	- EHentrada: elf header de um arquivo objeto especifico
	- SHentrada: lista com section header de um arquivo objeto especifico
	- e: lista que armazena o tipo das sections de um arquivo objeto especifico
	- deslocatext: deslocamento da section .text de um arquivo objeto especifico
	em relação ao inicio do segment .text
	- deslocadata: deslocamento da section .data de um arquivo objeto especifico
	em relação ao inicio do segment .data
	- tamtext: tamanho do segment .text
================================================================*/
int atualizavalor (Elf32_Sym *Tgd, Elf32_Ehdr *EHentrada, Elf32_Shdr *SHentrada, int *e, int deslocatext, int deslocadata, int tamtext){

/*===================variaveis locais=========================*/
	int addrtext;	/*recebe endereço de memórida de section .text*/
	int addrdata;	/*recebe endereço de memórida de section .data*/
/*===============fim variaveis locais=========================*/

	addrtext = leinf(EHentrada, SHentrada, e, TEXT, SHADDR);
	addrdata = leinf(EHentrada, SHentrada, e, DATA, SHADDR);

/*os if's são usados para definir se a symbol foi definida na section
.data ou na .text. Definido isso escolhe-se o aloritmo adequado
	se tiver na .data
		valor = tamanho do segment .text + deslocamento da symbol dentro do segment data
	se tiver na .data
		valor = deslocamento da symbol dentro do segment .text
*/
	if(addrtext > addrdata){

		if((Tgd->st_value) >= addrtext){
			(Tgd->st_value) = ((Tgd->st_value)-addrtext)+deslocatext;

		} else if((Tgd->st_value) >= addrdata){
			(Tgd->st_value) = ((Tgd->st_value)-addrdata)+tamtext+deslocadata;	

		} else {
		printf("erro indesperado1\n");
		exit (0);
		}

	}else if (addrdata > addrtext){

		if((Tgd->st_value) >= addrdata){
			(Tgd->st_value) = ((Tgd->st_value)-addrdata)+tamtext+deslocadata;
		} else if((Tgd->st_value) >= addrtext){
			(Tgd->st_value) = ((Tgd->st_value)-addrtext)+deslocatext;	

		} else {
		printf("erro indesperado2\n");
		exit (0);
		}
	}

return 0;
}
