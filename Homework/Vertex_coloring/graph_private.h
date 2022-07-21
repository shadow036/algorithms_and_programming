#pragma once
typedef struct vertex_s vertex_t;
typedef struct edge_s edge_t;
struct vertex_s {
	char id;
	int color;
	edge_t* edges;
	vertex_t* next_vertex;
};
struct edge_s {
	vertex_t* destination_vertex;
	edge_t* next_edge;
};