#include<stdio.h>
#include"desmontador.h"
/*
**	___________________desmontar.c___________________
**		
**	Chama todas as funções necessárias para desmontar o arquivo pelo Program Header.
**	
**	___________________desmontar.c___________________
**/

void desmontar(char *linguagemmaquina, char *linguagemassembly) {
	FILE *tabela, *lin_maquina, *codigo_assembly;
	tabelaS *p_tabela=NULL;
	labelS *p_label=NULL;
	undadosS *p_dadosbss=NULL;
	codeS *p_newcode=NULL;
	dataS *p_newdata=NULL;

/*============================================================
====================Abre arquivos=============================
============================================================*/

	if(!(tabela=fopen("tabela.txt", "r"))) 
		printf("**Erro: O arquivo tabela.txt não se encontra no diretório.\n");
	else
		printf("...O arquivo tabela.txt foi encontrado com sucesso.\n");

	if(!(lin_maquina=fopen(linguagemmaquina, "rb")))
		printf("**Erro: O arquivo %s não se encontra no diretório.\n", linguagemmaquina);
	else{
		printf("...O arquivo %s foi encontrado com sucesso.\n", linguagemmaquina);
		codigo_assembly=fopen(linguagemassembly, "w+");
	}

/*============================================================
====================Não existe erros==========================
============================================================*/

	/*Se estiver tudo ok com os arquivos, começa a desmontar:*/
	if(tabela && lin_maquina && codigo_assembly){ 


		/*============================================================
		====================Gera a tabela de instruções===============
		============================================================*/
		geratabela(&p_tabela, tabela);

		/*============================================================
		====================Gera o código=============================
		=============================================================*/
		p_label=geracodigo(lin_maquina, &p_dadosbss, &p_newcode, p_tabela, &p_newdata);

		/*============================================================
		====================Imprime o código==========================
		=============================================================*/
		imprimecodigo(codigo_assembly, p_label, p_tabela, linguagemassembly, p_dadosbss, p_newcode, p_newdata);

		/*============================================================
		====================Fecha arquivos============================
		=============================================================*/
		fechaarquivos(&tabela, &lin_maquina, &codigo_assembly);

		printf("...Bye!\n\n");
	}

}

