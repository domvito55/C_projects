#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"desmontador.h"

#define DEBUG "-g"

/*
**	___________________desmontador.c___________________
**		
**	Desmonta um arquivo em linguagem de máquina (.txt) em um arquivo em linguagem assembly 8085 (.txt).
**	
**	___________________desmontador.c___________________
**/


int main(int argc, char *argv[]) {
	char *linguagemdemaquina;
	char *linguagemassembly;

/*============================================================
====================Analisa a linha do terminal===============
============================================================*/

	/*==========Erro
	Chamada feita de modo incorreto*/
	if(argc == 1 || argc > 4){
	 	printf("**Erro: Uso incorreto do programa.\n...Maneira adequada: \n\t./desmontador <arquivo fonte>\n\t");
		printf("./desmontador <arquivo fonte> <arquivo alvo>\n\t./desmontador -g <arquivo fonte com informações ");
		printf("de debug>\n\t./desmontador -g <arquivo fonte com informações de debug> <arquivo alvo>");
	} else if(argc == 2){
		/*==========SEM INFO DEBUG: desmontador <entrada>*/
		linguagemdemaquina=argv[1];
		linguagemassembly=malloc(40*sizeof(char));
		sprintf(linguagemassembly, "%s%s", linguagemdemaquina, ".txt");
	 	printf("...O código %s será montado em %s.\n", linguagemdemaquina, linguagemassembly);
		desmontar(linguagemdemaquina, linguagemassembly);
	} else if(argc == 3){
		if(strcmp(argv[1],DEBUG)){
			/*==========SEM INFO DEBUG: desmontador <entrada> <saída>*/
			linguagemdemaquina=argv[1];
			linguagemassembly=argv[2];
		 	printf("...O código %s será montado em %s.\n", linguagemdemaquina, linguagemassembly);
			desmontar(linguagemdemaquina,linguagemassembly);
		} else {
			/*==========COM INFO DEBUG: desmontador -g <entrada>*/
			linguagemdemaquina=argv[2];
			linguagemassembly=malloc(40*sizeof(char));
			sprintf(linguagemassembly, "%s%s", linguagemdemaquina, ".txt");
		 	printf("...O código %s será montado em %s.\n", linguagemdemaquina, linguagemassembly);
			desmontarcomdebug(linguagemdemaquina, linguagemassembly);
		}
	} else if(argc == 4){
		if(!strcmp(argv[1],DEBUG)){
			/*==========COM INFO DEBUG: desmontador -g <entrada> <saída>*/
			linguagemdemaquina=argv[2];
			linguagemassembly=argv[3];
		 	printf("...O código %s será montado em %s.\n", linguagemdemaquina, linguagemassembly);
			desmontarcomdebug(linguagemdemaquina,linguagemassembly);
		}
		else {
		/*==========Erro
		Chamada feita de modo incorreto*/
	 	printf("**Erro: Uso incorreto do programa.\n...Maneira adequada: \n\t./desmontador <arquivo fonte>\n\t");
		printf("./desmontador <arquivo fonte> <arquivo alvo>\n\t./desmontador -g <arquivo fonte com informações ");
		printf("de debug>\n\t./desmontador -g <arquivo fonte com informações de debug> <arquivo alvo>");
		}
	}
	return 0;
}
