CC = gcc
CFLAGS = -O2

main: main.o
	$(CC) $(CFLAGS) main.o -o main -lgmp

main.o: main.c
	$(CC) $(CFLAGS) -c main.c