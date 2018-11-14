CC = gcc
CFLAGS = -O2

main: main.o myfunctions.o
	$(CC) $(CFLAGS) main.o myfunctions.o -o main -lgmp -lm

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

myfunctions.o: myfunctions.c
	$(CC) $(CFLAGS) -c myfunctions.c