CC=clang
LDFLAGS=-lncurses -llua


all: lncurses.so

lncurses.so: lncurses.c
	$(CC) -Wall -shared -o lncurses.so -fPIC lncurses.c $(LDFLAGS)

