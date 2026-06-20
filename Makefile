#NOTE: I enable gdb flag in GCC for testing purposes. Remove after use.


CC=gcc
CFLAGS=-Wall -std=c11 -g
LIBS=-lncurses

SRC=$(wildcard src/*.c)

all:
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o spotui

clean:
	rm -f spotui

