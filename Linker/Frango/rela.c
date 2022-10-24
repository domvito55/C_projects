#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"estruturas.h"
#include"constantes.h"

extern int atualizarelaoff (Elf32_Rela *rela, Elf32_Ehdr *EHentrada, Elf32_Shdr *SHentrada, int *e, int deslocatext, int deslocadata, int tamtext);
extern int atualizarelaadd (Elf32_Rela *rela, Elf32_Ehdr *EHentrada, Elf32_Shdr *SHentrada, int *e, int deslocatext, int deslocadata, int tamtext);
extern int busca(Elf32_Sym *sym, int symnum, int relaoff);
extern int lerela(FILE *codigo, Elf32_Shdr SHentrada, Elf32_Rela *Rela);

/*================reloca()===========================
faz relocação e imprime o segment dynamic
chamada por:
	- sym (sym.c)
@parametros:
	- código: lista com códigos objetos fontes
	- saida: arquivo de saida
	- EHentrada: lista de Elf Headers dos códigos objetos fontes
	- SHentrada: lista das Sections Tables dos arquivos objetos fontes
	- arqnum: numero de arquivos objetos passados pela linha de comando
	- matrix: matriz com tipos das sections headers
	- deslocatext: lista com os endereços de cada section .text
	(um de cada arquivo objeto fonte) em relação ao início do segent .text
	- deslocadata: lista com os endereços de cada section .data
	(um de cada arquivo objeto fonte) em relação ao início do segent .data
	- tamtext: tamaho do segment .text
	- sym: endereço para armazenamento das symbol tables de cada arquivo
	- symnum: lista com numero de symbolos em cada arquivo objeto fonte
retorna:
	- tamanho do segment dynamic

===================================================*/
int reloca(FILE **codigo, FILE *saida, Elf32_Ehdr **EHentrada, Elf32_Shdr **SHentrada, int arqnum, matriz *matrix, int deslocadata[], int deslocatext[], int tamtext, Elf32_Sym **sym, int *symnum, int tamdata){
	
	/*=========variáveis locais============*/	
	int j, i, a;
	int relanum;
	Elf32_Rela **rela;
	rela = (Elf32_Rela **)malloc(arqnum*sizeof(Elf32_Rela*));
	int externo = 0;
	int retorno = 0;
	/*=====fim variáveis locais============*/	
	
	
	for (j=0; j<arqnum; j++){
		for(i=0; i<EHentrada[j]->e_shnum; i++){
			if(matrix[j].e[i]==4){
				if(SHentrada[j][i].sh_offset != 0){

					/*aloca e le lista com os endereços relocaveis de um arquivo objeto*/
					rela[j] = (Elf32_Rela *)malloc(SHentrada[j][i].sh_size*sizeof(char));
					lerela(codigo[j],SHentrada[j][i],rela[j]);

					/*atualiza os offsets e addends de todos os rela de um arquivo objeto fonte*/
					relanum = SHentrada[j][i].sh_size/sizeof(Elf32_Rela);
					for(a=0; a<relanum; a++){
						atualizarelaoff (&(rela[j][a]), EHentrada[j], SHentrada[j], matrix[j].e, deslocatext[j], deslocadata[j], tamtext);
						atualizarelaadd (&(rela[j][a]), EHentrada[j], SHentrada[j], matrix[j].e, deslocatext[j], deslocadata[j], tamtext);

						/*escreve segment dynamic*/
						fseek(saida, sizeof(Elf32_Ehdr)+PHNUM*sizeof(Elf32_Phdr)+tamtext+tamdata+a*sizeof(rela[j][a]), SEEK_SET);		
						fwrite(&(rela[j][a]),sizeof(rela[j][a]),1,saida);

						/*busca na tabela de uso*/
						externo = busca(sym[j], symnum[j], rela[j][a].r_offset);
						if(externo == 0){
							/*busca a região do arquivo que deve ser alterada*/
							fseek(saida, sizeof(Elf32_Ehdr)+PHNUM*sizeof(Elf32_Phdr)+rela[j][a].r_offset, SEEK_SET);		
							/*escreve o valor correto, ou seja, faz a relocação*/
							fwrite(&(rela[j][a].r_addend),2,1,saida);
						}
					}
				}
			}
		}
	retorno = retorno+relanum;
	}
return (retorno*sizeof(Elf32_Rela));
}
