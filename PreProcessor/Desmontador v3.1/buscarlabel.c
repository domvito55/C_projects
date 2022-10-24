#include<stdio.h>
#include"estruturas.c"
/*
**	___________________buscarlabel.c___________________
**		
**	Busca na estrutura das labels se o endereço já existe, se existir, retorna a label correspondente, senão, retorna NULL.
**
**	___________________buscarlabel.c___________________
**/

labelS *buscarlabel(labelS *pinicio, int endereco){
	labelS *p_aux;

	p_aux=pinicio;

/*============================================================
====================Fim da estrutura?=========================
============================================================*/
	while((p_aux != NULL)){
		/*============================================================
		====================É o endereço procurado====================
		============================================================*/
		if(p_aux->endereco != endereco)
			/*============================================================
			====================Vai para o próximo endereço===============
			============================================================*/
			p_aux=p_aux->next;
		else
			break;
	}
	return p_aux;
}
