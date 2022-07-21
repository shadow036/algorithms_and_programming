#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treePublic.h"
#define DIM 50+1
nodeT *createNode(char *key){
    nodeT *newNode = (nodeT *) malloc(sizeof(nodeT));
    newNode->key = (char *) malloc((strlen(key)+1) * sizeof(char));
    strcpy(newNode->key,key);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
nodeT *insertNode(nodeT *currentNode,nodeT *newNode){
    if(currentNode == NULL)
        return newNode;
    if(strcmp(currentNode->key,newNode->key) > 0)
        currentNode->left = insertNode(currentNode->left,newNode);
    else
        currentNode->right = insertNode(currentNode->right,newNode);
    return currentNode;
}
void inOrderTraversal(nodeT *currentNode){
    if(currentNode == NULL)
        return;
    inOrderTraversal(currentNode->left);
    fprintf(stdout,"%s ",currentNode->key);
    inOrderTraversal(currentNode->right);
}
nodeT *createBST(FILE *f){
    char key[DIM];
    nodeT *root = NULL;
    while(fscanf(f,"%s ",key) != EOF)
        root = insertNode(root,createNode(key));
    return root;
}
int treeIsomorphism(nodeT *currentNode1,nodeT *currentNode2){
    if(currentNode1 == NULL && currentNode2 == NULL)
        return 1;
    if(currentNode1 == NULL && currentNode2 != NULL)    //THIS
        return 0;   //IS
    if(currentNode1 != NULL && currentNode2 == NULL)    //A
        return 0;   //XOR
    if(strcmp(currentNode1->key,currentNode2->key))
        return 0;
    return (treeIsomorphism(currentNode1->left,currentNode2->left) * treeIsomorphism(currentNode1->right,currentNode2->right));
}
