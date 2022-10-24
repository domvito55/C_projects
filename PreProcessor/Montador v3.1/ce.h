/**
Definicoes, estruturas e outros relacionados a estrutura ELF

@version 1.1
@author Murilo M. Marinho
*/

#ifndef CH_HEADER_GUARD
#define CH_HEADER_GUARD
/**

OBS: BSS por enquanto ficara incluido dentro da regiao .data como varios
dados zerados. Isso facilita a organizacao do arquivo, ja que poderiam ocorrer
intercalacoes entre varios db e ds.

Estrutura do arquivo:
Elf Header = sizeof(Elf32_Ehdr)
Section Header Table = 8*sizeof(Elf32_Shdr);
	Indice zero
	.shstrtab
	X.bssX
	.data
	.text
	.rela.text
	.srttab
	.symtab

.shstrtab:
\0.shstrtab\0.srttab\0X.bssX\0.data\0.text\0.symtab\0.rel.text\0 = 54 bytes
X.bss:
nada, tamanho descrito na sua sh_size.X
.data
(tamanho da regiao de dados, avaliado durante a montagem.)
.text
(tamanho da regiao de codigo de maquina, avaliado durante a montagem.)
.rela.text
(cria uma lista de estruturas Rela durante a fase de montagem,
uma para cada indice relativo, e depois imprime.)
[Adicionado na versao 0.5 adiante]
.srttab
as string que definem os simbolos da tabela de simbolos
.symtab
transcricao da tabela de simbolos ja criada anteriormente, sem nenhuma modificacao.

*/

#define Elf32_Addr  unsigned int       /*Unsigned program address*/
#define Elf32_Half  unsigned short int /*Unsigned medium integer*/
#define Elf32_Off   unsigned int       /*Unsigned file offset*/
#define Elf32_Sword int                /*Signed large integer*/
#define Elf32_Word  unsigned int       /*Unsigned large integer*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +++++++++++++++++++++++Elf Header++++++++++++++++++++++++++++
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*------------------------------
  --------e_ident---------------
  ------------------------------
  Bytes iniciais bem legais.*/

/*Indices importantes:*/
#define EI_MAG0    0
#define EI_MAG1    1
#define EI_MAG2    2
#define EI_MAG3    3
#define EI_CLASS   4  /*Classe de arquivo*/
#define EI_DATA    5  /*Codificacao do arquivo*/
#define EI_VERSION 6  /*Versao*/
#define EI_PAD     7  /*Inicio dos "padding bytes"*/
#define EI_NIDENT  16 /*Tamanho de e_ident[]*/

/*Indices os quais podem ter os seguintes valores:
  EI_MAG0 ate EI_MAG3
  Numero magico super 10*/
#define ELFMAG0 0x7f /*@ e_ident[EI_MAG0]*/
#define ELFMAG1 'E'  /*@ e_ident[EI_MAG1]*/
#define ELFMAG2 'L'  /*@ e_ident[EI_MAG2]*/
#define ELFMAG3 'F'  /*@ e_ident[EI_MAG3]*/

/*EI_CLASS*/
#define ELFCLASSNONE 0 /*Classe invalida*/
#define ELFCLASS32   1 /*32-bit*/
#define ELFCLASS64   2 /*64-bit*/

/*EI_DATA*/
#define ELFDATANONE 0 /*Codificacao invalida*/
#define ELFDATA2LSB 1 /*LSB complemento a 2*/
#define ELFDATA2MSB 2 /*MSB complemento a 2*/

/*EI_VERSION
 Usar EV_CURRENT*/

/*EI_PAD
  Marca o valor inicial dos bytes que nao sao utilizados em e_ident. Sao
  reservados e definidos como zero.*/

/*------------------------------
  --------e_type Types----------
  ------------------------------
  Define o tipo do arquivo*/
#define ET_NONE   0 /*No file type*/
#define ET_REL    1 /*Relocatable File*/
#define ET_EXEC   2 /*Executable File*/
#define ET_DYN    3 /*Shared Object File*/
#define ET_CORE   4 /*Core File*/
#define ET_LOPROC 0xff00 /*Processor-specific*/
#define ET_HIPROC 0xffff /*Processor-specific*/

