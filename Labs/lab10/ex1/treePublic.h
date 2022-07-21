#ifndef TREEPUBLIC_H_INCLUDED
#define TREEPUBLIC_H_INCLUDED
#include "treePrivate.h"
nodeT *loadFile(char *);
nodeT *createStudent(int,char *,char *,char *,char *,int);
nodeT *insertStudentName(nodeT *,nodeT *);
nodeT *insertStudentNumber(nodeT *,nodeT *);
nodeT *searchName(nodeT *,char *,char *);
nodeT *searchNumber(nodeT *,int);
void save(nodeT *,char *);
void saveInOrderName(nodeT *,FILE *);
#endif // TREEPUBLIC_H_INCLUDED
