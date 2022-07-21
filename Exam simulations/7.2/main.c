#include "implementation.h"
int main()
{
    int key;
    nodeT *root = NULL;
    for(int i=0;i<3;i++){
        fprintf(stdout,"key => ");
        fscanf(stdin,"%d",&key);
        root = insertNode(root,key);
    }
    fprintf(stdout,"\nNORMAL TREE:\n");
    inOrderVisit(root);
    duplicateTree(root);
    fprintf(stdout,"\n\nDUPLICATED TREE:\n");
    inOrderVisit(root);
    fprintf(stdout,"\n");
    return 0;
}
