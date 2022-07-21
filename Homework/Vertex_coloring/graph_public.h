#pragma once
#include "graph_private.h"
void generate_graph(FILE *);
vertex_t* create_graph(FILE *);
vertex_t* create_vertex(char);
edge_t* create_edge(vertex_t*);
vertex_t* find(vertex_t*, char);
void print_graph(vertex_t*);
void find_solution_wrapper(vertex_t *);
int find_solution(vertex_t *, vertex_t *,int);
int validate(vertex_t*);