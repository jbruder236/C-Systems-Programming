CC=gcc
CFLAGS=-g --std=c99 -D_XOPEN_SOURCE=600
LFLAGS=-lpthread -lrt

all:	dot pism

dot: dot.c
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

pism: pism.c
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

clean:
	rm -rf  dot pism *.o
