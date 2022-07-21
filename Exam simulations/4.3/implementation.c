#include "implementation.h"
#include <time.h>
char *generateRandomName(){
    srand(time(0));
    int nameLength = 1 + rand()%10;
    char *name = (char *) malloc((nameLength+1) * sizeof(char));
    int i;
    for(i=0;i<nameLength;i++){
        if(rand()%2 == 0){  //LOWER
            name[i] = 97+rand()%26;
        }else{  //UPPER
            name[i] = 65+rand()%26;
        }
    }
    name[i] = '\0';
    return name;
}
nodeT *insertNode(nodeT *root,char *firstName,char *lastName,int mark){
    srand(time(0));
    if(root == NULL)
        return createNode(firstName,lastName,mark);
    if(rand()%2 == 0)
        root->leftChild = insertNode(root->leftChild,firstName,lastName,mark);
    else
        root->rightSibling = insertNode(root->rightSibling,firstName,lastName,mark);
    return root;
}
nodeT *createNode(char *firstName,char *lastName,int mark){
    nodeT *newNode = (nodeT *) malloc(sizeof(nodeT));
    newNode->firstName = (char *) malloc((strlen(firstName)+1) * sizeof(char));
    strcpy(newNode->firstName,firstName);
    newNode->lastName = (char *) malloc((strlen(lastName)+1) * sizeof(char));
    strcpy(newNode->lastName,lastName);
    newNode->mark = mark;
    newNode->leftChild = NULL;
    newNode->rightSibling = NULL;
    return newNode;
}
void visit(nodeT *root){
    if(root == NULL)
        return;
    fprintf(stdout,"%s %s (%d)\n",root->firstName,root->lastName,root->mark);
    visit(root->leftChild);
    visit(root->rightSibling);
}
