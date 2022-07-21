#include "implementation.h"
int main()
{
    nodeT *root = NULL;
    for(int i=0;i<10;i++){
        char *firstName = generateRandomName();
        char *lastName = generateRandomName();
        root = insertNode(root,firstName,lastName,18+rand()%14);
    }
    visit(root);
    return 0;
}
