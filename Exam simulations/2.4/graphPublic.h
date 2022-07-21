#ifndef GRAPHPUBLIC_H_INCLUDED
#define GRAPHPUBLIC_H_INCLUDED
#include "graphPrivate.h"
vertexT *createVertex(char *);
edgeT *createEdge(vertexT *,int);
vertexT *findVertex(vertexT *,char *);
vertexT *createGraph(FILE *);
void printGraph(vertexT *);
void regularityCheck(vertexT *);
void findPathWrapper(vertexT *);
void findPath(vertexT *,vertexT *,edgeT **,int,edgeT **,int *);
edgeT *copyStack(edgeT *);
void clear(vertexT *);
#endif // GRAPHPUBLIC_H_INCLUDED
