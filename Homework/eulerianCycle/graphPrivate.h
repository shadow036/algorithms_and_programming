#ifndef GRAPHPRIVATE_H_INCLUDED
#define GRAPHPRIVATE_H_INCLUDED
enum{WHITE,GREY,BLACK};
typedef struct graphS graphT;
typedef struct vertexS vertexT;
typedef struct edgeS edgeT;
struct graphS{
    vertexT *graph;
    int numberOfEdges;
};
struct vertexS{
    int id;
    edgeT *edgesList;
    vertexT *nextVertex;
};
struct edgeS{
    vertexT *destination;
    int color;
    edgeT *nextEdge;
};


#endif // GRAPHPRIVATE_H_INCLUDED
