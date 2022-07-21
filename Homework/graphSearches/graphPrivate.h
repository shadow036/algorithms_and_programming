#ifndef GRAPHPRIVATE_H_INCLUDED
#define GRAPHPRIVATE_H_INCLUDED
enum{WHITE,GRAY,BLACK};
typedef struct vertexS vertexT;
typedef struct edgeS edgeT;
struct vertexS{
    char id;
    int color;
    int distance;
    int discoveryTime;
    int endprocessingTime;
    vertexT *predecessor;
    edgeT *edgesList;
    vertexT *nextVertex;
};
struct edgeS{
    vertexT *destination;
    edgeT *nextEdge;
};

#endif // GRAPHPRIVATE_H_INCLUDED
