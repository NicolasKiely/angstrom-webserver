CFLAGS=-Wall -std=c99

all: anghttpd

# Targets
anghttpd: angstrom.o StringIO.o
	gcc $(CFLAGS) -o anghttpd angstrom.o StringIO.o

# Object files
anstrom.o: angstrom.c StringIO.h

StringIO.o: StringIO.h
