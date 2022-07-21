#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treePublic.h"
#define DIM 50+1
nodeT *createNode(int key){
    nodeT *newNode = (nodeT *) malloc(sizeof(nodeT));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
nodeT *insertNode(nodeT *currentNode,nodeT *newNode){
    if(currentNode == NULL)
        return newNode;
    if(currentNode->key > newNode->key)
        currentNode->left = insertNode(currentNode->left,newNode);
    else
        currentNode->right = insertNode(currentNode->right,newNode);
    return currentNode;
}
void inOrderTraversal(nodeT *currentNode){
    if(currentNode == NULL)
        return;
    inOrderTraversal(currentNode->left);
    fprintf(stdout,"%d ",currentNode->key);
    inOrderTraversal(currentNode->right);
}
nodeT *createBST(FILE *f){
    int key;
    nodeT *root = NULL;
    while(fscanf(f,"%d ",&key) != EOF)
        root = insertNode(root,createNode(key));
    return root;
}
nodeT *treeMirror(nodeT *currentNode){
    if(currentNode == NULL)
        return NULL;
    nodeT *newNode = (nodeT *) malloc(sizeof(nodeT));
    newNode->key = currentNode->key;
    newNode->right = treeMirror(currentNode->left);
    newNode->left = treeMirror(currentNode->right);
    return newNode;
}
