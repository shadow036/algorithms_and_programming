#ifndef NEW_H_INCLUDED
#define NEW_H_INCLUDED
#include "graph.h"
#define EDGE_TYPES 4
int graph_bfs_count(graph_t *, vertex_t *);
void clearColors(graph_t *);
void graph_bfs_distance(graph_t *, vertex_t *,int *);
void graph_dfs_type(graph_t *, vertex_t *);
int graph_dfs_type_r(graph_t *, vertex_t *,int,int *);
void graph_dfs_depth(graph_t *, vertex_t *);
int graph_dfs_depth_r(graph_t *, vertex_t *,int,int,int *);
#endif // NEW_H_INCLUDED
