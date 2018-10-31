CC = gcc
CFLAGS = -O2

main: main.o
	$(CC) $(CFLAGS) main.o -o main -lgmp -lm

main.o: main.c
	$(CC) $(CFLAGS) -c main.c