.PHONY: all
CFLAGS=-g -pedantic -Werror
CC=gcc

all: mymail

mymail: mymail.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o mymail *~
