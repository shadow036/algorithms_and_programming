#ifndef GRAPHPUBLIC_H_INCLUDED
#define GRAPHPUBLIC_H_INCLUDED
#include "graphPrivate.h"
vertexT *createVertex(char *);
edgeT *createEdge(vertexT *);
vertexT *createGraph(FILE *);
vertexT *findVertex(vertexT *,char *);
void printGraph(vertexT *);
edgeT *createSet(vertexT *,FILE *);
int verifyIndipendence(edgeT *);
int countVertices(vertexT *);
void findMaximumIndipendentSetWrapper(vertexT *);
int findMaximumIndipendentSet(vertexT *,int,int,edgeT **);
#endif // GRAPHPUBLIC_H_INCLUDED
