# Makefile for 'hashtable' module
#
# Andres Ibarra, January 2022

OBJS = hashtabletest.o hash.o hashtable.o ../set/set.o ../lib/file.o ../lib/mem.o 
LIBS =

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

hashtabletest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hashtabletest.o: hashtable.h ../set/set.h ../lib/file.h
hashtable.o: hashtable.h ../set/set.h
../lib/file.o: ../lib/file.h

.PHONY: test valgrind clean

# expects a file `testWords` to exist; it can contain any text.
valgrind: hashtabletest testWords
	$(VALGRIND) ./hashtabletest < testWords

# expects a file `testWords` to exist; it can contain any text.
test:hashtabletest testWords
	./hashtabletest < testWords

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f hashtabletest
	rm -f core
