CC=gcc
CFLAGS=-I./include -Wall -Wextra -pedantic -std=c99 -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition
BINARIES=main

all : ${BINARIES}

% : %.c
	${CC} ${CFLAGS} $< -o $@

assembly : main.c
	${CC} ${CFLAGS} -S main.c -o $@.asm

clean :
	rm *.o

