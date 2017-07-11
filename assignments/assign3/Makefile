CC          =	gcc
# flags that are sent to the compiler  change the std if you wish
CFLAGS      =	-Wall -ansi -pedantic -g

# list of source files to be included in compilation
SRC = heap.c

# this is the target for building the main program
program: $(addprefix src/,$(SRC)) src/priorityQueue.c
	$(CC) $(CFLAGS) -lncurses -lm -Iinclude $(addprefix src/,$(SRC)) src/priorityQueue.c -o bin/vault

# this is the target for building the testing binary
test: $(addprefix src/,$(SRC)) src/testing.c
	$(CC) $(CFLAGS) -lncurses -lm -Iinclude $(addprefix src/,$(SRC)) src/testing.c -o bin/test

# run cppcheck
cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm -rf bin/*
