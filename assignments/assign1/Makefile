CC          =	gcc
# Flags that are sent to the compiler  change the std if you wish

CFLAGS      =	-Wall -std=c99 -pedantic -g  

# List of source files to be included in compilation
SRC = testing.c		\
      linkedlist.c	\
      KTest.c

# note that cpp check reports memory leaks on these files that wouldn't really be leaks when the program was run
# don't blindly believe everything it tells you- check to make sure it is correct.  Usually it is
# but not always.   
#run cppcheck
cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

#this is the target for building one main with a library  
test: $(addprefix src/,$(SRC))
	$(CC) $(CFLAGS) $(addprefix src/,$(SRC)) -o bin/test

doxy: Doxyfile
	doxygen

clean:
	rm bin/*


