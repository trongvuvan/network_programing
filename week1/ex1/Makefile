CFLAGS = -c -Wall
CC = gcc
LIBS = -lm 

all: exercise1
exercise1: main.o hazchem.o
		${CC} main.o hazchem.o -o exercise1

subject.o: subject.c
		${CC} ${CFLAGS} hazchem.c
	
clean:
		rm - f *.o *~