#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct nodeS nodeT;
struct nodeS{
    int value;
    nodeT *next;
};
void headToTail(nodeT *);
void tailToHead(nodeT *,nodeT *);
nodeT *insert(nodeT *);
nodeT *createNode(int);
nodeT *findTail(nodeT *);
int main()
{
    nodeT *nodes = NULL;
    int answer;
    do{
        nodeT *temp = findTail(nodes);
        fprintf(stdout,"\n1.Insert\n2.Print\n3.Print reverse\n4.Exit\n=> ");
        fscanf(stdin,"%d",&answer);
        switch(answer){
        case 1:
            nodes = insert(nodes);
            break;
        case 2:
            headToTail(nodes);
            break;
        case 3:
            tailToHead(nodes,temp);
            break;
        case 4:
            fprintf(stdout,"\nExiting...\n");
            break;
        default:
            fprintf(stdout,"\nInvalid command!\nExiting...\n");
            break;
        }
    }while(answer >= 1 && answer <= 3);
    return 0;
}
nodeT *insert(nodeT *nodes){
    int value;
    fprintf(stdout,"value => ");
    fscanf(stdin,"%d",&value);
    nodeT *newNode = createNode(value);
    newNode->next = nodes;
    nodes = newNode;
    return nodes;
}
nodeT *createNode(int value){
    nodeT *newNode = (nodeT *) malloc(sizeof(nodeT));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}
void headToTail(nodeT *nodes){
    if(nodes == NULL)
        return;
    fprintf(stdout,"%d ",nodes->value);
    headToTail(nodes->next);
}
void tailToHead(nodeT *head,nodeT *current){
    nodeT *temp = head;
    if(temp == current){
        fprintf(stdout,"%d ",temp->value);
        return;
    }
    while(temp->next != current)
        temp = temp->next;
    fprintf(stdout,"%d ",temp->next->value);
    tailToHead(head,temp);
}
nodeT *findTail(nodeT *nodes){
    if(nodes == NULL || nodes->next == NULL)
        return nodes;
    return findTail(nodes->next);
}
