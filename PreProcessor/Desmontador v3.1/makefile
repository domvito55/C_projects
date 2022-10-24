CFLAGS = -c -ansi -Wall
EXPATH = exemplos/
EXMPATH = exemplos_desmontados/
OBJS = desmontador.o fechaarquivos.o desmontar.o geratabela.o geracodigo.o gerarlabel.o buscartabela.o estruturas.o buscarlabel.o imprimecodigo.o imprimenatela.o estruturas_elf.o geracodigocomdebug.o desmontarcomdebug.o

desmontador: $(OBJS)
	gcc -o desmontador $(OBJS)

fechaarquivos.o: fechaarquivos.c
	gcc $(CFLAGS) fechaarquivos.c

desmontar.o: desmontar.c
	gcc $(CFLAGS) desmontar.c

desmontarcomdebug.o: desmontarcomdebug.c
	gcc $(CFLAGS) desmontarcomdebug.c

geratabela.o: geratabela.c
	gcc $(CFLAGS) geratabela.c

geracodigo.o: geracodigo.c
	gcc $(CFLAGS) geracodigo.c

geracodigocomdebug.o: geracodigocomdebug.c
	gcc $(CFLAGS) geracodigocomdebug.c

gerarlabel.o: gerarlabel.c
	gcc $(CFLAGS) gerarlabel.c

buscartabela.o: buscartabela.c
	gcc $(CFLAGS) buscartabela.c

buscarlabel.o: buscarlabel.c
	gcc $(CFLAGS) buscarlabel.c

estruturas.o: estruturas.c
	gcc $(CFLAGS) estruturas.c

estruturas_elf.o: estruturas_elf.c
	gcc $(CFLAGS) estruturas_elf.c

imprimecodigo.o: imprimecodigo.c
	gcc $(CFLAGS) imprimecodigo.c

imprimenatela.o: imprimenatela.c
	gcc $(CFLAGS) imprimenatela.c

desmontador.o: desmontador.c desmontador.h
	gcc $(CFLAGS) desmontador.c

clean:
	rm -f desmontador *.o codigo_assembly.txt

desmontar:
	./desmontador -g $(EXPATH)ex1_montado $(EXMPATH)ex1_desmontado.txt
	./desmontador -g $(EXPATH)ex2_montado $(EXMPATH)ex2_desmontado.txt
	./desmontador -g $(EXPATH)ex3_montado $(EXMPATH)ex3_desmontado.txt
	./desmontador -g $(EXPATH)ex4_montado $(EXMPATH)ex4_desmontado.txt
	./desmontador -g $(EXPATH)ex5_montado $(EXMPATH)ex5_desmontado.txt
	./desmontador -g $(EXPATH)ex_extra_1_montado $(EXMPATH)ex_extra_1_desmontado.txt
	./desmontador -g $(EXPATH)ex_extra_2_montado $(EXMPATH)ex_extra_2_desmontado.txt
	./desmontador -g $(EXPATH)ex_extra_3_montado $(EXMPATH)ex_extra_3_desmontado.txt
	./desmontador -g $(EXPATH)ex_extra_4_montado $(EXMPATH)ex_extra_4_desmontado.txt
	./desmontador -g $(EXPATH)ex_extra_5_montado $(EXMPATH)ex_extra_5_desmontado.txt

exemplos_clean:
	cd $(EXMPATH);\
	rm ex1_desmontado.txt ex2_desmontado.txt ex3_desmontado.txt ex4_desmontado.txt ex5_desmontado.txt ex_extra_1_desmontado.txt ex_extra_2_desmontado.txt ex_extra_3_desmontado.txt ex_extra_4_desmontado.txt ex_extra_5_desmontado.txt;\
	cd ..;\

