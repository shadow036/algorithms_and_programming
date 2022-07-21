#include "new.h"
#include "queuePublic.h"
int graph_bfs_count(graph_t *g, vertex_t *n){
  queue_t *qp;
  vertex_t *d;
  edge_t *e;
  //CLEAR COLORS
  clearColors(g);
  //GRAPH INITIALIZATION
  qp = queue_init (g->nv);
  //SOURCE VERTEX INITIALIZATION
  n->color = GREY;
  n->dist = 0;
  n->pred = NULL;
  queue_put (qp, (void *)n);
  int counter = 1;
  //ACTUAL BFS
  while (!queue_empty_m (qp)) {
    queue_get (qp, (void **)&n);    //dequeue
    e = n->head;
    while (e != NULL) { //scan through all adjacent nodes
      d = e->dst;
      if (d->color == WHITE) {  //if node is not visited (WHITE), update
        counter++;
        d->color = GREY;
        d->dist = n->dist + 1;
        d->pred = n;
        queue_put (qp, (void *)d);  //put node in the queue
      }
      e = e->next;
    }
    n->color = BLACK;   //all adjacent nodes has been visited: node n is now BLACK
  }
  queue_dispose (qp, NULL); //free queue

  return counter;
}
void clearColors(graph_t *g){
    vertex_t *n = g->g;
    while(n != NULL){
        n->color = WHITE;
        n->disc_time = -1;
        n->dist = -1;
        n->endp_time = -1;
        n->scc = -1;
        n = n->next;
    }
}
void graph_bfs_distance(graph_t *g, vertex_t *n,int *maxDistance){
  queue_t *qp;
  vertex_t *d;
  edge_t *e;
  //CLEAR COLORS
  clearColors(g);
  //GRAPH INITIALIZATION
  qp = queue_init (g->nv);
  //SOURCE VERTEX INITIALIZATION
  n->color = GREY;
  n->dist = 0;
  n->pred = NULL;
  queue_put (qp, (void *)n);
  //ACTUAL BFS
  while (!queue_empty_m (qp)) {
    queue_get (qp, (void **)&n);    //dequeue
    e = n->head;
    while (e != NULL) { //scan through all adjacent nodes
      d = e->dst;
      if (d->color == WHITE) {  //if node is not visited (WHITE), update
        d->color = GREY;
        d->dist = n->dist + 1;
        if(d->dist > *maxDistance)
            *maxDistance = d->dist;
        d->pred = n;
        queue_put (qp, (void *)d);  //put node in the queue
      }
      e = e->next;
    }
    n->color = BLACK;   //all adjacent nodes has been visited: node n is now BLACK
  }
  queue_dispose (qp, NULL); //free queue

  return;
}
void graph_dfs_type(graph_t *g, vertex_t *n){
  clearColors(g);
  int currTime=0;
  vertex_t *tmp, *tmp2;
  int edgeTypes[EDGE_TYPES];
  /*
  COUNTERS LEGEND:
  0 = TREE
  1 = FORWARD
  2 = BACKWARD
  3 = CROSS
  */
  for(int i=0;i<EDGE_TYPES;i++)
    edgeTypes[i] = 0;
  printf("List of edges:\n");
  currTime = graph_dfs_type_r (g, n, currTime,edgeTypes);
  for (tmp=g->g; tmp!=NULL; tmp=tmp->next) {
    if (tmp->color == WHITE) {
      currTime = graph_dfs_type_r (g, tmp, currTime,edgeTypes);
    }
  }

  printf("List of vertices:\n");
  for (tmp=g->g; tmp!=NULL; tmp=tmp->next) {
    tmp2 = tmp->pred;
    printf("%2d: %2d/%2d (%d)\n",
      tmp->id, tmp->disc_time, tmp->endp_time,
      (tmp2!=NULL) ? tmp->pred->id : -1);
  }
  fprintf(stdout,"Types of edges:\n");
  fprintf(stdout,"Tree edges: %d\n",edgeTypes[0]);
  fprintf(stdout,"Forward edges: %d\n",edgeTypes[1]);
  fprintf(stdout,"Backward edges: %d\n",edgeTypes[2]);
  fprintf(stdout,"Cross edges: %d\n",edgeTypes[3]);
}
int graph_dfs_type_r(graph_t *g, vertex_t *n,int currTime,int *edgesType){
    edge_t *e;
  vertex_t *tmp;
  n->color = GREY;
  n->disc_time = ++currTime;
  e = n->head;
  while (e != NULL) {
    tmp = e->dst;
    switch (tmp->color) {
      case WHITE: printf("%d -> %d : T\n", n->id, tmp->id);edgesType[0]++; break;
      case GREY : printf("%d -> %d : B\n", n->id, tmp->id);edgesType[2]++; break;
      case BLACK: if (n->disc_time < tmp->disc_time) {
                    printf("%d -> %d : F\n", n->disc_time, tmp->disc_time);
                    edgesType[1]++;
                  } else {
                    printf("%d -> %d : C\n", n->id, tmp->id);
                    edgesType[3]++;
                  }
    }
    if (tmp->color == WHITE) {
      tmp->pred = n;
      currTime = graph_dfs_type_r (g, tmp, currTime,edgesType);
    }
    e = e->next;
  }
  n->color = BLACK;
  n->endp_time = ++currTime;
  return currTime;
}
void graph_dfs_depth(graph_t *g, vertex_t *n){
  clearColors(g);
  int currTime=0;
  vertex_t *tmp, *tmp2;
  int maxDepth = -1;
  printf("List of edges:\n");
  currTime = graph_dfs_depth_r (g, n, currTime,0,&maxDepth);
  for (tmp=g->g; tmp!=NULL; tmp=tmp->next) {
    if (tmp->color == WHITE) {
      currTime = graph_dfs_depth_r (g, tmp, currTime,0,&maxDepth);
    }
  }

  printf("List of vertices:\n");
  for (tmp=g->g; tmp!=NULL; tmp=tmp->next) {
    tmp2 = tmp->pred;
    printf("%2d: %2d/%2d (%d)\n",
      tmp->id, tmp->disc_time, tmp->endp_time,
      (tmp2!=NULL) ? tmp->pred->id : -1);
  }
  fprintf(stdout,"\nThe depth of the DFS visit tree is %d",maxDepth);
}
int graph_dfs_depth_r(graph_t *g, vertex_t *n,int currTime,int currentDepth,int *maxDepth){
    edge_t *e;
  vertex_t *tmp;

  n->color = GREY;
  n->disc_time = ++currTime;
  e = n->head;
  while (e != NULL) {
    tmp = e->dst;
    switch (tmp->color) {
      case WHITE: printf("%d -> %d : T\n", n->id, tmp->id); break;
      case GREY : printf("%d -> %d : B\n", n->id, tmp->id); break;
      case BLACK: if (n->disc_time < tmp->disc_time) {
                    printf("%d -> %d : F\n", n->disc_time, tmp->disc_time);
                  } else {
                    printf("%d -> %d : C\n", n->id, tmp->id);
                  }
    }
    if (tmp->color == WHITE) {
      tmp->pred = n;
      currTime = graph_dfs_depth_r (g, tmp, currTime,currentDepth+1,maxDepth);
    }
    e = e->next;
  }
  if(currentDepth > *maxDepth)
    *maxDepth = currentDepth;
  n->color = BLACK;
  n->endp_time = ++currTime;

  return currTime;
}
