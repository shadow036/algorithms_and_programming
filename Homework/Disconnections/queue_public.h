#pragma once
#include "queue_private.h"
queue_t* create_queue(char);
void enqueue(queue_t**, queue_t**,char);
char dequeue(queue_t**);