#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX 1000
typedef struct vertexS vertexT;
typedef struct edgeS edgeT;
struct vertexS{
    char id;
    int color;
    int dist;
    int pred;
    edgeT *edges;
    vertexT *next;
};
struct edgeS{
    int weight;
    vertexT *destination;
    edgeT *next;
};
void generateGraph();
vertexT *loadGraph(dataT *);
vertexT *createVertex(char);
edgeT *createEdge(int,vertexT *);
int isPresent(vertexT *,char);
