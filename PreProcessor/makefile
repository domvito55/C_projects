CC = gcc 
AR = ar rcs 
CFLAGS = -c -Wall -g -O2 -I. 
OBJECTS = determinante.o fatorial.o media.o 
PROG = testa 
LIB = matematica 
LIBNAME = lib$(LIB).a 
RM = rm ­f 
$(LIB): $(OBJECTS)
	$(AR) $(LIBNAME)  $(OBJECTS) 
$(PROG): $(PROG).c 
	$(CC) $(CFLAGS) $(PROG).c ­o $(PROG).o 
	$(CC)  $(PROG).o -l$(LIB) ­L. ­o $(PROG) 
%.o : %.c 
	$(CC) $(CFLAGS) ­c $< 

