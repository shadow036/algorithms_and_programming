#include "implementation.h"
void duplicateTree(nodeT *root){
    if(root == NULL)
        return;
    nodeT *newNode = createNode(root->key);
    newNode->left = root->left;
    root->left = newNode;
    duplicateTree(root->left->left);
    duplicateTree(root->right);
}
nodeT *createNode(int key){
    nodeT *newNode = (nodeT *) malloc(sizeof(nodeT));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
nodeT *insertNode(nodeT *root,int key){
    if(root == NULL)
        return createNode(key);
    if(key < root->key)
        root->left = insertNode(root->left,key);
    else
        root->right = insertNode(root->right,key);
    return root;
}
void inOrderVisit(nodeT *root){
    if(root == NULL)
        return;
    inOrderVisit(root->left);
    fprintf(stdout,"%d ",root->key);
    inOrderVisit(root->right);
}
