all: fila_fifo.o logtree.o escalonador.o main.o
	gcc fila_fifo.o logtree.o escalonador.o main.o -o exe

main: main.c
	gcc -c main.c -o main.o

fila_fifo: fila_fifo.c
	gcc -c fila_fifo.c -o fila_fifo.o

logtree: logtree.c
	gcc -c logtree.c -o logtree.o

escalonador: escalonador.c
	gcc -c escalonador.c -o escalonador.o

clear:
	rm *.o