#include<stdio.h>
#include<stdlib.h>
#include"constantes.h"
#include"estruturas.h"

extern int criaEHsaida(Elf32_Ehdr* elfHeader, Elf32_Addr startAddress, Elf32_Half shnum);

extern int letext(FILE *codigo, Elf32_Shdr SHentrada, char *buffer);

extern int ledata(FILE *codigo, Elf32_Shdr SHentrada, char *buffer);

extern int preenchePHsaida(Elf32_Phdr* PHeader, Elf32_Word type,Elf32_Off offset, Elf32_Addr vaddr, Elf32_Addr paddr, Elf32_Word filesz, Elf32_Word memsz, Elf32_Word flags, Elf32_Word align);

extern int sym(FILE **codigo, Elf32_Ehdr **EHentrada, Elf32_Shdr **SHentrada, 		FILE *saida, int arqnum, matriz *matrix, Elf32_Sym **sym, Elf32_Sym **Tgd, Nome **nomesym, Nome **nometgd, int deslocatext[], int deslocadata[], int tamtext, int tamdata);

/*======================imprimedata()=================================
imrprime as sections .data em sequencia para formar o segment .text
é chamada por:
	- imprmesaida (imprime.c)
@parametros:
	- codigo: lista de codigos objetos fonte
	- saida: ponteiro para o arquivo de saida
	- EHentrada: lista com Elf Headers dos arquivos objetos fontes
	- SHentrada: lista com lista de Sections Headers de cada arquivo obejto 
	fonte. SHentrada[j][i] = i-ésimo section header do j-ésimo arquivo
	- arqnum: numero de arquivos objetos fontes
	- matrix: matriz que indica o tipo das section. matrix[[j][i]
	= ao tipo da i-ésima section do j-ésimo arquivo
	- desloca: vetor para armazenar o delocamento de cada section .text
	(uma de cada arquivo) dentro do segment .text do arquivo de saida
	- tamtext: tamanho do segment .text
retorna:
	- o tamanho do segment .data
====================================================================*/
int imprimedata(FILE **codigo, FILE *saida, Elf32_Ehdr **EHentrada, Elf32_Shdr **SHentrada, int arqnum, matriz *matrix, int desloca[], int tamtext){
	/*===============variáveis locais==================*/
	int i, j;	/*contadores*/
	char *buffer;
	int somatorio = 0; /*soma dos tamanhos das sections
					  .data que ja foram escritas*/
	/*===============variáveis locais==================*/

		/*este for é para que seja lido o .data de cada arquivo fonte*/
		for(j=0; j<arqnum; j++){

		/*preenchendo desloca*/
		desloca[j]= somatorio;

		/*este for e os dois if's que o seguem servem para achar a section .data*/
		for(i=0; i<(EHentrada[j]->e_shnum); i++){
			if(matrix[j].e[i]==DATA){
				if(SHentrada[j][i].sh_offset != 0){

					/*aqui buffer é ponteiro pra char porque um char = um byte
					a funcao ledata le byte a byte*/
					buffer = (char *)malloc(SHentrada[j][i].sh_size*sizeof(char));
					ledata(codigo[j], SHentrada[j][i], buffer);

					/*ajustando deslocamento dentro do arquivo saida e escrevendo*/
					fseek(saida, sizeof(Elf32_Ehdr)+PHNUM*sizeof(Elf32_Phdr)+somatorio+tamtext, SEEK_SET);
					fwrite(buffer, SHentrada[j][i].sh_size, 1, saida);

					somatorio = somatorio+SHentrada[j][i].sh_size;
				}
			}
		}
	}

return somatorio;
}

