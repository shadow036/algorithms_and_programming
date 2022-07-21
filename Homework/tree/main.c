#include <stdio.h>
#include <stdlib.h>
typedef struct nodeS nodeT;
struct nodeS{
    int key;
    nodeT *left;
    nodeT *right;
};
nodeT *insert(nodeT *,nodeT *);
nodeT *createNode(int);
void print();
int main()
{
    nodeT *root = NULL;
    int answer,value;
    do{
        fprintf(stdout,"\n1.Insert\n2.Print\n3.Exit\n=> ");
        fscanf(stdin,"%d",&answer);
        switch(answer){
        case 1:
            fprintf(stdout,"value => ");
            fscanf(stdin,"%d",&value);
            root = insert(root,createNode(value));
            break;
        case 2:
            print(root);
            fprintf(stdout,"\n");
            break;
        case 3:
            fprintf(stdout,"\nExiting...\n");
            break;
        default:
            break;
        }
    }while(answer != 3);
    return 0;
}
nodeT *insert(nodeT *root,nodeT *newNode){
    if(root == NULL)
        return newNode;
    if(newNode->key < root->key)
        root->left = insert(root->left,newNode);
    else
        root->right = insert(root->right
                             ,newNode);
    return root;
}
nodeT *createNode(int value){
    nodeT *newNode = (nodeT *) malloc(sizeof(nodeT));
    newNode->key = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
void print(nodeT *root){
    if(root == NULL)
        return;
    print(root->left);
    fprintf(stdout,"%d ",root->key);
    print(root->right);
}
