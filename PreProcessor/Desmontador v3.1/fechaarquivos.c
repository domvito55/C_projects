#include<stdio.h>
/*
**	___________________fechaarquivos.c___________________
**		
**	Fecha todos os arquivos utilizados no programa.
**
**	___________________fechaarquivos.c___________________
**/

void fechaarquivos(FILE **file1, FILE **file2, FILE **file3) {
/*============================================================
====================Fecha todos os arquivos===================
============================================================*/
	fclose(*file1);
	fclose(*file2);
	fclose(*file3);
	printf("...Arquivos fechados com sucesso.\n");
}
