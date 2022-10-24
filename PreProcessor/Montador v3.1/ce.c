/**
Funcoes para criacao de cabecalhos, impressao de estruturas e outros metodos relacionados a estrutura ELF

@version 1.1
@author Murilo M. Marinho
*/

#include<stdio.h>
#include<stdlib.h>
#include"ce.h"
#include"instrucao.h"
#include<string.h>

#define E_SHNUM 8
#define SHSTRTAB "\0.shstrtab\0.data\0.text\0.rela.text\0.strtab\0.symtab\0.stab\0"

int ce(FILE*fp, int entry_address, int data_size, int data_address, int text_size, int text_address, int relatext_num, int strtab_size, int simbol_num, int stab_num){
/*	printf("\nData Size = %i\n", data_size);
	printf("\nData Address = %i\n", data_address);
	printf("\nText Size = %i\n", text_size);
	printf("\nText Address = %i\n", text_address);
	printf("\nRela Text Num = %i\n", relatext_num);	
*/
	Elf32_Ehdr* elfHeader;
	newFileElfHeader(&elfHeader, entry_address, E_SHNUM);

	printFileElfHeader(elfHeader,fp);

	Elf32_Shdr* sectionHeaderTable[E_SHNUM];

	newEmptySectionHeader(&sectionHeaderTable[0]);

	/*Momento Section Header String Table*/
		char* shstrtab = SHSTRTAB;
		int shstrtab_size = sizeof(SHSTRTAB);

		int shstrtab_off = sizeof(Elf32_Ehdr);
		shstrtab_off += E_SHNUM*sizeof(Elf32_Shdr);

	newShstrtabSectionHeader(&sectionHeaderTable[1],1,shstrtab_off,shstrtab_size);

	/*Momento Section Data*/
		int data_offset = shstrtab_off + shstrtab_size;  

	newDataSectionHeader(&sectionHeaderTable[2],11,data_address, data_offset,data_size);

	/*Momento Section Text*/
		int text_offset = data_offset + data_size;

	newTextSectionHeader(&sectionHeaderTable[3],17,text_address, text_offset,text_size);

	/*Momento Relative Text*/
		int relatext_size = relatext_num*ELF32_RELA_SIZE;
		int relatext_offset = text_offset + text_size;

	newRelaTextSectionHeader(&sectionHeaderTable[4],23, relatext_offset,relatext_size);

	/*Momento String Table*/
		int strtab_offset = relatext_offset + relatext_size;

	newShstrtabSectionHeader(&sectionHeaderTable[5],34, strtab_offset,strtab_size);

	/*Momento SimbolTable*/
		int simbol_size = simbol_num*ELF32_SYM_SIZE;
		int simbol_offset = strtab_offset + strtab_size;

	newSymSectionHeader(&sectionHeaderTable[6],42, simbol_offset,simbol_size);

	/*Momento Stabs*/
		int stab_offset = simbol_size + simbol_offset;
		int stab_size = stab_num*STAB_SIZE;

	newStabSectionHeader(&sectionHeaderTable[7],50, stab_offset,stab_size);

	/*Imprime Os Section Headers*/
	int i = 0;
	for(i = 0; i < E_SHNUM;i++){
		printSectionHeader(sectionHeaderTable[i],fp);
	}
	/*Print Section Header String Table*/
	fwrite(shstrtab, sizeof(char), shstrtab_size, fp);


return 0;
}



