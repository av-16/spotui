
CC=gcc
CFLAGS=-Wall -std=c11
LIBS=-lncurses

SRC=$(wildcard src/*.c)

all:
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o spotui

clean:
	rm -f spotui

