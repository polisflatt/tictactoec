CC=gcc
CFLAGS=-pthread

tictactoec: main.o
	$(CC) main.c -o tictactoec -pthread

install: tictactoec
	install -d /usr/bin/
	install -m 777 tictactoec /usr/bin