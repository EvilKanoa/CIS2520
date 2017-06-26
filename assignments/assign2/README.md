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
This is a simple password vault for a single-user style setup. You may use it to store any passwords you wish. The vault program makes use of a hash table for faster use and more reliable performance.

***********
Compilation
***********
Use `make` or `make program` to compile the main password vault application. It will create an executable in the `bin/` directory called program which can be ran without any arguments to start the password vault UI.

Use `make test` to compile the testing program for the hashing function. It will create an executable in the `bin/` directory called `test` which can then be ran without any arguments to generate collision and hash information for ~60 top 100 sites to verify performance of the hashing function.

Use `make cppcheck` to run the C style checker over every `.c` file in the project.

Use `make doxy` to run doxygen based on the Doxyfile and generate documentation for the project.

Use `make clean` to remove all built binary files and remove unnecessary files from the project.

************************************
Known Limitations, Issues and Errors
************************************
Since this is only a prototype, it is quite unsecure. Neither the configuration file (`config.txt`) holding the master password, nor any of the password vault files are encrypted in any way. On the contrary, they are actually quite readily readable by prying eyes. I recommend that this is never used in a real-world situation in its current form and is instead used as an educational aid.

***************************
Data Storage Specifications
***************************
Each indivdual password vault file is stored in a JSON format. This may seem abnormal for a secruity application like a password manager, but given that this is a prototype and only an assignment for school, this method is ideal since it is easy to read in plain-text format while also being easy to extract for testing purposes.

If you are unaware of the JSON format, the only portions being used here is a single object of key-value pairs.

```JSON
{
    "descriptor1": "password1",
    "myDescriptor": "myPassword"
}
```

****************************
Hashing Function Performance
****************************
The provided testing program will create some sample data to view how well the hashing function performs. The data used for the testing program is ~60 of the top 100 web sites world-wide. Given that the hashing function is designed for a password manager, this was deemed reletively appropriate data.

**********
Complexity
**********
The Big O notation for each HashTableAPI function.

createTable: O(n)
- The creation function actually takes time to remove any garbage values from the table array which results in a O(n) creation time.

createNode: O(1)
- This function only allocates and sets up a node which is a constant time process.

destroyTable: O(n)
- This function has to traverse the table to free every node.

insertData: O(n)
- The upper limit is O(n) IF every single other piece of data in the table has collided in the same location, this function can (and normally should) be constant time.

removeData: O(n)
- The same issue as insertData applies here. Typically it is constant time but it has the possibility of being O(n).

lookupData: O(n)
- This function may have to iterate over every other node, but that is uncommon in the real world.
