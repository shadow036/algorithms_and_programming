#pragma once
#include "graph_private.h"
typedef struct queue_s queue_t;
struct queue_s {
	vertex_t* vertex;
	queue_t* next_queue;
};