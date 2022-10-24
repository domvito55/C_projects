#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"estruturas.h"

extern int leii(FILE **codigo,	char *saida, Elf32_Ehdr **EHentrada, Elf32_Shdr **SHentrada, matriz *matrix, int argc, char *argv[]);

extern int imprimesaida(FILE **codigo,char *saida, Elf32_Ehdr **EHentrada, Elf32_Shdr **SHentrada, matriz *matrix, int arqnum);

int main (int argc, char *argv[]){
	/*********************************************
	verificando se a chamada do programa foi feita
	corretamente e abrindo os arquivos objetos
	*********************************************/
	if(argc >= 2){
	
		/*============Variáveis locais=============*/
		FILE **codigo;			/*recebe os codigos objetos*/
		codigo= (FILE **) malloc(argc*sizeof(FILE*));
		
		int arqnum;
		
		char saida[20];		/*nome do arquivo de saida*/
		strcpy(saida,"");
		
		/*+++variáveis para armazenar informações dos arquivos de entrada+++*/
		Elf32_Ehdr **EHentrada;
		EHentrada= (Elf32_Ehdr **)malloc(argc*sizeof(Elf32_Ehdr*));
		Elf32_Shdr **SHentrada;
		SHentrada= (Elf32_Shdr **) malloc(argc*sizeof(Elf32_Shdr*));
		matriz *matrix;			/*armazena o tipo de section header*/

		/*alocando linhas para a matrix de tipos de section header.
		tipo. tipoSH[j][n] é o tipo do n-énesima section header
		do j-ésimo código fonte*/
		matrix = (matriz*)malloc(argc*sizeof(matrix));
		/*+Fim variáveis para armazenar informações dos arquivos de entrada+*/
	
		/*========Fim Variáveis locais=============*/

		/*******************************************
		lendo informações iniciais
		*******************************************/
		arqnum = leii(codigo, saida, EHentrada, SHentrada, matrix, argc, argv);
		/*nome padrão do arquivo de saida,
		caso o usuário não tenha fornecido um*/
		if((strcmp(saida,"")) == 0){
			strcpy(saida, "a.out");
		}

		/********************************************
		imprimindo arquivo final
		********************************************/		
		imprimesaida(codigo, saida, EHentrada, SHentrada, matrix, arqnum);

	}else {
	printf("\nErro: argumentos invalidos\n\n");
	exit(1);
	}
	
return 0;
}/*FIM DA MAIN*/


