CC          =	gcc
# flags that are sent to the compiler  change the std if you wish
CFLAGS      =	-Wall -ansi -pedantic -g

# list of source files to be included in compilation
SRC = gamesCsvModel.c \
	  screens.c \
	  tree.c \
	  linkedlist.c
PROGRAM = src/posSystem.c

# this is the target for building the testing binary
program: $(addprefix src/,$(SRC)) $(PROGRAM)
	$(CC) $(CFLAGS) -lm -Iinclude $(addprefix src/,$(SRC)) $(PROGRAM) -o bin/program

# run cppcheck
cppcheck:
	cppcheck --enable=all --language=c --std=c89 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: Doxyfile
	doxygen

clean:
	rm -rf bin/*