/*------------------------------
  --------e_machine-------------
  ------------------------------
  Define a arquitetura alvo*/
#define EM_NONE  0 /*No machine*/
#define EM_M32   1 /*AT&T WE 32100*/
#define EM_SPARC 2 /*SPARC*/
#define EM_386   3 /*Intel 80386*/
#define EM_68K   4 /*Motorola 68000*/
#define EM_88K   5 /*Motorola 88000*/
#define EM_860   7 /*Intel 80860*/
#define EM_MIPS  8 /*MIPS RS3000*/
#define EM_8085  300 /*Minha definicao para 8085*/

/*------------------------------
  --------e_version-------------
  ------------------------------
  O valor 1 significa o arquivo original, 
versoes acima de 1 sao associadas a extensoes.*/
#define EV_NONE    0 /*Invalid Version*/
#define EV_CURRENT 1 /*Current Version*/

/*------------------------------
  --------e_entry---------------
  ------------------------------
  Endereco virtual para o qual o sistema transfere o controle inicialmente. Caso
  nao tenha um ponto de entrada, preencher com zero.*/

/*------------------------------
  --------e_phoff---------------
  ------------------------------
  Armazena o offset da Program Header Table. Se nao possuir, guarda zero.*/

/*------------------------------
  --------e_shoff---------------
  ------------------------------
  Armazena o offset da Section Header Table. Se nao possuir, guarda zero.*/

/*------------------------------
  --------e_flags---------------
  ------------------------------
  Armazena flags especificas do arquivo relacionadas ao processador*/

/*------------------------------
  --------e_ehsize---------------
  ------------------------------
  Tamanho desse cabecalho (Elf HEADER) em bytes*/

/*------------------------------
  --------e_phentsize-----------
  ------------------------------
  Armazena o tamanho de uma entrada da program header table. Todas as
  entradas tem o mesmo tamanho.*/

/*------------------------------
  --------e_phnum---------------
  ------------------------------
  Numero de entradas na program header table. O produto de e_phentsize
  por e_phnum da o tamanho da table. Caso nao tenha header, manda zero nele.*/

/*------------------------------
  --------e_shentsize-----------
  ------------------------------
  Mesma coisa que a program, so que pra section.*/

/*------------------------------
  --------e_shnum---------------
  ------------------------------
  Iden e_phnum*/

/*------------------------------
  --------e_shstrndx------------
  ------------------------------
  Armazena o indice da entrada na section header table relativa 
  a tabela de Strings de nomes de secoes*/

/**
Estrutura de um Cabecalho ELF
*/  
typedef struct {
	unsigned char e_ident[EI_NIDENT]; /*SIZE = 16*/
	Elf32_Half e_type ;				  /*SIZE = 2*/
	Elf32_Half e_machine ;            /*SIZE = 2*/
	Elf32_Word e_version ;            /*SIZE = 4*/
	Elf32_Addr e_entry ;              /*SIZE = 4*/
	Elf32_Off e_phoff ;               /*SIZE = 4*/
	Elf32_Off e_shoff ;               /*SIZE = 4*/
	Elf32_Word e_flags ;              /*SIZE = 4*/
	Elf32_Half e_ehsize ;             /*SIZE = 2*/
	Elf32_Half e_phentsize ;          /*SIZE = 2*/
	Elf32_Half e_phnum ;              /*SIZE = 2*/
	Elf32_Half e_shentsize ;          /*SIZE = 2*/
	Elf32_Half e_shnum ;              /*SIZE = 2*/
	Elf32_Half e_shstrndx ;           /*SIZE = 2*/
} Elf32_Ehdr;
/*SIZE = 52*/

/**
Cria um novo Cabecalho ELF para 8085.

@param elfHeader O Novo Elf Header que sera alocado.
@param startAddress Endereco do ponto de entrada do programa, .start.
*/
void newFileElfHeader(Elf32_Ehdr** elfHeader, Elf32_Addr startAddress, Elf32_Half shnum);

