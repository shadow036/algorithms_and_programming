#include "members.h"
int main()
{
    memberT *membersList = createList(fopen("members.txt","r"));
    printList(membersList);
    char surname[LENGTH];
    char name[LENGTH];
    do{
        fprintf(stdout,"\n\nsurname name => ");
        fscanf(stdin,"%s %s",surname,name);
        memberT *target = searchMember(membersList,surname,name);
        if(target != NULL)
            findSoulMate(membersList,target);
    }while(strcmp(surname,"stop") || strcmp(name,"program"));
    return 0;
}
