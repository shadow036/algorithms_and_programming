#pragma once
#include "graph_private.h"
void generate_graph(FILE*);
vertex_t* create_graph(FILE*);
vertex_t* create_vertex(char);
edge_t* create_edge(int,vertex_t*);
vertex_t* find(vertex_t*, char);
void bfs(vertex_t *,char);
void dfs_wrapper(vertex_t*, char);
void dfs(vertex_t *,int *);
void reset(vertex_t*);
void print_graph(vertex_t*);