/**
Imprime o Cabecalho ELF para 8085.

@param elfHeader O cabecalho que se deseja imprimir.
@param fp O arquivo no qual se quer imprimir.
*/
int printFileElfHeader(Elf32_Ehdr* elfHeader, FILE* fp);

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +++++++++++++++++Section Header Table++++++++++++++++++++++++
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Permite a localizacao de todas as secoes presentes no arquivo
  Constituido de uma array de estruturas Elf32_Shdr*/
typedef struct{

	/*indice na String Table que representa o nome dessa secao.*/
	Elf32_Word sh_name;
	
	/*Define o conteúdo e semantica da secao. Tipos possiveis em [SH002]*/
	Elf32_Word sh_type;
	
	/*Flags de 1 bit que definem varios atributos. Veja mais em [SH003]*/
	Elf32_Word sh_flags;
	
	/*Contem 0, ou o endereco inicial da secao na memoria.*/
	Elf32_Addr sh_addr;
	
	/*A diferenca entre o inicio do arquivo ate o primeiro byte da secao.*/
	Elf32_Off sh_offset;
	
	/*O tamanho da secao, em bytes*/
	Elf32_Word sh_size;
	
	/*Link com a section header table. Valores especificos definidos em [SH004]*/

	Elf32_Word sh_link;
	
	/*Informacoes extras dependentes da secao. Valores especificos
	definidos em [SH004]*/
	Elf32_Word sh_info; 
	
	/*Valores 0 e 1 indicam que a secao nao tem nenhum alinhamento. Potencias
	integrais de dois definem outros possiveis alinhamentos.*/
	Elf32_Word sh_addralign;
	
	/*Tamanho das entradas fixas de uma tabela guardada por essa secao.
	(e.g. SimbolTable). 0 se nao conter esse tipo de tabela.*/
	Elf32_Word sh_entsize;
}Elf32_Shdr; /*SIZE = 40*/

/**
Cria um Section Header vazio, para o indice zero da Section Header Table

@param shdr Ponteiro para o novo local alocado na memoria.
*/
void newEmptySectionHeader(Elf32_Shdr** shdr);

/**
Cria um novo Header para uma secao .shstrtab.

@param shdr Ponteiro para o novo local alocado na memoria.
@param name Indice na .shstrtab do nome dessa secao.
@param offset Distancia do inicio do arquivo ate o inicio dessa secao.
@param size A quantidade de bytes contida nessa secao.
*/
void newShstrtabSectionHeader(Elf32_Shdr** shdr,Elf32_Word name,Elf32_Off offset,Elf32_Word size);

/**
Cria um novo Header para uma secao .data.

@param shdr Ponteiro para o novo local alocado na memoria.
@param name Indice na .shstrtab do nome dessa secao.
@param addr Endereco do primeiro byte no mapeamento de memoria. Usando zero como base.
@param offset Distancia do inicio do arquivo ate o inicio dessa secao.
@param size A quantidade de bytes contida nessa secao.
*/
void newDataSectionHeader(Elf32_Shdr** shdr,Elf32_Word name,Elf32_Addr addr, Elf32_Off offset,Elf32_Word size);

/**
Cria um novo Header para uma secao .text.

@param shdr Ponteiro para o novo local alocado na memoria.
@param name Indice na .shstrtab do nome dessa secao.
@param addr Endereco do primeiro byte no mapeamento de memoria. Usando zero como base.
@param offset Distancia do inicio do arquivo ate o inicio dessa secao.
@param size A quantidade de bytes contida nessa secao.
*/
void newTextSectionHeader(Elf32_Shdr** shdr,Elf32_Word name,Elf32_Addr addr, Elf32_Off offset,Elf32_Word size);
/**
Cria um novo Header para uma secao .rela.text.

@param shdr Ponteiro para o novo local alocado na memoria.
@param name Indice na .shstrtab do nome dessa secao.
@param offset Distancia do inicio do arquivo ate o inicio dessa secao.
@param size A quantidade de bytes contida nessa secao.
*/
void newRelaTextSectionHeader(Elf32_Shdr** shdr,Elf32_Word name, Elf32_Off offset,Elf32_Word size);
/**
Cria um novo Header para uma secao .sym.

@param shdr Ponteiro para o novo local alocado na memoria.
@param name Indice na .shstrtab do nome dessa secao.
@param offset Distancia do inicio do arquivo ate o inicio dessa secao.
@param size A quantidade de bytes contida nessa secao.
*/
void newSymSectionHeader(Elf32_Shdr** shdr,Elf32_Word name, Elf32_Off offset,Elf32_Word size);

