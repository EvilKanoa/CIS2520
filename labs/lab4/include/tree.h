#ifndef STUDENT_TREE_API_
#define STUDENT_TREE_API_
#include "balancedTreeAPI.h"

/*You may add anything to this .h file that you need to add to your tree ADT*/

/*YOU MUST LEAVE THESE TYPEDEFS AS IS.*/
/**typedef for struct name*/
typedef struct BalancedBinTreeNode TreeNode;

/**typedef for struct name*/
typedef struct BalancedBinTree Tree;

/*complete the struct definitions.  You can change the existing parts if you wish.
*/
struct BalancedBinTree {
  /*define your tree here.  You can change these if you need to but your tree must be abstract.*/
    TreeNode *root; /*< pointer to generic data that is to be stored in the tree*/
    int (*compareFP) (void *data1, void *data2); /*< function pointer to a comparison function for the purpose of inserting and deleting elements*/
    void (*destroyFP) (void *data); /*< function pointer to a function to free a single pointer that is deleted from the tree*/
    void *(*copyFP)(void *toBeCopy); /*< function pointer to a function that copies pointer data*/

  };



struct BalancedBinTreeNode{
    void *data; /*< pointer to generic data that is to be stored in the heap*/
    TreeNode *left; /*< pointer to left tree node of current node. Null if empty.*/
    TreeNode *right; /*< pointer to right tree node of current node. Null if empty.*/
    
    /*Add additional structure elements here*/
    int height;
};

/*add function prototypes as necessary*/

/**This function destroys a binary tree and all data that is in the tree
 *wbelow the given node recursively when destroy is called.
 *@param theTree pointer to a self-balancing binary tree
 *@param toBeDeleted pointer to binary tree node created via createBalancedBinTreeNode
 **/
void destroyBalancedBinTreeNodeTree(Tree *theTree, TreeNode *toBeDeleted);  

/**This function inserts a given node into an AVL tree recursively while rotating
 * the tree to preserve the AVL property.
 *@param theTree pointer to a self-balancing binary tree
 *@param node pointer to a self-balancing binary tree's root node
 *@param data new data to insert
 */
TreeNode *balancedBinTreeRecursiveInsert(Tree *theTree, TreeNode *node, void *data);

/**This function deletes a given node from an AVL tree recursively while rotating
 * the tree to preserve the AVL property.
 *@param theTree pointer to a self-balancing binary tree
 *@param node pointer to a self-balancing binary tree's root node
 *@param data data to delete
 */
TreeNode *balancedBinTreeRecursiveDelete(Tree *theTree, TreeNode *node, void *data);

/**This function rotates a nodes children to the right. A diagram to represent this can
 * be found at http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 * T1, T2, T3 and T4 are subtrees.
 *        z                                      y 
 *       / \                                   /   \
 *      y   T4      Right Rotate (z)          x      z
 *     / \          - - - - - - - - ->      /  \    /  \ 
 *    x   T3                               T1  T2  T3  T4
 *   / \
 * T1   T2
 *@param node the z node to rotate right
 *@return the y node (aka, the new parent node)
 */
TreeNode *balancedBinTreeRotateRight(TreeNode *node);

/**This function rotates a nodes children to the left. A diagram to represent this can
 * be found at http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 * T1, T2, T3 and T4 are subtrees.
 *    z                                y
 *  /  \                             /   \ 
 * T1   y      Left Rotate(z)       z      x
 *      /  \   - - - - - - - ->    / \    / \
 *    T2   x                     T1  T2 T3  T4
 *        / \
 *      T3  T4
 *@param node the z node to rotate left
 *@return the y node (aka, the new parent node)
 */
TreeNode *balancedBinTreeRotateLeft(TreeNode *node);

/**function to print a tree in-order starting from a root node. EG 
 *              A
 *            /    \
 *          B       C
 *         / \     / \
 *        D   F   G   E
 *would print nodes thusly: D->B->F->A->G->C->E
 *@param root pointer to a self-balancing binary tree root node
 *@param printNodeFP pointer to a function to print void pointer data.
 **/
void treeInOrderPrintRecursive(TreeNode *root, void (*printNodeFP) (void *data));

/**Function to print a tree pre-order starting from a root node. EG 
 *              A
 *            /   \
 *          B       C
 *         / \     / \
 *        D   F   G   E
 *would print nodes thusly: A->B->D->F->C->G->E
 *@param root pointer to a self-balancing binary tree root node
 *@param printNodeFP pointer to a function to print void pointer data.
 **/
void treePreOrderPrintRecursive(TreeNode *root, void (*printNodeFP) (void *data));

/**Function to print a tree in post-order starting from a root node. EG 
 *              A
 *            /   \
 *          B       C
 *         / \     / \
 *        D   F   G   E
 *would print nodes thusly: D->F->B->G->C->E->A
 *@param root pointer to a self-balancing binary tree root node
 *@param printNodeFP pointer to a function to print void pointer data.
 **/
void treePostOrderPrintRecursive(TreeNode *root, void (*printNodeFP) (void *data));

/* ----------------- */
/* Utility functions */
/* ----------------- */

/**This function returns the height of a given tree node.
 *@param node a node of an AVL tree
 *@return the height of the node in the tree (null nodes have a height of 0)
 */
int height(TreeNode *node);

/**This function returns the maximum height of a nodes children.
 *@param node node in an AVL tree
 *@return the maximum height of the two nodes
 */
int maxHeight(TreeNode *node);

/**This function returns the difference in height between a nodes two children.
 *@param node a node of an AVL tree
 *@return difference in height between node->left and node->right.
 */
int heightDiff(TreeNode *node);

#endif
