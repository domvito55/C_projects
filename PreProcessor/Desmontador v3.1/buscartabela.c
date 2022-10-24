#include<stdio.h>
#include"estruturas.c"
/*
**	___________________buscarnatabela.c___________________
**		
**	Busca na estrutura da tabela a intrução correspondente a chave.
**	
**	___________________buscarnatabela.c___________________
**/

tabelaS *buscartabela(tabelaS *pinicio, int chave){
	tabelaS *p_aux;

	p_aux=pinicio;
/*============================================================
====================Fim da estrutura, é opcode?===============
============================================================*/
	while( (p_aux != NULL) && (p_aux->opcode != chave) ){
		/*============================================================
		====================Fim da estrutura, é opcode?===============
		============================================================*/
		p_aux=p_aux->next;
	}

	/*============================================================
	====================Retorna a instrução=======================
	============================================================*/
	return p_aux;
}