/**
Cria um novo Cabecalho ELF para 8085.

@param elfHeader O Novo Elf Header que sera alocado.
@param startAddress Endereco do ponto de entrada do programa, .start.
@param shnum A quantidade de Section Headers contidos na Section Header Table
*/
void newFileElfHeader(Elf32_Ehdr** elfHeader, Elf32_Addr startAddress, Elf32_Half shnum){
	Elf32_Ehdr* header = (Elf32_Ehdr*)malloc(sizeof(Elf32_Ehdr));
	header->e_ident[EI_MAG0] = ELFMAG0;
	header->e_ident[EI_MAG1] = ELFMAG1;
	header->e_ident[EI_MAG2] = ELFMAG2;
	header->e_ident[EI_MAG3] = ELFMAG3;
	header->e_ident[EI_CLASS]= ELFCLASS32;
	header->e_ident[EI_DATA] = ELFDATA2LSB;
	header->e_ident[EI_VERSION] = EV_CURRENT;

	int i = 0;
	for(i = EI_PAD; i < EI_NIDENT; i++){
		header->e_ident[i] = 0;
	}
	
	header->e_type = ET_REL;
	
	header->e_machine = EM_8085;
	
	header->e_version = EV_CURRENT;
	
	header->e_entry = startAddress;

	header->e_phoff = 0;   
	
	header->e_shoff = sizeof(Elf32_Ehdr);    
	
	header->e_flags = 0; 
	
	header->e_ehsize = sizeof(Elf32_Ehdr);   
	
	header->e_phentsize = 0;   
	
	header->e_phnum = 0;       
	
	header->e_shentsize = sizeof(Elf32_Shdr);      
    
	header->e_shnum = shnum; /*1 + .text + .data + .rela + .sym + .str + .srthn*/       
	
	header->e_shstrndx = 1;

	(*elfHeader) = header;
}


/**
Imprime o Cabecalho ELF para 8085.

@param elfHeader O cabecalho que se deseja imprimir.
@param fp O arquivo no qual se quer imprimir.
*/
int printFileElfHeader(Elf32_Ehdr* elfHeader, FILE* fp){

	fwrite(elfHeader, sizeof(Elf32_Ehdr), 1, fp);

	return 1;
}

/**
Cria um Section Header vazio, para o indice zero da Section Header Table

@param shdr Ponteiro para o novo local alocado na memoria.
*/
void newEmptySectionHeader(Elf32_Shdr** shdr){

	Elf32_Shdr* secheader = (Elf32_Shdr*)malloc(sizeof(Elf32_Shdr));
	
	secheader->sh_name = 0xFFFFFFFF;
	secheader->sh_type = SHT_NULL;
	secheader->sh_flags = 0;
	secheader->sh_addr = 0;
	secheader->sh_offset = 0;
	secheader->sh_size = 0;
	secheader->sh_link = SHN_UNDEF;
	secheader->sh_info = 0; 
	secheader->sh_addralign = 0;
	secheader->sh_entsize = 0;

	(*shdr) = secheader;

}

/**
Cria um novo Header para uma secao .shstrtab.

@param shdr Ponteiro para o novo local alocado na memoria.
@param name Indice na .shstrtab do nome dessa secao.
@param offset Distancia do inicio do arquivo ate o inicio dessa secao.
@param size A quantidade de bytes contida nessa secao.
*/
void newShstrtabSectionHeader(Elf32_Shdr** shdr,Elf32_Word name,Elf32_Off offset,Elf32_Word size){

	Elf32_Shdr* secheader = (Elf32_Shdr*)malloc(sizeof(Elf32_Shdr));
	
	secheader->sh_name = name;
	secheader->sh_type = SHT_STRTAB;
	secheader->sh_flags = SHF_STRINGS;
	secheader->sh_addr = 0;
	secheader->sh_offset = offset;
	secheader->sh_size = size;
	secheader->sh_link = SHN_UNDEF;
	secheader->sh_info = 0; 
	secheader->sh_addralign = 0;
	secheader->sh_entsize = 0;

	(*shdr) = secheader;
}

