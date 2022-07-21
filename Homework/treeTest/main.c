#include "treePublic.h"
int main()
{
    nodeT *root = createTree(fopen("tree.txt","r"));
    inOrderTraversal(root);
    root = removeNode(root,20);
    root = removeNode(root,70);
    root = removeNode(root,50);
    fprintf(stdout,"\n");
    inOrderTraversal(root);
    return 0;
}
