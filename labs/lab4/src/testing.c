/**
 * @file testing.c
 * @author Kanoa Haley - 0956712 - khaley@mail.uoguelph.ca
 * @date July 30, 2017
 * @brief File containing tests for a tree library
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "KTest.h"
#include "balancedTreeAPI.h"

#define PROGRAM_NAME "Tree Library"

void destroyData(void *data);
void printData(void *data);
int compare(void *first, void *second);
void *copyData(void *data);
Tree *resetTree(TestingContext *context, Tree *tree);

int main()
{
    int fails;

    Tree *tree;
    TreeNode *node;
    int i10 = 10, i20 = 20, i25 = 25, i27 = 27, i30 = 30, i33 = 33, i35 = 35, i40 = 40, i50 = 50;
    int *p10 = &i10, *p20 = &i20, *p25 = &i25, *p27 = &i27, *p30 = &i30, *p33 = &i33, *p35 = &i35, *p40 = &i40, *p50 = &i50;

    TestingContext *context = newContext(PROGRAM_NAME);
    begin(context);

    /* Testing: createBalancedBinTree */
    section(context, "createBalancedBinTree");
    test(context, "should not create tree without any FP", createBalancedBinTree(NULL, NULL, NULL) == NULL);
    test(context, "should not create tree with only compare FP", createBalancedBinTree(compare, NULL, NULL) == NULL);
    test(context, "should not create tree with only destroy FP", createBalancedBinTree(NULL, destroyData, NULL) == NULL);
    tree = createBalancedBinTree(compare, destroyData, NULL);
    test(context, "should create tree without copy FP", tree != NULL);
    destroyBalancedBinTree(tree);
    tree = createBalancedBinTree(compare, destroyData, copyData);
    test(context, "should create tree with all FP", tree != NULL);
    test(context, "should have correct compare FP", tree != NULL && tree->compareFP == compare);
    test(context, "should have correct destroy FP", tree != NULL && tree->destroyFP == destroyData);
    test(context, "should have correct copy FP", tree != NULL && tree->copyFP == copyData);
    test(context, "should have null root node", tree != NULL && tree->root == NULL);


    /* Testing: createBalancedBinNode */
    section(context, "createBalancedBinNode");
    test(context, "should not create node without data", createBalancedBinNode(NULL) == NULL);
    node = createBalancedBinNode(p10);
    test(context, "should create new node", node != NULL);
    test(context, "should have correct data", node != NULL && node->data == p10);

    tree = resetTree(context, tree);
    tree->root = node;
    tree = resetTree(context, tree);


    /* Testing: destroyBalancedBinTree */
    section(context, "destroyBalancedBinTree");
    tree = resetTree(context, tree);
    treeInsertNode(tree, p10);
    treeInsertNode(tree, p20);
    treeInsertNode(tree, p30);
    tprint(context, "should print deleted for 10, 30, 20");
    destroyBalancedBinTree(tree);
    test(context, "should have printed the correct deletes in order", 1);


    /* Testing: treeInsertNode */
    section(context, "treeInsertNode");
    tree = createBalancedBinTree(compare, destroyData, copyData);
    treeInsertNode(tree, p10);
    test(context, "should insert as root node", tree != NULL && tree->root != NULL && tree->root->data == p10);
    treeInsertNode(tree, p20);
    test(context, "should insert as root->right node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->data == p20);
    treeInsertNode(tree, p30);
    test(context, "should insert as root->right node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->data == p30);
    test(context, "should have correct root->left node", tree != NULL && tree->root != NULL && tree->root->left != NULL && tree->root->left->data == p10);
    test(context, "should have correct root node", tree != NULL && tree->root != NULL && tree->root->data == p20);
    treeInsertNode(tree, p25);
    test(context, "should insert as root->right->left node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->left != NULL && tree->root->right->left->data == p25);
    treeInsertNode(tree, p27);
    tprint(context, "Tree should now be: \n   20\n  /  \\\n10   27\n    /  \\\n   25   30");
    test(context, "should insert as root->right node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->data == p27);
    test(context, "should have correct root->right->left node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->left != NULL && tree->root->right->left->data == p25);
    test(context, "should have correct root->right->right node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->right != NULL && tree->root->right->right->data == p30);

    tree = resetTree(context, tree);
    treeInsertNode(tree, p10);
    treeInsertNode(tree, p20);
    treeInsertNode(tree, p30);
    treeInsertNode(tree, p40);
    treeInsertNode(tree, p35);
    tprint(context, "Tree should now be: \n   20\n  /  \\\n10   35\n    /  \\\n   30   40");
    test(context, "should insert as root->right node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->data == p35);
    test(context, "should have correct root->right->left node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->left != NULL && tree->root->right->left->data == p30);
    test(context, "should have correct root->right->right node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->right != NULL && tree->root->right->right->data == p40);

    tree = resetTree(context, tree);
    treeInsertNode(tree, p10);
    treeInsertNode(tree, p20);
    treeInsertNode(tree, p30);
    treeInsertNode(tree, p40);
    treeInsertNode(tree, p50);
    tprint(context, "Tree should now be: \n   20\n  /  \\\n10   40\n    /  \\\n   30   50");
    test(context, "should insert as root->right node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->data == p40);
    test(context, "should have correct root->right->left node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->left != NULL && tree->root->right->left->data == p30);
    test(context, "should have correct root->right->right node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->right != NULL && tree->root->right->right->data == p50);

    tree = resetTree(context, tree);
    treeInsertNode(tree, p10);
    treeInsertNode(tree, p20);
    treeInsertNode(tree, p30);
    treeInsertNode(tree, p35);
    treeInsertNode(tree, p33);
    tprint(context, "Tree should now be: \n   20\n  /  \\\n10   33\n    /  \\\n   30   35");
    test(context, "should insert as root->right node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->data == p33);
    test(context, "should have correct root->right->left node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->left != NULL && tree->root->right->left->data == p30);
    test(context, "should have correct root->right->right node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->right != NULL && tree->root->right->right->data == p35);


    /* Testing: treeDeleteNode */
    section(context, "treeDeleteNode");
    tree = resetTree(context, tree);
    test(context, "should not print any deletes when deleted with NULL tree and NULL data", 1);
    treeDeleteNode(NULL, NULL);
    test(context, "should not print any deletes when deleted with NULL data", 1);
    treeDeleteNode(tree, NULL);
    test(context, "should not print any deletes when deleted with NULL tree", 1);
    treeDeleteNode(NULL, p10);
    test(context, "should not print any deletes when deleted with non existent data", 1);
    treeDeleteNode(tree, p10);

    treeInsertNode(tree, p10);
    treeDeleteNode(tree, p10);
    test(context, "should have deleted when data is root and printed 10", 1);

    tree = resetTree(context, tree);
    treeInsertNode(tree, p10);
    treeInsertNode(tree, p20);
    treeInsertNode(tree, p30);
    treeInsertNode(tree, p40);
    treeInsertNode(tree, p35);
    treeInsertNode(tree, p33);
    treeDeleteNode(tree, p10);
    test(context, "should have printed delete 10", 1);
    tprint(context, "Tree should now be: \n   30\n  /  \\\n20   35\n    /  \\\n   33   40");
    test(context, "should have correct root->right node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->data == p35);
    test(context, "should have correct root->right->left node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->left != NULL && tree->root->right->left->data == p33);
    test(context, "should have correct root->right->right node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->right != NULL && tree->root->right->right->data == p40);

    tree = resetTree(context, tree);
    treeInsertNode(tree, p10);
    treeInsertNode(tree, p20);
    treeInsertNode(tree, p30);
    treeInsertNode(tree, p40);
    treeInsertNode(tree, p35);
    treeInsertNode(tree, p33);
    treeDeleteNode(tree, p10);
    treeDeleteNode(tree, p20);
    test(context, "should have printed delete 10 and 20", 1);
    tprint(context, "Tree should now be: \n  35\n /  \\\n30  40\n \\\n  33");
    test(context, "should have correct root->right node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->data == p40);
    test(context, "should have correct root->left node", tree != NULL && tree->root != NULL && tree->root->left != NULL && tree->root->left->data == p30);
    test(context, "should have correct root->left->right node", tree != NULL && tree->root != NULL && tree->root->left != NULL && tree->root->left->right != NULL && tree->root->left->right->data == p33);

    tree = resetTree(context, tree);
    treeInsertNode(tree, p10);
    treeInsertNode(tree, p20);
    treeInsertNode(tree, p30);
    treeInsertNode(tree, p40);
    treeInsertNode(tree, p35);
    treeInsertNode(tree, p33);
    treeDeleteNode(tree, p10);
    treeDeleteNode(tree, p35);
    test(context, "should have printed delete 10 and 35", 1);
    tprint(context, "Tree should now be: \n  30\n /  \\\n30  40\n    /\n   33");
    test(context, "should have correct root->right node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->data == p40);
    test(context, "should have correct root->left node", tree != NULL && tree->root != NULL && tree->root->left != NULL && tree->root->left->data == p20);
    test(context, "should have correct root->right->left node", tree != NULL && tree->root != NULL && tree->root->right != NULL && tree->root->right->left != NULL && tree->root->right->left->data == p33);


    /* Testing: treeIsEmpty */
    section(context, "treeIsEmpty");
    tree = resetTree(context, tree);
    test(context, "should return 1 for empty tree", treeIsEmpty(tree) == 1);


    /* Testing: treeHasTwoChildren */
    section(context, "treeHasTwoChildren");
    test(context, "should be 1 for NULL tree", treeHasTwoChildren(NULL) == 1);
    node = createBalancedBinNode(p20);
    test(context, "should be 1 for one node (root) tree", treeHasTwoChildren(node) == 1);
    node->left = createBalancedBinNode(p10);
    test(context, "should be 1 for two node (root & left) tree", treeHasTwoChildren(node) == 1);
    node->right = createBalancedBinNode(p30);
    test(context, "should be 0 for three node (root & left & right) tree", treeHasTwoChildren(node) == 0);

    tree = resetTree(context, tree);
    tree->root = node;
    tree = resetTree(context, tree);


    /* Testing: treeFindNode */
    section(context, "treeFindNode");
    tree = resetTree(context, tree);
    test(context, "should return NULL when tree and data are NULL", treeFindNode(NULL, NULL) == NULL);
    test(context, "should return NULL when tree is NULL", treeFindNode(NULL, p10) == NULL);
    test(context, "should return NULL when data is NULL", treeFindNode(tree, NULL) == NULL);
    test(context, "should not find data when it is isn't in the tree", treeFindNode(tree, p10) == NULL);
    treeInsertNode(tree, p10);
    test(context, "should correctly find data when data is root", treeFindNode(tree, p10) == p10);
    treeInsertNode(tree, p20);
    treeInsertNode(tree, p30);
    treeInsertNode(tree, p35);
    treeInsertNode(tree, p33);
    test(context, "should correctly find data when data is in a filled tree", treeFindNode(tree, p35) == p35);


    /* Testing: treeFindMin */
    section(context, "treeFindMin");
    test(context, "should return NULL for NULL tree", treeFindMin(NULL) == NULL);
    tree = resetTree(context, tree);
    test(context, "should return NULL for empty tree", treeFindMin(tree) == NULL);
    treeInsertNode(tree, p40);
    treeInsertNode(tree, p20);
    treeInsertNode(tree, p25);
    test(context, "should return 20", treeFindMin(tree) == p20);
    treeInsertNode(tree, p50);
    treeInsertNode(tree, p10);
    treeInsertNode(tree, p27);
    test(context, "should return 10", treeFindMin(tree) == p10);
    treeInsertNode(tree, p30);
    treeInsertNode(tree, p33);
    treeInsertNode(tree, p35);
    test(context, "should return 10", treeFindMin(tree) == p10);


    /* Testing: treeFindMax */
    section(context, "treeFindMax");
    test(context, "should return NULL for NULL tree", treeFindMax(NULL) == NULL);
    tree = resetTree(context, tree);
    test(context, "should return NULL for empty tree", treeFindMax(tree) == NULL);
    treeInsertNode(tree, p40);
    treeInsertNode(tree, p20);
    treeInsertNode(tree, p25);
    test(context, "should return 40", treeFindMax(tree) == p40);
    treeInsertNode(tree, p50);
    treeInsertNode(tree, p10);
    treeInsertNode(tree, p27);
    test(context, "should return 50", treeFindMax(tree) == p50);
    treeInsertNode(tree, p30);
    treeInsertNode(tree, p33);
    treeInsertNode(tree, p35);
    test(context, "should return 50", treeFindMax(tree) == p50);


    /* Testing: treeInOrderPrint */
    section(context, "treeInOrderPrint");
    tree = resetTree(context, tree);
    treeInsertNode(tree, p20);
    treeInsertNode(tree, p10);
    treeInsertNode(tree, p30);
    tprint(context, "expecting print 10, 20, 30");
    treeInOrderPrint(tree, printData);
    test(context, "should have printed correctly", 1);


    /* Testing: treePreOrderPrint */
    section(context, "treePreOrderPrint");
    tree = resetTree(context, tree);
    treeInsertNode(tree, p20);
    treeInsertNode(tree, p10);
    treeInsertNode(tree, p30);
    tprint(context, "expecting print 20, 10, 30");
    treePreOrderPrint(tree, printData);
    test(context, "should have printed correctly", 1);


    /* Testing: treePostOrderPrint */
    section(context, "treePostOrderPrint");
    tree = resetTree(context, tree);
    treeInsertNode(tree, p20);
    treeInsertNode(tree, p10);
    treeInsertNode(tree, p30);
    tprint(context, "expecting print 10, 30, 20");
    treePostOrderPrint(tree, printData);
    test(context, "should have printed correctly", 1);


    tprint(context, "clearing old data, ignore any printed deletes...");
    destroyBalancedBinTree(tree);
    fails = context->failCount;
    done(context);
    return fails;
}

void destroyData(void *data)
{
    printf("deleted %d\n", *((int *) data));
}

void printData(void *data)
{
    /* create variables for debugging purposes (lldb) */
    int me = *((int *) data);
    printf("%d\n", me);
}

int compare(void *first, void *second)
{
    /* create variables for debugging purposes (lldb) */
    int i1 = *((int *) first), i2 = *((int *) second);
    return i1 - i2;
}

void *copyData(void *data)
{
    return data;
}

Tree *resetTree(TestingContext *context, Tree *tree)
{
    tprint(context, "clearing old data, ignore any printed deletes...");
    destroyBalancedBinTree(tree);
    return createBalancedBinTree(compare, destroyData, copyData);
}
