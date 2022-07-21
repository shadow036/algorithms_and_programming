#ifndef GRAPHPUBLIC_H_INCLUDED
#define GRAPHPUBLIC_H_INCLUDED
#include "graphPrivate.h"
#include "queuePrivate.h"
void graphGenerator();
vertexT *createGraph(FILE *);
vertexT *createVertex(int);
edgeT *createEdge(vertexT *);
vertexT *findVertex(vertexT *,int);
void printGraph(vertexT *);
int countVertices(vertexT *);
void findHamiltonianCycleWrapper(vertexT *,int);
int findHamiltonianCycle(vertexT *,vertexT *,int,queueT **,queueT **);
#endif // GRAPHPUBLIC_H_INCLUDED
