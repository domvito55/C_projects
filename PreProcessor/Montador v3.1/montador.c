/**
Contem a função main e as funções de montagem. Engloba todas as funções do programa para realizar
a montagem do código.

LEIA README v3.0.pdf (totalmente equivalente para a v3.1) para descrição das estruturas de dados e funcionamento do programa.

Como usar:
make <- compila o programa
make exemplos  <- monta todos os exemplos disponiveis, todos ficam na pasta exemplos_montados

Como limpar:
make clean <- limpa os .o
make exemplos_clean <- limpa os codigos exemplo montados

Como descrito em montador.c:
Uso: ./montador arquivodeentrada.txt arquivodesaida

Saida do arquivo conforme padroes ELF.
Adicao automatica de simbolos de DEBUG na sintaxe STABS

>>>>>> Observações: 

Escrita:   Não faz diferenciação entre maísculas e minúsculas: ADD_LOVE = add_love = Add_Love
	   O mesmo serve para instruções e diretivas.

Endereços: Em HEXADECIMAL devem iniciar com número E terminar com H. Não são aceitos número de endereços em outro formato (DECIMAL, BINARIO, OCTAL...)

Imediatos e diretivas: Numeros positivos. Ou Decimais ou Hexadecimais, sendo a diferenciação entre eles o H no final.
	   Exemplo: adi 16   => C6a 10a
		    adi 16H  => C6a 16a
		    adi 0AAH => C6a AAa
		    adi AAH  => Erro

Estrutura do código:

	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		   .begin <identificador>
		   	<Diretivas PUBLIC e EXTERN>
		   .text
			<.start <identificador>> <= facultativo.
			<INSTRUÇÕES>
		   .data
			<DIRETIVAS DS E DB>
		   .end

	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	.text e .data podem estar invertidos.
	Falhas em seguir essa sintaxe geram erros, e as mensagens nem sempre ajudam muito.
	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Estrutura de instruções:
	<INSTRUCAO> <ESPAÇO> <ARGUMENTO> <VIRGULA> <ARGUMENTO> => Qualquer espaçamento entre as vírgulas e os argumentos dará, sem dúvidas, um ERRO FATAL.

Estrutura da diretiva DB também segue esse modelo:
	<DB> <ESPAÇO> <VALOR> <VIRGULA> <VALOR> <VIRGULA> <...>

Erros:
	A maioria dos erros é verificado e informado devidamente ao usuário. Alguns errors, contudo, passam e são visíveis apenas no código de saída.
	São uma minoria mas não custa avisar. Por mais que os codigos de erro tenham sido revisados nessa versao, algumas coisas fogem da logica.

@author Murilo Marques Marinho
@version 3.1
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"errors.h"
#include"preProcessor.h"
#include"lexicAnaliser.h"
#include"line.h"
#include"token.h"
#include"tokenTable.h"
#include"mcline.h"
#include"mctable.h"
#include"simboltable.h"
#include"simbolline.h"
#include"instrucao.h"
#include<string.h>
#include"dirline.h"
#include"dirtable.h"
#include"directives.h"
#include"definitionline.h"
#include"definitiontable.h"
#include"useline.h"
#include"usetable.h"
#include"ce.h"
#include"elfprint.h"

#ifndef DEBUG
#define DEBUG 0
#endif

int findEntryAddress(SimbolTable** st, char* label);
void updateStWithDt(SimbolTable** st, DefinitionTable** dt);
int monta(struct TokenTable *tokenTable, char* arquivosaida, char* arquivoentrada);

int main(int argc, char *argv[]){
	/**********codigo adicionado por Matheus**********/
	/*variaveis que permitem inserir nome de arquivos*/
	char v1[300];
	char v2[300];
	/******fim de codigo adicionado por Matheus*******/

	if(argc != 3){
		printf("\n\tUso incorreto do programa: montador <nome arquivo entrada> <nome arquivo saida>\n");
		/*****************************************************codigo adicionado por Matheus*****************************************************/
		/*Permite inserir nome de arquivo                                                                                                      */
		printf("\n\tPor favor entre com o caminho completo do arquivo que queira montar, isto eh, <caminho>/<nome do arquivo a ser compilado>\n");
		scanf("%s",v1);
		printf("\n\tPor favor entre com o caminho completo de saida, isto é,  <caminho>/<nome do arquivo de saida>\n");
		scanf("%s",v2);
	}
	strcpy(v1,argv[1]);
	if(argv[2])
		strcpy(v2,argv[2]);
		/*****************************************************codigo adicionado por Matheus*****************************************************/

	/*O ponteiro para o arquivo de entrada.*/
	FILE *fp;

	/*Se nao conseguir abrir o arquivo, gera um erro fatal*/
	if(!(fp = fopen(v1, "r")))
		return 1;

	int errorcode = 0;

	errorcode = preProcess(&fp);
	if(errorcode){
		error(errorcode);
	}

	/*A tabela de tokens que sera usada por todo o programa.*/
	TokenTable *tokenTable;
	/*Aloca a tokentable na memoria*/
	newTokenTable(&tokenTable);

	errorcode = lexicAnalise(&tokenTable, fp);
	if(errorcode){
		error(errorcode + 2);
	}
	
	/*Realiza as duas passagens do montador.*/
	errorcode = monta(tokenTable, v2, v1);
	if(errorcode){
		error(errorcode + 6);
	}

	return 0;
}

