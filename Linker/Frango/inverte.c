#include<stdio.h>


/*=====================inverte()==============================
sai da notação little ending
chamada por:
	atulaiza (atualizar.c)
@parametro:
	- variavel que deve ser transformada pra big ending
retorna:
	- a varivel passada em big ending
============================================================*/
int inverte(int addr){

/*==========variaveis locais==============*/
int byte1;
int byte2;

int mascara1 = 0x0000ff00;
int mascara2 = 0x000000ff;
int retorno;
/*==========variaveis locais==============*/

byte1 = addr<<8;
byte2 = addr>>8;

byte1 = byte1 & mascara1;
byte2 = byte2 & mascara2;

retorno = byte1 | byte2;

return retorno;

}
