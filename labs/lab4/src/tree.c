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

    if (compareFP == NULL || destroyFP == NULL) {
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
    TreeNode *node;

    if (theTree == NULL || toBeInserted == NULL) {
        return;
    }

    node = theTree->root;
    if (node == NULL) {
        theTree->root = createBalancedBinNode(toBeInserted);
        return;
    } else {
        theTree->root = balancedBinTreeRecursiveInsert(theTree, theTree->root, toBeInserted);
    }

}

TreeNode *balancedBinTreeRecursiveInsert(Tree *theTree, TreeNode *node, void *data)
{
    int compare, diff;

    if (theTree == NULL || node == NULL || data == NULL) {
        return createBalancedBinNode(data);
    }

    compare = theTree->compareFP(data, node->data);
    if (compare > 0) {
        /* insert right */
        node->right = balancedBinTreeRecursiveInsert(theTree, node->right, data);
    } else if (compare < 0) {
        /* insert left */
        node->left = balancedBinTreeRecursiveInsert(theTree, node->left, data);
    } else {
        /* equals keys, don't insert */
        return node;
    }

    node->height = maxHeight(node) + 1;

    /* determine node unbalanced case: right right, right left, left left, or left right */
    diff = heightDiff(node);
    if (diff > 1) {
        if (theTree->compareFP(data, node->left->data) > 0) {
            node->left = balancedBinTreeRotateLeft(node->left);
            return balancedBinTreeRotateRight(node);
        } else {
            return balancedBinTreeRotateRight(node);
        }
    } else if (diff < -1) {
        if (theTree->compareFP(data, node->right->data) > 0) {
            return balancedBinTreeRotateLeft(node);
        } else {
            node->right = balancedBinTreeRotateRight(node->right);
            return balancedBinTreeRotateLeft(node);
        }
    }

    return node;
}

TreeNode *balancedBinTreeRotateRight(TreeNode *node)
{
    TreeNode *y = node == NULL ? NULL : node->left;

    if (y == NULL) {
        return node;
    }

    /* move T3 to z's left */
    node->left = y->right;
    /* switch z into y's right */
    y->right = node;

    /* correct heights */   
    node->height = maxHeight(node);
    y->height = maxHeight(y);

    return y;
}

TreeNode *balancedBinTreeRotateLeft(TreeNode *node)
{
    TreeNode *y = node == NULL ? NULL : node->right;

    if (y == NULL) {
        return node;
    }

    /* move T2 to z's right */
    node->right = y->left;
    /* switch z into y's left */
    y->left = node;

    /* correct heights */   
    node->height = maxHeight(node);
    y->height = maxHeight(y);

    return y;
}

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
    return (root != NULL && root->left != NULL && root->right != NULL) ? 0 : 1;
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

    treeInOrderPrintRecursive(root->left, printNodeFP);
    printNodeFP(root->data);
    treeInOrderPrintRecursive(root->right, printNodeFP);
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

    treePostOrderPrintRecursive(root->left, printNodeFP);
    treePostOrderPrintRecursive(root->right, printNodeFP);
    printNodeFP(root->data);
}

int height(TreeNode *node)
{
    return node == NULL ? -1 : node->height;
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
