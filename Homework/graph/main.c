#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#define ID 10
#define WHITE 0
#define GRAY 1
#define BLACK 2
typedef struct vertexS vertexT;
typedef struct edgeS edgeT;
typedef struct nodeS nodeT;
//VERTEX STRUCTURE
struct vertexS{
    char *id;
    edgeT *edges;
    //BFS & DFS
    int color;
    vertexT *predecessor;
    //BFS
    int distance;
    //DFS
    int d;
    int f;
    int visited;
    vertexT *next;
};
//EDGE STRUCTURE
struct edgeS{
    int weight;
    vertexT *destination;
    edgeT *next;
};
//QUEUE NODE
struct nodeS{
    vertexT *currentVertex;
    nodeT *next;
};
void randomGraphGenerator();
vertexT *loadGraph();
vertexT *search(vertexT *,char *);
vertexT *createVertex(vertexT **,char *);
void createEdge(vertexT *,vertexT *,int);
void printGraph(vertexT *);
void bfs(vertexT *);
void dfs(vertexT *);
int dfsRecursive(vertexT *,int);
void enqueue(nodeT **,nodeT **,vertexT *);
nodeT *dequeue(nodeT **);
nodeT *createNode(vertexT *);
int isReachable(vertexT *graph,char *,char *);
int isReachableRecursive(vertexT *,vertexT *);
int main()
{
    //randomGraphGenerator();
    vertexT *graph = loadGraph();
    printGraph(graph);
    bfs(graph);
    dfs(graph);
    char id[ID];
    char id2[ID];
    int i=0;
    while(i < 10){
        fprintf(stdout,"\nsourceId destinationId => ");
        fscanf(stdin,"%s %s",id,id2);
        if(isReachable(graph,id,id2) == 1)
            fprintf(stdout,"%s and %s are reachable!\n",id,id2);
        else
            fprintf(stdout,"%s and %s are not reachable!\n",id,id2);
        i++;
    }
    return 0;
}
void randomGraphGenerator(){
    srand(time(0));
    FILE *f = fopen("graph.txt","w");
    for(int i=0;i<100;i++)
        fprintf(f,"%c %d %c\n",65+rand()%26,rand()%10,65+rand()%26);
    fclose(f);
}
vertexT *loadGraph(){
    vertexT *graph = NULL;
    FILE *f = fopen("graph.txt","r");
    char sourceId[ID];
    int weight;
    char destinationId[ID];
    while(fscanf(f,"%s %d %s",sourceId,&weight,destinationId) != EOF){
        vertexT *sourceVertex = NULL;
        vertexT *destinationVertex = NULL;
        if(search(graph,sourceId) == NULL){
            sourceVertex = createVertex(&graph,sourceId);
        }else{
            sourceVertex = search(graph,sourceId);
        }
        if(search(graph,destinationId) == NULL){
            destinationVertex = createVertex(&graph,destinationId);
        }else{
            destinationVertex = search(graph,destinationId);
        }
       createEdge(sourceVertex,destinationVertex,weight);
    }
    fclose(f);
    return graph;
}
vertexT *createVertex(vertexT **graph,char *id){
    vertexT *newVertex = (vertexT *) malloc(sizeof(vertexT));
    newVertex->id = (char *) malloc((strlen(id)+1) * sizeof(char));
    strcpy(newVertex->id,id);
    newVertex->edges = NULL;
    newVertex->next = *graph;
    *graph = newVertex;
    return newVertex;
}
void createEdge(vertexT *sourceVertex,vertexT *destinationVertex,int weight){
    edgeT *newEdge = (edgeT *) malloc(sizeof(edgeT));
    newEdge->destination = destinationVertex;
    newEdge->weight = weight;
    newEdge->next = sourceVertex->edges;
    sourceVertex->edges = newEdge;
}
vertexT *search(vertexT *vertices,char *id){
    vertexT *temp = vertices;
    while(temp != NULL){
        if(strcmp(temp->id,id) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
void printGraph(vertexT *graph){
    vertexT *temp = graph;
    while(temp != NULL){
        fprintf(stdout,"%s",temp->id);
        edgeT *temp2 = temp->edges;
        while(temp2 != NULL){
            fprintf(stdout,"\n  weight: %d, destination: %s",temp2->weight,temp2->destination->id);
            temp2 = temp2->next;
        }
        fprintf(stdout,"\n");
        temp = temp->next;
    }
}
void bfs(vertexT *graph){
    vertexT *temp = graph->next;
    while(temp != NULL){
        temp->color = WHITE;
        temp->distance = INT_MAX;
        temp = temp->next;
    }
    temp = graph;
    temp->color = GRAY;
    temp->distance = 0;
    temp->predecessor = NULL;
    nodeT *head = NULL;
    nodeT *tail = NULL;
    enqueue(&head,&tail,temp);
    while(head != NULL){
        nodeT *dequeuedNode = dequeue(&head);
        fprintf(stdout,"\n%s (%d)",dequeuedNode->currentVertex->id,dequeuedNode->currentVertex->distance);
        edgeT *temp2 = dequeuedNode->currentVertex->edges;
        while(temp2 != NULL){
            if(temp2->destination->color == WHITE){
                temp2->destination->color = GRAY;
                temp2->destination->distance = dequeuedNode->currentVertex->distance+1;
                temp2->destination->predecessor = dequeuedNode->currentVertex;
                enqueue(&head,&tail,temp2->destination);
            }
            temp2 = temp2->next;
        }
        dequeuedNode->currentVertex->color = BLACK;
    }
    //PRINT DISCONNECTED NODES
    temp = graph->next;
    while(temp != NULL){
        if(temp->color == WHITE)
            fprintf(stdout,"\n%s (INFINITY)",temp->id);
        temp = temp->next;
    }
    fprintf(stdout,"\n");
}
void enqueue(nodeT **head,nodeT **tail,vertexT *newVertex){
    nodeT *newNode = createNode(newVertex);
    if(*head == NULL){
        *tail = newNode;
        *head = newNode;
    }else{
        (*tail)->next = newNode;
        *tail = newNode;
    }
}
nodeT *dequeue(nodeT **head){
    if(*head != NULL){
        nodeT *dequeuedNode = *head;
        *head = (*head)->next;
        return dequeuedNode;
    }else{
        return NULL;
    }
}
nodeT *createNode(vertexT *newVertex){
    nodeT *newNode = (nodeT *) malloc(sizeof(nodeT));
    newNode->currentVertex = newVertex;
    newNode->next = NULL;
    return newNode;
}
void dfs(vertexT *graph){
    vertexT *temp = graph;
    while(temp != NULL){
        temp->color = WHITE;
        temp->predecessor = NULL;
        temp = temp->next;
    }
    int time = -1;
    temp = graph;
    while(temp != NULL){
        if(temp->color == WHITE){
            time = dfsRecursive(temp,time);
        }
        temp = temp->next;
    }
    fprintf(stdout,"\n");
}
int dfsRecursive(vertexT *temp,int time){
    time = time+1;
    temp->d = time;
    temp->color = GRAY;
    edgeT *temp2 = temp->edges;
    while(temp2 != NULL){
        if(temp2->destination->color == WHITE){
            temp2->destination->predecessor = temp;
            time = dfsRecursive(temp2->destination,time);
        }
        temp2 = temp2->next;
    }
    temp->color = BLACK;
    time = time+1;
    temp->f = time;
    fprintf(stdout,"\n%s (%d/%d)",temp->id,temp->d,temp->f);
    return time;
}
int isReachable(vertexT *graph,char *sourceId,char *destinationId){ //WRAPPER
    for(vertexT *temp = graph;temp != NULL;temp = temp->next)
        temp->visited = 0;
    vertexT *source = search(graph,sourceId);
    vertexT *destination = search(graph,destinationId);
    return isReachableRecursive(source,destination);
}
int isReachableRecursive(vertexT *source,vertexT *destination){
    if(source == destination)
        return 1;
    if(source->visited == 1)
        return 0;
    source->visited = 1;
    for(edgeT *s = source->edges;s != NULL;s = s->next){
        if(isReachableRecursive(s->destination,destination) == 1)
            return 1;
    }
    source->visited = 0;
    return 0;
}
