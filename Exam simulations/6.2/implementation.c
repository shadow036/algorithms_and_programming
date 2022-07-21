#include "implementation.h"
void writePath(nodeT *root,int height,int currentLevel,int *path){
    if(currentLevel == height){
        path[currentLevel] = root->key;
        for(int i=0;i<=currentLevel;i++)
            fprintf(stdout,"%d ",path[i]);
        fprintf(stdout,"\n");
        return;
    }
    /*
    if(root == NULL){
        for(int i=0;i<currentLevel;i++)
            fprintf(stdout,"%d ",path[i]);
        fprintf(stdout,"\n");
        return;
    }
    */
    path[currentLevel] = root->key;
    writePath(root->left,height,currentLevel+1,path);
    writePath(root->right,height,currentLevel+1,path);
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
