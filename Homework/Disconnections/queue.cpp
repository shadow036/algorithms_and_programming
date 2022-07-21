#include <stdio.h>
#include <stdlib.h>
#include "queue_public.h"
queue_t* create_queue(char id) {
	queue_t* new_queue = (queue_t*)malloc(sizeof(queue_t));
	new_queue->id = id;
	new_queue->next_queue = NULL;
	return new_queue;
}
void enqueue(queue_t** head, queue_t** tail,char id) {
	queue_t* new_queue = create_queue(id);
	if (*head == NULL) {
		*head = new_queue;
		*tail = new_queue;
	}
	else {
		(*tail)->next_queue = new_queue;
		*tail = new_queue;
	}
}
char dequeue(queue_t** head) {
	if (*head == NULL)
		return NULL;
	char id = (*head)->id;
	*head = (*head)->next_queue;
	return id;
}