/*======================imprimetext()=================================
imrprime as sections .text em sequencia para formar o segment .text
é chamada por:
	- imprmesaida (imprime.c)
@parametros:
	- codigo: lista de codigos objetos fonte
	- saida: ponteiro para o arquivo de saida
	- EHentrada: lista com Elf Headers dos arquivos objetos fontes
	- SHentrada: lista com lista de Sections Headers de cada arquivo obejto 
	fonte. SHentrada[j][i] = i-ésimo section header do j-ésimo arquivo
	- arqnum: numero de arquivos objetos fontes
	- matrix: matriz que indica o tipo das section. matrix[[j][i]
	= ao tipo da i-ésima section do j-ésimo arquivo
	- desloca: vetor para armazenar o delocamento de cada section .text
retorna:
	- o tamanho do segment
====================================================================*/
int imprimetext(FILE **codigo, FILE *saida, Elf32_Ehdr **EHentrada, Elf32_Shdr **SHentrada, int arqnum, matriz *matrix, int desloca[]){
	/*===============variáveis locais==================*/
	int i, j;	/*contadores*/
	char *buffer;
	int somatorio = 0; /*soma dos tamanhos das sections
					  .text que ja foram escritas*/
	/*===============variáveis locais==================*/

	/*este for é para que seja lido o .text de cada arquivo fonte*/
	for(j=0; j<arqnum; j++){

		/*preenchendo desloca*/
		desloca[j]= somatorio;
		
		/*este for e os dois if's que o seguem servem para achar a section .tex*/
		for(i=0; i<(EHentrada[j]->e_shnum); i++){
			if(matrix[j].e[i]==TEXT){
				if(SHentrada[j][i].sh_offset != 0){
					/*aqui buffer é ponteiro pra char porque um char = um byte
					a funcao letext le byte a byte*/
					buffer = (char *)malloc(SHentrada[j][i].sh_size*sizeof(char));
					letext(codigo[j], SHentrada[j][i], buffer);

					/*ajustando deslocamento dentro do arquivo saida e escrevendo*/
					fseek(saida, sizeof(Elf32_Ehdr)+PHNUM*sizeof(Elf32_Phdr)+somatorio, SEEK_SET);
					fwrite(buffer, SHentrada[j][i].sh_size, 1, saida);
					
					somatorio = somatorio+SHentrada[j][i].sh_size;
				}
			}
		}
	}

return somatorio;
}

/*======================imprimeEH()=================================
imrprime Elf Header no arquivo de saida
é chamada por:
	- imprmesaida (imprime.c)
@parametros:
	- elfHeader: ponteiro para Elf Header que deve ser imprimido
	- fp: arquivo de saida
====================================================================*/
int imprimeEH(Elf32_Ehdr* elfHeader, FILE* fp){

	fseek(fp, 0, SEEK_SET);
	fwrite(elfHeader, sizeof(Elf32_Ehdr), 1, fp);

	return 0;
}

/*======================imprimePH()=================================
imrprime Program Header Table no arquivo de saida
é chamada por:
	- imprmesaida (imprime.c)
@parametros:
	- PHeader: ponteiro para Program Header que deve ser imprimido
	- fp: arquivo de saida
====================================================================*/
int imprimePH(Elf32_Phdr* PHeader, FILE* fp){

	fseek(fp, sizeof(Elf32_Ehdr), SEEK_SET);
	fwrite(PHeader, PHNUM*sizeof(Elf32_Phdr), 1, fp);

	return 0;
}

