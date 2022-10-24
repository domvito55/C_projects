#Montarilo MAKEFILE
#MURILO MARQUES MARINHO 08/37369
#VERSION 2.0
CFLAGS = -c -ansi -Wall
EXPATH = exemplos/
EXMPATH = exemplos_montados/

montador: montador.o errors.o preProcessor.o lexicAnaliser.o line.o token.o tokenTable.o mctable.o mcline.o simboltable.o simbolline.o instrucao.o directives.o dirline.o dirtable.o definitionline.o definitiontable.o usetable.o useline.o ce.o elfprint.o funcmice.o
	gcc -o montador line.o token.o tokenTable.o montador.o  mctable.o mcline.o simboltable.o simbolline.o instrucao.o errors.o lexicAnaliser.o preProcessor.o directives.o dirline.o dirtable.o definitionline.o definitiontable.o usetable.o useline.o ce.o elfprint.o funcmice.o
run:
	./montador ex1.txt ex1_montado.txt ;\
	readelf -a love

exemplos: ex1 ex2 ex3 ex4 ex5 ex6_1 ex6_2 ex1_ex ex2_ex ex3_ex ex4_ex ex5_ex 

ex1:
	./montador $(EXPATH)ex1.txt $(EXMPATH)ex1_montado
ex2:
	./montador $(EXPATH)ex2.txt $(EXMPATH)ex2_montado
ex3:
	./montador $(EXPATH)ex3.txt $(EXMPATH)ex3_montado
ex4:
	./montador $(EXPATH)ex4.txt $(EXMPATH)ex4_montado
ex5:
	./montador $(EXPATH)ex5.txt $(EXMPATH)ex5_montado
ex6_1:
	./montador $(EXPATH)ex6_1.txt $(EXMPATH)ex6_1_montado
ex6_2:
	./montador $(EXPATH)ex6_2.txt $(EXMPATH)ex6_2_montado
ex1_ex:
	./montador $(EXPATH)ex_extra_1.txt $(EXMPATH)ex_extra_1_montado
ex2_ex:
	./montador $(EXPATH)ex_extra_2.txt $(EXMPATH)ex_extra_2_montado
ex3_ex:
	./montador $(EXPATH)ex_extra_3.txt $(EXMPATH)ex_extra_3_montado
ex4_ex:
	./montador $(EXPATH)ex_extra_4.txt $(EXMPATH)ex_extra_4_montado
ex5_ex:
	./montador $(EXPATH)ex_extra_5.txt $(EXMPATH)ex_extra_5_montado

exemplos_clean:
	cd exemplos_montados ;\
	rm -f ex1_montado ex2_montado ex3_montado ex4_montado ex5_montado ex6_1_montado ex6_2_montado ex_extra_1_montado ex_extra_2_montado ex_extra_3_montado ex_extra_4_montado ex_extra_5_montado ;\
	cd .. ;\

debug:
	valgrind --track-origins=yes --leak-check=full -v ./montador codigo.txt codigomaquina.txt

montador.o: montador.c
	gcc $(CFLAGS) montador.c 

errors.o: errors.c errors.h
	gcc $(CFLAGS) errors.c

preProcessor.o: preProcessor.c preProcessor.h errors.h 
	gcc $(CFLAGS) preProcessor.c

line.o: line.c line.h token.h
	gcc $(CFLAGS) line.c

token.o: token.c token.h
	gcc $(CFLAGS) token.c

tokenTable.o: tokenTable.c tokenTable.h line.h token.h
	gcc $(CFLAGS) tokenTable.c

mcline.o: mcline.c mcline.h
	gcc $(CFLAGS) mcline.c

mctable.o: mctable.c mctable.h mcline.h
	gcc $(CFLAGS) mctable.c

simbolline.o: simbolline.c simbolline.h
	gcc $(CFLAGS) simbolline.c

simboltable.o: simboltable.c simboltable.h simbolline.h
	gcc $(CFLAGS) simboltable.c

lexicAnaliser.o: lexicAnaliser.c lexicAnaliser.h
	gcc $(CFLAGS) lexicAnaliser.c

instrucao.o: instrucao.c instrucao.h
	gcc $(CFLAGS) instrucao.c

directives.o: directives.c directives.h token.h dirline.h dirtable.h
	gcc $(CFLAGS) directives.c

dirline.o: dirline.c dirline.h
	gcc $(CFLAGS) dirline.c

dirtable.o: dirtable.c dirtable.h
	gcc $(CFLAGS) dirtable.c

definitionline.o: definitionline.c definitionline.h
	gcc $(CFLAGS) definitionline.c

definitiontable.o: definitiontable.c definitiontable.h
	gcc $(CFLAGS) definitiontable.c

useline.o: useline.c useline.h
	gcc $(CFLAGS) useline.c

usetable.o: usetable.c usetable.h
	gcc $(CFLAGS) usetable.c

ce.o: ce.c ce.h
	gcc $(CFLAGS) ce.c

elfprint.o: elfprint.c elfprint.h
	gcc $(CFLAGS) elfprint.c
	
funcmice.o: funcmice.c funcmice.h
	gcc  $(CFLAGS) funcmice.c

clean:
	rm -f montador.o montador instrucao.o errors.o preProcessor.o line.o token.o tokenTable.o lexicAnaliser.o mctable.o mcline.o simboltable.o simbolline.o dirtable.o dirline.o directives.o definitionline.o definitiontable.o usetable.o useline.o ce.o elfprint.o
