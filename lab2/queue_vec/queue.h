#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

typedef struct Queue Queue;

Queue* init_queue(size_t size);
Queue** init_queues_arr(size_t size, unsigned int count);
Queue* shift_elem_in_queues_arr(Queue** q_arr, unsigned int count);
short push_queue(Queue* q, void* elem);
void* pop_queue(Queue* q);
void* get_queue_top(Queue* q);
void clear_queues_arr(Queue** q_arr, unsigned int count);
void clear_queue(Queue* q);
char is_queue_empty(Queue* q);
char is_queue_full(Queue* q);

#endif
