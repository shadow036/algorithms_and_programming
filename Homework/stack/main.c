#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ANSWER 10+1
typedef struct elementS elementT;
struct elementS{
    int value;
    elementT *next;
};
elementT *push(elementT *);
elementT *createElement(int);
elementT *pop(elementT *);
void print(elementT *);
int main()
{
    elementT *top = NULL;
    char answer[ANSWER];
    do{
        fprintf(stdout,"\n->push value\n->pop\n->print\n->exit\n\n=>");
        fscanf(stdin,"%s",answer);
        if(strcmp(answer,"push") == 0){
            top = push(top);
        }else if(strcmp(answer,"pop") == 0){
            top = pop(top);
        }else if(strcmp(answer,"print") == 0){
            print(top);
        }else if(strcmp(answer,"exit") == 0){
            fprintf(stdout,"\nExiting...\n");
        }else{
            fprintf(stdout,"\nInvalid command!\nExiting...\n");
        }
    }while(strcmp(answer,"push") == 0 || strcmp(answer,"pop") == 0 || strcmp(answer,"print") == 0);
    return 0;
}
elementT *push(elementT *top){
    int value;
    fscanf(stdin,"%d",&value);
    elementT *element = createElement(value);
    element->next = top;
    top = element;
    return top;
}
elementT *createElement(int value){
    elementT *element = (elementT *) malloc(sizeof(elementT));
    element->value = value;
    element->next = NULL;
    return element;
}
elementT *pop(elementT *top){
    if(top == NULL){
        fprintf(stdout,"\nUNDERFLOW!\n");
        return NULL;
    }else{
        elementT *temp = top;
        top = top->next;
        free(temp);
        return top;
    }
}
void print(elementT *top){
    fprintf(stdout,"\n");
    elementT *temp = top;
    while(temp != NULL){
        fprintf(stdout,"%d\n",temp->value);
        temp = temp->next;
    }
    fprintf(stdout,"NULL\n");
}