/**
Cria um novo Header para uma secao .data.

@param shdr Ponteiro para o novo local alocado na memoria.
@param name Indice na .shstrtab do nome dessa secao.
@param addr Endereco do primeiro byte no mapeamento de memoria. Usando zero como base.
@param offset Distancia do inicio do arquivo ate o inicio dessa secao.
@param size A quantidade de bytes contida nessa secao.
*/
void newDataSectionHeader(Elf32_Shdr** shdr,Elf32_Word name,Elf32_Addr addr, Elf32_Off offset,Elf32_Word size){

	Elf32_Shdr* secheader = (Elf32_Shdr*)malloc(sizeof(Elf32_Shdr));
	
	secheader->sh_name = name;
	secheader->sh_type = SHT_PROGBITS;
	secheader->sh_flags = SHF_ALLOC + SHF_WRITE;
	secheader->sh_addr = addr;
	secheader->sh_offset = offset;
	secheader->sh_size = size;
	secheader->sh_link = SHN_UNDEF;
	secheader->sh_info = 0; 
	secheader->sh_addralign = 0;
	secheader->sh_entsize = 0;

	(*shdr) = secheader;
}

/**
Cria um novo Header para uma secao .text.

@param shdr Ponteiro para o novo local alocado na memoria.
@param name Indice na .shstrtab do nome dessa secao.
@param addr Endereco do primeiro byte no mapeamento de memoria. Usando zero como base.
@param offset Distancia do inicio do arquivo ate o inicio dessa secao.
@param size A quantidade de bytes contida nessa secao.
*/
void newTextSectionHeader(Elf32_Shdr** shdr,Elf32_Word name,Elf32_Addr addr, Elf32_Off offset,Elf32_Word size){

	Elf32_Shdr* secheader = (Elf32_Shdr*)malloc(sizeof(Elf32_Shdr));
	
	secheader->sh_name = name;
	secheader->sh_type = SHT_PROGBITS;
	secheader->sh_flags = SHF_ALLOC + SHF_EXECINSTR;
	secheader->sh_addr = addr;
	secheader->sh_offset = offset;
	secheader->sh_size = size;
	secheader->sh_link = SHN_UNDEF;
	secheader->sh_info = 0; 
	secheader->sh_addralign = 0;
	secheader->sh_entsize = 0;

	(*shdr) = secheader;
}

/**
Cria um novo Header para uma secao .rela.text.

@param shdr Ponteiro para o novo local alocado na memoria.
@param name Indice na .shstrtab do nome dessa secao.
@param offset Distancia do inicio do arquivo ate o inicio dessa secao.
@param size A quantidade de bytes contida nessa secao.
*/
void newRelaTextSectionHeader(Elf32_Shdr** shdr,Elf32_Word name, Elf32_Off offset,Elf32_Word size){

	Elf32_Shdr* secheader = (Elf32_Shdr*)malloc(sizeof(Elf32_Shdr));
	
	secheader->sh_name = name;
	secheader->sh_type = SHT_RELA;
	secheader->sh_flags = 0;
	secheader->sh_addr = 0;
	secheader->sh_offset = offset;
	secheader->sh_size = size;
	secheader->sh_link = SHN_UNDEF;
	secheader->sh_info = 3; 
	secheader->sh_addralign = 0;
	secheader->sh_entsize = 12;

	(*shdr) = secheader;
}

/**
Cria um novo Header para uma secao .sym.

@param shdr Ponteiro para o novo local alocado na memoria.
@param name Indice na .shstrtab do nome dessa secao.
@param offset Distancia do inicio do arquivo ate o inicio dessa secao.
@param size A quantidade de bytes contida nessa secao.
*/
void newSymSectionHeader(Elf32_Shdr** shdr,Elf32_Word name, Elf32_Off offset,Elf32_Word size){

	Elf32_Shdr* secheader = (Elf32_Shdr*)malloc(sizeof(Elf32_Shdr));
	
	secheader->sh_name = name;
	secheader->sh_type = SHT_SYMTAB;
	secheader->sh_flags = 0;
	secheader->sh_addr = 0;
	secheader->sh_offset = offset;
	secheader->sh_size = size;
	secheader->sh_link = 5;
	secheader->sh_info = 0; 
	secheader->sh_addralign = 0;
	secheader->sh_entsize = 16;

	(*shdr) = secheader;
}

