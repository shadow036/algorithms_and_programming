#ifndef GRAPHPUBLIC_H_INCLUDED
#define GRAPHPUBLIC_H_INCLUDED
#include "graphPrivate.h"
#include "stackPrivate.h"
vertexT *createVertex(char *id);
edgeT *createEdge(vertexT *,int);
vertexT *findVertex(vertexT *,char *);
vertexT *createGraph(FILE *);
//void findPath(vertexT *,vertexT *,vertexT *,nodeT **,nodeT **,int,nodeT **,int *,int,int);
void findPath(vertexT *,vertexT *,vertexT *,nodeT **,nodeT **,int,nodeT **,int *,int,int,int);
int checkRepetitions(vertexT *,int);
void update(nodeT **,nodeT *);
void printPath(nodeT *);
#endif // GRAPHPUBLIC_H_INCLUDED