void newStabSectionHeader(Elf32_Shdr** shdr,Elf32_Word name, Elf32_Off offset,Elf32_Word size);

/**
Imprime um dos cabecalhos da Section Header Table

@param shdr O cabecalho que se deseja imprimir.
@param fp O arquivo no qual se deseja imprimir.
*/
int printSectionHeader(Elf32_Shdr* shdr, FILE *fp);
/**
Imprime todos os cabecalhos da Section Header Table

@param shdrt A array de Section Headers
@param fp O arquivo no qual se deseja imprimir
*/
int printSectionHeaderTable(Elf32_Shdr shdrt[], FILE *fp);

/*------------------------------
  [SH001]Indices Reservados-----
  ------------------------------*/
#define SHN_UNDEF     0
	/*O indice zero sempre existe na Section Header Table.
	A estrutura e:
		sh_name 	 0 			No name
		sh_type 	 SHT_NULL	Inactive
		sh_flags 	 0 			No flags
		sh_addr 	 0 			No address
		sh_offset 	 0	 		No file offset
		sh_size 	 0 			No size
		sh_link 	 SHN_UNDEF 	No link information
		sh_info 	 0 			No auxiliary information
		sh_addralign 0 			No alignment
		sh_entsize   0 			No entries
	*/
#define SHN_LORESERVE 0xff00
#define SHN_LOPROC    0xff00
#define SHN_HIPROC    0xff1f
#define SHN_ABS       0xfff1
#define SHN_COMMON    0xfff2
#define SHN_HIRESERVE 0xffff

/*------------------------------
  [SH002]Section Types----------
  ------------------------------*/
#define SHT_NULL 	 0           /*Secao inativa*/
#define SHT_PROGBITS 1           /*Informacoes definidas pelo programa.*/
#define SHT_SYMTAB   2           /*Tabela de simbolos. Apenas 1*/
#define SHT_STRTAB   3           /*String Table*/
#define SHT_RELA     4			 /*Secoes de relocacao.*/
#define SHT_HASH     5           /*Symbol Hash Table*/
#define SHT_DYNAMIC  6           /*Informacao para ligacao dinamica.*/
#define SHT_NOTE     7           /*Informacao que marca o arquivo de alguma forma.*/
#define SHT_NOBITS   8           /*Quem endender levante a mao*/
#define SHT_REL      9           /*Entradas de relocacao sem adendos explicitos (?)*/
#define SHT_SHLIB    10          /*Reservada mas nao tem semantica especifica.*/
#define SHT_DYNSYM   11          /*Simbolos dinamicos da tabela de simbolos. Apenas 1*/
#define SHT_LOPROC   0x70000000
#define SHT_HIPROC   0x7fffffff
#define SHT_LOUSER   0x80000000
#define SHT_HIUSER   0xffffffff

/*------------------------------
  [SH003]Flag Types-------------
  ------------------------------*/
#define SHF_WRITE     0x1         /*Secao contem dados que podem ser escritos durante a execucao*/
#define SHF_ALLOC     0x2         /*Essa secao ocupa memoria durante a execucao.*/
#define SHF_EXECINSTR 0x4         /*Essa secao possui intrucoes executaveis de maquina*/
#define SHF_STRINGS   0x20
#define SHF_MASKPROC  0xf0000000  /*Coisas de processador*/

/*------------------------------
  [SH004]Flag Types-------------
  ------------------------------*/
