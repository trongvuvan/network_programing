CFLAGS = -c -Wall
CC = gcc
LIBS = -lm 

all: exercise2
exercise2: main.o subject.o menu.o
		${CC} main.o menu.o subject.o -o exercise2
subject.o: subject.c
		${CC} ${CFLAGS} subject.c
menu.o: menu.c
		${CC} ${CFLAGS} menu.c	
clean:
		rm - f *.o *~