/**
Acha o valor da diretiva .start

@param st A SimbolTable na qual se deseja procurar.
@param label A label de .start
*/
int findEntryAddress(SimbolTable** st, char* label){
	if(label == NULL) return 0;

	SimbolLine* sl;


	if((*st)->firstSimbolLine == NULL){
		return 0;
	}

	for(sl = (*st)->firstSimbolLine; sl!= NULL; sl = sl->nextSimbolLine){
		if(!strcmp(label,sl->label)){
			return sl->valor;
		}
	}
	return 0;
}

/**
Atualiza os valores da simboltable que sao publicos. Utilizado para definir visibilidade na impressao
final.

@param st A SimbolTable a ser atualizada.
@param df A DefinitionTable que tem as definicoes de simbolos publicos.

*/
void updateStWithDt(SimbolTable** st, DefinitionTable** dt){

	DefinitionLine* dl;
	SimbolLine* sl;

	int deffound = 0;

	if((*dt)->firstDefLine == NULL){
		return;
	}

	for(dl = (*dt)->firstDefLine; dl != NULL; dl = dl->nextDefLine){
		deffound = 0;
		for(sl = (*st)->firstSimbolLine; sl != NULL; sl = sl->nextSimbolLine){
			if(!strcmp(dl->label, sl->label)){
				sl->publico = 1;
				deffound = 1;
			}
		}
		if(!deffound){
			error(40);
		}

	}
}


