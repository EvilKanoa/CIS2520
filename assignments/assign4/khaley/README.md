****************************************************
```
Kanoa Haley                             0956712
CIS*2520                                Assignment 4
khaley@mail.uoguelph.ca                 August 7, 2017
```
****************************************************

*******************
Program Description
*******************
A barebones point of sale (POS) system to be used for a video game inventory. Allows the user to view their inventory and create customer invoices which update the inventory. Provides the ability to search and delete from the inventory.

The addition I chose to implement was loading another inventory file into the current program, and hence file. I added it as another option on the main menu that simply pulls all the inventory from any file the user specifies into the running application and causes the main inventory file to be updated on exit.

***********
Compilation
***********

Use `make` or `make program` to compile the main program for the POS system. It will create an executable in the `bin/` directory called `program` which can then be ran without any arguments to run the system.

Use `make cppcheck` to run the C style checker over every `.c` file in the project.

Use `make doxy` to run doxygen based on the Doxyfile and generate documentation for the project.

Use `make clean` to remove all built binary files and remove unnecessary files from the project.

**********
Complexity
**********
### The Big O notation for each TreeADT function. ###

createBalancedBinTree: O(1)
- This function allocates a new binary tree.
- The size is irrelevent at this point.

createBalancedBinNode: O(1)
- Creates a new node for a tree.
- The size of the tree has no effect on node creation.

destroyBalancedBinTree: O(n)
- Has to traverse the entire tree to delete every node.

treeInsertNode: O(log n)
- Has to traverse the entire tree to find the correct insert spot and rebalance the tree.

treeDeleteNode: O(log n)
- Has to traverse the entire tree to find the correct node to delete and then rebalance the tree.

treeIsEmpty: O(1)
- Checks if a root node exists.

treeHasTwoChildren: O(1)
- Checks a nodes two children.

treeFindNode: O(log n)
- Has to traverse all levels of a tree to find a node.

treeFindMin: O(log n)
- Similar to treeFindNode.
- Has to traverse the all levels of a tree to find the minimum node.

treeFindMax: O(log n)
- Similar to treeFindNode.
- Has to traverse the all levels of a tree to find the maximum node.

treeInOrderPrint: O(n)
- Prints all nodes recursively.
- Has to traverse the entire tree to print every node.

treePreOrderPrint: O(n)
- Prints all nodes recursively.
- Has to traverse the entire tree to print every node.

treePostOrderPrint: O(n)
- Prints all nodes recursively.
- Has to traverse the entire tree to print every node.

destroyBalancedBinTreeNodeTree: O(n)
- Used by destroyBalancedBinTree.
- Has to traverse the entire tree to delete every node.

balancedBinTreeRecursiveInsert: O(log n)
- Used by treeInsert.
- Recursively tries to insert checking all the nodes of a subtree (or root).
- Has to traverse all levels of a tree to find the correct location to insert and rebalance.

balancedBinTreeRecursiveDelete: O(log n)
- Used by destroyBalancedBinTreeNodeTree and by association, destroyBalancedBinTree.
- Recursively deletes all the nodes of a subtree (or root).
- Has to traverse the entire tree to delete every node.

balancedBinTreeRotateRight: O(1)
- Rotates a set number of nodes.

balancedBinTreeRotateLeft: O(1)
- Rotates a set number of nodes.

************************************
Known Limitations, Issues and Errors
************************************
This POS system confirms to the assignment specifications but does have limitions if considered for real-world use. It does not allow in-depth modification of the inventory from within the program such as addition, game modification, or quantity specific removal. It also feels quite limited in customization options for printed reports.
