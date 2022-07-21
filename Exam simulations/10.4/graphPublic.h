#ifndef GRAPHPUBLIC_H_INCLUDED
#define GRAPHPUBLIC_H_INCLUDED
#include "graphPrivate.h"
#include "stackPrivate.h"
vertexT *createVertex(char *,int);
edgeT *createEdge(vertexT *,int);
vertexT *findVertex(vertexT *,char *);
vertexT *createGraph(FILE *);
void printGraph(vertexT *);
void findPathWrapper(vertexT *);
void findPath(vertexT *,vertexT *,nodeT *,int,nodeT **,int *);
void findPathWrapper2(vertexT *);
void findPath2(vertexT *,vertexT *,nodeT *,int,nodeT **,int *,int,int);
void clearVertices(vertexT *);
nodeT *copyStack(nodeT *);
#endif // GRAPHPUBLIC_H_INCLUDED
