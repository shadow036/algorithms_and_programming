#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ANSWER 10+1
typedef struct elementS elementT;
struct elementS{
    int value;
    elementT *next;
};
void enqueue(elementT **,elementT **);
elementT *createElement(int);
void dequeue(elementT **,elementT **);
void print(elementT *);
int main()
{
    elementT *head = NULL;
    elementT *tail = NULL;
    char answer[ANSWER];
    do{
        fprintf(stdout,"\n->enqueue value\n->dequeue\n->print\n->exit\n\n=>");
        fscanf(stdin,"%s",answer);
        if(strcmp(answer,"enqueue") == 0){
            enqueue(&head,&tail);
        }else if(strcmp(answer,"dequeue") == 0){
            dequeue(&head,&tail);
        }else if(strcmp(answer,"print") == 0){
            print(head);
        }else if(strcmp(answer,"exit") == 0){
            fprintf(stdout,"\nExiting...\n");
        }else{
            fprintf(stdout,"\nInvalid command!\nExiting...\n");
        }
    }while(strcmp(answer,"enqueue") == 0 || strcmp(answer,"dequeue") == 0 || strcmp(answer,"print") == 0);
    return 0;
}
void enqueue(elementT **head,elementT **tail){
    int value;
    fscanf(stdin,"%d",&value);
    elementT *element = createElement(value);
    if(*head == NULL){
        *head = element;
        *tail = element;
    }else{
        (*tail)->next = element;
        *tail = element;
    }
}
elementT *createElement(int value){
    elementT *element = (elementT *) malloc(sizeof(elementT));
    element->value = value;
    element->next = NULL;
    return element;
}
void dequeue(elementT **head,elementT **tail){
    if(*head == NULL){
        fprintf(stdout,"\nUNDERFLOW!\n");
    }else if((*head)->next == NULL){
        elementT *temp = *head;
        free(temp);
        *head = NULL;
        *tail = NULL;
    }else{
        elementT *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
void print(elementT *head){
    fprintf(stdout,"\n");
    elementT *temp = head;
    while(temp != NULL){
        fprintf(stdout,"%d\n",temp->value);
        temp = temp->next;
    }
    fprintf(stdout,"NULL\n");
}
