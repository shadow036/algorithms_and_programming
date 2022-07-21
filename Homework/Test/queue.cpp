#include "queue_public.h"
#include <stdio.h>
#include <stdlib.h>
queue_t* create_queue(vertex_t* vertex) {
	queue_t* new_queue = (queue_t*)malloc(sizeof(queue_t));
	new_queue->vertex = vertex;
	new_queue->next_queue = NULL;
	return new_queue;
}
void enqueue(queue_t** head, queue_t** tail, vertex_t* vertex) {
	queue_t* new_queue = create_queue(vertex);
	if (*head == NULL) {
		*head = new_queue;
		*tail = new_queue;
	}
	else
	{
		(*tail)->next_queue = new_queue;
		*tail = new_queue;
	}
}
queue_t* dequeue(queue_t** head) {
	if (*head == NULL)
		return NULL;
	queue_t* temp = *head;
	(*head) = (*head)->next_queue;
	return temp;
}