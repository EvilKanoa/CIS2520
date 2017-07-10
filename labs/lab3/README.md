****************************************************
```
Kanoa Haley                             0956712
CIS*2520                                Lab 3
khaley@mail.uoguelph.ca                 June 25, 2017
```
****************************************************

*******************
Program Description
*******************
This is an implemention of a heap backed by an array as well as a test suite for the heap.

The array implemention simply uses an array of the required size and to find a nodes parent, or children, it performs calculations on the nodes index. The calculations are:
Parent of node      = (index + 1) / 2
Left child of node  = (2 * index) + 1
Right child of node = (2 * index) + 2

***********
Compilation
***********

Use `make` or `make test` to compile the testing program for the heap library. It will create an executable in the `bin/` directory called `test` which can then be ran without any arguments to run a suite of unit tests for the heap library.

Use `make cppcheck` to run the C style checker over every `.c` file in the project.

Use `make doxy` to run doxygen based on the Doxyfile and generate documentation for the project.

Use `make clean` to remove all built binary files and remove unnecessary files from the project.

************************************
Known Limitations, Issues and Errors
************************************
