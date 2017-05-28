CC          =	gcc
# Flags that are sent to the compiler  change the std if you wish

CFLAGS      =	-Wall -std=c99 -pedantic -g  


# note that cpp check reports memory leaks on these files that wouldn't really be leaks when the program was run
# don't blindly believe everything it tells you- check to make sure it is correct.  Usually it is
# but not always.   
#run cppcheck
cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

#this is the target for building one main with a library  
test: src/testing.c src/linkedlist.c src/KTest.c
	$(CC) $(CFLAGS) src/testing.c src/linkedlist.c src/KTest.c  -Iinclude -o bin/test

doxy: Doxyfile
	doxygen

clean:
	rm bin/*


