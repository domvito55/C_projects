CFLAGS = -c -g -ansi -Wall
EXPATH = exemplos/
EXMPATH = exemplos_desmontados/
OBJS = desmontador.o fechaarquivos.o desmontar.o geratabela.o geracodigo.o gerarlabel.o buscartabela.o estruturas.o buscarlabel.o imprimecodigo.o imprimenatela.o estruturas_elf.o geracodigocomdebug.o desmontarcomdebug.o

ligar: b.o le.o preenche.o tipar.o imprime.o cria.o sym.o inverte.o atualizar.o rela.o buscar.o
	gcc -o ligadorb b.o le.o preenche.o tipar.o imprime.o cria.o sym.o inverte.o atualizar.o rela.o buscar.o
b.o: b.c
	gcc $(CFLAGS) b.c

le.o: le.c
	gcc $(CFLAGS) le.c
	
preenche.o: preenche.c
	gcc $(CFLAGS) preenche.c

tipar.o: tipar.c
	gcc $(CFLAGS) tipar.c

imprime.o: imprime.c
	gcc $(CFLAGS) imprime.c

cria.o: cria.c
	gcc $(CFLAGS) cria.c

sym.o: sym.c
	gcc $(CFLAGS) sym.c

inverte.o: inverte.c
	gcc $(CFLAGS) inverte.c

atualizar.o: atualizar.c
	gcc $(CFLAGS) atualizar.c

rela.o: rela.c
	gcc $(CFLAGS) rela.c

buscar.o: buscar.c
	gcc $(CFLAGS) buscar.c

clean:
	rm -f b.o le.o preencheSH.o ligadorb tipar.o imprime.o cria.o sym.o preenche.o rela.o atualizar.o buscar.o inverte.o

