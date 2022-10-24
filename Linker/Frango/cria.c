#include"estruturas.h"
#include"constantes.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

extern int atualizavalor (Elf32_Sym *Tgd, Elf32_Ehdr *EHentrada, Elf32_Shdr *SHentrada, int *e, int deslocatext, int deslocadata, int tamtex);

/*====================criaTgd()====================================
cria a tabela global de definições
é chamada por:
	- sym (sym.c)
@parametros:
	- sym: tabela de simbolos de um arquivo objeto fonte
	- Tgd: endereço de armazenamento da tabela de definições de um arquivo objeto fonte
	- symnum: numero de entradas na Symbol Table de um arquivo objeto fonte
	- nomesym: ponteiro para lista com nome dos symbols de um arquivo objeto fonte
	- nometgd: ponteiro para lista com nome dos symbols na tabela global de definições
	- EHentrada: Lista com elf headers de um arquivo objeto
	- SHentrada: Lista com sections headers de um arquivo objeto
	- e: lista que armazena o tipo das section headers de um arquivo objeto
	- deslocatext: deslocamento da section .text de um arquivo objeto especifico
	em relação ao inicio do segment .text
	- deslocadata: deslocamento da section .data de um arquivo objeto especifico
	em relação ao inicio do segment .data
retorna:
	- numero de entradas na tabela global de definições
================================================================*/
int criaTgd(Elf32_Sym *sym, Elf32_Sym *Tgd, int symnum, Nome *nomesym, Nome *nometgd, Elf32_Ehdr *EHentrada, Elf32_Shdr *SHentrada, int *e,  int deslocatext, int deslocadata, int tamtext){

	/*============variaveis locais=============*/
	int i, j; /*contador*/
	/*========fim variaveis locais=============*/

	for(i=0, j=0; i<symnum; i++){
		if(((ELF32_ST_BIND(sym[i].st_info))==STB_GLOBAL && ((sym[i].st_shndx) != SHN_UNDEF))){
			Tgd[j] = sym[i];

			nometgd[j] = nomesym[i];
			/*atualizar endereços*/
			atualizavalor (&(Tgd[j]), EHentrada, SHentrada, e,  deslocatext, deslocadata, tamtext);
			j++;
		}
	}


return j;
}



/*====================criaEH()====================================
cria um Elf Header para o programa executavel
é chamada por:
	- imprimesaida (imprime.c)
@parametros:
	- elfHeader: endereço para armazenamento do elf header
	- startAdress: endereço de entrada do programa principal
	- phnum: numero de entradas na Program Header Table
================================================================*/
int criaEHsaida(Elf32_Ehdr* elfHeader, Elf32_Addr startAddress, Elf32_Half phnum){
	elfHeader->e_ident[EI_MAG0] = ELFMAG0;
	elfHeader->e_ident[EI_MAG1] = ELFMAG1;
	elfHeader->e_ident[EI_MAG2] = ELFMAG2;
	elfHeader->e_ident[EI_MAG3] = ELFMAG3;
	elfHeader->e_ident[EI_CLASS]= ELFCLASS32;
	elfHeader->e_ident[EI_DATA] = ELFDATA2LSB;
	elfHeader->e_ident[EI_VERSION] = EV_CURRENT;

	int i = 0;
	for(i = EI_PAD; i < EI_NIDENT; i++){
		elfHeader->e_ident[i] = 0;
	}

/*########conferir########*/	
	elfHeader->e_type = ET_EXEC;
/*####FIM conferir########*/	
	elfHeader->e_machine = EM_8085;
	elfHeader->e_version = EV_CURRENT;
	elfHeader->e_entry = startAddress;
	elfHeader->e_phoff = sizeof(Elf32_Ehdr);   
	elfHeader->e_shoff = 0;    
	elfHeader->e_flags = 0; 
	elfHeader->e_ehsize = sizeof(Elf32_Ehdr);   
	elfHeader->e_phentsize = sizeof(Elf32_Phdr);   
/*########conferir########*/	
	elfHeader->e_phnum = phnum; /*1 + .text + .data + .rela + .sym + .str + .srthn*/      
/*####Fim conferir########*/	
	elfHeader->e_shentsize = 0;      
	elfHeader->e_shnum = 0;        
/*########conferir########*/	
	elfHeader->e_shstrndx = SHN_UNDEF;
/*####Fim conferir########*/	


return 0;
}


