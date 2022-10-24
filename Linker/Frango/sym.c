#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"estruturas.h"
#include"constantes.h"

extern int lesym(FILE *codigo, Elf32_Shdr SHentrada, Elf32_Sym *sym);

extern int criaTgd(Elf32_Sym *sym, Elf32_Sym *Tgd, int symnum, Nome *nomesym, Nome *nometgd, Elf32_Ehdr *EHentrada, Elf32_Shdr *SHentrada, int *e, int deslocatext,int deslocadata, int tamtext);

extern int leinf(Elf32_Ehdr *EHentrada, Elf32_Shdr *SHentrada, int *e, int tipos, int inf);

extern int lenome(FILE *codigo, int symnum, int off, Elf32_Sym *sym, Nome *nomesym);

extern int atualizavalor (Elf32_Sym *Tgd, Elf32_Ehdr *EHentrada, Elf32_Shdr *SHentrada, int *e, int deslocatext, int deslocadata, int tamtex);

extern int reloca(FILE **codigo, FILE *saida, Elf32_Ehdr **EHentrada, Elf32_Shdr **SHentrada, int arqnum, matriz *matrix, int deslocadata[], int deslocatext[], int tamtext, Elf32_Sym **sym, int *symnum, int tamdata);


/*====================sym()====================================
resolve referencias cruzadas e faz realocação
é chamada por:
	- imprimesaida (imprime.c)
@parametros:
	- código: lista com códigos objetos fontes
	- EHentrada: lista de Elf Headers dos códigos objetos fontes
	- SHentrada: lista das Sections Tables dos arquivos objetos fontes
	- arqnum: numero de arquivos objetos passados pela linha de comando
	- matrix: matriz com tipos das sections headers
	- sym: endereço para armazenamento das symbol tables de cada arquivo
	- Tgd: endereço para armazenamento da tabela global de definições
	- nomesym: matriz com nome de todos os simbolos
	- nometgd: matriz com nome dos simbolos publicos
	- deslocatext: lista com os endereços de cada section .text
	(um de cada arquivo objeto fonte) em relação ao início do segent .text
	- deslocadata: lista com os endereços de cada section .data
	(um de cada arquivo objeto fonte) em relação ao início do segent .data
	- tamtext: tamaho do segment .text
	- tamdata: tamaho do segment .data
================================================================*/

int sym(FILE **codigo, Elf32_Ehdr **EHentrada, Elf32_Shdr **SHentrada,	FILE *saida, int arqnum, matriz *matrix, Elf32_Sym **sym, Elf32_Sym **Tgd, Nome** nomesym, Nome** nometgd, int deslocatext[], int deslocadata[], int tamtext, int tamdata){
	
	/*==========variáveis locais=====================*/
	int j, i, a, b;		/*contadores*/
	int flag;			/*so para terminar o for mais cedo*/
	int off;			/*armazena offset da string table*/
	int symnum[arqnum]; /*numero de entradas na symbol table*/
	int tgdnum[arqnum]; /*numero de entradas na tabela golbal de definições*/
	int tamdym;
	/*==========fim variáveis locais=====================*/

	nomesym = (Nome **)malloc(arqnum*sizeof(Nome *));
	nometgd = (Nome **)malloc(arqnum*sizeof(Nome *));
	
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	preparando variaveis para a criação de da tabela global de definições e a
	criando
	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	for (j=0; j<arqnum; j++){
		for(i=0; i<EHentrada[j]->e_shnum; i++){
			if(matrix[j].e[i]==SYMTAB){
				if(SHentrada[j][i].sh_offset != 0){

					/*aloca espaço e le symbol table de um arquivo objeto de entrada*/
					sym[j] = (Elf32_Sym *)malloc(SHentrada[j][i].sh_size*sizeof(char));
					lesym(codigo[j],SHentrada[j][i],sym[j]);

					/*calcula numero de entradas da symbol table de um arquivo objeto de entra*/
					symnum[j] = (SHentrada[j][i].sh_size)/(sizeof(Elf32_Sym));

					/*aloca variáveis para a criação da tabela global de definições*/
					nometgd[j] = (Nome *)malloc(symnum[j]*sizeof(Nome));
					Tgd[j] = (Elf32_Sym *)malloc(symnum[j]*sizeof(Elf32_Sym));

					/*alocando espaço e lendo nomes dos symbols armazenadas na simbol table de
					um arquivo objeto de entrada*/
					nomesym[j] = (Nome *)malloc(symnum[j]*sizeof(Nome));
					off = leinf(EHentrada[j], SHentrada[j], matrix[j].e, STRTAB, SHOFFSET);
					lenome(codigo[j], symnum[j], off, sym[j], nomesym[j]);

					/*cria tabela de definições global*/
					tgdnum[j] = criaTgd(sym[j], Tgd[j], symnum[j], nomesym[j], nometgd[j], EHentrada[j], SHentrada[j], matrix[j].e, deslocatext[j], deslocadata[j], tamtext);
				}
			}
		}
	}
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	fim preparando variaveis para a criação de da tabela global de definições
	e a	criando
	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	resolvendo referencias cruzadas
	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

	/*achando symbolos na tabela de uso*/
	for (j=0; j<arqnum; j++){
		for(i=0; i<symnum[j]; i++){
			/*if = tá na tabela de uso?*/
			if(((ELF32_ST_BIND(sym[j][i].st_info))==STB_GLOBAL && ((sym[j][i].st_shndx) == SHN_UNDEF))){

				/*buscando o valor na tabela global de definições*/
				for (a=0; a<arqnum; a++){
					for(b=0; b<tgdnum[a]; b++){
						if( (strcmp(nomesym[j][i].str, nometgd[a][b].str)) == 0){

							/*atualiza o valor do symbol, ou seja, escreve em value o deslocamento dele
							ao incio do segment .text*/
							atualizavalor (&(sym[j][i]), EHentrada[j], SHentrada[j], matrix[j].e,  deslocatext[j], deslocadata[j], tamtext);

							/*busca a região do arquivo que deve ser alterada*/
							fseek(saida, sizeof(Elf32_Ehdr)+PHNUM*sizeof(Elf32_Phdr)+sym[j][i].st_value, SEEK_SET);		

							/*escreve o valor correto, ou seja, resolve a referencia cruzada*/
							fwrite(&(Tgd[a][b].st_value),2,1,saida);
							flag = 1; /*parar a busca na tabela global, e iniciar a busca pela proxima
							symbol indefinida, pois esta acabou de ser corrigida*/
							break;
						}
					}
					if (flag == 1){
						flag = 0;
						break;
					}
				}

			}
		}
	}
	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	fim resolvendo referencias cruzadas
	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	
	/*realocação*/
	tamdym = reloca(codigo, saida, EHentrada, SHentrada, arqnum, matrix, deslocadata, deslocatext, tamtext, sym, symnum, tamdata);
return tamdym;
}
