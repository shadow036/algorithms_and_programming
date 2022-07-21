#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treePublic.h"
int main()
{
    nodeT *root1 = createBST(fopen("tree1.txt","r"));
    nodeT *root2 = createBST(fopen("tree2.txt","r"));
    fprintf(stdout,"TREE #1\n");
    inOrderTraversal(root1);
    fprintf(stdout,"\nTREE #2\n");
    inOrderTraversal(root2);
    if(treeIsomorphism(root1,root2) == 1)
        fprintf(stdout,"\n\nThe two trees ARE isomorphic!\n");
    else
        fprintf(stdout,"\n\nThe two trees ARE NOT isomorphic!\n");
    return 0;
}
