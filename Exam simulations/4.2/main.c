#include "implementation.h"
int main()
{
    char string[MAX];
    fprintf(stdout,"string => ");
    fscanf(stdin,"%s",string);
    nodeT *head = stringSplit(string);
    printList(head);
    return 0;
}