/*
sh_type                     sh_link                              sh_info
SHT_DYNAMIC        O indice da section header                        0
                   da tabela de Strings que 
				   armazena os entradas dessa secao.
				   
SHT_HASH           O indice da section header                        0
                   da tabela de simbolos para a qual
                   essa hash table se aplica.				   
 
SHT_REL            O indice da section header            O indice da section header
SHT_RELA           da symbol table associada.            da secao a qual essa relocacao
                                                         se aplica.
														 
SHT_SYMTAB         O indice da section header            Um a mais que o indice do ultimo 
SHT_DYNSYM         da string table associada.            simbolo local. (STB_LOCAL)

outros             SHN_UNDEF                                           0
*/


/*------------------------------
  [SH005]Secoes Especiais Relevantes
  ------------------------------*/
/*
.bss   : SHT_NOBITS     SHF_ALLOC + SHF_WRITE
.data  : SHT_PROGBITS   none

.srttab: SHT_STRTAB     idem .symtab
	Armazena sequências de Strings terminadas com \0. Inicia sempre com
	\0, e termina sempre com \0. O indice se refere a um byte nao nulo
	da string.
	
.symtab: SHT_SYMTAB     (Se o arquivo carregar essa secao na memoria, por algum motivo estranho, tera SHF_ALLOC)
	Veja [SIMBOLTABLE]
	
.shstrtab: SHT_STRTAB   none
	Essa secao armazena os nomes das secoes.

.text  : SHT_PROGBITS   SHF_ALLOC + SHF_EXECINSTR

.rel.text: SHT_REL
*/

/*------------------------------
  ---------[SIMBOLTABLE]--------
  ------------------------------*/
/*Formato de uma entrada da simboltable.*/

/*------------------------------
  ---------Indice Reservado-----
  ------------------------------*/
/*O indice zero e reservado e sempre aparece
na simboltable (se ela existir).
 Name         Value          Note 
st_name 		0 	      No name
st_value    	0 	      Zero value
st_size     	0 	      No size
st_info     	0 	      No type, local binding
st_other    	0
st_shndx    	SHN_UNDEF No section
*/  
  
typedef struct Elf32_Sym{
	/*Indice na string table que representa o nome do simbolo*/
	Elf32_Word st_name;
	
	/*Valor associado ao simbolo*/	
	Elf32_Addr st_value;
	
	/*Tamanho alocado para o simbolo. 0 para tamanho desconhecido ou se nao tiver tamanho.*/
	Elf32_Word st_size;


	/*Especifica atributos maneiros e o tipo do simbolo. Ver [ST001]*/
	unsigned char st_info;
	
	/*Guarda 0*/
	unsigned char st_other;
	
	/*Indice na Section Header table ao qual esse simbolo se refere.*/
	Elf32_Half st_shndx;

}Elf32_Sym;  
#define ELF32_SYM_SIZE 16

/*------------------------------
  [ST001]Macros para st_info
  ------------------------------*/
#define ELF32_ST_BIND(i)	((i)>>4) /*Veja [ST002]*/
#define ELF32_ST_TYPE(i)	((i)&0xf) /*Veja [ST003]*/
#define ELF32_ST_INFO(b,t) (((b)<<4)+((t)&0xf))
/*Uso(?): ELF32_ST_INFO(STB_LOCAL,STT_OBJECT)*/

/*------------------------------
  [ST002]Simbol Table Binding
  ------------------------------*/
#define STB_LOCAL  0  /*Simbolos locais*/
#define STB_GLOBAL 1  /*Simbolos exportados*/
#define STB_WEAK   2  /*Quem sabe?*/
#define STB_LOPROC 13 /*O mesmo de sempre*/
#define STB_HIPROC 15 /*Don't worry*/

/*------------------------------
  [ST003]Simbol Table Types
  ------------------------------*/
#define STT_NOTYPE  0 /*Tipo nao especificado*/
#define STT_OBJECT  1 /*Simbolo associado com dados -> Para simbolos relativos a .data*/
#define STT_FUNC    2 /*Simbolo associado com funcao ou outro codigo executavel -> Para simbolos de jump*/
#define STT_SECTION 3 /*Simbolo associado com uma secao.*/
#define STT_FILE    4 /*Nao entendi nada*/
#define STT_LOPROC  13
#define STT_HIPROC  15
/*OBS: Usar SHN_ABS para simbolos absolutos.*/

