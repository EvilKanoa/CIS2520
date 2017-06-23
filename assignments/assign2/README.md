****************************************************
```
Kanoa Haley                             0956712
CIS*2520                                Assignment 3
khaley@mail.uoguelph.ca                 June 25, 2017
```
****************************************************

*******************
Program Description
*******************
This is a simple password vault for a single-user style setup. You may use it to store any passwords you wish and the passwords themselves will be encrypted using MD5. The vault program makes use of a hash table for faster use and more reliable performance.

***********
Compilation
***********
Use `make` or `make program` to compile the main password vault application. It will create an executable in the `bin/` directory called program which can be ran without any arguments to start the password vault UI.

Use `make test` to compile the testing program and the hash table API. It will create an executable in the `bin/` directory called `test` which can then be ran without any arguments to run unit tests on the API and display the results.

Use `make cppcheck` to run the C style checker over every `.c` file in the project.

Use `make doxy` to run doxygen based on the Doxyfile and generate documentation for the project.

Use `make clean` to remove all built binary files and remove unnecessary files from the project.

************************************
Known Limitations, Issues and Errors
************************************
