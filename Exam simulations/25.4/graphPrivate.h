#ifndef GRAPHPRIVATE_H_INCLUDED
#define GRAPHPRIVATE_H_INCLUDED
#define ID 20+1
enum{FREE,TAKEN};
typedef struct vertexS vertexT;
typedef struct edgeS edgeT;
struct vertexS{
    char id[ID];
    int status;
    edgeT *edges;
    vertexT *nextVertex;
};
struct edgeS{
    vertexT *destination;
    edgeT *nextEdge;
};

#endif // GRAPHPRIVATE_H_INCLUDED
