#pragma once
#include "queue_private.h"
queue_t* create_queue(vertex_t*);
void enqueue(queue_t **,queue_t **,vertex_t *);
queue_t* dequeue(queue_t**);