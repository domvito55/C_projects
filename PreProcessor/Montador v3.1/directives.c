/**
Armazenas as funções relativas a diretivas.

@author Murilo Marques Marinho
@version 1.2
*/


#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include"token.h"
#include"directives.h"
#include"dirline.h"
#include"dirtable.h"
#include"instrucao.h"

/**
Cria uma nova DirDS.

@param dirds A DirDS que sera alocada
@param nome A String que representara o valor numerico dessa DirDS
@return 0 Sem erros.
	1 Overflow.
	2 Underflow.
	3 Erro na conversão.
*/
int newDirDS(DirDS** dirds, char* nome){
	DirDS* newdirds;

	newdirds = (DirDS*)malloc(sizeof(DirDS));

	/*Verifica se é um número hexadecimal ou decimal válido*/
	int imd = strToPosInt(nome);
	if(imd < 0){
		return (-1*imd);
	}

	newdirds->size = imd;

	(*dirds) = newdirds;

	return 0;
}

/**
Cria uma nova DirDBPart

@param dirdbpart A DirDBPart que sera alocada
@param value O valor numerico que sera adicionado a essa DirDBPart
*/
void newDirDBPart(DirDBPart** dirdbpart, int value){
	DirDBPart* newdirdbpart;	

	newdirdbpart = (DirDBPart*)malloc(sizeof(DirDBPart));
	newdirdbpart->value = value;
	newdirdbpart->nextValue = NULL;

	(*dirdbpart) = newdirdbpart;
}


/**
Adiciona uma DirDBPart a uma DirDB

@param dirdb a DirDB na qual se quer adicionar a DirDBPart
@param nome a String que representa o valor numerico a ser adicionado
@return 0 Sem erros.
	1 Overflow.
	2 Underflow.
	3 Erro na conversão.
*/
int addDirDBPart(DirDB** dirdb, char* nome){

	/*Verifica se é um número hexadecimal ou decimal válido*/
	int imd = strToPosInt(nome);
	if(imd < 0){
		return (-1*imd);
	}

	/*Cria nova DirDBPart*/	
	DirDBPart* dirdbpart;
	newDirDBPart(&dirdbpart, imd);

	/*Adiciona em dirdb*/
	/*Se o promeiro elemento for NULL*/
	if((*dirdb)->firstValue == NULL){
		(*dirdb)->firstValue = dirdbpart;
	}
	/*Se nao...*/
	else{
		DirDBPart* searcher = NULL;
		for(searcher = (*dirdb)->firstValue; searcher->nextValue != NULL; searcher = searcher->nextValue);
		searcher->nextValue = dirdbpart;
	}

	(*dirdb)->size++;

	return 0;
}

/**
@brief Cria uma nova DirDB

Recebe como entrada uma Token. Essa Token tem que representar o primeiro valor da diretiva DB.
Automaticamente percorre ate o final da cadeia de Tokens e verifica, tambem, a presenca das virgulas.

@param dirdb O ponteiro para a nova DirDB alocada
@param token A token na linha cujo nome representa o primeiro valor da DirDB
@return 0 Sem erros.
	1 Overflow.
	2 Underflow.
	3 Erro na conversão.
	4 Não é devidamente dividido em vírgulas. 
*/
int newDirDB(DirDB** dirdb,struct Token* token){
	int error = 0;	

	DirDB* newdirdb;
	struct Token *dummyToken = token;

	newdirdb = (DirDB*)malloc(sizeof(struct DirDB));
	newdirdb->size = 0;
	newdirdb->firstValue = NULL;
	(*dirdb) = newdirdb;

	/*Roda nas tokens adicionando os valores*/
	for(dummyToken = token; dummyToken != NULL; dummyToken = dummyToken->nextToken){
		/*Adiciona o valor*/
		error = addDirDBPart(dirdb, dummyToken->nome);
		if(error)
			return error;

		/*Ve se a proxima token eh uma virgula*/
		if(dummyToken->nextToken != NULL){
			if(!strcmp(",",dummyToken->nextToken->nome)){
				dummyToken = dummyToken->nextToken;
			}
			else{
				/*Erro: nao é separado por vírgulas.*/
				return 4;
			}
		}
	}

	return 0;
}


/**
Adiciona uma nova Directive a DirLine

Ajusta automaticamente o tipo da DirLine para que o programa saiba de qual tipo e seu ponteiro directive.
Verifica automaticamente se a Token representa uma diretiva valida.
Necessario ter uma Token como entrada para funcionar em par com a diretiva DB.

@param dirline A DirLine na qual se deseja adicionar a Directive
@param Token a Token que pode representar essa diretiva
@return 0 Se nao houver erros.
	1 Se a diretiva nao existe.
	2 Se a diretiva não é seguida de nenhum valor.
	3 Overflow.
	4 Underflow.
	5 Erro na conversão.
*/
int addDirective(DirLine **dirline, struct Token* token){

	char* holder = token->nome;

	if(token->nextToken == NULL){
		return 2;
	}
	token = token->nextToken;
	
	int error = 0;
	if(!strcmp(holder, "db")){
		DirDB* dirdb;
		error = newDirDB(&dirdb, token);
		if(error){
			return (error + 2);
		}
		(*dirline)->dirType = 1;
		(*dirline)->directive = dirdb;
		return 0;
	}
	else if(!strcmp(holder, "ds")){
		DirDS* dirds;
		error = newDirDS(&dirds, token->nome);
		if(error){
			return (error + 2);
		}
		(*dirline)->dirType = 2;
		(*dirline)->directive = dirds;
		return 0;
	}
	/*Adicione novas diretivas aqui*/

	return 1;
}

/**
Libera a DirDB da memoria

@param dd a DirDB que sera liberada
*/
void freeDirDB(DirDB** dd){
	DirDBPart *ddp;
  
	if((*dd)->firstValue != NULL){
		for(;;){
			ddp = (*dd)->firstValue;
			if((*dd)->firstValue->nextValue == NULL){
				free((*dd)->firstValue);
				free(*dd);
				*dd = NULL;
				return;
			}
			(*dd)->firstValue = (*dd)->firstValue->nextValue;
			ddp->nextValue = NULL;
			free(ddp);
		}

	}
	else{
		free(*dd);
		*dd = NULL;
	}
}

