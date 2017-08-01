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

/**Function to delete a node from a self-balancing binary tree.
 *@param theTree pointer to a self-balancing binary tree
 *@param toBeDeleted pointer to generic data that is to be deleted from the self-balancing binary tree
 **/
void treeDeleteNode(Tree *theTree, void *toBeDeleted);

/**Function to determine if a binary tree is empty.
 *@param theTree pointer to a self-balancing binary tree
 *@return If tree is empty, return 1. Otherwise, return 0.
 **/
int treeIsEmpty(Tree *theTree);

/**Function to determine if a binary tree node has two children.
 *@param root pointer to a self-balancing binary tree's root
 *@return If tree is empty, or does not exist, return 1. Otherwise, return 0.
 **/
int treeHasTwoChildren(TreeNode *root);

/**Function to return a given value in the tree, dependant on the compare function pointer parameters.
 *Compares nodes, until compare function returns zero, or the tree is exhausted.
 *@param theTree pointer to a self-balancing binary tree's root
 *@return pointer to the data found. If tree is empty or data is not found, return NULL.
 **/
void *treeFindNode(Tree *theTree, void *data);

/**Function to return the smallest value of a tree, dependant on the compare function pointer parameters.
 *@param theTree pointer to a self-balancing binary tree's root
 *@return pointer to the min found. If tree is empty, return NULL.
 **/
void *treeFindMin(Tree *theTree);

/**Function to return the largest value of a tree, dependant on the compare function pointer parameters.
 *@param theTree pointer to a self-balancing binary tree's root
 *@return pointer to the maximum value  found. If tree is empty, return NULL.
 **/
void *treeFindMax(Tree *theTree);

/**function to print a tree in-order. EG 
 *              A
 *            /    \
 *          B       C
 *         / \     / \
 *        D   F   G   E
 *would print nodes thusly: D->B->F->A->G->C->E
 *@param theTree pointer to a self-balancing binary tree
 *@param printNodeFP pointer to a function to print void pointer data.
 **/
void treeInOrderPrint(Tree *theTree, void (*printNodeFP) (void *data));

/**Function to print a tree pre-order. EG 
 *              A
 *            /   \
 *          B       C
 *         / \     / \
 *        D   F   G   E
 *would print nodes thusly: A->B->D->F->C->G->E
 *@param theTree pointer to a self-balancing binary tree
 *@param printNodeFP pointer to a function to print void pointer data.
 **/
void treePreOrderPrint(Tree *theTree, void (*printNodeFP) (void *data));

/**Function to print a tree in post-order. EG 
 *              A
 *            /   \
 *          B       C
 *         / \     / \
 *        D   F   G   E
 *would print nodes thusly: D->F->B->G->C->E->A
 *@param theTree pointer to a self-balancing binary tree's root
 *@param printNodeFP pointer to a function to print void pointer data.
 **/
void treePostOrderPrint(Tree *theTree, void (*printNodeFP) (void *data));

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
