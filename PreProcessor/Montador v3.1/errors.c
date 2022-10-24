/**
Armazena as funções e códigos de erro.

@author Murilo Marques Marinho
@version 1.2
*/
#include<stdio.h>
#include<stdlib.h>


/**
Codifica o parâmetro de entrada em um dos possíveis tipos de erro.
Erros podem ser apenas FATAIS.

*/
void error(int errorCode){

	switch (errorCode){
		/*Pré*/
		case 1: printf("\n\tErro no preprocessamento:\n\tErro na abertura do arquivo temporario temp.txt.\n");
		break;
		case 2: printf("\n\tErro no preprocessamento:\n\tCaractere invalido no arquivo de entrada.\n");
		break;

		/*Lex*/
		case 3: printf("\n\tErro na analise lexica:\n\tReadline buffer overflow: Linha grande demais.\n");
		break;
		case 4: printf("\n\tErro na analise lexica:\n\tErro na remocao do arquivo temporario.\n");
		break;
		case 5: printf("\n\tErro na analise lexica:\n\tDuas virgulas consecutivas.\n");
		break;
		case 6: printf("\n\tErro na analise lexica:\n\tToken buffer overflow: Token muito grande\n");
		break;

		/*Monta*/
		case 7: printf("\n\tErro na montagem:\n\tPrograma nao comeca com .begin.\n");
		break;
		case 8: printf("\n\tErro na montagem:\n\t.begin nao eh seguido de identificador.\n");
		break;		
		case 9: printf("\n\tErro na montagem:\n\tLinha de .begin possui uma Token a mais do que deveria.\n");
		break;
		case 10: printf("\n\tErro na montagem:\n\tPrograma nao possui nada alem de .begin.\n");
		break;
		case 11: printf("\n\tErro na montagem:\n\tUso incorreto da diretiva PUBLIC. Deve ser seguida de uma label.\n");
		break;
		case 12: printf("\n\tErro na montagem:\n\tUso incorreto da diretiva PUBLIC. Linha tem mais Tokens do que deveria.\n");
		break;
		case 13: printf("\n\tErro na montagem:\n\tUso incorreto da diretiva EXTERN. Deve ser seguida de uma label.\n");
		break;
		case 14: printf("\n\tErro na montagem:\n\tUso incorreto da diretiva EXTERN. Linha tem mais Tokens do que deveria.\n");
		break;
		case 15: printf("\n\tErro na montagem:\n\tEncontrado algo que nao eh uma diretiva PUBLIC ou EXTERN na regiao .begin do programa.\n");
		break;
		case 16: printf("\n\tErro na montagem:\n\tDiretiva .text nao deve ser seguida de nenhuma declaracao na mesma linha.\n");
		break;
		case 17: printf("\n\tErro na montagem:\n\tPrograma sem .end. Regiao .text vazia.\n");
		break;
		case 18: printf("\n\tErro na montagem:\n\tRegiao .data declarada duas vezes.\n");
		break;
		case 19: printf("\n\tErro na montagem:\n\tDiretiva .end nao deve ser seguida de nenhuma declaracao na mesma linha.\n");
		break;
		case 20: printf("\n\tErro na montagem:\n\tDiretiva .start encontrada mais de uma vez\n");
		break;
		case 21: printf("\n\tErro na montagem:\n\t.start deve ser seguido de um identificador.\n");
		break;
		case 22: printf("\n\tErro na montagem:\n\tLinha da diretiva .start tem mais Tokens do que deveria.\n");
		break;
		case 23: printf("\n\tErro na montagem:\n\tToken encontrada nao representa um argumento valido para a instrucao.\n");
		break;
		case 24: printf("\n\tErro na montagem:\n\tSintaxe de instrucao incorreta.\n");
		break;
		case 25: printf("\n\tErro na montagem:\n\tOperandos, de uma instrucao com 2 operandos, nao estao separados por virgula.\n");
		break;
		case 26: printf("\n\tErro na montagem:\n\tLinha de instrucao tem mais Tokens do que deveria\n");
		break;
		case 27: printf("\n\tErro na montagem:\n\tToken encontrada nao representa instrucao ou label.\n");
		break;
		case 28: printf("\n\tErro na montagem:\n\tPrimeiro Token da Linha Igual a NULL. Provavel erro de preprocessamento.\n");
		break;
		case 29: printf("\n\tErro na montagem:\n\tPrograma chegou ao fim sem encontrar a diretiva .end\n");
		break;
		case 30: printf("\n\tErro na montagem:\n\tDiretiva .text encontrada duas vezes.\n");
		break;
		case 31: printf("\n\tErro na montagem:\n\tDiretiva .data nao deve ser seguida de nenhuma declaracao na mesma linha.\n");
		break;
		case 32: printf("\n\tErro na montagem:\n\tPrograma sem .end. Regiao .data vazia.\n");
		break;
		case 33: printf("\n\tErro na montagem:\n\tDiretiva .start encontrada na regiao .data.\n");
		break;
		case 34: printf("\n\tErro na montagem:\n\tToken encontrada nao representa diretiva ou label..\n");
		break;
		case 35: printf("\n\tErro na montagem:\n\tDiretiva .data encontrada duas vezes.\n");
		break;
		case 36: printf("\n\tErro na montagem:\n\tLabel foi utilizada mas não foi declarada.\n");
		break;
		case 37: printf("\n\tErro na montagem:\n\tInstrucao aceita imediatos, mas houve overflow.\n");
		break;
		case 38: printf("\n\tErro na montagem:\n\tInstrucao aceita imediatos, mas houve underflow.\n");
		break;
		case 39: printf("\n\tErro na montagem:\n\tInstrucao aceita imediatos, mas o operando nao é um número válido.\n");
		break;
		case 40: printf("\n\tErro na montagem:\n\tInstrucao aceita endereços, mas houve overflow.\n");
		break;
		case 41: printf("\n\tErro na montagem:\n\tInstrucao aceita endereços, mas houve underflow.\n");
		break;
		case 42: printf("\n\tErro na montagem:\n\tInstrucao aceita endereços, mas o operando nao é um endereço válido.\n");
		break;
		case 43: printf("\n\tErro na montagem:\n\tDiretiva usada na região .data nao existe.\n");
		break;
		case 44: printf("\n\tErro na montagem:\n\tDiretiva usada na região .data seguida de nenhum valor.\n");
		break;
		case 45: printf("\n\tErro na montagem:\n\tElemento na diretiva usada na região .data maior que 8bits.\n");
		break;
		case 46: printf("\n\tErro na montagem:\n\tElemento na diretiva usada na região .data não é um número válido.\n");
		break;
		case 47: printf("\n\tErro na montagem:\n\tlabel invalida\n");
		break;
		default: printf("\n\tCodigo de erro sem traducao.\n");
		break;
	}
	exit(100);

}