/**
Cria um novo Header para uma secao .stab.

@param shdr Ponteiro para o novo local alocado na memoria.
@param name Indice na .shstrtab do nome dessa secao.
@param offset Distancia do inicio do arquivo ate o inicio dessa secao.
@param size A quantidade de bytes contida nessa secao.
*/
void newStabSectionHeader(Elf32_Shdr** shdr,Elf32_Word name, Elf32_Off offset,Elf32_Word size){

	(*shdr) = (Elf32_Shdr*)malloc(sizeof(Elf32_Shdr));
	
	(*shdr)->sh_name = name;
	(*shdr)->sh_type = SHT_PROGBITS;
	(*shdr)->sh_flags = 0;
	(*shdr)->sh_addr = 0;
	(*shdr)->sh_offset = offset;
	(*shdr)->sh_size = size;
	(*shdr)->sh_link = 5;
	(*shdr)->sh_info = 0; 
	(*shdr)->sh_addralign = 0;
	(*shdr)->sh_entsize = STAB_SIZE;

}

/**
Imprime um dos cabecalhos da Section Header Table

@param shdr O cabecalho que se deseja imprimir.
@param fp O arquivo no qual se deseja imprimir.
*/
int printSectionHeader(Elf32_Shdr* shdr, FILE *fp){

	/*TODO Adicionar verificacao de erro*/
	fwrite(shdr, sizeof(Elf32_Shdr), 1, fp);

	return 1;
}

/*
RELATIVE STUFF
*/



/**
Aloca na memora uma nova estrutura de armazenamento de dados relativos com adendo.

@param rela O ponteiro para a estrutura que sera alocada.
@param offset A distancia, na secao .text, ate os bytes a serem relocados.
@param addend O valor da posicao com base zero.
*/
void newRela(Elf32_Rela** rela, Elf32_Addr offset, Elf32_Sword addend){

	(*rela) = (Elf32_Rela*)malloc(sizeof(Elf32_Rela));

	(*rela)->r_offset = offset;

	
	(*rela)->r_info = ELF32_R_INFO((SHN_UNDEF),(R_386_32));

	(*rela)->r_addend = addend;
	
	(*rela)->next = NULL;
}

/**
Adiciona na lista mais uma estrutura Elf32_Rela.

@param root A raiz dessa lista
@param offset A distancia, na secao .text, ate os bytes a serem relocados.
@param addend O valor da posicao com base zero.
*/
void addNewRela(Elf32_Rela** root, Elf32_Addr offset, Elf32_Sword addend){
	Elf32_Rela* newr;
	newRela(&newr, offset, addend);

	if((*root)->next == NULL){
		(*root)->next = newr;
		return;
	}
	else{
		Elf32_Rela* t;

		for(t = (*root)->next; t->next != NULL; t = t->next);

		t->next = newr;
		
		return;
	}
}

/**
Imprime no arquivo a lista de estruturas Elf32_Rela.

@param root A raiz dessa lista que sera impressa.
@param fp O arquivo no qual se quer imprimir.
*/
void printRelaList(Elf32_Rela** root, FILE* fp){

	Elf32_Rela* t;
	if((*root)->next == NULL){
		return;
	}

	for(t = (*root)->next; t!= NULL; t = t->next){
		fwrite(t, ELF32_RELA_SIZE, 1, fp);
	}

}

/*
SIMBOL TABLE
*/

/**
Modifica os valores de um simbolo ja alocado.

@param sym O ponteiro que tera seus valores modificados
@param name O indice na StrTab que representa esse simbolo
@param value O valor armazenado nesse simbolo
@param islocal 1 se for local, 0 se for global
@param shndx 0 se for dado da tabela de uso, 2 se for referente a .data e 3 se for referente a .text 
*/
void changeSym(Elf32_Sym** sym, Elf32_Word name, Elf32_Addr value, int islocal, int shndx){

	/*Indice na string table que representa o nome do simbolo*/
	(*sym)->st_name = name;
	
	/*Valor associado ao simbolo*/	
	(*sym)->st_value = value;
	
	/*Tamanho alocado para o simbolo. 0 para tamanho desconhecido ou se nao tiver tamanho.*/
	(*sym)->st_size = 0;

	/*Especifica atributos maneiros e o tipo do simbolo. Ver [ST001]*/
	int b = 0;
	int t = 0;	

	if(islocal) b = STB_LOCAL;
	else b = STB_GLOBAL;

	if(shndx == 3) t = STT_FUNC;
	else if(shndx == 2)t = STT_OBJECT;

	(*sym)->st_info = ELF32_ST_INFO(b,t);

	/*Guarda 0*/
	(*sym)->st_other = 0;
	
	/*Indice na Section Header table ao qual esse simbolo se refere.*/
	(*sym)->st_shndx = shndx;
}

