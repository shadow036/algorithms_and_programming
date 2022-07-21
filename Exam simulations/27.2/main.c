#include <stdio.h>
#include <stdlib.h>
typedef struct nodeS nodeT;
struct nodeS{
    int value;
    nodeT *next;
};
nodeT *insert(nodeT *);
nodeT *createNode(int);
void listComplete(nodeT *);
void print(nodeT *);
int main()
{
    int answer;
    nodeT *head = NULL;
    do{
        fprintf(stdout,"\n1.Add\n2.Complete\n3.Print\n4.Exit\n=> ");
        fscanf(stdin,"%d",&answer);
        switch(answer){
            case 1:
                head = insert(head);
                break;
            case 2:
                listComplete(head);
                break;
            case 3:
                print(head);
                break;
            case 4:
                break;
            default:
                break;
        }
    }while(answer >= 1 && answer <= 3);
    return 0;
}
nodeT *insert(nodeT *head){
    int value;
    fprintf(stdout,"value => ");
    fscanf(stdin,"%d",&value);
    nodeT *newNode = createNode(value);
    if(head == NULL || head->value > value){
        newNode->next = head;
        head = newNode;
    }else{
        nodeT *temp = head;
        while(temp->next != NULL && temp->next->value < value){
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    return head;
}
nodeT *createNode(int value){
    nodeT *newNode = (nodeT *) malloc(sizeof(nodeT));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}
void listComplete(nodeT *head){
    nodeT *temp = head;
    while(temp->next != NULL){
        if(temp->next->value != temp->value+1){
            nodeT *newNode = createNode(temp->value+1);
            newNode->next = temp->next;
            temp->next = newNode;
        }
        temp = temp->next;
    }
}
void print(nodeT *head){
    nodeT *temp = head;
    while(temp != NULL){
        fprintf(stdout,"%d -> ",temp->value);
        temp = temp->next;
    }
    fprintf(stdout,"NULL\n");
}
