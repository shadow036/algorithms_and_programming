#include <stdio.h>
#include <stdlib.h>
typedef struct nodeS nodeT;
struct nodeS{
    int key;
    nodeT *left;
    nodeT *right;
};
void listInsert(nodeT **,nodeT **,int,int);
void listWrite(nodeT *,nodeT *,int);
nodeT *createNode(int);
int main()
{
    nodeT *left = NULL;
    nodeT *right = NULL;
    int answer,key,leftRight;
    do{
        fprintf(stdout,"\nleftRight = 0 -> insertion/print on the left\nleftRight = 1 -> insertion/print on the right\n\n1.Insert key leftRight\n2.Print leftRight\n3.Exit\n=> ");
        fscanf(stdin,"%d",&answer);
        switch(answer){
        case 1:
            fprintf(stdout,"key leftRight => ");
            fscanf(stdin,"%d %d",&key,&leftRight);
            listInsert(&left,&right,key,leftRight);
            break;
        case 2:
            fprintf(stdout,"leftRight => ");
            fscanf(stdin,"%d",&leftRight);
            listWrite(left,right,leftRight);
            break;
        case 3:
            fprintf(stdout,"\nExiting...\n");
            break;
        default:
            fprintf(stdout,"\nInvalid command!\nExiting...\n");
            break;
        }
    }while(answer == 1 || answer == 2);
    return 0;
}
void listInsert(nodeT **left,nodeT **right,int key,int leftRight){
    nodeT *newNode = createNode(key);
    if(*left == NULL && *right == NULL){
        *left = *right = newNode;
    }else if(leftRight == 0){
        (*left)->left = newNode;
        newNode->right = *left;
        *left = newNode;
    }else if(leftRight == 1){
        (*right)->right = newNode;
        newNode->left = *right;
        *right = newNode;
    }
}
void listWrite(nodeT *left,nodeT *right,int leftRight){
    if(leftRight == 0){
        nodeT *temp = left;
        while(temp != NULL){
            fprintf(stdout,"%d -> ",temp->key);
            temp = temp->right;
        }
        fprintf(stdout,"NULL\n");
    }else if(leftRight == 1){
        nodeT *temp = right;
        while(temp != NULL){
            fprintf(stdout,"%d -> ",temp->key);
            temp = temp->left;
        }
        fprintf(stdout,"NULL\n");
    }
}
nodeT *createNode(int key){
    nodeT *node = (nodeT *) malloc(sizeof(nodeT));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}
