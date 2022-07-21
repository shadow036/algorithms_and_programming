#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph_public.h"
#include "queue_public.h"
void generate_graph(FILE* f) {
	srand(time(0));
	fprintf(f, "%d\n", rand() % 2);
	int number_of_edges = 5 + rand() % 95;
	for (int i = 0; i < number_of_edges; i++)
		fprintf(f, "%c %d %c\n", 97 + rand() % 26, rand() % 10, 97 + rand() % 26);
}
vertex_t* create_graph(FILE* f) {
	vertex_t* graph = NULL;
	char source_id, destination_id;
	int weight;
	int flag;	//flag = 0 means undirected, flag = 1 means directed
	fscanf(f, "%d\n", &flag);
	while (fscanf(f, "%c %d %c\n", &source_id, &weight, &destination_id) != EOF) {
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
		edge_t* new_edge = create_edge(weight, destination_vertex);
		new_edge->next_edge = source_vertex->edges;
		source_vertex->edges = new_edge;
		if (!flag) {
			edge_t* new_edge2 = create_edge(weight, source_vertex);
			new_edge2->next_edge = destination_vertex->edges;
			destination_vertex->edges = new_edge2;
		}
	}
	return graph;
}
vertex_t* create_vertex(char id) {
	vertex_t* new_vertex = (vertex_t*)malloc(sizeof(vertex_t));
	new_vertex->id = id;
	new_vertex->color = WHITE;
	new_vertex->distance = -1;
	new_vertex->predecessor = NULL;
	new_vertex->discovery_time = 0;
	new_vertex->endprocessing_time = 0;
	new_vertex->edges = NULL;
	new_vertex->next_vertex = NULL;
	return new_vertex;
}
edge_t* create_edge(int weight, vertex_t* destination_vertex) {
	edge_t* new_edge = (edge_t*)malloc(sizeof(edge_t));
	new_edge->weight = weight;
	new_edge->destination_vertex = destination_vertex;
	new_edge->next_edge = NULL;
	return new_edge;
}
vertex_t* find(vertex_t* graph, char id) {
	for (vertex_t* temp = graph; temp != NULL; temp = temp->next_vertex) {
		if (temp->id == id)
			return temp;
	}
	return NULL;
}
void bfs(vertex_t *graph,char starting_vertex_id) {
	reset(graph);
	vertex_t* starting_vertex = find(graph, starting_vertex_id);
	if (starting_vertex == NULL)
		exit(EXIT_FAILURE);
	starting_vertex->color = GRAY;
	starting_vertex->distance = 0;
	queue_t* head = NULL;
	queue_t* tail = NULL;
	enqueue(&head, &tail, starting_vertex);
	while (head != NULL) {
		vertex_t* current_vertex = dequeue(&head)->vertex;
		if(current_vertex->predecessor == NULL)
			fprintf(stdout, "\n%c\n  distance: %d\n  predecessor: NULL",current_vertex->id,current_vertex->distance);
		else
			fprintf(stdout, "\n%c\n  distance: %d\n  predecessor: %c", current_vertex->id, current_vertex->distance, current_vertex->predecessor->id);
		for (edge_t* temp = current_vertex->edges; temp != NULL; temp = temp->next_edge) {
			if (temp->destination_vertex->color == WHITE) {
				temp->destination_vertex->color = GRAY;
				temp->destination_vertex->distance = current_vertex->distance + 1;
				temp->destination_vertex->predecessor = current_vertex;
				enqueue(&head, &tail, temp->destination_vertex);
			}
		}
		current_vertex->color = BLACK;
	}
	for (vertex_t* temp = graph; temp != NULL; temp = temp->next_vertex) {
		if(temp->color == WHITE)
			fprintf(stdout, "\n\n%c\n  distance: INFINITY\n  predecessor: NULL", temp->id);
	}
}
void dfs_wrapper(vertex_t* graph, char initial_vertex_id) {
	reset(graph);
	vertex_t* initial_vertex = find(graph, initial_vertex_id);
	if (initial_vertex == NULL)
		exit(EXIT_FAILURE);
	int time = 0;
	dfs(initial_vertex, &time);
	for (vertex_t* temp = graph; temp != NULL; temp = temp->next_vertex) {
		if (temp->color == WHITE)
			//fprintf(stdout, "\n\n%c\n  discovery time: INFINITY\n  endprocessing time: INFINITY", temp->id);
			dfs(temp, &time);
	}
}
void dfs(vertex_t* current_vertex,int *time) {
	current_vertex->color = GRAY;
	current_vertex->discovery_time = (*time)++;
	for (edge_t* temp = current_vertex->edges; temp != NULL; temp = temp->next_edge)
		if (temp->destination_vertex->color == WHITE)
			dfs(temp->destination_vertex, time);
	current_vertex->color = BLACK;
	current_vertex->endprocessing_time = (*time)++;
	fprintf(stdout, "\n%c\n  discovery time: %d\n  endprocessing time: %d", current_vertex->id, current_vertex->discovery_time, current_vertex->endprocessing_time);
}
void reset(vertex_t* graph) {
	for (vertex_t* temp = graph; temp != NULL; temp = temp->next_vertex) {
		temp->color = WHITE;
	}
}
void print_graph(vertex_t* graph) {
	for (vertex_t* temp = graph; temp != NULL; temp = temp->next_vertex) {
		fprintf(stdout, "\n%c => ", temp->id);
		for (edge_t* temp2 = temp->edges; temp2 != NULL; temp2 = temp2->next_edge)
			fprintf(stdout, "%c (%d) -> ", temp2->destination_vertex->id, temp2->weight);
		fprintf(stdout, "NULL");
	}
}