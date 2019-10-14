all: comprime descomprime

comprime: arvore.o lista.o codigo.o comprime.c
	c99 -g arvore.o lista.o codigo.o comprime.c -o comprime
descomprime: arvore.o lista.o codigo.o descomprime.c
	c99 -g arvore.o lista.o codigo.o descomprime.c -o descomprime
arvore.o: arvore.h arvore.c
	c99 -c arvore.c
lista.o: lista.h lista.c
	c99 -c lista.c
codigo.o: codigo.h codigo.c
	c99 -c codigo.c

clean: 
	rm -rf *.o comprime descomprime