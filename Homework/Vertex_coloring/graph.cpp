#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph_public.h"
void generate_graph(FILE* f) {
	srand(time(0));
	fprintf(f, "%d", rand() % 2);	//0 = undirected, 1 = directed
	int number_of_edges = 5 + rand() % 15;
	for (int i = 0; i < number_of_edges; i++)
		fprintf(f, "\n%c %c", 97 + rand() % 26, 97 + rand() % 26);
}
vertex_t* create_graph(FILE* f) {
	vertex_t* graph = NULL;
	int flag;
	char source_id, destination_id;
	fscanf(f, "%d\n", &flag);
	while (fscanf(f, "%c %c\n", &source_id, &destination_id) != EOF) {
		vertex_t* source_vertex = find(graph, source_id);
		if (source_vertex == NULL) {
			source_vertex = create_vertex(source_id);
			source_vertex->next_vertex = graph;
			graph = source_vertex;
		}
		vertex_t* destination_vertex = find(graph, destination_id);
		if (destination_vertex == NULL) {
			destination_vertex = create_vertex(destination_id);
			destination_vertex->next_vertex = graph;
			graph = destination_vertex;
		}
		edge_t* new_edge = create_edge(destination_vertex);
		new_edge->next_edge = source_vertex->edges;
		source_vertex->edges = new_edge;
		if (!flag) {
			edge_t* new_edge2 = create_edge(source_vertex);
			new_edge2->next_edge = destination_vertex->edges;
			destination_vertex->edges = new_edge2;
		}
	}
	return graph;
}
vertex_t* create_vertex(char id) {
	vertex_t* new_vertex = (vertex_t*)malloc(sizeof(vertex_t));
	new_vertex->id = id;
	new_vertex->color = 0;
	new_vertex->edges = NULL;
	new_vertex->next_vertex = NULL;
	return new_vertex;
}
edge_t* create_edge(vertex_t* destination_vertex) {
	edge_t* new_edge = (edge_t*)malloc(sizeof(edge_t));
	new_edge->destination_vertex = destination_vertex;
	new_edge->next_edge = NULL;
	return new_edge;
}
vertex_t* find(vertex_t*graph, char id) {
	for (vertex_t* temp = graph; temp != NULL; temp = temp->next_vertex)
		if (temp->id == id)
			return temp;
	return NULL;
}
void find_solution_wrapper(vertex_t* graph) {
	fprintf(stdout, "\n");
	for (int i = 1;; i++) {
		fprintf(stdout, "\nChecking with %d colors...", i);
		if (find_solution(graph, graph, i) == 1) {
			fprintf(stdout, "\n\nMinimum number of colors: %d\n", i);
			for (vertex_t* temp = graph; temp != NULL; temp = temp->next_vertex)
				fprintf(stdout, "\nID: %c, color: %d", temp->id, temp->color);
			fprintf(stdout, "\n");
			return;
		}
	}
}
int find_solution(vertex_t * graph,vertex_t* current_vertex, int max_colors) {
	if (current_vertex == NULL) {
		if (validate(graph) == 1)
			return 1;
		return 0;
	}
	for (int i = 0; i < max_colors; i++) {
		current_vertex->color = i;
		if (find_solution(graph, current_vertex->next_vertex, max_colors) == 1)
			return 1;
	}
	return 0;
}
int validate(vertex_t *graph) {
	for (vertex_t* temp = graph; temp != NULL; temp = temp->next_vertex) {
		for (edge_t* temp2 = temp->edges; temp2 != NULL; temp2 = temp2->next_edge) {
			if (temp->color == temp2->destination_vertex->color && temp->id != temp2->destination_vertex->id)
				return 0;
		}
	}
	return 1;
}
void print_graph(vertex_t* graph) {
	for (vertex_t* temp = graph; temp != NULL; temp = temp->next_vertex) {
		fprintf(stdout, "\n%c => ", temp->id);
		for (edge_t* temp2 = temp->edges; temp2 != NULL; temp2 = temp2->next_edge)
			fprintf(stdout, "%c -> ", temp2->destination_vertex->id);
		fprintf(stdout, "NULL");
	}
}
