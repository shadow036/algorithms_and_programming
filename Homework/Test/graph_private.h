#pragma once
typedef struct vertex_s vertex_t;
typedef struct edge_s edge_t;
enum{WHITE,GRAY,BLACK};
struct vertex_s {
	char id;
	int color;
	int distance;
	int discovery_time;
	int endprocessing_time;
	vertex_t* predecessor;
	edge_t* edges;
	vertex_t* next_vertex;
};
struct edge_s {
	int weight;
	vertex_t* destination_vertex;
	edge_t* next_edge;
};