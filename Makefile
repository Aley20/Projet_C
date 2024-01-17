CC=gcc
CFLAGS=-Wall
DEPS=arbre.h
EXEC=test

all: $(EXEC)

arbre.o: arbre.c $(DEPS)
	$(CC) $(CFLAGS) -c arbre.c

test.o: test.c $(DEPS)
	$(CC) $(CFLAGS) -c test.c

test: test.o arbre.o
	$(CC) $(CFLAGS) -o test test.o arbre.o

clean:
	rm -rf $(EXEC) *.o
