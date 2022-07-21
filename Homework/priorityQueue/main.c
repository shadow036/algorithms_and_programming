#include <stdio.h>
#include <stdlib.h>
typedef struct dataS dataT;
struct dataS{
    char id;
    int priority;
    dataT *next;
};
void push(dataT **,char,int);
void pop(dataT **);
void peek(dataT *);
dataT *createData(char,int);
int isAlreadyPresent(dataT *,char);
void show(dataT *);
int main()
{
    dataT *head = NULL;
    int answer = 1;
    char id;
    int priority;
    while(answer > 0 && answer < 5){
        fprintf(stdout,"\n1.PUSH\n2.POP\n3.PEEK\n4.SHOW\n5.STOP\n=> ");
        fscanf(stdin,"%d%*c",&answer);
        switch(answer){
        case 1:
            fprintf(stdout,"\nId Priority => ");
            fscanf(stdin,"%c %d",&id,&priority);
            push(&head,id,priority);
            break;
        case 2:
            pop(&head);
            break;
        case 3:
            peek(head);
            break;
        case 4:
            show(head);
            break;
        default:
            break;
        }
    }
    return 0;
}
void push(dataT **head,char id,int priority){
    if(isAlreadyPresent(*head,id))
        return;
    dataT *newData = createData(id,priority);
    if(*head == NULL || newData->priority >= (*head)->priority){
        newData->next = *head;
        *head = newData;
        return;
    }
    dataT *temp = *head;
    while(temp->next != NULL && temp->next->priority > newData->priority){
        temp = temp->next;
    }
    newData->next = temp->next;
    temp->next = newData;
}
void pop(dataT **head){
    dataT *temp = *head;
    *head = (*head)->next;
    free(temp);
}
void peek(dataT *head){
    fprintf(stdout,"\nID: %c\nPRIORITY: %d\n",head->id,head->priority);
}
dataT *createData(char id,int priority){
    dataT *newData = (dataT *) malloc(sizeof(dataT));
    newData->id = id;
    newData->priority = priority;
    newData->next = NULL;
    return newData;
}
int isAlreadyPresent(dataT *head,char id){
    dataT *temp = head;
    while(temp != NULL){
        if(temp->id == id)
            return 1;
        temp = temp->next;
    }
    return 0;
}
void show(dataT *head){
    dataT *temp = head;
    while(temp != NULL){
        fprintf(stdout,"\nID: %c PRIORITY: %d",temp->id,temp->priority);
        temp = temp->next;
    }
    fprintf(stdout,"\n");
}
