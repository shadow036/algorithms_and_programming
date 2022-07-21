#pragma once
enum{ WHITE, GRAY, BLACK};
enum { DISCONNECTED, CONNECTED };
typedef struct vertex_s vertex_t;
typedef struct edge_s edge_t;
struct vertex_s {
	char id;
	int color;
	edge_t* edges;
	vertex_t* next_vertex;
};
struct edge_s {
	int status;
	vertex_t* destination_vertex;
	edge_t* next_edge;
};