/*=====================imprimesaida()=============================
Imprime o arquivo Elf de saída.
Chamada por:
	- main (b.c)
@parametros:
	- código: lista com códigos objetos fontes
	- saidac: nome do arquivo de saida
	- EHentrada: lista de Elf Headers dos códigos objetos fontes
	- SHentrada: lista das Sections Tables dos arquivos objetos fontes
	- matrix: matriz com tipos das sections headers
================================================================*/
int imprimesaida(FILE **codigo,char *saidac, Elf32_Ehdr **EHentrada, Elf32_Shdr **SHentrada, matriz *matrix, int arqnum){
		/*============Variáveis locais=============*/
		int i; /*contador*/
		int tamdym; /*tamanho do segment dynamic*/
		/*+++variáveis para armazenar informações do arquivo de saida+++*/
		Elf32_Ehdr EHsaida;
		Elf32_Phdr *PHsaida;

		/*alocando Program Header Table*/
		PHsaida = (Elf32_Phdr *)malloc(PHNUM*sizeof(Elf32_Phdr));
		
		/*abrindo arquivo de saida*/
		FILE *saida;
		if(!(saida = fopen(saidac, "wb"))){
				printf("\nErro: Falha na abertura do arquivo de saida\n");
				exit (0);
			}

		/*+variaceis que guardam o deslocamento de uma secao dentro de 
		um segment de mesmo nome (ou .text ou .data)+*/
		int deslocatext[arqnum];
		int deslocadata[arqnum];

		/*+fim variaceis que guardam o deslocamento de uma secao dentro de 
		um segment de mesmo nome+*/

		/*+guardam o tamanho de um segmento (ou .text ou .data)+*/
		int tamtext;
		int tamdata;
		/*+ fim guardam o tamanho de um segmento+*/

		/*+variaveis para a criação da tabela global de definições*/
		Elf32_Sym **symt; /*armazena symbol tables  dos arquivos:
							sym[j][i]: i-ésima symbol table do j-ésimo
							arquivo objeto fonte*/
		Elf32_Sym **Tgd; /*endereço da tabela global de definições*/
		symt = (Elf32_Sym **)malloc(arqnum*sizeof(Elf32_Sym*));
		Tgd = (Elf32_Sym **)malloc(arqnum*sizeof(Elf32_Sym*));

		/*+ponteiros para guardar nomes de symbols+*/
		Nome **nomesym = NULL;
		Nome **nometgd = NULL;
		/*+fim ponteiros para guardar nomes de symbols+*/
		
		/*+fim variaveis para a criação da tabela global de definições*/

		/*+++variáveis para armazenar informações do arquivo de saida+++*/


/*##########REVER############*/		
		/*++++++++endereço de entrada++++++++++++*/
		i = 0;
		/*enquato não descobrir qual é a
		section header .text do arquivo principal*/
		while(matrix[0].e[i]!=TEXT){
			i++;
		}

		/*calculo do endereço de entrada: (enderço de entrada do programa principal)*/
		 Elf32_Addr startAddress = EHentrada[0]->e_entry;
		/*++++fim endereço de entrada++++++++++++*/
		 
		 /*numero de entradas no program header*/
		 Elf32_Half phnum=PHNUM;
/*######fim REVER############*/		
		/*========Fim Variáveis locais=============*/
		
		/*imprime Elf Header da saída*/
		criaEHsaida(&EHsaida, startAddress, phnum);
		imprimeEH(&EHsaida, saida);
		
		/*imprime Program Header Table. (necessária atualização posterior)*/
		imprimePH(PHsaida, saida);

		/*imprime segment .text*/
		tamtext = imprimetext(codigo, saida, EHentrada, SHentrada, arqnum, matrix, deslocatext);
		
		/*atualiza entrada no program header relativo ao segment .text*/
		preenchePHsaida(&(PHsaida[0]), PT_LOAD, sizeof(Elf32_Ehdr)+sizeof(Elf32_Phdr)*PHNUM, 0, 0, tamtext, tamtext, PF_R+PF_X, 0);
		
		/*imprime segment .data*/
		tamdata = imprimedata(codigo, saida, EHentrada, SHentrada, arqnum, matrix, deslocadata, tamtext);
		
		/*atualiza entrada no program header relativo ao segment .data*/
		preenchePHsaida(&(PHsaida[1]), PT_LOAD, sizeof(Elf32_Ehdr)+sizeof(Elf32_Phdr)*PHNUM+tamtext, tamtext, 0, tamdata, tamdata, PF_R+PF_W+PF_X, 0);

		/*resolve referencias cruzadas e faz realocação*/
		tamdym = sym(codigo, EHentrada, SHentrada, saida, arqnum, matrix, symt, Tgd, nomesym, nometgd, deslocatext, deslocadata, tamtext, tamdata);

		/*atualiza entrada no program header relativo ao segment .data*/
		preenchePHsaida(&(PHsaida[2]), PT_DYNAMIC, sizeof(Elf32_Ehdr)+sizeof(Elf32_Phdr)*PHNUM+tamtext+tamdata, 0, 0, tamdym, 0, PF_R+PF_W, 0);

		/*imprime o PHsaida atualizado*/
		imprimePH(PHsaida, saida);

return 0;
}

