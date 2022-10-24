#include<stdio.h>
#include"desmontador.h"
/*
**	___________________imprimenatela.c___________________
**		
**	Imprime o código na tela.
**	
**	___________________imprimenatela.c___________________
**/

void imprimenatela(labelS *p_label, tabelaS *p_tabela, char *linguagemassembly, undadosS *p_dadosbss, codeS *p_newcode, dataS *p_newdata) {

	labelS *pl=NULL;
	tabelaS *pt=NULL;
	int n=0, i=0, posicao_code=0, posicao_data=0;

/*============================================================
====================Imprime .begin, .text, .start=============
============================================================*/
	printf("\n===================================================\n");
	printf("\n.begin %s\n\n", linguagemassembly);
	printf(".text\n");
	printf(".start");

	/*Imprimir o .start caso exista dados ou instruções*/
	if( (p_newcode!=NULL) && (p_newdata!=NULL) ){
	} else{
		if(p_label!=NULL)
			printf(" %s", p_label->label);
	}
	printf("\n\n");

	if( (p_newcode!=NULL) ){
/*============================================================
====================Existe instrução?=========================
============================================================*/
	while(p_newcode->codigocompleto[i]!=0x100){

		/*============================================================
		====================Existe endereço para essa label===========
		============================================================*/
		if( (pl=buscarlabel(p_label, p_newcode->endereco + posicao_code))!=NULL ){
			/*============================================================
			====================Imprima a label===========================
			============================================================*/
			printf("%s:\t ", pl->label);
		} else{
			printf("\t");
		}

		/*Busca o tipo da instrução*/
		pt=buscartabela(p_tabela, (p_newcode->codigocompleto[i]) );		

		/*Imprime tipo 1*/
		if( (pt->tipo) == 1 ){
			printf("\t");
			n=0;
			/*============================================================
			====================Imprime instrução=========================
			============================================================*/
			while( (pt->nome[n]) != '\n'){
				printf("%c", pt->nome[n]);
				n++;
			}
			printf("\n");
		}

		/*Imprime tipo 2*/
		else if( (pt->tipo) == 2 ){ 					
			printf("\t");
			n=0;
			/*============================================================
			====================Imprime instrução e próximo byte==========
			============================================================*/
			while( (pt->nome[n]) != '\n'){
				printf("%c", pt->nome[n]);
				n++;
			}
			i++;
			posicao_code++;
			printf("%d", p_newcode->codigocompleto[i]);

			printf("\n");
		}

		/*Imprime tipo 3*/
		else if( (pt->tipo) == 3 ){						
			printf("\t");
			n=0;
			/*============================================================
			====================Imprime instrução=========================
			============================================================*/
			while( (pt->nome[n]) != '\n'){
				printf("%c", pt->nome[n]);
				n++;
			}
			/*Não imprimir um espaço, caso seja lxi.*/
			if( (p_newcode->codigocompleto[i] == 0x1) || (p_newcode->codigocompleto[i] == 0x11) || (p_newcode->codigocompleto[i] == 0x21) || (p_newcode->codigocompleto[i] == 0x31)){
			}else{
				printf(" ");
			}
			/*============================================================
			====================Existe label para esse endereço?==========
			============================================================*/
			i++;
			posicao_code++;
			pl=buscarlabel(p_label, (p_newcode->codigocompleto[i])+(p_newcode->codigocompleto[i+1])*256 );
			if(pl!=NULL){
				/*============================================================
				====================Imprime label=============================
				============================================================*/
				printf("%s", pl->label);
			}
			else{
				/*============================================================
				====================Imprime endereço==========================
				============================================================*/
				if((p_newcode->codigocompleto[i]+256*p_newcode->codigocompleto[i+1]) > 40960)
					printf("0");
				printf("%.4xH", (p_newcode->codigocompleto[i])+(p_newcode->codigocompleto[i+1]) );
			}
			i++;
			posicao_code++;
			printf("\n");
		}

		i++;
		posicao_code++;

	}
}
/*============================================================
====================Imprime .data=============================
============================================================*/
	printf("\n.data\n\n");

if( (p_newdata!=NULL) ){
	i=0;
	while(p_newdata->datacompleto[i]!=0x100){
		/*============================================================
		====================Existe endereço para essa label===========
		============================================================*/
		if( (pl=buscarlabel(p_label, p_newdata->endereco + posicao_data))!=NULL ){
			/*============================================================
			====================Imprima a label===========================
			============================================================*/
			printf("%s:\t ", pl->label);
		} else{
			printf("\t");
		}


		printf("\tdb %d\n", p_newdata->datacompleto[i]);

		posicao_data++;
		i++;
	}

/*============================================================
====================Imprime .bss=============================
============================================================*/
	if(p_dadosbss->quantidade!=0){
		/*============================================================
		====================Existe endereço para essa label===========
		============================================================*/
		if( (pl=buscarlabel(p_label, p_dadosbss->endereco))!=NULL ){
			/*============================================================
			====================Imprima a label===========================
			============================================================*/
			printf("%s:\t ", pl->label);
		} else{
			printf("\t");
		}

		printf("\tds %x\n", p_dadosbss->quantidade);
	}
}
/*============================================================
====================Imprime .end==============================
============================================================*/
	printf("\n.end\n\n");	/*Imprime .end*/
	printf("===================================================\n");
}
