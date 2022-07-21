#include "members.h"
memberT *createList(FILE *f){
    memberT *membersList = NULL;
    char surname[LENGTH];
    char name[LENGTH];
    char gender;
    while(fscanf(f,"%s %s %c",surname,name,&gender) != EOF){
        memberT *newMember = createMember(surname,name,gender);
        char filename[3 * LENGTH] = "";
        strcat(filename,surname);
        strcat(filename,"_");
        strcat(filename,name);
        strcat(filename,".txt");
        newMember->characteristicsList = createSecondaryList(fopen(filename,"r"));
        newMember->nextMember = membersList;
        membersList = newMember;
    }
    return membersList;
}
memberT *createMember(char *surname,char *name,char gender){
    memberT *newMember = (memberT *) malloc(sizeof(memberT));
    strcpy(newMember->name,name);
    strcpy(newMember->surname,surname);
    newMember->gender = gender;
    newMember->nextMember = NULL;
    return newMember;
}
memberT *searchMember(memberT *membersList,char *surname,char *name){
    memberT *temp = membersList;
    while(temp != NULL){
        if(!strcmp(surname,temp->surname) && !strcmp(name,temp->name))
            return temp;
        temp = temp->nextMember;
    }
    return NULL;
}
void findSoulMate(memberT *membersList,memberT *target){
    int max = -1;
    memberT *soulMate = NULL;
    memberT *temp = membersList;
    while(temp != NULL){
        if(temp != target && target->gender != temp->gender){
            int counter = 0;
            characteristicT *targetCharacteristics = target->characteristicsList;
            while(targetCharacteristics != NULL){
                characteristicT *tempCharacteristics = temp->characteristicsList;
                while(tempCharacteristics != NULL){
                    if(!strcmp(targetCharacteristics->name,tempCharacteristics->name) && !strcmp(targetCharacteristics->value,tempCharacteristics->value))
                        counter++;
                    tempCharacteristics = tempCharacteristics->nextCharacteristic;
                }
                targetCharacteristics = targetCharacteristics->nextCharacteristic;
            }
            if(soulMate == NULL || counter > max){
                max = counter;
                soulMate = temp;
            }
        }
        temp = temp->nextMember;
    }
    fprintf(stdout,"%s %s (%d common characteristics)",soulMate->surname,soulMate->name,max);
}
void printList(memberT *membersList){
    memberT *temp = membersList;
    while(temp != NULL){
        fprintf(stdout,"%s %s %c\n",temp->surname,temp->name,temp->gender);
        characteristicT *temp2 = temp->characteristicsList;
        while(temp2 != NULL){
            fprintf(stdout,"  %s %s\n",temp2->name,temp2->value);
            temp2 = temp2->nextCharacteristic;
        }
        fprintf(stdout,"\n");
        temp = temp->nextMember;
    }
}
