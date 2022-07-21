#include "graphPublic.h"
#include "stackPublic.h"
vertexT *createVertex(char *id){
    vertexT *newVertex = (vertexT *) malloc(sizeof(vertexT));
    strcpy(newVertex->id,id);
    newVertex->numberOfTimesVisited = 0;
    newVertex->edges = NULL;
    newVertex->nextVertex = NULL;
    return newVertex;
}
edgeT *createEdge(vertexT *destination,int weight){
    edgeT *newEdge = (edgeT *) malloc(sizeof(edgeT));
    newEdge->destination = destination;
    newEdge->weight = weight;
    newEdge->nextEdge = NULL;
    return newEdge;
}
vertexT *findVertex(vertexT *graph,char *id){
    vertexT *temp = graph;
    while(temp != NULL){
        if(!strcmp(temp->id,id))
            return temp;
        temp = temp->nextVertex;
    }
    return NULL;
}
vertexT *createGraph(FILE *f){
    vertexT *graph = NULL;
    char sourceId[ID];
    int weight;
    char destinationId[ID];
    while(fscanf(f,"%s %d %s",sourceId,&weight,destinationId) != EOF){
        vertexT *sourceVertex = findVertex(graph,sourceId);
        if(sourceVertex == NULL){
            sourceVertex = createVertex(sourceId);
            sourceVertex->nextVertex = graph;
            graph = sourceVertex;
        }
        vertexT *destinationVertex = findVertex(graph,destinationId);
        if(destinationVertex == NULL){
            destinationVertex = createVertex(destinationId);
            destinationVertex->nextVertex = graph;
            graph = destinationVertex;
        }
        edgeT *newEdge = createEdge(destinationVertex,weight);
        newEdge->nextEdge = sourceVertex->edges;
        sourceVertex->edges = newEdge;
    }
    return graph;
}
/*void findPath(vertexT *graph,vertexT *current,vertexT *destination,nodeT **bos,nodeT **tos,int currentLength,nodeT **bestPath,int *maxLength,int maxNumberVisited,int maxRepetitions){
    if(current == destination){
        if(checkRepetitions(graph,maxRepetitions) && currentLength > *maxLength){
            *maxLength = currentLength;
            update(bestPath,*bos);
        }
        return;
    }
    for(edgeT *temp = current->edges;temp != NULL;temp = temp->nextEdge){
        if(temp->destination->numberOfTimesVisited < maxNumberVisited+1){
            push(bos,tos,temp->destination->id);
            temp->destination->numberOfTimesVisited++;
            fprintf(stdout,"\nEnqueueing %s (times visited %d)",temp->destination->id,temp->destination->numberOfTimesVisited);
            findPath(graph,temp->destination,destination,bos,tos,currentLength+temp->weight,bestPath,maxLength,maxNumberVisited,maxRepetitions);
            pop(bos,tos);
            temp->destination->numberOfTimesVisited--;
            fprintf(stdout,"\nDequeueing %s (times visited %d)",temp->destination->id,temp->destination->numberOfTimesVisited);
        }
    }
}*/
void findPath(vertexT *graph,vertexT *current,vertexT *destination,nodeT **bos,nodeT **tos,int currentLength,nodeT **bestPath,int *maxLength,int maxNumberVisited,int currentRepetitions,int maxRepetitions){
    if(current == destination){
        if(/*checkRepetitions(graph,maxRepetitions) && */currentLength > *maxLength){
            *maxLength = currentLength;
            update(bestPath,*bos);
        }
        return;
    }
    for(edgeT *temp = current->edges;temp != NULL;temp = temp->nextEdge){
        if(temp->destination->numberOfTimesVisited < maxNumberVisited+1){
            if(temp->destination->numberOfTimesVisited == 1 && currentRepetitions == maxRepetitions)
                continue;
            push(bos,tos,temp->destination->id);
            temp->destination->numberOfTimesVisited++;
            if(temp->destination->numberOfTimesVisited == 2)
                currentRepetitions++;
            fprintf(stdout,"\nPushing %s (times visited %d)",temp->destination->id,temp->destination->numberOfTimesVisited);
            findPath(graph,temp->destination,destination,bos,tos,currentLength+temp->weight,bestPath,maxLength,maxNumberVisited,currentRepetitions,maxRepetitions);
            pop(bos,tos);
            temp->destination->numberOfTimesVisited--;
            fprintf(stdout,"\nPopping %s (times visited %d)",temp->destination->id,temp->destination->numberOfTimesVisited);
            if(temp->destination->numberOfTimesVisited == 1)
                currentRepetitions--;
        }
    }
}
int checkRepetitions(vertexT *graph,int maxRepetitions){
    int counter = 0;
    for(vertexT *temp = graph;temp != NULL;temp = temp->nextVertex){
        if(temp->numberOfTimesVisited > 1)
            counter++;
    }
    if(counter > maxRepetitions)
        return 0;
    else
        return 1;
}
void update(nodeT **bestPath,nodeT *bos){
    *bestPath = NULL;
    nodeT *tos = NULL; //DUMMY
    for(nodeT *temp = bos;temp != NULL;temp = temp->nextNode)
        push(bestPath,&tos,temp->id);
}
void printPath(nodeT *path){
    fprintf(stdout,"\n\n");
    for(nodeT *temp = path;temp != NULL;temp = temp->nextNode)
        fprintf(stdout,"%s -> ",temp->id);
    fprintf(stdout,"NULL");
}
