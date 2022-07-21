#include <stdio.h>
#include <stdlib.h>
typedef struct elementS elementT;
struct elementS{
	int value;
	elementT *next;
};
int showOptions();
elementT *insert(elementT *);
elementT *createElement();
void search(elementT *);
elementT *deleteFirst(elementT *);
elementT *deleteLast(elementT *);
elementT *deleteValue(elementT *);
void print(elementT *);
int main()
{
    int answer;
    elementT *head = NULL;
    do{
        answer = showOptions();
        switch(answer){
            case 1:
                head = insert(head);
                break;
            case 2:
                search(head);
                break;
            case 3:
                head = deleteFirst(head);
                break;
            case 4:
                head = deleteLast(head);
                break;
            case 5:
                head = deleteValue(head);
                break;
            case 6:
                print(head);
                break;
            case 7:
                fprintf(stdout,"\nExiting...\n");
                break;
            default:
                fprintf(stdout,"\nInvalid command!\nExiting...\n");
                break;
        }
    }while(answer > 0 && answer < 7);
    return 0;
}
int showOptions(){
    int answer;
    fprintf(stdout,"\n1.Insert\n2.Search\n3.Delete first\n4.Delete last\n5.Delete\n6.Print\n7.Stop\n=> ");
    fscanf(stdin,"%d",&answer);
    return answer;
}
elementT *insert(elementT *head){
    elementT *element = createElement();
    if(head == NULL){
        head = element;
    }else if(head->value > element->value){
        element->next = head;
        head = element;
    }else{
        elementT *temp = head;
        while(temp->next != NULL && temp->next->value < element->value){
            temp = temp->next;
        }
        element->next = temp->next;
        temp->next = element;
    }
    return head;
}
elementT *createElement(){
    int value;
    fprintf(stdout,"\nvalue => ");
    fscanf(stdin,"%d",&value);
    elementT *element = (elementT *) malloc(sizeof(elementT));
    element->value = value;
    element->next = NULL;
    return element;
}
void search(elementT *head){
    elementT *temp = head;
    int value;
    fprintf(stdout,"\nvalue => ");
    fscanf(stdin,"%d",&value);
    int i = 0;
    while(temp != NULL){
        if(temp->value == value){
            fprintf(stdout,"\nValue found in position %d!\n",i);
            return;
        }
        temp = temp->next;
        i++;
    }
    fprintf(stdout,"\nValue not found!\n");
}
void print(elementT *head){
    fprintf(stdout,"\n");
    elementT *temp = head;
    while(temp != NULL){
        fprintf(stdout,"%d -> ",temp->value);
        temp = temp->next;
    }
    fprintf(stdout,"NULL\n");
}
elementT *deleteFirst(elementT *head){
    if(head == NULL)
        return NULL;
    elementT *temp = head;
    head = head->next;
    free(temp);
    return head;
}
elementT *deleteLast(elementT *head){
    if(head == NULL)
        return NULL;
    elementT *temp = head;
    while(temp->next->next != NULL){
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
    return head;
}
elementT *deleteValue(elementT *head){
    if(head == NULL)
        return NULL;
    int value;
    fprintf(stdout,"\nvalue => ");
    fscanf(stdin,"%d",&value);
    elementT *temp = head;
    while(temp != NULL){
        if(head->value == value){
            head = deleteFirst(head);
            temp = head;
        }else if(temp->next->value == value){
            temp->next = temp->next->next;
            temp = temp->next;
        }
    }
    return head;
}
