CFLAGS = -c -Wall
CC = gcc
LIBS = -lm 

all: resolver
resolver: main.o host.o
		${CC} main.o host.o -o resolver
host.o: host.c
		${CC} ${CFLAGS} host.c
clean:
		rm - f *.o *~