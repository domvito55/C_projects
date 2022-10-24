#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"estruturas.h"

extern int preencheSH(FILE *codigo, Elf32_Shdr *SHeader, int posicaostr, int SHnum, int shoff, matriz tipo);

/*======================lerela()=================================
le uma section .rela
é chamada por:
	- sym (sym.c)
@parametros:
	- codigo: codigo objeto fonte
	- SHentrada: Sections Headers que deve ser lida
	- rela: vetor para ser preenchido com informações de relocação
	====================================================================*/
int lerela(FILE *codigo, Elf32_Shdr SHentrada, Elf32_Rela *rela){

		fseek(codigo, SHentrada.sh_offset, SEEK_SET);		
		fread(rela,SHentrada.sh_size,1,codigo);
	
return 0;
}

/*======================lenome()=================================
le os nomes de uma symboltable
é chamada por:
	- sym (sym.c)
@parametros:
	- codigo: codigo objeto fonte
	- symnum: numero de entradas na symbol table
	- off: offset da strtable
	- sym: symboltable
	- nomesym: endereço para armazenar os nomes
	====================================================================*/
int lenome(FILE *codigo, int symnum, int off, Elf32_Sym *sym, Nome *nomesym){
	
	/*===============variáveis locais==================*/
	int a, k;
	char buffer[20];
	char byteatual;

	/*===========fim variáveis locais==================*/
	
	for (a = 0; a<(symnum); a++){
		fseek(codigo, off+sym[a].st_name, SEEK_SET);							
		for (k = 0; k<20; k++){
			fread(&byteatual,1,1,codigo);
			buffer[k] = byteatual;
			if (byteatual == '\0')
				break;
		}
		strcpy(nomesym[a].str,  buffer);

	}
return 0;
}

/*======================lesym()=================================
le todos os symbols de um arquivo objeto fonte
é chamada por:
	- sym (sym.c)
@parametros:
	- codigo: codigo objeto fonte
	- SHentrada: Sections Headers que deve ser lida
	- sym: endereço para armazenar todos os simbol de uma arquivo objeto
	====================================================================*/
int lesym(FILE *codigo, Elf32_Shdr SHentrada, Elf32_Sym *sym){
		fseek(codigo, SHentrada.sh_offset, SEEK_SET);		
		fread(sym,SHentrada.sh_size,1,codigo);
return 0;
}

/*======================leinf()=================================
retorna o offset de uma section
é chamada por:
	- sym (sym.c)
	- atualizavalor (atualizar.c)
@parametros:
	- EHentrada: Elf Header de um arquivo objeto especifico
	- SHentrada: Sections Headers de um arquivo objeto especifico
	- e: lista que armaze os tipos de das sections de um arquivo objeto especifico
	- tipos: defini o tipo de section que se quer ler
	(segue a tabela de tipos: especificada no arquivo tipar)
	- inf: define a informação que se quer ler
	0	sh_name;
	1	sh_type;
	2	sh_flags;
	3	sh_addr;
	4	sh_offset;
	5	sh_size;
	6	sh_link;
	7	sh_info;
	8	sh_addralign;
	9	sh_entsize;
	====================================================================*/
int leinf(Elf32_Ehdr *EHentrada, Elf32_Shdr *SHentrada, int *e, int tipos, int inf){

	/*===============variáveis locais==================*/
	int i;	/*contadores*/
	/*===============variáveis locais==================*/

		for(i=0; i<(EHentrada->e_shnum); i++){
			if(e[i]==tipos){
				if(SHentrada[i].sh_offset != 0){
					if(inf == 0)
						return SHentrada[i].sh_name;
					if(inf == 1)
						return SHentrada[i].sh_type;
					if(inf == 2)
						return SHentrada[i].sh_flags;
					if(inf == 3)
						return SHentrada[i].sh_addr;
					if(inf == 4)
						return SHentrada[i].sh_offset;
					if(inf == 5)
						return SHentrada[i].sh_size;
					if(inf == 6)
						return SHentrada[i].sh_link;
					if(inf == 7)
						return SHentrada[i].sh_info;
					if(inf == 8)
						return SHentrada[i].sh_addralign;
					if(inf == 9)
						return SHentrada[i].sh_entsize;
				}
			}
		}
	
return -1;
}

/*======================ledata()=================================
le uma sections .data
é chamada por:
	- imprmedata (imprime.c)
@parametros:
	- codigo: lista de codigos objetos fonte
	- SHentrada: Sections Headers que deve ser lida
	- buffer: endereço de buffer onde o código deve ser salvo
	====================================================================*/
int ledata(FILE *codigo, Elf32_Shdr SHentrada, char *buffer){

	/*===============variáveis locais==================*/
	int k;	/*contador*/
	char byteatual;
	/*===============variáveis locais==================*/

		fseek(codigo, SHentrada.sh_offset, SEEK_SET);		
		for (k = 0; (fread(&byteatual,1,1,codigo) != 0 ) && k < SHentrada.sh_size; buffer[k++] = byteatual);
	
return 0;
}

/*======================letext()=================================
le uma sections .text
é chamada por:
	- imprmetext (imprime.c)
@parametros:
	- codigo: lista de codigos objetos fonte
	- SHentrada: Sections Headers que deve ser lida
	- buffer: endereço de buffer onde o código deve ser salvo
	====================================================================*/
int letext(FILE *codigo, Elf32_Shdr SHentrada, char *buffer){

	/*===============variáveis locais==================*/
	int k;	/*contador*/
	char byteatual;
	/*===============variáveis locais==================*/

		fseek(codigo, SHentrada.sh_offset, SEEK_SET);		
		for (k = 0; (fread(&byteatual,1,1,codigo) != 0 ) && k < SHentrada.sh_size; buffer[k++] = byteatual);
	
return 0;
}

