# list/Makefile
#
# Makefile for list implementation and test file.
#
# <Author>
//list: list.c main.c
//	gcc list.c main.c -o list

CC = gcc
CFLAGS = -Wall -g -std=c99

all: list

list: main.o list.o
	$(CC) $(CFLAGS) -o list main.o list.o

main.o: main.c list.h
	$(CC) $(CFLAGS) -c main.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

clean:
	rm -f *.o list

