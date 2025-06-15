CC=gcc
CFLAGS=-Wall -g

all: manager worker main

manager:
	$(CC) -c manager.c
	ar rcs libmanager.a manager.o

worker:
	$(CC) -c worker.c
	ar rcs libworker.a worker.o

main:
	$(CC) -o projekt main.c -L. -lmanager -lworker

clean:
	rm -f *.o *.a projekt
