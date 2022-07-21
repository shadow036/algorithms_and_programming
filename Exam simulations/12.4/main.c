#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "list.h"
int main(){
    FILE *f = fopen("tree.txt","r");
    nodeT *root = loadTree(f);
    int maxDepth = 0;
    findMaxDepth(root,&maxDepth,0);
    visitWrapper(root,maxDepth);
    int maxLength = 0;
    elementT *head = NULL;
    elementT *bestPath = NULL;
    addElement(&head,root->id);
    fprintf(stdout,"\n");
    findLongestID(root,head,&bestPath,&maxLength);
    head = bestPath;
    while(head != NULL){
        fprintf(stdout,"%s ",head->id);
        head = head->next;
    }
    fprintf(stdout," (length: %d)\n",maxLength);
    return 0;
}
