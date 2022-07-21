#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph_public.h"
#include "queue_public.h"
void generate_graph(FILE* f) {
	srand(time(0));
	int number_of_edges = 5 + rand()%95;
	for (int i = 0; i < number_of_edges; i++)
		fprintf(f, "%c %c\n",97 + rand()%26,97 + rand()%26);
}
vertex_t* create_graph(FILE* f) {
	vertex_t* graph = NULL;
	char source_id, destination_id;
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
		edge_t* new_edge2 = create_edge(source_vertex);
		new_edge2->next_edge = destination_vertex->edges;
		destination_vertex->edges = new_edge2;
	}
	return graph;
}
vertex_t* create_vertex(char id) {
	vertex_t* new_vertex = (vertex_t*)malloc(sizeof(vertex_t));
	new_vertex->id = id;
	new_vertex->color = WHITE;
	new_vertex->edges = NULL;
	new_vertex->next_vertex = NULL;
	return new_vertex;
}
edge_t* create_edge(vertex_t* destination_vertex) {
	edge_t* new_edge = (edge_t*)malloc(sizeof(edge_t));
	new_edge->status = CONNECTED;
	new_edge->destination_vertex = destination_vertex;
	new_edge->next_edge = NULL;
	return new_edge;
}
vertex_t* find(vertex_t* graph, char id) {
	for (vertex_t* temp = graph; temp != NULL; temp = temp->next_vertex)
		if (temp->id == id)
			return temp;
	return NULL;
}
void find_solution_wrapper(vertex_t* graph) {
	fprintf(stdout, "\n");
	for (int i = 0;; i++) {
		fprintf(stdout, "\nChecking with %d disconnections...", i);
		if (find_solution(graph, 0, i) == 1) {
			fprintf(stdout, "\n\nNumber of disconnections: %d\nDisconnections\n", i);
			for (vertex_t* temp = graph; temp != NULL; temp = temp->next_vertex) {
				for (edge_t* temp2 = temp->edges; temp2 != NULL; temp2 = temp2->next_edge) {
					if (temp2->status == DISCONNECTED)
						fprintf(stdout, "  (%c -> %c)\n", temp->id, temp2->destination_vertex->id);
				}
			}
			return;
		}
	}
}
int find_solution(vertex_t* graph, int disconnections, int max_disconnections) {
	if (disconnections == max_disconnections) {
		if (validate(graph) == 1)
			return 1;
		return 0;
	}
	for (vertex_t* temp = graph; temp != NULL; temp = temp->next_vertex) {
		for (edge_t* temp2 = temp->edges; temp2 != NULL; temp2 = temp2->next_edge) {
			if (temp2->status == CONNECTED) {
				change_status(temp, temp2->destination_vertex, DISCONNECTED);
				if (find_solution(graph, disconnections + 1, max_disconnections) == 1)
					return 1;
				change_status(temp, temp2->destination_vertex, CONNECTED);
			}
		}
	}
	return 0;
}
int validate(vertex_t* graph) {	//THIS IS BASICALLY A BFS
	reset(graph);
	graph->color = GRAY;
	queue_t* head = NULL;
	queue_t* tail = NULL;
	enqueue(&head, &tail, graph->id);
	while (head != NULL) {
		vertex_t* current_vertex = find(graph, dequeue(&head));
		for (edge_t* temp = current_vertex->edges; temp != NULL; temp = temp->next_edge) {
			if (temp->destination_vertex->color == WHITE && temp->status == CONNECTED) {
				temp->destination_vertex->color = GRAY;
				enqueue(&head, &tail, temp->destination_vertex->id);
			}
		}
		current_vertex->color = BLACK;
	}
	for (vertex_t* temp = graph; temp != NULL; temp = temp->next_vertex)
		if (temp->color == WHITE)
			return 1;
	return 0;
}
void reset(vertex_t* graph) {
	for (vertex_t* temp = graph; temp != NULL; temp = temp->next_vertex)
		temp->color = WHITE;
}
void change_status(vertex_t* vertex1, vertex_t* vertex2, int new_state) {
	for (edge_t* temp = vertex1->edges; temp != NULL; temp = temp->next_edge) {
		if (temp->destination_vertex == vertex2 && temp->status != new_state) {
			temp->status = new_state;
			break;
		}
	}
	for (edge_t* temp = vertex2->edges; temp != NULL; temp = temp->next_edge) {
		if (temp->destination_vertex == vertex1 && temp->status != new_state) {
			temp->status = new_state;
			break;
		}
	}
}
void print_graph(vertex_t* graph) {
	for (vertex_t* temp = graph; temp != NULL; temp = temp->next_vertex) {
		fprintf(stdout, "\n%c => ",temp->id);
		for (edge_t* temp2 = temp->edges; temp2 != NULL; temp2 = temp2->next_edge)
			fprintf(stdout, "%c -> ",temp2->destination_vertex->id);
		fprintf(stdout, "NULL");
	}
}