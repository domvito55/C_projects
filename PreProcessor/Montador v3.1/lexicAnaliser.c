/**
Reponsavel por transformar o arquivo em uma TokenTable.

Transforma cada linha em uma string com lexicAnalise() 
e entao quebra a linha em tokens com tokenMaker().

@author Murilo Marques Marinho
@version 1.2
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include"line.h"
#include"token.h"
#include"tokenTable.h"
#include"preProcessor.h"
#include"lexicAnaliser.h"

/**
 *A estrutura especifica de uma TokenTable e descrita no PDF anexo.
 *Tentar analisar um arquivo sem o devido preProcessamento tem um resultado indefinido.
 *
 *@param tokenTable a raiz da tabela de tokens. Sera modificado.
 *@param fp o arquivo de entrada, já aberto, que sera lido em busca das tokens.
 *@return 0 Caso nao tenha dado erros.
 *@return 1 ReadLine buffer Overflow.
 *@return 2 Erro na remocao do arquivo temporario.
  @return 3 Duas virgulas consecutivas
  @return 4 Buffer overflow
 */
int lexicAnalise(struct TokenTable **tokenTable, FILE* fp){

	/*Buffer de caracteres (2 porque origem e destino do strncpy nao podem ser iguais. Pode causar o nascimento de caracteres misterioros	*/
	char l_buffer[MAX_LINE_BUFFER_SIZE];

	/*Buffer de caracteres (2 porque origem e destino do strncpy nao podem ser iguais. Pode causar o nascimento de caracteres misterioros*/
	char l_buffer_2[MAX_LINE_BUFFER_SIZE];

	/*Caracter lido um por vez*/
	char c = 10;

	/*Contador para o tamanho da lina*/
	int i = 0;

	/*Cria duas l_structs temporarias*/
	struct Line *l_struct;

	/*Enquanto nao chegar no fim do arquivo*/
	while((c = fgetc(fp)) != EOF){

		/*Adiciona o caracter no buffer*/
		l_buffer[i] = c;
		/*Incrementa o tamanho da linha*/
		i++;

		/*Se encontrar um \n, cria uma nova linha e envia para o tokenMaker*/
		if(c == '\n'){

			/*Retira o ultimo caractere lido do buffer*/
			l_buffer[i - 1] = '\0';	

			/*Copia somente a parte importante o buffer*/
			strncpy(l_buffer_2, l_buffer, i);

			/*Cria a linha e aloca na memoria*/
			newLine(&l_struct);
			
			/*Adiciona a linha a tabela de simbolos*/
			addLineToTokenTable(&l_struct, tokenTable);		

			/*Envia a linha para ser quebrada em tokens*/
			int errorcode = tokenMaker(l_buffer_2, i, &l_struct);
			if(errorcode){
				return errorcode+2;
			}
			
			/*Zera o tamanho da linha*/
			i = 0;
		}
		/*Se o tamanho da linha for maior que o tamanho maximo do buffer, gera um erro fatal.*/
		if(i >= MAX_LINE_BUFFER_SIZE){
			return 1;
		}

	}

	/*Deleta o arquivo temporario*/
	fclose(fp);
	if (remove("temp.txt") == -1)
    		return 2;

	return 0;
}

/**
Recebe uma char[] e quebra em Tokens, colocando-as em ordem na struct Line. O tamanho e necessario.
Funcao diretamente dependende de um pre-processamento eficiente.

@param line[] Uma array que contem a linha que se deseja quebrar em Token
@param lineSize O tamanho da linha
@param l_struct Uma estrutura do tipo Line na qual as Token serao adicionas. E modificada durante o processo.
@return 0 Execucao sem erros
@return 1 Duas virgulas consecutivas
@return 2 Buffer overflow
*/
int tokenMaker(char line[], int lineSize, struct Line **l_struct){

	/*Contador do buffer*/
	int i = 0;
	/*Contador da linha*/
	int j = 0;
	/*Buffer*/
	char t_buffer[MAX_TOKEN_BUFFER_SIZE];
	/*Caractere de armazenamento*/
	char c = 10;
	/*Ponteiro para as Novas tokens*/
	char *holder = NULL;
	/*Contador de virgulas*/
	int commaFound = 0;

	while((j <= lineSize)){
		c = line[j];

		t_buffer[i] = c;

		i++; j++;
		if((c == ' ') ||(c ==  ',' )||(c ==  ':')||(j == lineSize)){

			/*Caso encontre uma virgula duas vezes consecutivas, gera um erro fatal*/
			if(c == ','){
				if(commaFound){
					return 1;
				}
				commaFound = 1;
			}

			/*Modifica o caractere anterior*/
			if(c != ':'){
				t_buffer[i - 1] = '\0';
			}
			/*Modifica o caractere posterior*/
			else{
				if(!isalnum(line[j])){
					continue;
				}
				t_buffer[i] = '\0';
			}

			/*Cria um novo char* para conter os caracteres. Tentativas sem fazer isso faz todos os tokens apontarem para o mesmo char.*/	
			holder = (char *)malloc(sizeof(char)*i);
			strncpy(holder, t_buffer, i);
			/*Cria uma nova token com o conteudo de holder e adiciona na linha*/
			addNewTokenToLine(l_struct, holder);
			
			/*Caso encontre uma virgula, adiciona na tabela de tokens*/
			if((c ==  ',' )){
				holder = (char *)malloc(sizeof(char)*2);
				(*holder) = ',';
				(holder) += sizeof(char);
				(*holder) = '\0';
				holder -= sizeof(char); 
				addNewTokenToLine(l_struct, holder);
			}
			
			/*Vai para a proxima linha se chegou no final*/
			if((j == lineSize)){
				return 0;
			}

			i = 0;
		}
		/*Zera a contagem de virgulas*/
		else{
			commaFound = 0;
		}
		/*Testa se o buffer atingiu um valor maior que o maximo permitido*/
		if(i >= MAX_TOKEN_BUFFER_SIZE){
			return 2;
		}

	}

	return 0;
}

