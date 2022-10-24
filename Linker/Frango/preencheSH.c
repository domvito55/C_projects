#include<stdio.h>
#include"estruturas.h"

extern int leSH(FILE *codigo, Elf32_Shdr *SHeader, int posicao);
extern int tiparSH (FILE *codigo, Elf32_Shdr *SHeader, int posicaostr);

int preencheSH(FILE *codigo, Elf32_Shdr *SHeader, int posicaostr, int SHnum, int shoff, matriz tipo)
{
	/*========Variáveis Locais===========*/
	int i;				/*contadores*/
	int posicao;		/*armazena a posicao da sectio header atual*/
	/*====Fim Variáveis Locais===========*/

	for(i=0;i<SHnum;i++){
		posicao = shoff+i*(sizeof(Elf32_Shdr));
		/*evita a releitura do section header
		relativa a string table*/
		if (posicao == posicaostr)
			continue;
		leSH(codigo, &(SHeader[i]), posicao);
		tipo.e[i]=tiparSH(codigo, &(SHeader[i]), posicaostr);
	}

return 0;
}

int preenchePHsaida(Elf32_Phdr* PHeader, Elf32_Addr startAddress, Elf32_Half phnum){
	PHeader->p_type = type;
	PHeader->p_offset = offset;
	PHeader->p_vaddr = vaddr;
	PHeader->p_paddr = paddr;
	PHeader->p_filesz= filesz;
	PHeader->p_memsz = memsz;
	PHeader->p_flags = flags;
	PHeader->p_align = align;

return 0;
}

