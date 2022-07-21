#include "treePublic.h"
nodeT *createNode(int key){
    nodeT *newNode = (nodeT *) malloc(sizeof(nodeT));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
nodeT *searchNode(nodeT *currentNode,int key){
    if(currentNode == NULL)
        return NULL;
    else if(currentNode->key == key)
        return currentNode;
    else if(currentNode->key > key)
        return searchNode(currentNode->left,key);
    else
        return searchNode(currentNode->right,key);
}
nodeT *createTree(FILE *f){
    int key;
    nodeT *root = NULL;
    while(fscanf(f,"%d",&key) != EOF){
        nodeT *newNode = createNode(key);
        root = insertNode(root,newNode);
    }
    return root;
}
nodeT *insertNode(nodeT *currentNode,nodeT *newNode){
    if(currentNode == NULL)
        return newNode;
    else if(currentNode->key > newNode->key)
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
nodeT *removeNode(nodeT *currentNode,int key){
    if(currentNode == NULL)    //IF ROOT IS NULL
        return NULL;
    if(currentNode->key > key)
        currentNode->left = removeNode(currentNode->left,key);
    else if(currentNode->key < key)
        currentNode->right = removeNode(currentNode->right,key);
    else{   //NODE TO BE DELETED
        if(currentNode->left == NULL)   //HAS 0 OR 1 CHILD
            return currentNode->right;
        else if(currentNode->right == NULL)
            return currentNode->left;
        else{   //HAS 2 CHILDREN
            nodeT *temp = minimumNode(currentNode->right);
            currentNode->key = temp->key;
            currentNode->right = removeNode(currentNode->right,temp->key);
        }
    }
    return currentNode;
}
nodeT *minimumNode(nodeT *currentNode){
    if(currentNode == NULL) //IF ROOT IS NULL
        return NULL;
    if(currentNode->left == NULL)
        return currentNode;
    return minimumNode(currentNode->left);
}
nodeT *maximumNode(nodeT *currentNode){
    if(currentNode == NULL) //IF ROOT IS NULL
        return NULL;
    if(currentNode->right == NULL)
        return currentNode;
    return maximumNode(currentNode->right);
}
