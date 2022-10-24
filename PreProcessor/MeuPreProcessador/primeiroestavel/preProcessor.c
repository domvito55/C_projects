/*****************************************************************************/
/*Armazena a função de preprocessamento.									 */
/*																			 */
/*@author Murilo Marques Marinho											 */
/*@version 1.1																 */
/*	Com alteracoes por Matheus Vinícius Ferreira de Figueiredo Teixeira      */
/*****************************************************************************/

#include<ctype.h>
#include<stdlib.h>
#include<stdio.h>
#include"preProcessor.h"
/**Se tentar usar a funcao isspace(c), ele acha um caractere invalido. Não me pergunte porque*/
#define ESPACO ((c == ' ') || (c == '\t'))

/*********************************************************************************************************************/
/* - Retira as linhas em branco.																					 */
/* - Retira comentários.																						 	 */
/* - Retira linhas que possuem apenas comentários.															 		 */
/* - Reduz todo o texto para caixa baixa.															 				 */
/* - Verifica caracteres inválidos.															 						 */
/* - Reduz qualquer espaçamento >= 1 para 1.															 			 */
/* @param arquivo O arquivo que sera preprocessado															 		 */
/* @return Ajusta o ponteiro de entrada para apontar para o arquivo pre-processado. E transparente ao usuario,		 */
/*	mas o programa cria um arquivo temporario temp.txt que e o apontado na saida.									 */
/* @return 0 Execucao sem erros.																					 */
/* @return 1 Erro na abertura do arquivo temporario.																 */
/* @return 2 Caractere invalido.																					 */
/*********************************************************************************************************************/
 

int preProcess(FILE** arquivo){

	/*Caractere de leitura*/
	char c = 0;/*Esquece de inicializar pra voce ver o que acontece com esse pobre algoritmo*/
	
	/**********************Variaveis adicionadas por Matheus**************************/

	/* Variaveis adicionadas para execucao de calculos simples com inteiros			 */
	float operador1f, operador2f;
	int contador = 1;
	int indice = 0;
	char operador1[32], operador2[32];
	/*Flag para saber se fez operacao ou nao*/
	int operacao = 0;
	
	/*******************fim das Variaveis adicionadas por Matheus*********************/
	
	
	/*Arquivo de saida. E escrito durante o loop central*/	
	FILE *temp;

	/*Modo de atualizacao de arquivo. Cria se ele nao existir. Permite escrever ou ler. Depois de uma surra epica, esse W+ foi minha salvacao*/
	if(!(temp = fopen("temp.txt", "w+")))
		return 1;

	/*Caso tenha linhas que so tenham comentarios, esse flag eh necessario*/
	int el_trimmer = 0; /*empty line trimmer*/

	/*Para retirar linhas e comentarios que precedem o codigo.*/	
	int begin_trimmer = 1;

	c = fgetc(*arquivo);
	while(c!= EOF) {
		
		if(ESPACO){
			/*Joga todos os espacos fora.*/
			while(ESPACO){
				c = fgetc(*arquivo);
			}
			/*Se o ultimo caractere era um line feed*/
			if(c == '\n' || c == ';')
				{}
			else
				fputc(' ', temp);
		}
		if(c == ';'){
			/*Joga todos os caracteres fora ateh o fim da linha, excluindo o \n*/
			while((c = fgetc(*arquivo)) != '\n');
		}
		if(c == '\n'){
			while((c == '\n') || ESPACO){
				c = fgetc(*arquivo);
				if(c == ';'){
					el_trimmer = 1;
					break;
				}			
			}
			if(!el_trimmer){
				if(!begin_trimmer){				
					fputc('\n', temp);
				}
				else{
					begin_trimmer = 0;	
				}
			}
			else{
				el_trimmer = 0;
			}
			continue;
		}
		if(c == '\0'){
	 		c = fgetc(*arquivo);
	 		continue;
	 	}
		if((!isalnum(c)) && (c != '_') && (c != ':') && (c != '.') && (c != '\n') && (c != ' ') && (c != ',') && (c != ';')){
			return 2;
		}
		if(begin_trimmer){
			begin_trimmer = 0;
		}
		c = tolower(c);

		/********************************Codigo Adicionado por Matheus*********************************/
		/*executa os calculos simples (adicao, subtracao, divisao e multiplicacao) presentes no codigo*/
		/**********************************************************************************************/
		if(isdigit(c)){
			operacao = 1;
			while((isdigit(c))||(c=='.')){
				operador1[indice] = c;
				c = fgetc(*arquivo);
				contador++;
				indice++;
			}	
			operador1[indice] = '\0';
			if(c==ESPACO){
				c = fgetc(*arquivo);
				contador++;
			}
			if(c=='-'){
				c = fgetc(*arquivo);
				contador++;
				if(c==ESPACO){
					c = fgetc(*arquivo);
					contador++;
				}
				indice = 0;
				if(isdigit(c)){
					while((isdigit(c))||(c=='.')){
						operador2[indice] = c;
					c = fgetc(*arquivo);
					contador++;
					indice++;
					}
				operador2[indice] = '\0';
				operador1f = atof(operador1);
				operador2f = atof(operador2);
				operador1f = operador1f - operador2f;
printf("%.0f", operador1f);
				fprintf (temp, "%.0f",operador1f);
				}
			}
			else{
			fseek ((*arquivo), -contador, SEEK_CUR);
			c = fgetc(*arquivo);
			operacao = 0;
			indice = 0;
			}
		contador = 1;
		}

		/******************Fim de Codigo Adicionado por Matheus**********************/
		/* a estrutura if foi adicionado por Matheus*/
	if(operacao==0)
printf("%c", c);
		fputc(c, temp);
		c = fgetc(*arquivo);
	operacao = 0;/*adicionado por Matheus*/
	}

	fclose(*arquivo);

	rewind(temp);

	(*arquivo) = temp;

	return 0;
}

