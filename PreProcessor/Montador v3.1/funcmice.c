/*arquivo com funcoes micelanes de suporte ao preprocessamento*/



#define ESPACO (((*c) == ' ') || ((*c) == '\t'))
/*deixa aberta a possibilidade de trabalhar com mais BITS, caso queira-se usar esse preprocessamento em outro montador*/
#define BITS 8
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>

int TransformToDecimal(int *operacao, FILE **arquivo, char *c, FILE **temp, char *tipo,	float *operador1f, 	char operador1[], int *contador);


/*faz operacoes simples nas bases bin, dec, hex, octal. sempre retorna hexa, considerando complemento a dois*/
int conta(int *operacao, FILE **arquivo, char *c, FILE **temp){
	float operador1f = 0; /*recebe operando1 e acumula o resultado*/
	float operador2f = 0;
	int contador = 1;
	char operador1[BITS+2], operador2[BITS+2];
	char tipo1 = 0;  /*armazena tipo da varialvel operador1f, hex, dec, octal, bin*/
	char tipo2 = 0;
	char caux[4]; /*vairaveis auxiliares para conversao de numeros para hexa*/
	char caux2[4]; 
	tipo1 = 'd';
	tipo2 = 'd';
	(*operacao) = 0; /*avisa programa principal se houve operacao*/
	
	/*prparacao do primeiro operando*/
	TransformToDecimal(operacao, arquivo, c, temp, &tipo1, &operador1f, operador1, &contador);

	/*if que faz operacao de subtracao*/
	if((*c)=='-'){
			(*c) = fgetc(*arquivo);
			contador++;
			if(ESPACO){
				while(ESPACO){
					(*c) = fgetc(*arquivo);
					contador++;
				}
			}
		if((isdigit(*c))||((*c)=='-')){
		/*prparacao do segundo operando e ajuste do primeiro, se necessario*/
			TransformToDecimal(operacao, arquivo, c, temp, &tipo2, &operador2f, operador2, &contador);
			if((tipo1 == 'd')||(tipo1 == 'D'))
				operador1f = atof(operador1);
			if((tipo2 == 'd')||(tipo2 == 'D'))
				operador2f = atof(operador2);
		/*operacao e impressao de arquivo*/
			operador1f = operador1f - operador2f;
			if((operador1f<0)&&(operador1f>=-128)){
				sprintf(caux, "%hx", (int)operador1f);
				sprintf(caux2, "%c%c", caux[2],caux[3]);
				fprintf ((*temp), "0%sh",caux2);
printf ("0%sh",caux2);
				return 0;
			}	
			fprintf ((*temp), "0%xh",(int)operador1f);
printf ("0%xh",(int)operador1f);
			return 0;
		}
	}
	/*if que faz operacao de adicao, semelnahte em tudo ao de subtracao*/
	if((*c)=='+'){
		(*c) = fgetc(*arquivo);
		contador++;
		if(ESPACO){
			while(ESPACO){
				(*c) = fgetc(*arquivo);
				contador++;
			}
		}
		if((isdigit(*c))||((*c)=='-')){
			TransformToDecimal(operacao, arquivo, c, temp, &tipo2, &operador2f, operador2, &contador);
			if((tipo1 == 'd')||(tipo1 == 'D'))
				operador1f = atof(operador1);
			if((tipo2 == 'd')||(tipo2 == 'D'))
				operador2f = atof(operador2);
			operador1f = operador1f + operador2f;
			if((operador1f<0)&&(operador1f>=-128)){
				sprintf(caux, "%hx", (int)operador1f);
				sprintf(caux2, "%c%c", caux[2],caux[3]);
				fprintf ((*temp), "0%sh",caux2);
printf ("0%sh",caux2);
				return 0;
			}	
			fprintf ((*temp), "0%xh",(int)operador1f);
printf ("0%xh",(int)operador1f);
			return 0;
		}
	}
	/*if que faz operacao de multiplicacao, semelnahte em tudo ao de subtracao*/
	if((*c)=='*'){
		(*c) = fgetc(*arquivo);
		contador++;
		if(ESPACO){
			while(ESPACO){
				(*c) = fgetc(*arquivo);
				contador++;
			}
		}
		if((isdigit(*c))||((*c)=='-')){
			TransformToDecimal(operacao, arquivo, c, temp, &tipo2, &operador2f, operador2, &contador);
			if((tipo1 == 'd')||(tipo1 == 'D'))
				operador1f = atof(operador1);
			if((tipo2 == 'd')||(tipo2 == 'D'))
				operador2f = atof(operador2);
			operador1f = operador1f * operador2f;
			if((operador1f<0)&&(operador1f>=-128)){
				sprintf(caux, "%hx", (int)operador1f);
				sprintf(caux2, "%c%c", caux[2],caux[3]);
				fprintf ((*temp), "0%sh",caux2);
printf ("0%sh",caux2);
				return 0;
			}	
		fprintf ((*temp), "0%xh",(int)operador1f);
printf ("0%xh",(int)operador1f);
			return 0;
		}
	}	
	/*if que faz operacao de divisao, semelnahte em tudo ao de subtracao*/
	if((*c)=='/'){
		(*c) = fgetc(*arquivo);
		contador++;
		if(ESPACO){
			while(ESPACO){
				(*c) = fgetc(*arquivo);
				contador++;
			}
		}
	if((isdigit(*c))||((*c)=='-')){
		TransformToDecimal(operacao, arquivo, c, temp, &tipo2, &operador2f, operador2, &contador);
		if((tipo1 == 'd')||(tipo1 == 'D'))
			operador1f = atof(operador1);
		if((tipo2 == 'd')||(tipo2 == 'D'))
			operador2f = atof(operador2);
		operador1f = operador1f / operador2f;
			if((operador1f<0)&&(operador1f>=-128)){
				sprintf(caux, "%hx", (int)operador1f);
				sprintf(caux2, "%c%c", caux[2],caux[3]);
				fprintf ((*temp), "0%sh",caux2);
printf ("0%sh",caux2);
				return 0;
			}	
		fprintf ((*temp), "0%xh",(int)operador1f);
printf ("0%xh",(int)operador1f);
			return 0;
		}
	}
		
	/*else: caso nao haja operacao nenhuma apenas imprime o numero original, mas em hex*/
	else{
		if(tipo1=='d'){
			operador1f = atof(operador1);
			tipo1 = 'd';
			if((operador1f<0)&&(operador1f>=-128)){
				sprintf(caux, "%hx", (int)operador1f);
				sprintf(caux2, "%c%c", caux[2],caux[3]);
				fprintf ((*temp), "0%sh",caux2);
printf ("0%sh",caux2);
				return 0;
			}	
			fprintf ((*temp), "0%hxh",(int)operador1f);
printf ("0%hxh",(int)operador1f);
			return 0;
		}
		if(tipo1=='h'){
			tipo1 = 'd';
			if((operador1f<0)&&(operador1f>=-128)){
				sprintf(caux, "%hx", (int)operador1f);
				sprintf(caux2, "%c%c", caux[2],caux[3]);
				fprintf ((*temp), "0%sh",caux2);
printf ("0%sh",caux2);
				return 0;
			}	
			fprintf ((*temp), "0%hxh",(int)operador1f);
printf ("0%hxh",(int)operador1f);
			return 0;
		}
		if(tipo1=='o'){
			tipo1 = 'd';
			if((operador1f<0)&&(operador1f>=-128)){
				sprintf(caux, "%hx", (int)operador1f);
				sprintf(caux2, "%c%c", caux[2],caux[3]);
				fprintf ((*temp), "0%sh",caux2);
printf ("0%sh",caux2);
				return 0;
			}	
			fprintf ((*temp), "0%xh",(int)operador1f);
printf ("0%xh",(int)operador1f);
			return 0;
		}
		if(tipo1=='b'){
			tipo1 = 'd';
			if((operador1f<0)&&(operador1f>=-128)){
				sprintf(caux, "%hx", (int)operador1f);
				sprintf(caux2, "%c%c", caux[2],caux[3]);
				fprintf ((*temp), "0%sh",caux2);
printf ("0%sh",caux2);
				return 0;
			}	
			fprintf ((*temp), "0%xh",(int)operador1f);
printf ("0%hxh",(int)operador1f);
			return 0;
		}
		(*operacao) = 0;
		fseek ((*arquivo), -contador, SEEK_CUR);
		(*c) = fgetc(*arquivo);
	}
	return 0;
}

