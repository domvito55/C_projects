#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"desmontador.h"

/*
**	___________________geracodigo.c___________________
**		
**	Lê o cabeçalho, lê o program header, lê as instruções (gera labels aleatórias), lê os dados (.data e .bss)
**	e com tudo isso gera as estruturas de dados com o código, os dados e as labels.
**	
**	___________________geracodigo.c___________________
**/


/*============================================================
====================DEBUG=====================================
============================================================*/
#define DEBUGlabelx
#define ElfHeaderx
#define ProgramHeaderx
#define DEBUGdatax

#ifdef DEBUGlabel
void varrerlabel(labelS *p_inicio);
#endif

#ifdef DEBUGdata
void varrerdados(dadosS *p_inicio);
#endif


labelS *geracodigo(FILE *codigo, undadosS **p_iniciodadosun, codeS **p_newcode, tabelaS *p_tabela, dataS **p_newdata){

	int offset_code=0, addr_code=0, size_code=0, addr_data=0, size_data=0, byteatual=0, offset_data=0, i=0, size_bss=0;
	int *code, *data;
	char *label=NULL;
	tabelaS *pt=NULL;
	labelS *p_labels=NULL;
	Elf32_Ehdr *elfHeader;
	Elf32_Phdr *programHeader;

/*============================================================
====================Leitura ELF's Header======================
============================================================*/

	elfHeader=malloc(sizeof(Elf32_Ehdr));
	fseek(codigo, 0, SEEK_SET);
	fread(elfHeader,sizeof(Elf32_Ehdr),1,codigo);
	label=gerarlabel(&p_labels, elfHeader->e_entry, 0);

#ifdef ElfHeader
printf("\nTudo que é necessário do Elf Header:\n\ne_entry:\t%.4x", elfHeader->e_entry);
printf("\ne_phoff:\t%.4x\ne_shoff:\t%.4x", elfHeader->e_phoff, elfHeader->e_shoff);
printf("\ne_phentsize:\t%.4x\ne_phnum:\t%.4x", elfHeader->e_phentsize, elfHeader->e_phnum);
printf("\ne_shentsize:\t%.4x\ne_shnum:\t%.4x", elfHeader->e_shentsize, elfHeader->e_shnum);
printf("\ne_shstrndx:\t%.4x\n\n", elfHeader->e_shstrndx);
#endif
#ifdef DEBUGlabel
varrerlabel(p_labels);
#endif

/*============================================================
====================Leitura Program Header====================
============================================================*/

	/*Verificando se é um arquivo elf.*/
	if( ((elfHeader->e_ident[0] == 0x7f ) && (elfHeader->e_ident[1] == 0x45 ) && (elfHeader->e_ident[2] == 0x4c ) && (elfHeader->e_ident[3] == 0x46 )) ){

		/*Verificando se é executável##################*/
		if(elfHeader->e_type==2){

			for(i=0;i<(elfHeader->e_phnum);i++){

				programHeader=malloc(sizeof(Elf32_Phdr));
				fseek(codigo, (elfHeader->e_phoff)+i*(sizeof(Elf32_Phdr)), SEEK_SET);
				fread(programHeader,sizeof(Elf32_Phdr),1,codigo);

				/*p_type = 1 significa LOAD*/
				if(programHeader->p_type==1){
					/*O que é necessário para o code (p_flags=5):*/
					if((programHeader->p_flags)==5){
						offset_code=programHeader->p_offset;
						addr_code=programHeader->p_vaddr;
						size_code=programHeader->p_filesz;
					}
					/*O que é necessário para o .data (p_flags=6):*/
					if((programHeader->p_flags)==6){
						offset_data=programHeader->p_offset;
						addr_data=programHeader->p_vaddr;
						size_data=programHeader->p_filesz;
						size_bss=programHeader->p_mesz;
					}		
				}

			#ifdef ProgramHeader
				printf("\nTudo que é necessário do Program Header (%d):\n\np_type:\t\t%d", i, programHeader->p_type);
				printf("\np_offset:\t%.4x\np_vaddr:\t%.8x", programHeader->p_offset, programHeader->p_vaddr);
				printf("\np_paddr:\t%.8x\np_filesz:\t%x", programHeader->p_paddr, programHeader->p_filesz);
				printf("\np_mesz:\t\t%x\np_flags:\t%.4x", programHeader->p_mesz, programHeader->p_flags);
				printf("\np_allign:\t%.4x\n\n", programHeader->p_allign);
			#endif
			}
		} else{
			printf("**Erro: Não é um arquivo executável e não pode ser desmontado.\n...Não foi possível gerar o código.\n");
			exit(1);
		}
	/*caso não seja um arquivo elf*/
	} else{
			printf("**Erro: Não é um arquivo do tipo ELF e não pode ser desmontado.\n...Não foi possível gerar o código.\n");
			exit(1);
	}

/*============================================================
====================Leitura do Código=========================
============================================================*/
if(elfHeader->e_phoff!=0){
	if(offset_code!=0){
		code=malloc(size_code*sizeof(int));
		fseek(codigo, offset_code, SEEK_SET);		
		for (i = 0; (fread(&byteatual,1,1,codigo) != 0 ) && i < size_code; code[i++] = byteatual);

		(*p_newcode)=malloc(sizeof(codeS));
		((*p_newcode)->codigocompleto)=code;

		(*p_newcode)->endereco=addr_code;
	}

	(*p_newcode)->codigocompleto[i]=0x100;

	/*============================================================
	====================Gerando labels aleatórias=================
	============================================================*/
	i=0;
	while( (*p_newcode)->codigocompleto[i]!=0x100){

		/*Busca o tipo da instrução*/
		pt=buscartabela(p_tabela, ( (*p_newcode)->codigocompleto[i]) );
		if( pt->tipo == 2){
			i++;
		}
		if(pt->tipo == 3){
			label=gerarlabel(&p_labels, ((*p_newcode)->codigocompleto[i+1]+(*p_newcode)->codigocompleto[i+2]*256), 0);
			i++;
			i++;
		}

		i++;
	}

/*============================================================
====================Leitura dos Dados (.data)=================
============================================================*/
	if(offset_data!=0){
		data=malloc(size_data*sizeof(int));
		fseek(codigo, offset_data, SEEK_SET);		
		for (i = 0; (fread(&byteatual,1,1,codigo) != 0 ) && i < size_data; data[i++] = byteatual);

		(*p_newdata)=malloc(sizeof(dataS));
		((*p_newdata)->datacompleto)=data;

		(*p_newdata)->endereco=addr_data;
	}

	(*p_newdata)->datacompleto[i]=0x100;

/*============================================================
====================Leitura dos Dados (.bss)=================
============================================================*/

	/*Gerar label para esse endereço.*/
	if((size_bss-size_data)!=0){
		(*p_iniciodadosun)=malloc(sizeof(undadosS));

		(*p_iniciodadosun)->quantidade=(size_bss-size_data);
		(*p_iniciodadosun)->endereco=addr_data+size_data;

		label=gerarlabel(&p_labels, (*p_iniciodadosun)->endereco, 0);
	}

	}else{
		printf("**Aviso: Não existe o Program Header, pode-se tentar desmontar pelo Section Header:\n\t./desmontador -g <nomedoprograma>\n\n");
		exit(1);
	}

#ifdef DEBUGlabel
varrerlabel(p_labels);
#endif

#ifdef DEBUGdata
varrerdados(*p_iniciodados);
#endif

	printf("...Código gerado com sucesso.\n");
	return p_labels;
}

#ifdef DEBUGlabel
void varrerlabel(labelS *p_inicio){
	labelS *p1;
	p1=p_inicio;
	while(p1!=NULL){
		printf("%x %s\n", p1->endereco, p1->label);
		p1=p1->next;
	}
}
#endif
#ifdef DEBUGdata
void varrerdados(dadosS *p_inicio){
	dadosS *p1;
	elementosdadosS *pd1;
	p1=p_inicio;
	while(p1!=NULL){
		pd1=p1->elementos;
		printf("%x", p1->endereco);
		while(pd1!=NULL){
			printf(" %d", pd1->byte1);
			pd1=pd1->next;
		}
		printf("\n");
		p1=p1->next;
	}
}
#endif
