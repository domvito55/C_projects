#include<stdio.h>
#include"estruturas.h"
#include"constantes.h"

/*=================busca()===========================
faz busca na tabela de uso
chamada por:
	- reloca (rela.c)
@parametros:
	- sym: lista onde se encontram os symbolos de um arquivo objeto fonte
	- symnum: numero de entradas nessa lista
	- relaoff: valor que se deseja saber se é externo
retorna:
	- 0 se for simbolo externo
	- 1 se não for
===================================================*/
int busca(Elf32_Sym *sym, int symnum, int relaoff){
	
	/*=========variáveis locais============*/	
	int i;
	/*=====fim variáveis locais============*/	
	
	
		for(i=0; i<symnum; i++){
			if(relaoff == sym[i].st_value){
				if(((ELF32_ST_BIND(sym[i].st_info))==STB_GLOBAL && ((sym[i].st_shndx) == SHN_UNDEF))){
					return 1;
				}
			}
		
		}

return 0;
}
