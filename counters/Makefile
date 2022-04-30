# Makefile for 'counters' module
#
# Andres Ibarra, January 2022

OBJS = counterstest.o counters.o ../lib/file.o ../lib/mem.o 
LIBS =

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

counterstest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

counterstest.o: counters.h ../lib/file.h
counters.o: counters.h
../lib/file.o: ../lib/file.h

.PHONY: test valgrind clean

# expects a file `testNums` to exist; it can contain any text.
test: counterstest testNums
	./counterstest < testNums

# expects a file `testNums` to exist; it can contain any text.
valgrind: counterstest testNums
	$(VALGRIND) ./counterstest < testNums

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f settest
	rm -f core
