#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"desmontador.h"

/*
**	___________________geracodigocomdebug.c___________________
**		
**	Lê o cabeçalho, lê o section header, lê as strings, gera as labels, lê as instruções, lê os dados (.data e .bss)
**	e com tudo isso gera as estruturas de dados com o código, os dados e as labels.
**	
**	___________________geracodigocomdebug.c___________________
**/


/*============================================================
====================DEBUG=====================================
============================================================*/

#define DEBUGSHx
#define DEBUGsymtabx
#define DEBUGsrttabx
#define DEBUGstringx
#define DEBUGdatax
#define DEBUGbssx
#define DEBUGlabelx

#ifdef DEBUGlabel
void varrerlabel(labelS *p_inicio);
#endif

labelS *geracodigocomdebug(FILE *codigo, undadosS **p_iniciodadosun, codeS **p_newcode, tabelaS *p_tabela, dataS **p_newdata){

	int byteatual=0, i=0, k=0;
	int sh_offset_code=0, sh_addr_code=0, size_code=0;
	int sh_offset_data=0, sh_addr_data=0, size_data=0;
	int sh_offset_bss=0, sh_addr_bss=0, size_bss=0;
	int sh_offset_string=0, size_string=0, sh_name=0, size_name=0;
	char *buffer_string, char_name=0, *buffer_name;
	int sh_offset_symtab=0, size_symtab=0, sh_entsize_symtab=0;
	int sh_offset_srttab=0, size_srttab=0;
	char *buffer_srttab;
	int *code, *data;
	labelS *p_labels=NULL;
	char *label=NULL;

	Elf32_Ehdr *elfHeader;
	Elf32_Shdr *sectionHeader;
	Elf32_Sym *symTab;

/*============================================================
====================Leitura ELF's Header======================
============================================================*/

	elfHeader=malloc(sizeof(Elf32_Ehdr));
	fseek(codigo, 0, SEEK_SET);
	fread(elfHeader,sizeof(Elf32_Ehdr),1,codigo);

#ifdef ElfHeader
printf("\nTudo que é necessário do Elf Header:\n\ne_entry:\t%.4x", elfHeader->e_entry);
printf("\ne_phoff:\t%.4x\ne_shoff:\t%.4x", elfHeader->e_phoff, elfHeader->e_shoff);
printf("\ne_phentsize:\t%.4x\ne_phnum:\t%.4x", elfHeader->e_phentsize, elfHeader->e_phnum);
printf("\ne_shentsize:\t%.4x\ne_shnum:\t%.4x", elfHeader->e_shentsize, elfHeader->e_shnum);
printf("\ne_shstrndx:\t%.4x\n\n", elfHeader->e_shstrndx);
#endif

/*============================================================
====================Leitura Section Header ===================
============================================================*/

	/*Verificando se é um arquivo elf.*/
	if( ((elfHeader->e_ident[0] == 0x7f ) && (elfHeader->e_ident[1] == 0x45 ) && (elfHeader->e_ident[2] == 0x4c ) && (elfHeader->e_ident[3] == 0x46 )) ){

		/*Verificando se é executável (OU OBJETO)*/
		if(elfHeader->e_type==2 || elfHeader->e_type==1){

			/*============================================================
			====================Leitura SHString Table====================
			============================================================*/

			if((elfHeader->e_shstrndx)!=0){

				sectionHeader=malloc(sizeof(Elf32_Shdr));
				fseek(codigo, (elfHeader->e_shoff)+(elfHeader->e_shstrndx)*(sizeof(Elf32_Shdr)), SEEK_SET);
				fread(sectionHeader,sizeof(Elf32_Shdr),1,codigo);

				/*p_type = 3 significa SHSTRING Table*/
				if(sectionHeader->sh_type==3){
					sh_offset_string=sectionHeader->sh_offset;
					printf("\nRAMIRO 1: %d\n\n",sectionHeader->sh_offset);

					size_string=sectionHeader->sh_size;
				}

				buffer_string=malloc(size_string*sizeof(char));
				fseek(codigo, sh_offset_string, SEEK_SET);
				for (i = 0; (fread(&byteatual,1,1,codigo) != 0 ) && i < size_string; buffer_string[i++] = byteatual);

				#define DEBUGstring
				#ifdef DEBUGstring
/*				printf("As Strings encontradas na String Table são:\n");
				for(i=0;i<(size_string);i++){
					printf("%c", buffer_string[i]);
				}
				printf("\n\n");
	*/			#endif
			}

		/*============================================================
		====================Voltando para a SHT=======================
		============================================================*/
		
			for(i=0;i<(elfHeader->e_shnum);i++){

				fseek(codigo, (elfHeader->e_shoff)+i*(sizeof(Elf32_Shdr)), SEEK_SET);
				fread(sectionHeader,sizeof(Elf32_Shdr),1,codigo);

				size_name=0;
				sh_name=sectionHeader->sh_name;
				#ifdef DEBUGstring
/*				printf("\n%x\n", sh_name);*/
				#endif

				/*Ir na String Table e ler o nome da seção.*/	
				if(sh_name!=0){
					fseek(codigo, (sh_offset_string+sh_name), SEEK_SET);
					do{
						fread(&byteatual,1,1,codigo);
						char_name=byteatual;
						size_name++;
					}while(char_name != 0);

					buffer_name=malloc(size_name*sizeof(char));
					fseek(codigo, (sh_offset_string+sh_name), SEEK_SET);

					for(k=0; ((fread(&byteatual,1,1,codigo) != 0 ) && (k < size_name));  buffer_name[k++]=byteatual);
					
					#ifdef DEBUGstring
					printf("%s\n\n", buffer_name);
					#endif
				}

				/*Salvando os Endereços*/
				if(sectionHeader->sh_type==1){
					if( strcmp(buffer_name,".text") == 0 ){
						sh_addr_code=sectionHeader->sh_addr;
					}else if( strcmp(buffer_name,".data") == 0){
						sh_addr_data=sectionHeader->sh_addr;							
					}
				} else if(sectionHeader->sh_type==8 && ( strcmp(buffer_name,".bss") == 0) ){
					sh_addr_bss=sectionHeader->sh_addr;
				}

				/*Salvando os Offsets*/
				if(sectionHeader->sh_type==1){
					if( (strcmp(buffer_name,".text") == 0) ){
						sh_offset_code=sectionHeader->sh_offset;
					} else if(strcmp(buffer_name,".data") == 0){
						sh_offset_data=sectionHeader->sh_offset;
					}					
				} else if(sectionHeader->sh_type==8 && (strcmp(buffer_name,".bss") == 0 ) ){
					sh_offset_bss=sectionHeader->sh_offset;
				} else if(sectionHeader->sh_type==2 && ( strcmp(buffer_name,".symtab") == 0) ){
					sh_offset_symtab=sectionHeader->sh_offset;
				} else if(sectionHeader->sh_type==3 && ( strcmp(buffer_name,".strtab") == 0) ){
					sh_offset_srttab=sectionHeader->sh_offset;
				}

				/*Salvando os tamanhos*/
				if(sectionHeader->sh_type==1){
					if(strcmp(buffer_name,".text") == 0){
						size_code=sectionHeader->sh_size;
					} else if(strcmp(buffer_name,".data") == 0){
						size_data=sectionHeader->sh_size;
					}
				} else if(sectionHeader->sh_type==8 && (strcmp(buffer_name,".bss") == 0) ){
					size_bss=sectionHeader->sh_size;
				} else if(sectionHeader->sh_type==2 && ( strcmp(buffer_name,".symtab") == 0) ){
					size_symtab=sectionHeader->sh_size;
				} else if(sectionHeader->sh_type==3 && ( strcmp(buffer_name,".strtab") == 0) ){
					size_srttab=sectionHeader->sh_size;
				}

				/*Salvando o tamanho do Symtab*/
				if(sectionHeader->sh_type==2 && ( strcmp(buffer_name,".symtab") == 0) ){
					sh_entsize_symtab=sectionHeader->sh_entsize;
				}
			}

				#ifdef DEBUGSH
					printf("\n(code, data, bss, symtab, srttab)\n\n");
					printf("size: %x %x %x %x %x \n", size_code, size_data, size_bss, size_symtab, size_srttab);
					printf("offset: %x %x %x %x %x \n", sh_offset_code, sh_offset_data, sh_offset_bss, sh_offset_symtab, sh_offset_srttab);
					printf("addr: %x %x %x\n", sh_addr_code, sh_addr_data, sh_addr_bss);
					printf("\n");
				#endif

		} else{
			printf("**Erro: Não é um arquivo executável e não pode ser desmontado.\n...Não foi possível gerar o código.\n");
			exit(1);
		}

	/*caso não seja um arquivo elf*/
	} else{
		printf("**Erro: Não é um arquivo do tipo ELF e não pode ser desmontado.\n...Não foi possível gerar o código.\n");
		exit(1);
	} /*Fim do if do Magic Number*/


/*============================================================
====================Leitura SYMBOL TABLE======================
============================================================*/
	if(size_srttab!=0){
		/*============================================================
		====================Leitura String Table (símbolos)===========
		============================================================*/

			#ifdef DEBUGsrttab
			printf("O offset do inicio do srttab é: %.8x\n", sh_offset_srttab);
			printf("O tamanho do srttab é: %d\n", size_srttab);
			#endif

			/*Daqui eu tiro os nomes de todos (concatenados)*/
			buffer_srttab=malloc(size_srttab*sizeof(char));
			fseek(codigo, sh_offset_srttab, SEEK_SET);
			fread(buffer_srttab,(size_srttab*sizeof(char)),1,codigo);

			#ifdef DEBUGsrttab
			printf("Srttab:\n");
			for(i=0;i<size_srttab;i++){
				printf("%c", buffer_srttab[i]);
			}
			printf("\n\n");
			#endif

	/*Gerar label para entry.*/
	if(size_srttab==0){
		label=gerarlabel(&p_labels, elfHeader->e_entry, 0);
	}

	/*Daqui eu tiro os nomes e os endereços.*/
	if(sh_offset_symtab!=0){ 

		#ifdef DEBUGsymtab
		printf("O offset do inicio do symtab é: %.8x\n", sh_offset_symtab);
		printf("O tamanho do symtab é: %d\n", size_symtab);
		#endif

		for(i=0;i<(size_symtab/sh_entsize_symtab);i++){

			symTab=malloc(sizeof(Elf32_Sym));
			fseek(codigo, sh_offset_symtab+i*(sizeof(Elf32_Sym)), SEEK_SET);
			fread(symTab,sizeof(Elf32_Sym),1,codigo);

			/*Ir na String Table e ler o nome da seção.*/	
			if(symTab->st_name!=0){
				fseek(codigo, (sh_offset_srttab+(symTab->st_name)), SEEK_SET);
				do{
					fread(&byteatual,1,1,codigo);
					char_name=byteatual;
					size_name++;
				}while(char_name != 0);

				buffer_name=malloc((size_name)*sizeof(char));
				fseek(codigo, (sh_offset_srttab+(symTab->st_name)), SEEK_SET);
				for(k=0; ((fread(&byteatual,1,1,codigo) != 0 ) && (k < size_name));  buffer_name[k++]=byteatual);

			label=gerarlabel(&p_labels, symTab->st_value, buffer_name);

			}/*Fim da leitura do nome*/
		}
	}/*If Leitura do symtab*/

/*============================================================
====================Não existem informações de DEBUG==========
============================================================*/
	}else{
		printf("**Aviso: Não existem informações de DEBUG, o desmontador fará o melhor esforço.\n**Talvez funcione melhor assim:\n\t./desmontador <nomedoprograma>\n\n");
	}

/*============================================================
====================Leitura do Código=========================
============================================================*/
	if(sh_offset_code!=0){
		code=malloc(size_code*sizeof(int));
		fseek(codigo, sh_offset_code, SEEK_SET);		
		for (i = 0; (fread(&byteatual,1,1,codigo) != 0 ) && i < size_code; code[i++] = byteatual);
		(*p_newcode)=malloc(sizeof(codeS));
		((*p_newcode)->codigocompleto)=code;
		(*p_newcode)->endereco=sh_addr_code;
	}

	(*p_newcode)->codigocompleto[i]=0x100;


/*============================================================
====================Leitura dos Dados (.data)=================
============================================================*/
	if(sh_offset_data!=0){
		data=malloc(size_data*sizeof(int));
		fseek(codigo, sh_offset_data, SEEK_SET);		
		for (i = 0; (fread(&byteatual,1,1,codigo) != 0 ) && i < size_data; data[i++] = byteatual);

		(*p_newdata)=malloc(sizeof(dataS));
		((*p_newdata)->datacompleto)=data;

		(*p_newdata)->endereco=sh_addr_data;
	}

	(*p_newdata)->datacompleto[i]=0x100;

/*============================================================
====================SALVAR EM "quantidade" OS DADOS (.bss)====
============================================================*/

	(*p_iniciodadosun)=malloc(sizeof(undadosS));

	(*p_iniciodadosun)->quantidade=size_bss;
	(*p_iniciodadosun)->endereco=sh_addr_bss;

	/*Gerar label para esse endereço.*/
	if(((*p_iniciodadosun)->quantidade)!=0){
		if(sh_offset_symtab==0)
			label=gerarlabel(&p_labels, (*p_iniciodadosun)->endereco, 0);
	}

/**/


#ifdef DEBUGbss
if(sh_offset_bss!=0){
	printf("O offset do inicio dos dados (.bss) é: %.8x\n", sh_offset_bss);
	printf("Existem %d dados não inicializados.\n\n", size_bss);
}
#endif
#ifdef DEBUGlabel
varrerlabel(p_labels);
#endif

	printf("...Código gerado com sucesso.\n");

	return p_labels;
} /*Fim*/

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