int TransformToDecimal(int *operacao, FILE **arquivo, char *c, FILE **temp, char *tipo, 	float *operador1f, 	char operador1[], int *contador){

	int indice = 0;
	int expoente = 0; /*variavel auxiliar para o calculo de expoentes, para a transformacao entre bases, pow, da*/
	int expoente2 = 1;/*biblioteca math nao aceita variavel como expoente*/
	int len;
	int espaco = 0;/*flag que auxilia na deteccao de labels mal formadas*/
	float aux=0;
	char caux[2];

	/****estrutura par identificacao de labels mal formadas*****/
	fseek ((*arquivo), -2, SEEK_CUR);
	(*c) = fgetc(*arquivo);
	if((ESPACO) || ((*c) == '\n')){
		espaco = 1;
	}
	(*c) = fgetc(*arquivo);
	/*fim de estrutura par identificacao de labels mal formadas*/

	if((isdigit(*c))||((*c)=='-')){
		(*tipo) ='d';
		(*operacao) = 1;

		/*if: prepara numeros negativos*/
		if (((*c)=='-')){
			(*c) = fgetc(*arquivo);
			(*contador)++;
			if(ESPACO){
				while(ESPACO){
					(*c) = fgetc(*arquivo);
					(*contador)++;
				}
			}
			if( (!(isdigit(*c) ) ) && ((*c)!='a') && ((*c)!='b') && ((*c)!='c') && ((*c)!='d') && ((*c)!='e') && ((*c)!='f') && ((*c)!='A') && ((*c)!='B') && ((*c)!='C') && ((*c)!='D') && ((*c)!='E') && ( (*c)!='F') ){
				(*operacao) = 0;
				fseek ((*arquivo), -(*contador), SEEK_CUR);
				(*c) = fgetc(*arquivo);
				return 0;
			}
			else{
				operador1[indice] = '-';
				indice++;
			}
		}
		while( (isdigit(*c)) || ((*c)=='.') || ((*c)=='a') || ((*c)=='b') || ((*c)=='c') || ((*c)=='d') || ((*c)=='e') || ((*c)=='f') || ((*c)=='A') || ((*c)=='B') || ((*c)=='C') || ((*c)=='D') || ((*c)=='E') || ((*c)=='F')){
			operador1[indice] = (*c);
			(*c) = fgetc(*arquivo);
			(*contador)++;
			indice++;
		}

		/*if: identifica label mal formada*/
		if (espaco == 1){
			while(((*c)!='\n') && (!ESPACO)){
				espaco++;
				(*c) = fgetc(*arquivo);
				if((*c)==':'){
					printf("\n\n\n\tlabel invalida: comeca com numero\n\n\n\n");	
					exit(100);
				}
			}
		fseek ((*arquivo), -espaco, SEEK_CUR);
		(*c) = fgetc(*arquivo);
		espaco = 0;	
		}
		
		if(ESPACO){
			while(ESPACO){
				(*c) = fgetc(*arquivo);
				(*contador)++;
			}
		}
		
		/*if: identifica decimal terminado com d ou binarios*/
		if(((*c)!='h')||((*c)!='H')){
			if( (operador1[indice-1]=='d')||(operador1[indice-1]=='D') ){
				operador1[indice-1] = '\0';
				(*tipo) = 'd';
			}
			if( (operador1[indice-1]=='b')||(operador1[indice-1]=='B') ){
				operador1[indice-1] = '\0';
				(*tipo) = 'b';
			}
		}
		
		/*if: transforma hexa para dec*/
		if(((*c)=='h')||((*c)=='H')){
			(*tipo) = 'h';
			(*c) = fgetc(*arquivo);
			(*contador)++;
			operador1[indice] = '\0';
			indice = 0;
			aux = 0;
			while( (operador1[indice])!='\0' ){
				(caux[0]) = operador1[indice];
				(caux[1]) = '\0';
				if( ((caux[0])=='a')||((caux[0])=='A') )
					aux = 10;
				if( ((caux[0])=='b')||((caux[0])=='B') )
					aux = 11;
				if( ((caux[0])=='c')||((caux[0])=='C') )
					aux = 12;
				if( ((caux[0])=='d')||((caux[0])=='D') )
					aux = 13;
				if( ((caux[0])=='e')||((caux[0])=='E') )
					aux = 14;
				if( ((caux[0])=='f')||((caux[0])=='F') )
					aux = 15;
				if(isdigit(caux[0]))
					aux = atof(caux);
				expoente2=1;
				len = strlen(operador1);	
				if(operador1[0]!='-'){
					for(expoente=len;expoente>(indice+1);expoente--){
						expoente2=expoente2*16;
					}
					aux = aux*expoente2;
					(*operador1f) = (*operador1f)+aux;
					indice++;
				}
				if(operador1[0]=='-'){
					if(indice == 0)
						aux = 0;
					for(expoente=(len-1);expoente>(indice);expoente--){
						expoente2=expoente2*16;
					}
					aux = aux*expoente2;
					(*operador1f) = (*operador1f)-aux;
					indice++;
				}
			}
		}

		/*if: transforma octal para dec*/
		if(((*c)=='o')||((*c)=='O')){
			(*tipo) = 'o';
			(*c) = fgetc(*arquivo);
			(*contador)++;
			operador1[indice] = '\0';
			indice = 0;
			aux = 0;
			while( (operador1[indice])!='\0' ){
				(caux[0]) = operador1[indice];
				(caux[1]) = '\0';
				aux = atof(caux);
				expoente2=1;
				len = strlen(operador1);	
				if(operador1[0]!='-'){
					for(expoente=len;expoente>(indice+1);expoente--){
						expoente2=expoente2*8;
					}
					aux = aux*expoente2;
					(*operador1f) = (*operador1f)+aux;
					indice++;
				}

				if(operador1[0]=='-'){
					if(indice == 0)
						aux = 0;
					for(expoente=(len-1);expoente>(indice);expoente--){
						expoente2=expoente2*8;
					}
					aux = aux*expoente2;
					(*operador1f) = (*operador1f)-aux;
					indice++;
				}
			}
		}
		
		/*if: transforma bin para dec*/
		if(((*tipo)=='b')){
			indice = 0;
			aux = 0;
			while( (operador1[indice])!='\0' ){
				(caux[0]) = operador1[indice];
				(caux[1]) = '\0';
				aux = atof(caux);
				expoente2=1;
				len = strlen(operador1);	
				if(operador1[0]!='-'){
					for(expoente=len;expoente>(indice+1);expoente--){
						expoente2=expoente2*2;
					}
					aux = aux*expoente2;
					(*operador1f) = (*operador1f)+aux;
					indice++;
				}
				if(operador1[0]=='-'){
					if(indice == 0)
						aux = 0;
					for(expoente=(len-1);expoente>(indice);expoente--){
						expoente2=expoente2*2;
					}
					aux = aux*expoente2;
					(*operador1f) = (*operador1f)-aux;
					indice++;
				}
			}
		}
		if(ESPACO){
			while(ESPACO){
				(*c) = fgetc(*arquivo);
				contador++;
			}
		}
	}
	return 0;
}

