#pragma once
typedef struct queue_s queue_t;
struct queue_s {
	char id;
	queue_t* next_queue;
};