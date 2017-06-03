CC          =	gcc
# Flags that are sent to the compiler  change the std if you wish

CFLAGS      =	-Wall -std=c99 -pedantic -g

# List of source files to be included in compilation
SRC = linkedlist.c	\
      KTest.c

#compiles the main program
main: $(addprefix src/,$(SRC)) src/fourwaystop.c
	$(CC) $(CFLAGS) $(addprefix src/,$(SRC)) src/fourwaystop.c -o bin/fourwaystop

#run cppcheck
cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

#this is the target for building one main with a library
test: $(addprefix src/,$(SRC)) src/testing.c
	$(CC) $(CFLAGS) $(addprefix src/,$(SRC)) src/testing.c -o bin/test

doxy: Doxyfile
	doxygen

clean:
	rm -r bin/*
