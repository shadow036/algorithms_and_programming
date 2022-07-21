#ifndef GRAPHPRIVATE_H_INCLUDED
#define GRAPHPRIVATE_H_INCLUDED
enum{FALSE,TRUE,WHITE,GRAY,BLACK};
typedef struct vertexS vertexT;
typedef struct edgeS edgeT;
struct vertexS{
    char id;
    int color;
    edgeT *edgesList;
    vertexT *nextVertex;
};
struct edgeS{
    vertexT *destination;
    int connected;
    edgeT *nextEdge;
};

#endif // GRAPHPRIVATE_H_INCLUDED