/**
Realiza a montagem do codigo.
Percorre a TokenTable apenas uma vez, criando a SimbolTable, MCTable, DirTable, DefTable e UseTable equivalentes.

@param tokenTable A TokenTable, ja preenchida, que sera montada.
@param arquivosaida A String que representa o nome do arquivo de saida
@return 0 Se a execucao nao retornar erros.
	1 Programa nao comeca com .begin
	2 .begin nao eh seguido de identificador
	3 Linha de .begin possui uma Token a mais do que deveria.
	4 Programa nao possui nada alem de .begin
	5 Uso incorreto da diretiva PUBLIC. Deve ser seguida de uma label.
	6 Uso incorreto da diretiva PUBLIC. Linha tem mais Tokens do que deveria.
	7 Uso incorreto da diretiva EXTERN. Deve ser seguida de uma label.
	8 Uso incorreto da diretiva EXTERN. Linha tem mais Tokens do que deveria.
	9 Encontrado algo que nao eh uma diretiva PUBLIC ou EXTERN na regiao .begin do programa.
	10 Diretiva .text nao deve ser seguida de nenhuma declaracao na mesma linha.
	11 Programa sem .end. Regiao .text vazia.
	12 Regiao .data declarada duas vezes.
	13 Diretiva .end nao deve ser seguida de nenhuma declaracao na mesma linha.
	14 Diretiva .start encontrada mais de uma vez
	15 .start deve ser seguido de um identificador.
	16 Linha da diretiva .start tem mais Tokens do que deveria.
	17 Token encontrada nao representa um argumento valido para a instrucao.
	18 Sintaxe de instrucao incorreta.
	19 Operandos, de uma instrucao com 2 operandos, nao estao separados por virgula.
	20 Linha de instrucao tem mais Tokens do que deveria
	21 Token encontrada nao representa instrucao ou label.
	22 Primeiro Token da Linha Igual a NULL. Provavel erro de preprocessamento.
	23 Programa chegou ao fim sem encontrar a diretiva .end
	24 Diretiva .text encontrada duas vezes.
	25 Diretiva .data nao deve ser seguida de nenhuma declaracao na mesma linha.
	26 Programa sem .end. Regiao .data vazia.
	27 Diretiva .start encontrada na regiao .data.
	28 Token encontrada nao representa diretiva ou label.
	29 Diretiva .data encontrada duas vezes.
	30 Label utilizada mas não declarada.
	31 Instrucao aceita imediatos, mas houve overflow
	32 Instrucao aceita imediatos, mas houve underflow
	33 Instrucao aceita imediatos, mas operando nao e um numero valido
	34 Instrucao aceita endereços, mas houve overflow
	35 Instrucao aceita endereços, mas houve underflow
	36 Instrucao aceita endereços, mas operando nao e um endereço valido
	37 Diretiva usada na região .data nao existe
	38 Diretiva usada na região .data seguida de nenhum valor
	39 Elemento na diretiva usada na região .data maior que 8bits
	40 Elemento na diretiva usada na região .data não é um número válido
*/
int monta(struct TokenTable *tokenTable, char* arquivosaida, char* arquivoentrada){
	/*Bem, o nome diz tudo*/
	int datafound = 0;
	int textfound = 0;
	int endfound = 0;
	int startfound = 0;

	/*Avisa se a label e extern ou public*/
	int validbegindirective = 0;

	/*Para consertar o problema de achar um .text depois de um .data*/
	int textfix = 0;
	struct Line *textfixLine;

	/*Linha e Token para percorrer a TokenTable*/
	struct Line *dummyLine;
	struct Token *dummyToken;

	/*Estruturas de MCTable*/
	MCLine *mcLine;
	MCTable *mcTable;
	newMCTable(&mcTable);
	Inst *dummyInst;

	/*Estruturas de SimbolTable*/
	SimbolTable* simbolTable;
	newSimbolTable(&simbolTable);
	SimbolLine* simbolLine;

	/*Estruturas de DirTable*/
	DirTable* dirtable;
	newDirTable(&dirtable);
	DirLine* dirline;
	
	/*Estruturas de uma DefinitionTable*/
	DefinitionTable* defTable;
	newDefinitionTable(&defTable);
	DefinitionLine* defLine;

	/*Estruturas de uma UseTable*/
	UseTable* useTable;
	newUseTable(&useTable);
	UseLine* useLine;

	/*Variáveis necessárias para impressão ELF*/
	int data_size = 0;
	int data_address = 0;

	int text_size = 0;
	int text_address = 0;

	int relatext_num = 0;

	int simbol_num = 1;

	int strtab_size = 1;

	char* start_label = NULL;

	int stabstr_size = 0;

	int stab_num = 0;

	Elf32_Str* strr;
	newElf32_Str(&strr);
	strr->index = 1;

	/*Endereco atual*/
	int end = 0;

	/*Avisa se uma label foi achada como primeira token, de forma que ele nao aceitara uma segunda na mesma linha.*/
	int labelFound = 0;

	/*Verifica se a primeira token da primeira linha eh .begin*/
	if(strcmp(tokenTable->firstLine->firstToken->nome, ".begin")){
		return 1;/*Programa nao comeca com .begin*/
	}
	/*Verifica se ha identificador*/
	if(tokenTable->firstLine->firstToken->nextToken == NULL){
		return 2;/*.begin nao eh seguido de identificador*/
	}
	/*Verifica se nao ha nenhum token alem disso*/
	if(tokenTable->firstLine->firstToken->nextToken->nextToken != NULL){
		return 3;/*Linha de .begin possui uma Token a mais do que deveria.*/
	}
	/*Verifica se a linha apos .begin eh NULL*/
	if(tokenTable->firstLine->nextLine == NULL){
		return 4;/*Programa nao possui nada alem de .begin*/
	}
	/*Para todas as linhas da tabela*/
	for(dummyLine = tokenTable->firstLine->nextLine; dummyLine != NULL; dummyLine = dummyLine->nextLine){

		if(textfix){
			dummyLine = textfixLine;
			textfix = 0;
		}

		/*************************************************************************************************************************************************/
		/**************************************EXTERN/PUBLIC IF*******************************************************************************************/
		/*************************************************************************************************************************************************/
		/*Enquanto nao achou um .text, .data ou .end*/
		/*If para diretivas extern e public*/
		if(!textfound && !endfound && !datafound){
					dummyToken = dummyLine->firstToken;

					/*Indica se uma diretiva PUBLIC foi achada*/
					validbegindirective = 0;

					if(!strcmp(dummyToken->nome,"public")){

						validbegindirective = 1;

						if(dummyToken->nextToken == NULL)
							return 5;/*Uso incorreto da diretiva PUBLIC. Deve ser seguida de uma label.*/
						if(dummyToken->nextToken->nextToken != NULL)
							return 6;/*Uso incorreto da diretiva PUBLIC. Linha tem mais Tokens do que deveria.*/

						/*Seu valor sera adicionado na segunda passagem*/			
						newDefinitionLine(&defLine, dummyToken->nextToken->nome);
						addDefinitionLineToDefinitionTable(&defLine, &defTable);

					}
					if(!strcmp(dummyToken->nome,"extern")){

						validbegindirective = 1;

						if(dummyToken->nextToken == NULL)
							return 7;/*Uso incorreto da diretiva EXTERN. Deve ser seguida de uma label.*/
						if(dummyToken->nextToken->nextToken != NULL)
							return 8;/*Uso incorreto da diretiva EXTERN. Linha tem mais Tokens do que deveria.*/

						/*Adiciona na tabela de simbolos indicando que e externa*/
						newSimbolLine(&simbolLine, dummyToken->nextToken->nome);
						simbolLine->externo = 1;
						addSimbolLineToSimbolTable(&simbolLine, &simbolTable);
					}

					/*Se nao era uma diretiva EXTERN ou PUBLIC, erro*/
					if((!validbegindirective) && (strcmp(dummyToken->nome,".text")) && (strcmp(dummyToken->nome,".data")) && (strcmp(dummyToken->nome,".end"))){
						return 9;/*Encontrado algo que nao eh uma diretiva PUBLIC ou EXTERN na regiao .begin do programa.*/
					}
		}



		/*************************************************************************************************************************************************/
		/**************************************TEXT LOOP**************************************************************************************************/
		/*************************************************************************************************************************************************/
		/*Se achou .text, nao achou nenhum outro .text e nao achou o .end*/
		if(!strcmp(dummyLine->firstToken->nome, ".text") && !textfound && !endfound){

			/*A diretiva .text foi encontrada pela primeira vez*/			
			textfound = 1;

			/*Armazena o endereco inicial da secao .text*/
			text_address = end;

			/*Verifica se a proxima token eh NULL*/
			if(dummyLine->firstToken->nextToken != NULL)
				return 10;/*Diretiva .text nao deve ser seguida de nenhuma declaracao na mesma linha.*/	

			/*Vai para a proxima linha*/
			if(dummyLine->nextLine != NULL){
				dummyLine = dummyLine->nextLine;
			}
			else{
				return 11;/*Programa sem .end. Regiao .text vazia.*/
			}
		
			/*Anda no codigo ate encontrar .end ou .data*/	
			for(;(dummyLine != NULL); dummyLine = dummyLine->nextLine){

				dummyToken = dummyLine->firstToken;

				/*Verificacao da diretiva .data*/
				if(!strcmp(dummyLine->firstToken->nome, ".data")){
					if(!datafound){
						break;
					}
					else{
						return 12;/*Regiao .data declarada duas vezes.*/
					}
				}
				/*Verifica se achou .end*/
				if(!strcmp(dummyLine->firstToken->nome, ".end")){
					endfound = 1;
					/*Verifica se a proxima token eh NULL*/
					if(dummyLine->firstToken->nextToken != NULL){
						return 13;/*Diretiva .end nao deve ser seguida de nenhuma declaracao na mesma linha.*/
					}
					/*Terminou o .text*/
					break;
				}
				/*Verifica se achou .start*/
				if(!strcmp(dummyLine->firstToken->nome, ".start")){

					startfound ++;
					if(startfound > 1)
						return 14;/*Diretiva .start encontrada mais de uma vez*/
					
					/*Verifica sintaxe*/
					if(dummyToken->nextToken == NULL)
						return 15;/*.start deve ser seguido de um identificador.*/
					if(dummyToken->nextToken->nextToken != NULL)
						return 16;/*Linha da diretiva .start tem mais Tokens do que deveria.*/

					/*Armazena o nome da label .start*/
					start_label = dummyToken->nextToken->nome;

					/*Vai para a proxima iteracao*/
					continue;
				}


				/*Ve se a primeira token e diferente de NULL*/
				if(dummyLine->firstToken != NULL){
					/*Reinicia a flag de label, usada para situacoes nas quais uma label eh seguida de uma instrucao*/					
					labelFound = 0;

					/*Pega a primeira token*/
					dummyToken = dummyLine->firstToken;

					/*Ordem dos ifs e importante para verificar labels seguidas de instrucoes*/
					/*Ve se eh uma label*/
					if(isLabel(dummyToken->nome)){

						/*Retira o : para armazenar*/
						labelClear(&dummyToken->nome);

						/*Cria um novo simbolo, define seus valores e adiciona na tabela de simbolos*/
						newSimbolLine(&simbolLine, dummyToken->nome);
						simbolLine->valor = end; 
						simbolLine->istextsim = 1;
						simbolLine->name = addStrToStrTab(&strr, dummyToken->nome);
						simbol_num++;
						addSimbolLineToSimbolTable(&simbolLine, &simbolTable);

						/*Verifica se a Label eh seguida de alguma token.*/
						if(dummyToken->nextToken != NULL){
							dummyToken = dummyToken->nextToken;
						}
						else{
							labelFound = 1;				
						}
					}
					/*Tenta criar uma instrucao com essa token*/
					if(newInst(&dummyInst, dummyToken->nome)){

						/*Incrementa o endereco*/
						end += dummyInst->size;

						/*Incrementa o tamanho da secao .text*/
						text_size += dummyInst->size;

						/*Contador que itera no numero de operandos*/
						int opnum = 0;
						for(opnum = 1; opnum <= dummyInst->nop;opnum++){

							/*Se conseguiu criar a instrucao, pega a proxima token*/
							if((dummyToken = dummyToken->nextToken)!= NULL){
								int errorcode = 0;
								/*Tenta adicionar os possiveis operandos.*/
								if(addReg(dummyToken->nome, &dummyInst, opnum)){}
								else if(addRegPair(dummyToken->nome, &dummyInst)){}
								else if((errorcode = addIm(dummyToken->nome, &dummyInst, opnum)) != 4){
									if(errorcode == 1)
										return 31; /*Instrucao aceita imediatos, mas houve overflow*/
									else if(errorcode == 2)
										return 32; /*Instrucao aceita imediatos, mas houve underflow*/
									else if(errorcode == 3)
										return 33; /*Instrucao aceita imediatos, mas operando nao e um numero valido*/
								}
								else if((errorcode = addLabel(dummyToken->nome, &dummyInst, opnum)) != 4){
				              										
									if(errorcode == 1)
										return 34; /*Instrucao aceita endereços, mas houve overflow*/
									else if(errorcode == 2)
										return 35; /*Instrucao aceita endereços, mas houve underflow*/
									else if(errorcode == 3)
										return 36; /*Instrucao aceita endereços, mas operando nao e um endereço valido*/

									/* Se a label eh externa, adiciona na tabela de uso*/
									if(isExtern(&simbolTable, dummyToken->nome)){

										newUseLine(&useLine, dummyToken->nome);
										useLine->name = addStrToStrTab(&strr, dummyToken->nome);
										useLine->valor = (end-2);
										addUseLineToUseTable(&useLine, &useTable);
										simbol_num++;
						
									}
									relatext_num++;	
								}
								else
									return 17;/*Token encontrada nao representa um argumento valido para a instrucao.*/
							}
							else
								return 18;/*Sintaxe de instrucao incorreta.*/

							/*Ajusta para proxima Token se for instrucao de 2 argumentos.*/
							if(opnum == 1 && dummyInst->nop == 2){
								if(dummyToken->nextToken != NULL){
									dummyToken = dummyToken->nextToken;
									if(strcmp(dummyToken->nome, ","))
										return 19;/*Os argumentos de uma instrucao de 2 argumentos devem ser separados por virgulas.*/		
								}else
									return 18;/*Sintaxe de instrucao incorreta.*/
							}
							
						}/*END FOR OPERANDOS DA INSTRUCAO*/

						if(dummyToken->nextToken != NULL)
							return 20;/*Linha de instrucao tem mais Tokens do que deveria*/	

						/*Cria uma nova machine code Line*/		
						newMCLine(&mcLine);
						/*Adiciona a machine code Line a Machine Code Table*/
						addMCLineToMCTable(&mcTable, &mcLine);
						/*Adiciona a instrucao a linha*/
						mcLine->inst = dummyInst;

					}/*END IF NEWINST*/
					else if(!labelFound){
						return 21;/*Token encontrada nao representa instrucao ou label.*/
					}

				}/*End IF FIRST TOKEN NOT NULL*/
				else{
					return 22;/*Primeiro Token da Linha Igual a NULL. Provavel erro de preprocessamento.*/
				}
			}/*End For .text*/
			if(dummyLine == NULL){
				return 23;/*Programa chegou ao fim sem encontrar a diretiva .end*/
			}

		}/*END TEXT LOOP*/
		else if(!strcmp(dummyLine->firstToken->nome, ".text") && textfound){
			return 24;/*Diretiva .text encontrada duas vezes.*/
		}

		/*************************************************************************************************************************************************/
		/**************************************DATA LOOP**************************************************************************************************/
		/*************************************************************************************************************************************************/


		/*Se achou .data, nao achou nenhum outro .data e nao achou o .end*/
		if(!strcmp(dummyLine->firstToken->nome, ".data") && !datafound && !endfound){

			if(dummyLine->firstToken->nextToken != NULL)
				return 25;/*Diretiva .data nao deve ser seguida de nenhuma declaracao na mesma linha.*/

			/*Foi encontrado o primeiro .data*/			
			datafound = 1;
			/*Endereço inicial da seção .data*/
			data_address = end;

			/*Vai para a proxima linha*/
			if(dummyLine->nextLine != NULL){
				dummyLine = dummyLine->nextLine;
			}
			else{
				return 26;/*Programa sem .end. Regiao .data vazia.*/
			}


			/*Anda no codigo ate encontrar .end ou .text*/	
			for(;(dummyLine != NULL); dummyLine = dummyLine->nextLine){

				dummyToken = dummyLine->firstToken;

				/*Verifica se achou .text e nao achou outro*/
				if(!strcmp(dummyLine->firstToken->nome, ".text")){
					if(!textfound){
						textfix = 1;
						textfixLine = dummyLine;
						break;
					}
					else{
						return 24;/*Diretiva .text encontrada duas vezes*/
					}
				}
				/*Verifica se achou .end*/
				if(!strcmp(dummyLine->firstToken->nome, ".end")){
					endfound = 1;
					/*Verifica se a proxima token eh NULL*/
					if(dummyLine->firstToken->nextToken != NULL){
						return 13;
					}
					/*Terminou o .data*/
					break;
				}
				/*Verifica se achou .start*/
				if(!strcmp(dummyLine->firstToken->nome, ".start")){
					return 27;/*Diretiva .start encontrada na regiao .data.*/
				}


				/*Ve se a primeira token e diferente de NULL*/
				if(dummyLine->firstToken != NULL){
					/*Reinicia a flag*/					
					labelFound = 0;
					
					/*Pega a primeira token*/
					dummyToken = dummyLine->firstToken;

					/*Cria uma nova dirline e adiciona a tabela*/
					newDirLine(&dirline);
					addDirLineToDirTable(&dirtable, &dirline);

					/*Ordem dos ifs e importante para verificar labels seguidas de diretivas*/
					/*Ve se eh uma label*/
					if(isLabel(dummyToken->nome)){

						labelClear(&dummyToken->nome);

						newSimbolLine(&simbolLine, dummyToken->nome);
						simbolLine->valor = end; 
						simbolLine->istextsim = 0;
						simbolLine->name = addStrToStrTab(&strr, dummyToken->nome);
						simbol_num++;
						addSimbolLineToSimbolTable(&simbolLine, &simbolTable);

						if(dummyToken->nextToken != NULL){
							dummyToken = dummyToken->nextToken;
						}
						else{
							labelFound = 1;				
						}
					}
					/*Tenta criar uma diretiva com essa token*/
					int errorcode = 0;
					if(!(errorcode = addDirective(&dirline, dummyToken))){

						/*Atualiza os enderecos*/
						if(dirline->dirType == 1){
							end += ((DirDB*)dirline->directive)->size;
							data_size += ((DirDB*)dirline->directive)->size;
						}
						else if(dirline->dirType == 2){
							end += ((DirDS*)dirline->directive)->size;
							data_size += ((DirDS*)dirline->directive)->size;
						}



					}
					else if(errorcode){
						if(errorcode == 1)return 37; /*Diretiva usada na região .data nao existe.*/
						if(errorcode == 2)return 38; /*Diretiva usada na região .data seguida de nenhum valor.*/
						if(errorcode == 3)return 39; /*Elemento na diretiva usada na região .data maior que 8bits.*/
						if(errorcode == 5)return 40; /*Elemento na diretiva usada na região .data não é um número válido.*/

					}
					else if(!labelFound){
						return 28;
					}


				}/*End IF FIRST TOKEN NOT NULL*/
				else{
					return 22;/*Primeiro Token da Linha Igual a NULL. Provavel erro de preprocessamento.*/
				}
			}/*End For .data*/
			if(dummyLine == NULL){
				return 23;/*Programa chegou ao fim sem encontrar a diretiva .end*/
			}
		}
		else if(!strcmp(dummyLine->firstToken->nome, ".data") && datafound){
			return 29;/*Diretiva .data encontrada duas vezes*/
		}


	}/*Fim da primeira passagem do montador*/
	/*Verifica se achou .end*/
	if(!endfound){
		return 23;/*Programa chegou ao fim sem encontrar a diretiva .end*/
	}

	/*INICIO DA SEGUNDA PASSAGEM DO MONTADOR E FUNCOES RELACIONADAS*/

	/*Reinicia o contador de enderecos*/
	end = 0;

	/*Abre o arquivo de saida*/
	FILE *fp2;
	fp2 = fopen(arquivosaida,"wb+");
	int entry_address = 0;
	entry_address = findEntryAddress(&simbolTable, start_label);

	stab_num = simbol_num;
	/*Cria a lista Stab*/
	Stab* f_stab;
	newStab(&f_stab,0,addStrToStrTab(&strr, arquivoentrada),stab_num - 1,0);
	/*Cria o Table Header*/
	strtab_size = getStrTabSize(&strr);
	f_stab->n_value = strtab_size;

	if(simbol_num == 1){
		simbol_num = 0;
		strtab_size = 0;
		stabstr_size = 0;
		stab_num = 0;
	}

	/*Cria o cabecalho ELF*/
	ce(fp2, entry_address, data_size, data_address, text_size, text_address, relatext_num, strtab_size, simbol_num, stab_num);
	/*Imprime a regiao .data*/
	elfPrintData(fp2, dirtable);
	/*Imprime a regiao .text*/
	if(elfPrintText(fp2, mcTable, simbolTable, &text_address))
		return 30;
		

	/*Decide se tem simboltable a imprimir*/
	if(simbol_num != 1){
		/*Imprime a tabela de simbolos e relacionados*/
		elfPrintStrTab(fp2, &strr);
		updateStWithDt(&simbolTable, &defTable);
		elfPrintSimbolTable(fp2, &simbolTable, &useTable, &f_stab, start_label);
		elfPrintStab(fp2,&f_stab);
	}
	

	freeSimbolTable(&simbolTable);
	freeTokenTable(&tokenTable);
	freeMCTable(&mcTable);
	freeDirTable(&dirtable);
	freeUseTable(&useTable);
	freeDefinitionTable(&defTable);

	/*Fecha o arquivo de saída*/
	fclose(fp2);

	return 0;
}
