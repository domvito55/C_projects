#include<stdio.h>
#include"estruturas.h"

extern int leSH(FILE *codigo, Elf32_Shdr *SHeader, int posicao);
extern int tiparSH (FILE *codigo, Elf32_Shdr *SHeader, int posicaostr);

/*================preenceSH()============================
função para preencher uma Section Header Table
chamada por:
	-leii (le.c)
@parametros:
	- codigo: código obejto fonte
	- SHeader: ponteiro para inicio da lista (Table)
	- posicaostr: posição da string table
	- SHnum: numero de section headers no codigo objeto fonte
	- shoff: offset da Section Header Table
	- tipo: matriz que indica o tipo da Section Header
=======================================================*/
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

/*================preencePHsaida()========================
função para preencher uma Program Header Table
chamada por:
	-impimesaida (imprime.c)
@parametros:
	- PHeader: Program Header que deve ser preenchido
	- type: tipo de section
	- offset: offset do segment
	- vaddr: endereço virtual do segment
	- paddr: enderço físico, se for relevante
	- filesz: numero de bytes do segment na imagem de arquivo
	- memsz: numero de bytes do segment na imagem de memória
	- flags: define as flags relevantes do segment
	- align: sei lá
=======================================================*/
int preenchePHsaida(Elf32_Phdr* PHeader, Elf32_Word type,Elf32_Off offset, Elf32_Addr vaddr, Elf32_Addr paddr, Elf32_Word filesz, Elf32_Word memsz, Elf32_Word flags, Elf32_Word align){
	PHeader->p_type = type;
	PHeader->p_offset = offset;
	PHeader->p_vaddr = vaddr;
	PHeader->p_paddr = paddr;
	PHeader->p_filesz= filesz;
	PHeader->p_mesz = memsz;
	PHeader->p_flags = flags;
	PHeader->p_allign = align;

return 0;
}

