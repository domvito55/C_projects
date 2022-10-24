#include<stdio.h>
#include"desmontador.h"
#include<string.h>
/*
**	___________________imprimecodigol.c___________________
**		
**	Imprime o código no arquivo alvo.
**	
**	___________________imprimecodigo.c___________________
**/
#define testex
#define blahx
void imprimecodigo(FILE *codigo_assembly, labelS *p_label, tabelaS *p_tabela, char *linguagemassembly, undadosS *p_dadosbss, codeS *p_newcode, dataS *p_newdata) {

	labelS *pl=NULL;
	tabelaS *pt=NULL;
	int n=0, i=0, posicao_code=0, posicao_data=0;
	char resposta=0;


/*============================================================
====================Imprime .begin, .text, .start=============
============================================================*/

	fprintf(codigo_assembly, ".begin %s\n\n", linguagemassembly);
	fprintf(codigo_assembly, ".text\n");
	fprintf(codigo_assembly, ".start");


	/*Imprimir o .start caso exista dados ou instruções*/
	if( (p_newcode!=NULL) && (p_newdata!=NULL) ){
	} else{
		if(p_label!=NULL)
			fprintf(codigo_assembly, " %s", p_label->label);
	}

	fprintf(codigo_assembly, "\n\n");

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
			fprintf(codigo_assembly, "%s:\t ", pl->label);
		} else{
			fprintf(codigo_assembly, "\t");
		}

		/*Busca o tipo da instrução*/
		pt=buscartabela(p_tabela, (p_newcode->codigocompleto[i]) );		

		/*Imprime tipo 1*/
		if( (pt->tipo) == 1 ){
			fprintf(codigo_assembly, "\t");
			n=0;
			/*============================================================
			====================Imprime instrução=========================
			============================================================*/
			while( (pt->nome[n]) != '\n'){
				fprintf(codigo_assembly, "%c", pt->nome[n]);
				n++;
			}
			fprintf(codigo_assembly, "\n");
		}

		/*Imprime tipo 2*/
		else if( (pt->tipo) == 2 ){ 					
			fprintf(codigo_assembly, "\t");
			n=0;
			/*============================================================
			====================Imprime instrução e próximo byte==========
			============================================================*/
			while( (pt->nome[n]) != '\n'){
				fprintf(codigo_assembly, "%c", pt->nome[n]);
				n++;
			}
			i++;
			posicao_code++;
			fprintf(codigo_assembly, "%d", p_newcode->codigocompleto[i]);

			fprintf(codigo_assembly, "\n");
		}

		/*Imprime tipo 3*/
		else if( (pt->tipo) == 3 ){						
			fprintf(codigo_assembly, "\t");
			n=0;
			/*============================================================
			====================Imprime instrução=========================
			============================================================*/
			while( (pt->nome[n]) != '\n'){
				fprintf(codigo_assembly, "%c", pt->nome[n]);
				n++;
			}
			/*Não imprimir um espaço, caso seja lxi.*/
			if( (p_newcode->codigocompleto[i] == 0x1) || (p_newcode->codigocompleto[i] == 0x11) || (p_newcode->codigocompleto[i] == 0x21) || (p_newcode->codigocompleto[i] == 0x31)){
			}else{
				fprintf(codigo_assembly, " ");
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
					fprintf(codigo_assembly, "%s", pl->label);
			} else{
				/*============================================================
				====================Imprime endereço==========================
				============================================================*/
				if((p_newcode->codigocompleto[i]+256*p_newcode->codigocompleto[i+1]) > 40960)
					fprintf(codigo_assembly, "0");
				fprintf(codigo_assembly, "%.4xH", (p_newcode->codigocompleto[i])+(p_newcode->codigocompleto[i+1]) );
			}
			i++;
			posicao_code++;
			fprintf(codigo_assembly, "\n");
		}

		i++;
		posicao_code++;

	}
}

/*============================================================
====================Imprime .data=============================
============================================================*/
	fprintf(codigo_assembly, "\n.data\n\n");


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
			fprintf(codigo_assembly, "%s:\t ", pl->label);
		} else{
			fprintf(codigo_assembly, "\t");
		}


		fprintf(codigo_assembly, "\tdb %d\n", p_newdata->datacompleto[i]);

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
			fprintf(codigo_assembly, "%s:\t ", pl->label);
		} else{
			fprintf(codigo_assembly, "\t");
		}

		fprintf(codigo_assembly, "\tds %x\n", p_dadosbss->quantidade);
	}

}
/*============================================================
====================Imprime .end==============================
============================================================*/
	fprintf(codigo_assembly, "\n.end\n");	/*Imprime .end*/
	printf("...Código foi impresso com sucesso.\n");

/*============================================================
====================Imprimir na tela?=========================
============================================================*/
	printf("\nVocê deseja ver também na tela o resultado? (s/n)");
	scanf("%c", &resposta);

	if( resposta == 's' )
		imprimenatela(p_label, p_tabela, linguagemassembly, p_dadosbss, p_newcode, p_newdata);

	printf("\n");

}
