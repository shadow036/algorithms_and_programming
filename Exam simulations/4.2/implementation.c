#include "implementation.h"
nodeT *stringSplit(char *str){
    nodeT *head = NULL;
    int i=0;
    int start = 0;
    int finish = 0;
    while(str[i] != '\0'){
        if(str[i+1] == '.' || str[i+1] == '\0'){
            finish = i;
            nodeT *newNode = createNode(str,start,finish);
            newNode->next = head;
            head = newNode;
            if(str[i+1] != '\0'){
                start = i+2;
                i+=2;
            }else{
                return head;
            }
        }else{
            i++;
        }
    }
}
nodeT *createNode(char *str,int start,int finish){
    nodeT *newNode = (nodeT *) malloc(sizeof(nodeT));
    newNode->str = (char *) malloc((finish - start + 2) * sizeof(char));
    int i;
    for(i=0;i<(finish - start + 1);i++)
        newNode->str[i] = str[start+i];
    newNode->str[i] = '\0';
    newNode->next = NULL;
    return newNode;
}
void printList(nodeT *head){
    fprintf(stdout,"\n");
    while(head != NULL){
        fprintf(stdout,"%s -> ",head->str);
        head = head->next;
    }
    fprintf(stdout,"NULL\n");
}
