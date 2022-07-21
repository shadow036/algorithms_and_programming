#include "treePrivate.h"
#include "treeAddition.h"
void countNode(node_t *root,int *array){
    if(root == NULL)
        return;
    countNode(root->left,array);
    if(root->left != NULL && root->right != NULL)
        array[2]++;
    else if(root->left != NULL || root->right != NULL)
        array[1]++;
    else
        array[0]++;
    countNode(root->right,array);
}
void countLevel(node_t *root,int *array,int l){
    if(root == NULL)
        return;
    countLevel(root->left,array,l+1);
    array[l]++;
    countLevel(root->right,array,l+1);
}
void countPath(node_t *root,int *np,int *length){
    if(root->left == NULL && root->right == NULL){
        (*np)++;
        return;
    }
    countPath(root->left,np,length);
    (*length)++;
    countPath(root->right,np,length);
    (*length)++;
}
int visit(node_t *root,int key1,int key2){
    if(key1 < root->val && key2 > root->val){
        visit(root->left,key1,-1);
        visit(root->left,-1,key2);
    }else if(key2 < root->val && key1 > root->val){
        visit(root->left,key1,-1);
        visit(root->left,-1,key2);
    }
    return 0;
}
