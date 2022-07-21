#include <stdio.h>
#include <stdlib.h>
#include "treePublic.h"
int main()
{
    nodeT *root = createBST(fopen("tree.txt","r"));
    nodeT *root2 = treeMirror(root);
    inOrderTraversal(root);
    inOrderTraversal(root2);
    return 0;
}
