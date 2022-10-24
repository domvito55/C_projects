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

/*------------------------------
  --------e_version-------------
  ------------------------------
  O valor 1 significa o arquivo original, 
versoes acima de 1 sao associadas a extensoes.*/
#define EV_NONE    0 /*Invalid Version*/
#define EV_CURRENT 1 /*Current Version*/

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


/*tipos de program header*/
#define PT_NULL 0
#define PT_LOAD 1
#define PT_DYNAMIC 2
#define PT_INTERP 3
#define PT_NOTE 4
#define PT_SHLIB 5
#define PT_PHDR 6
#define PT_LOPROC 0x70000000
#define PT_HIPROC 0x7fffffff

/*permissões*/
#define PF_X 0x1
#define PF_W 0x2
#define PF_R 0x3
#define PF_MASKPROC 0xf0000000

/*------------------------------
  ---------[RELOCAcaO]----------
  ------------------------------*/
#define ELF32_RELA_SIZE 12

#define ELF32_ST_BIND(i) ((i)>>4)
#define ELF32_ST_TYPE(i) ((i)&0xf)
#define ELF32_ST_INFO(b,t) (((b)<<4)+((t)&0xf))

/*------------------------------
  ----tipos de symbol----------
  ------------------------------*/
#define STB_LOCAL 0
#define STB_GLOBAL 1
#define STB_WEAK 2
#define STB_LOPROC 13
#define STB_HIPROC 15

/*##########REVER############*/
/*numero de entradas no program header*/		
#define PHNUM 3
/*######fim REVER############*/		

/*para usar com a leinf: tipo de section*/
#define SHSTRTAB 1
#define TEXT 2
#define DATA 3
#define RELATEXT 4
#define STRTAB 5
#define SYMTAB 6
#define STAB 7

/*para usar com a leinf: informação que se quer*/
#define SHNAME 0
#define SHTYPE 1
#define SHFLAGS 2
#define SHADDR 3
#define SHOFFSET 4
#define SHSIZE 5
#define SHLINK 6
#define SHINFO 7
#define SHADDRLIGN 8
#define SHENTSIZE 9

