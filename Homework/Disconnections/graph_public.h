#pragma once
#include "graph_private.h"
void generate_graph(FILE*);
vertex_t* create_graph(FILE*);
vertex_t* create_vertex(char);
edge_t* create_edge(vertex_t*);
vertex_t* find(vertex_t*, char);
void find_solution_wrapper(vertex_t*);
int find_solution(vertex_t*, int, int);
int validate(vertex_t*);
void reset(vertex_t*);
void change_status(vertex_t *,vertex_t *, int);
void print_graph(vertex_t*);