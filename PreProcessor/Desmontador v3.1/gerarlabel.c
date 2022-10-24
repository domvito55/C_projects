#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"desmontador.h"
/*
**	___________________gerarlabel.c___________________
**		
**	Gera a estrutura de dados com os endereços e as labels utilizadas no código e retorna a label do endereço requerido nos parâmetros.
**	
**	___________________gerarlabel.c___________________
**/

char *gerarnomes(labelS *pinicio);

char *gerarlabel(labelS **p_label, int endereco, char *nome) {
	labelS *p1, *p2;
	/*Procura endereço em p_label*/
	p1=buscarlabel(*p_label, endereco);	

/*============================================================
====================Label existe?=============================
============================================================*/
	if(p1!=NULL){
		/*============================================================
		====================Retorna a label===========================
		============================================================*/
		return (p1->label);
	}
	/*Se não existe:*/
	else{
		/*============================================================
		====================Gera a label==============================
		============================================================*/
		if((*p_label)==NULL){
			(*p_label)=malloc(sizeof(labelS));
			if(nome==0)
				(*p_label)->label="start";
			else
				(*p_label)->label=nome;
			((*p_label)->endereco)=endereco;
			(*p_label)->next=NULL;
			return ((*p_label)->label);
		}
		/*Se p_label não vazia:*/
		else{
			p2=malloc(sizeof(labelS));
			if(nome==0)
				p2->label=gerarnomes(*p_label);
			else
				p2->label=nome;
			p2->endereco=endereco;
			p2->next=NULL;

			p1=(*p_label);
			while((p1->next)!=NULL){
				p1=p1->next;
			}
			p1->next=p2;

			return (p2->label);
		}
	}
}

char *gerarnomes(labelS *pinicio){
	labelS *p_aux;
	char *pokemon;
	int contador=0;
	char *buffer;

	pokemon=malloc(10*sizeof(char));
	buffer=malloc(4*sizeof(char));

	p_aux=pinicio;
	while(p_aux!=NULL){
		contador++;
		p_aux=p_aux->next;
	}

	if(contador==1){
		pokemon="Raichu";
		return pokemon;
	} else if(contador==2){
		pokemon="Pikach";
		return pokemon;
	} else if(contador==3){
		pokemon="Charma";
		return pokemon;
	} else if(contador==4){
		pokemon="Squirt";
		return pokemon;
	} else if(contador==5){
		pokemon="Caterp";
		return pokemon;
	} else if(contador==6){
		pokemon="Pidgey";
		return pokemon;
	} else if(contador==7){
		pokemon="Jiggly";
		return pokemon;
	} else if(contador==8){
		pokemon="Meowth";
		return pokemon;
	} else if(contador==9){
		pokemon="Abra";
		return pokemon;
	} else if(contador==10){
		pokemon="Tentac";
		return pokemon;
	} else if(contador==11){
		pokemon="Dragon";
		return pokemon;
	} else if(contador==12){
		pokemon="Horsea";
		return pokemon;
	} else if(contador==13){
		pokemon="Eevee";
		return pokemon;
	} else if(contador==14){
		pokemon="Snorla";
		return pokemon;
	} else if(contador==15){
		pokemon="Mewxxx";
		return pokemon;
	} else if(contador==16){
		pokemon="Murilo";
		return pokemon;
	} else if(contador==17){
		pokemon="Anapuf";
		return pokemon;
	} else if(contador==18){
		pokemon="Ivande";
		return pokemon;
	} else if(contador==19){
		pokemon="Danico";
		return pokemon;
	} else if(contador==20){
		pokemon="Leosau";
		return pokemon;
	} else if(contador==21){
		pokemon="Blasto";
		return pokemon;
	} else if(contador==22){
		pokemon="Metapo";
		return pokemon;
	} else if(contador==23){
		pokemon="Butter";
		return pokemon;
	} else if(contador==24){
		pokemon="Weedle";
		return pokemon;
	} else if(contador==25){
		pokemon="Kakuna";
		return pokemon;
	} else if(contador==26){
		pokemon="Beedri";
		return pokemon;
	} else if(contador==27){
		pokemon="Pidgeo";
		return pokemon;
	} else if(contador==28){
		pokemon="Pidgeo";
		return pokemon;
	} else if(contador==29){
		pokemon="Rattat";
		return pokemon;
	} else if(contador==30){
		pokemon="Ratica";
		return pokemon;
	} else{
		sprintf(buffer, "%d", contador);
		sprintf(pokemon, "%s%s", "Pokemon", buffer);
		return pokemon;
	}
}
