#ifndef GRAPHPUBLIC_H_INCLUDED
#define GRAPHPUBLIC_H_INCLUDED
#include "graphPrivate.h"
#include "queuePrivate.h"
void graphGenerator(int *);
vertexT *createGraph(FILE *);
vertexT *createVertex(int);
edgeT *createEdge(vertexT *);
vertexT *findVertex(vertexT *,int);
edgeT *findEdge(vertexT *,int,int);
void printGraph(vertexT *);
void colorEdge(vertexT *,int,int,int);
void findEurelianCycleWrapper(vertexT *,char,char,int);
int findEurelianCycle(vertexT *,edgeT *,char,char,int,queueT **,queueT **);
#endif // GRAPHPUBLIC_H_INCLUDED
