#include "implementation.h"
int main()
{
    int key;
    nodeT *root = NULL;
    for(int i=0;i<7;i++){
        fprintf(stdout,"key => ");
        fscanf(stdin,"%d",&key);
        root = insertNode(root,key);
    }
    int path[2];
    writePath(root,2,0,path);
    return 0;
}