/*------------------------------
  ---------[RELOCAcaO]----------
  ------------------------------*/
#define ELF32_RELA_SIZE 12

  typedef struct Elf32_Rela{
    /*Offset entre o inicio da secao ate a unidade a ser afetada pela relocacao.*/
	Elf32_Addr r_offset;
	/*SHN_UNDEF*/
	Elf32_Word r_info;
	/*Valor que o campo possui, para ser adicionado na relocacao.*/
	Elf32_Sword r_addend;
	/*Aponta para o proximo*/
	struct Elf32_Rela* next;
} Elf32_Rela;

/*------------------------------
  [R001]Macros para r_info
  ------------------------------*/
#define ELF32_R_SYM(i)	((i)>>8) /*Simbol Table Index, ou SHN_UNDEF*/
#define ELF32_R_TYPE(i)	((unsigned char)(i)) /*Veja [R002]*/
#define ELF32_R_INFO(s,t) (((s)<<8)+((unsigned char)(t)))

/*------------------------------
  [R002]Relocation Types
  ------------------------------*/
#define R_386_NONE      0
#define R_386_32        1
#define R_386_PC32      2
#define R_386_GOT32     3
#define R_386_PLT32     4
#define R_386_COPY      5 
#define R_386_GLOB_DAT  6
#define R_386_JMP_SLOT  7
#define R_386_RELATIVE  8
#define R_386_GOTOFF    9
#define R_386_GOTPC     10


/*
Aloca na memora uma nova estrutura de armazenamento de dados relativos com adendo.

@param rela O ponteiro para a estrutura que sera alocada.
@param offset A distancia, na secao .text, ate os bytes a serem relocados.
@param addend O valor da posicao com base zero.
*/
void newRela(Elf32_Rela** rela, Elf32_Addr offset, Elf32_Sword addend);

/**
Adiciona na lista mais uma estrutura Elf32_Rela.

@param root A raiz dessa lista
@param offset A distancia, na secao .text, ate os bytes a serem relocados.
@param addend O valor da posicao com base zero.
*/
void addNewRela(Elf32_Rela** root, Elf32_Addr offset, Elf32_Sword addend);

/**
Imprime no arquivo a lista de estruturas Elf32_Rela.

@param root A raiz dessa lista que sera impressa.
@param fp O arquivo no qual se quer imprimir.
*/
void printRelaList(Elf32_Rela** root, FILE* fp);

void changeSym(Elf32_Sym** sym, Elf32_Word name, Elf32_Addr value, int islocal, int istextsimbol);

/*------------------------------
  ------------[STRTAB]----------
  ------------------------------*/
typedef struct Elf32_Str{
	/**
	String representada por essa estrutura
	*/
	char* str;
	/**
	O indice dessa string
	*/
	int index;
	/**
	Proxima Elf32_Str
	*/
	struct Elf32_Str* next;
} Elf32_Str;

/**
Adiciona uma String na StrTab

@param root A raiz dessa list de Elf32_Str.
@param str A string que se quer adicionar.
@return O indice dessa String na .strtab
*/
int addStrToStrTab(Elf32_Str** root, char* str);

/**
Retorna o tamanho dessa strTab

@param root A raiz dessa list de Elf32_Str.
@return O tamanho dessa .strtab
*/
int getStrTabSize(Elf32_Str** root);

/**
Procura uma String na StrTab e retorna seu indice.
@param root A raiz dessa list de Elf32_Str.
@param str A string que se quer buscar
@return O indice dessa String na .strtab.
	0 se nao achar.
*/
int findStrInStrTab(Elf32_Str** root, char* str);

/**
Cria uma nova Elf32_Str

@param s O ponteiro para essa nova estrutura criada.
*/
void newElf32_Str(Elf32_Str** s);