/**
Adiciona uma String na StrTab se ela nao existir. Se ja existir, 
retorna seu indice.
@param root A raiz dessa list de Elf32_Str.
@param str A string que se quer adicionar.
@return O indice dessa String na .strtab
*/
int addStrToStrTab(Elf32_Str** root, char* str){
	if((*root)== NULL){
		return 0;
	}

	int findret = findStrInStrTab(root,str);
	if(findret != 0){
		return findret;
	}

	Elf32_Str* s;
	for(s = (*root); s->next != NULL; s = s->next);
	newElf32_Str(&(s->next));
	s->next->str = str; 
	s->next->index = (s->index + (getStringSize(s->str)));

	return s->next->index;
}

/**
Retorna o tamanho dessa strTab

@param root A raiz dessa list de Elf32_Str.
@return O tamanho dessa .strtab
*/
int getStrTabSize(Elf32_Str** root){
	if((*root)== NULL){
		return 0;
	}
	if((*root)->next == NULL){
		return 0;
	}

	Elf32_Str* s;
	for(s = (*root)->next; s->next != NULL; s = s->next);

	return (s->index + getStringSize(s->str));
}

/**
Procura uma String na StrTab e retorna seu indice.
@param root A raiz dessa list de Elf32_Str.
@param str A string que se quer buscar
@return O indice dessa String na .strtab.
	0 se nao achar.
*/
int findStrInStrTab(Elf32_Str** root, char* str){
	if((*root)== NULL || str == NULL){
		return 0;
	}
	if((*root)->next == NULL){
		return 0;
	}

	Elf32_Str* s;
	for(s = (*root)->next; s != NULL; s = s->next){
		if(!strcmp(s->str, str)){
			return s->index;
		}
	}

	return 0;
}

/**
Cria uma nova Elf32_Str

@param s O ponteiro para essa nova estrutura criada.
*/
void newElf32_Str(Elf32_Str** s){
	(*s) = (Elf32_Str*)malloc(sizeof(Elf32_Str));
	(*s)->str = NULL;
	(*s)->index = 0;
	(*s)->next = NULL;
}


/**
Aloca e inicializa uma nova Stab

@param s O ponteiro para essa nova estrutura criada.
@param name O índice na .stabstr desse simbolo
@param type O tipo da Stab
@param desc Número de Stabs remenascentes
@param value O valor representado por esse simbolo
*/
void newStab(Stab** s, unsigned long name, unsigned char type, unsigned short desc, unsigned long value){
	(*s) = (Stab*)malloc(sizeof(Stab));
	(*s)->n_strx = name;
	(*s)->n_type = type;
	(*s)->n_other = 0;
	(*s)->n_desc = desc;
	(*s)->n_value = value;
	(*s)->next = NULL;
}

/**
Adiciona uma nova Stab à lista.

@param root O ponteiro para a raiz da lista.
@param name O índice na .stabstr desse simbolo.
@param type O tipo da Stab.
@param desc Número de Stabs remenascentes.
@param value O valor representado por esse simbolo.
*/
void addStab(Stab** root, unsigned long name, unsigned char type, unsigned short desc, unsigned long value){

	if((*root)== NULL){
		return;
	}

	Stab* s;
	for(s = (*root); s->next != NULL; s = s->next);
	newStab(&(s->next), name, type, desc, value);


	return;
}



