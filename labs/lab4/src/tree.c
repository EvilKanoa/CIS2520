/**
 * @file tree.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 30, 2017
 * @brief File containing the implementation for a balanced binary search tree library
 */

#include "balancedTreeAPI.h"

Tree *createBalancedBinTree(int (*compareFP) (void *data1, void *data2), void (*destroyFP) (void *toBeDeleted),void *(*copyFP)(void *toBeCopy))
{
    Tree *tree;

    if (compareFP == NULL || destroyFP == NULL || copyFP == NULL) {
        return NULL;
    }

    tree = malloc(sizeof(Tree));

    tree->root = NULL;
    tree->compareFP = compareFP;
    tree->destroyFP = destroyFP;
    tree->copyFP = copyFP;

    return tree;
}

TreeNode *createBalancedBinNode(void *data)
{
    TreeNode *node;

    if (data == NULL) {
        return NULL;
    }

    node = malloc(sizeof(TreeNode));
    node->left = NULL;
    node->right = NULL;
    node->height = 0;
    node->data = data;

    return node;
}

void destroyBalancedBinTree(Tree *toBeDeleted)
{
    if (toBeDeleted == NULL) {
        return;
    }

    destroyBalancedBinTreeNodeTree(toBeDeleted, toBeDeleted->root);
    free(toBeDeleted);
}

void destroyBalancedBinTreeNodeTree(Tree *theTree, TreeNode *toBeDeleted)
{
    if (toBeDeleted == NULL) {
        return;
    }

    destroyBalancedBinTreeNodeTree(theTree, toBeDeleted->left);
    destroyBalancedBinTreeNodeTree(theTree, toBeDeleted->right);

    theTree->destroyFP(toBeDeleted->data);
    free(toBeDeleted);
}

void treeInsertNode(Tree *theTree, void *toBeInserted)
{
    TreeNode *newNode, *node;

    if (theTree == NULL || toBeInserted == NULL) {
        return;
    }

    newNode = createBalancedBinNode(toBeInserted);
    node = theTree->root;
    if (node == NULL) {
        theTree->root = newNode;
        return;
    } else {
        balancedBinTreeRecursiveInsert(theTree, theTree->root, newNode);
    }

}

TreeNode *balancedBinTreeRecursiveInsert(Tree *theTree, TreeNode *node, TreeNode *newNode)
{
    int compare, diff;

    if (theTree == NULL || node == NULL) {
        return newNode;
    }

    compare = theTree->compareFP(newNode, node);
    if (compare > 0) {
        /* insert right */
        node->right = balancedBinTreeRecursiveInsert(theTree, node->right, newNode);
    } else if (compare < 0) {
        /* insert left */
        node->left = balancedBinTreeRecursiveInsert(theTree, node->left, newNode);
    } else {
        /* equals keys, don't insert */
        return node;
    }

    node->height = maxHeight(node) + 1;

    /* determine node unbalanced case: right right, right left, left left, or left right */
    diff = heightDiff(node);
    if (diff > 1) {
        if (theTree->compareFP(node, node->left) > 0) {
            /* left right */
        } else {
            /* left left */
        }
    } else if (diff < -1) {
        if (theTree->compareFP(node, node->right) > 0) {
            /* right right */
        } else {
            /* right left */
        }
    } else {
        return node;
    }

}

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

/**Function to delete a node from a self-balancing binary tree.
 *@param theTree pointer to a self-balancing binary tree
 *@param toBeDeleted pointer to generic data that is to be deleted from the self-balancing binary tree
 **/
void treeDeleteNode(Tree *theTree, void *toBeDeleted);

int treeIsEmpty(Tree *theTree)
{
    return (theTree->root == NULL) ? 1 : 0;
}

int treeHasTwoChildren(TreeNode *root)
{
    return (root->left != NULL && root->right != NULL) ? 0 : 1;
}

void *treeFindNode(Tree *theTree, void *data)
{
    int compare;
    TreeNode *node;

    if (theTree == NULL || data == NULL) {
        return NULL;
    }

    node = theTree->root;
    while (node != NULL) {
        compare = theTree->compareFP(data, node->data);
        if (compare < 0) {
            node = node->left;
        } else if (compare > 0) {
            node = node->right;
        } else {
            return node->data;
        }
    }

    return NULL;
}

void *treeFindMin(Tree *theTree)
{
    TreeNode *node;

    if (theTree == NULL || theTree->root == NULL) {
        return NULL;
    }

    node = theTree->root;
    while (node->left != NULL) {
        node = node->left;
    }

    return node->data;
}

void *treeFindMax(Tree *theTree)
{
    TreeNode *node;

    if (theTree == NULL || theTree->root == NULL) {
        return NULL;
    }

    node = theTree->root;
    while (node->right != NULL) {
        node = node->right;
    }

    return node->data;
}

void treeInOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
    if (theTree == NULL || printNodeFP == NULL) {
        return;
    }

    treeInOrderPrintRecursive(theTree->root, printNodeFP);
}


void treeInOrderPrintRecursive(TreeNode *root, void (*printNodeFP) (void *data))
{
    if (root == NULL || printNodeFP == NULL) {
        return;
    }

    treePreOrderPrintRecursive(root->left, printNodeFP);
    printNodeFP(root->data);
    treePreOrderPrintRecursive(root->right, printNodeFP);
}

void treePreOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
    if (theTree == NULL || printNodeFP == NULL) {
        return;
    }

    treePreOrderPrintRecursive(theTree->root, printNodeFP);
}

void treePreOrderPrintRecursive(TreeNode *root, void (*printNodeFP) (void *data))
{
    if (root == NULL || printNodeFP == NULL) {
        return;
    }

    printNodeFP(root->data);
    treePreOrderPrintRecursive(root->left, printNodeFP);
    treePreOrderPrintRecursive(root->right, printNodeFP);
}

void treePostOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
    if (theTree == NULL || printNodeFP == NULL) {
        return;
    }

    treePostOrderPrintRecursive(theTree->root, printNodeFP);
}

void treePostOrderPrintRecursive(TreeNode *root, void (*printNodeFP) (void *data))
{
    if (root == NULL || printNodeFP == NULL) {
        return;
    }

    treePreOrderPrintRecursive(root->left, printNodeFP);
    treePreOrderPrintRecursive(root->right, printNodeFP);
    printNodeFP(root->data);
}

int height(TreeNode *node)
{
    return node == NULL ? 0 : node->height;
}

int maxHeight(TreeNode *node)
{
    int h1 = height(node->left);
    int h2 = height(node->right);
    return h1 > h2 ? h1 : h2;
}

int heightDiff(TreeNode *node)
{
    return node == NULL ? 0 : height(node->left) - height(node->right);
}
