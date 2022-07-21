#ifndef MEMBERS_H_INCLUDED
#define MEMBERS_H_INCLUDED
#include "characteristics.h"
typedef struct memberS memberT;
struct memberS{
    char surname[LENGTH];
    char name[LENGTH];
    char gender;
    characteristicT *characteristicsList;
    memberT *nextMember;
};
memberT *createList(FILE *);
memberT *createMember(char *,char *,char);
memberT *searchMember(memberT *,char *,char *);
void findSoulMate(memberT *,memberT *);
void printList(memberT *);
#endif // MEMBERS_H_INCLUDED