int ce(FILE*fp, int entry_address, int data_size, int data_address, int text_size, int text_address, int relatext_num, int simbol_num, int stabstr_size, int stab_num);





/**
STABS
*/

/*
Paths and Names of the Source Files

 Before any other stabs occur, there must be a stab specifying the source file.
 This information is contained in a symbol of stab type N_SO; the string field
 contains the name of the file. The value of the symbol is the start address
 of the portion of the text section corresponding to that file.

With the Sun Solaris2 compiler, the desc field contains a source-language code.

Some compilers (for example, GCC2 and SunOS4 `/bin/cc') also include the 
directory in which the source was compiled, in a second N_SO symbol preceding 
the one containing the file name. This symbol can be distinguished by the fact
 that it ends in a slash. Code from the cfront C++ compiler can have additional
 N_SO symbols for nonexistent source files after the N_SO for the real source 
 file; these are believed to contain no useful information.

For example:

.stabs "/cygint/s1/users/jcm/play/",100,0,0,Ltext0     # 100 is N_SO
.stabs "hello.c",100,0,0,Ltext0
        .text
Ltext0:
Instead of N_SO symbols, XCOFF uses a .file assembler directive which assembles
 to a standard COFF .file symbol; explaining this in detail is outside the 
 scope of this document.
 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
 
 The following example shows a stab for a function main which returns type 
 number 1. The _main specified for the value is a reference to an assembler 
 label which is used to fill in the start address of the function.

.stabs "main:F1",36,0,0,_main      # 36 is N_FUN

XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Each time the assembler encounters a stab directive, it puts each field of 
the stab into a corresponding field in a symbol table entry of its output 
file. If the stab contains a string field, the symbol table entry for that 
stab points to a string table entry containing the string data from the stab. Assembler labels become relocatable addresses. Symbol table entries in a.out have the format:
*/

typedef struct internal_nlist {
	unsigned long n_strx;         /* index into string table of name */
	unsigned char n_type;         /* type of symbol */
	unsigned char n_other;        /* misc info (usually empty) */
	unsigned short n_desc;        /* description field */
	unsigned long n_value;        /* value of symbol */
	struct internal_nlist* next;  /* pointer to the next stab*/
}Stab;

#define STAB_SIZE ((sizeof(Stab))-(sizeof(struct internal_nlist*))) 

/*
If the stab has a string, the n_strx field holds the offset in bytes of the
 string within the string table. The string is terminated by a NUL character. If the stab lacks a string (for example, it was produced by a .stabn or .stabd directive), the n_strx field is zero.

Symbol table entries with n_type field values greater than 0x1f originated 
as stabs generated by the compiler (with one random exception). The other 
entries were placed in the symbol table of the executable by the assembler 
or the linker.

The first stab in the .stab section for each compilation unit is synthetic,
generated entirely by the assembler, with no corresponding .stab directive
as input to the assembler. This stab contains the following fields:

n_strx
Offset in the .stabstr section to the source filename.
n_type
N_UNDF.
n_other
Unused field, always zero.
n_desc
Count of upcoming symbols, i.e., the number of remaining stabs for this 
source file.
n_value
Size of the string table fragment associated with this source file, in bytes.

The .stabstr section always starts with a null byte (so that string offsets 
of zero reference a null string), followed by random length strings, each 
of which is null byte terminated.

The ELF section header for the .stab section has its sh_link member set 
to the section number of the .stabstr section, and the .stabstr section 
has its ELF section header sh_type member set to SHT_STRTAB to mark it as
a string table. 
*/ 
#define N_GSYM 0x20  /*Global symbol; see section Global Variables.*/
#define N_FUN 0x24  /*Function name (see section Procedures) or text segment variable 
(see section Static Variables).*/
#define N_STSYM 0x26 /*Data segment file-scope variable; see section Static Variables.*/
#define N_MAIN 0x2a /*Name of main routine; see section Main Program.*/

void newStab(Stab** s, unsigned long name, unsigned char type, unsigned short desc, unsigned long value);
void addStab(Stab** root, unsigned long name, unsigned char type, unsigned short desc, unsigned long value);

#endif