/*==================leEH()====================================
Função para ler Elf Headers.
É chamada por:
	-leii (le.c)
@parametros
	-codigo: Codigo objeto fonte
	-elfHeader: endereço de onde vai ser armazenado o novo Elf
	Header
============================================================*/
int leEH(FILE *codigo, Elf32_Ehdr *elfHeader)
{
	fseek(codigo, 0, SEEK_SET);
	fread(elfHeader,sizeof(Elf32_Ehdr),1,codigo);

return 0;
}

/*=====================leSH()================================
Função para ler Sections Headers.
É chamada por:
	-leii (le.c)
	-preencheSH(preenche.c)
@parametros
	-codigo: Codigo objeto fonte
	-SHeader: endereço de onde vai ser armazenado o novo
	Section	Header
	-posicao: deslocamento em bytes a partir do incio do codigo
	objeto fonte, em que se encontra a section header
============================================================*/
int leSH(FILE *codigo, Elf32_Shdr *SHeader, int posicao)
{
	fseek(codigo, posicao, SEEK_SET);
	fread(SHeader,sizeof(Elf32_Shdr),1,codigo);

return 0;
}


/*=====================Leii()==================================
Função para ler as informações iniciais: todos os sections headers
e todos os Elf Headers de todas os códigos objetos.
É chamada por:
	-main (b.c)
@parametros
	-codigo: lista de arquivos objetos
	-saida: nome no arquivo de saida
	-EHentrada: ponteiro para lista de ElfHeaders (um de cada programa objeto)
	-SHeader: ponteiro para as listas de Section Headers (uma para cada programa)
	-matrix: matrix que indica o tipo da Section (Matrix[j].e[i]: i-ésima section do j-ésimo arquivo objeto)
	- argc: numero de parametros passados na linha de comando
	- argv: lista de strings passadas como parametro na linha de comando
retorna:
	- numero de arquivos objetos passados como argumentos
==============================================================*/
int leii(FILE **codigo,	char *saida, Elf32_Ehdr **EHentrada, Elf32_Shdr **SHentrada, matriz *matrix, int argc, char *argv[])
{
		/*============Variáveis locais=============*/
		int i, j;	/*contadores*/
		/*========Fim Variáveis locais=============*/

		/********************************************
		lendo argumentos passados no terminal
		********************************************/
		for(i=1, j=0; i<argc; i++){
			/*verificar se usuário definiu nome do 
			arquivo de saída*/
			if(strcmp(argv[i], "-o")==0){
				i++;
				strcpy (saida, argv[i]);
				continue;
			}

/*###########Olhar############*/
			/*Informações de DEBUG*/
			if(strcmp(argv[i], "-g")==0){
				continue;
			}
			/* Fim Informações de DEBUG*/

			/*abrir arquivos fonte*/
			if(!(codigo[j] = fopen(argv[i], "rb"))){
				printf("\nAviso: arquivo %s não encontrado!\n", argv[i]);
				printf("Se possivel a ligação será feita sem ele\n\n");
				continue;
			}
/*#######Fim Olhar############*/
			
			/*aloca novo Elf header*/
			EHentrada[j] = (Elf32_Ehdr *)malloc(sizeof(Elf32_Ehdr));

			/*lê novo Elf Header*/
			leEH(codigo[j], EHentrada[j]);

			/*Verificar se é arquivo objeto no formato elf*/
			if( ((EHentrada[j]->e_ident[0] == 0x7f ) && (EHentrada[j]->e_ident[1] == 0x45 ) && (EHentrada[j]->e_ident[2] == 0x4c ) && (EHentrada[j]->e_ident[3] == 0x46 ))&& (EHentrada[j]->e_type==1) ){
				printf("\t%s é um arquivo objeto válido		OK\n", argv[i]);
			} else {
				printf("\nAviso: %s não é um arquivo objeto válido\n\n", argv[i]);
			}

			/*aloca array de Section Headers relativos
			ao j-ésimo arquivo objeto*/
			SHentrada[j] = (Elf32_Shdr *)malloc((EHentrada[j]->e_shnum)*sizeof(Elf32_Shdr));

			/*alocando colunas para a matrix de tipos de section header.
			tipo. tipoSH[j][n] é o tipo do n-énesima section header
			do j-ésimo código fonte*/
			matrix[j].e = (int *) malloc((EHentrada[j]->e_shnum)*sizeof(int));

			/*verifica se existe string table*/
			if((EHentrada[j]->e_shstrndx)!=0){

				/*coloca a Section Header 0 naposição 0 do array
				de Sections Headers relativo ao código objeto atual.
				SHentrada[j][k]: é o k-ésimo section header
				do j-ésimo arquivo objeto*/
				leSH(codigo[j], &(SHentrada[j][0]), (EHentrada[j]->e_shoff));

				/*coloca a Section Header relativa a string table na
				segunda posição do array de Sections Headers relativo
				ao código objeto atual. SHentrada[j][k]: é o k-ésimo
				section header do j-ésimo arquivo objeto*/
				leSH(codigo[j], &(SHentrada[j][1]), (EHentrada[j]->e_shoff)+(EHentrada[j]->e_shstrndx)*(sizeof(Elf32_Shdr)));
	
				/*preenche o resto da array de Section Headers
				relativo ao código atual. SHentrada[j][k]: é o k-ésimo
				section header do j-ésimo arquivo objeto*/
				preencheSH(codigo[j], SHentrada[j], SHentrada[j][1].sh_offset, EHentrada[j]->e_shnum, EHentrada[j]->e_shoff, matrix[j]);

			} else {
				printf("arquivo objeto incompleto: falta string table com nome das sections");
				exit (0);
			}
			j++;
		}

	return j;		
}
