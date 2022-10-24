#define Elf32_Addr  unsigned int
#define Elf32_Half  unsigned short int
#define Elf32_Off   unsigned int
#define Elf32_Sword int
#define Elf32_Word  unsigned int
#define EI_NIDENT  16

typedef struct matriz{		/*Estrutura das labels*/
	int *e;
} matriz;

/*Estrutura do Elf Header*/  
typedef struct EH{
	unsigned char e_ident[EI_NIDENT];
	Elf32_Half e_type;
	Elf32_Half e_machine;
	Elf32_Word e_version;
	Elf32_Addr e_entry;
	Elf32_Off e_phoff;
	Elf32_Off e_shoff;
	Elf32_Word e_flags;
	Elf32_Half e_ehsize;
	Elf32_Half e_phentsize;
	Elf32_Half e_phnum;
	Elf32_Half e_shentsize;
	Elf32_Half e_shnum;
	Elf32_Half e_shstrndx;
} Elf32_Ehdr;

/*Estrutura do Program Header*/  
typedef struct PH{
	Elf32_Word p_type;
	Elf32_Off p_offset;
	Elf32_Addr p_vaddr;
	Elf32_Addr p_paddr;
	Elf32_Word p_filesz;
	Elf32_Word p_mesz;
	Elf32_Word p_flags;
	Elf32_Word p_allign;
} Elf32_Phdr;

/*Estrutura do Section Header*/ 
typedef struct SH{
	Elf32_Word sh_name;
	Elf32_Word sh_type;
	Elf32_Word sh_flags;
	Elf32_Addr sh_addr;
	Elf32_Off sh_offset;
	Elf32_Word sh_size;
	Elf32_Word sh_link;
	Elf32_Word sh_info;
	Elf32_Word sh_addralign;
	Elf32_Word sh_entsize;
} Elf32_Shdr;

/*Estrutura do Symbol Table*/
typedef struct Symtab{
	Elf32_Word st_name;
	Elf32_Addr st_value;
	Elf32_Word st_size;
	unsigned char st_info;
	unsigned char st_other;
	Elf32_Half st_shndx;
} Elf32_Sym;

  typedef struct Elf32_Rela{
    /*Offset entre o inicio da secao ate a unidade a ser afetada pela relocacao.*/
	Elf32_Addr r_offset;
	/*SHN_UNDEF*/
	Elf32_Word r_info;
	/*Valor que o campo possui, para ser adicionado na relocacao.*/
	Elf32_Sword r_addend;
} Elf32_Rela;

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

typedef struct Nome{
	char str[20];
} Nome;

