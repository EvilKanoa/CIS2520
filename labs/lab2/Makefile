CC          =	gcc
# Flags that are sent to the compiler  change the std if you wish

CFLAGS      =	-Wall -ansi -pedantic -g

# List of source files to be included in compilation
SRC = KTest.c \
	  hashtable.c

#this is the target for building one main with a library
test: $(addprefix src/,$(SRC)) src/testing.c
	$(CC) $(CFLAGS) -Iinclude $(addprefix src/,$(SRC)) src/testing.c -o bin/test

#run cppcheck
cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm -r bin/*
