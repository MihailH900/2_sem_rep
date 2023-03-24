#include "queue.h"
#include "list.h"
#include <stdio.h>

struct Queue
{
	List* q_list;
	size_t size;
};

Queue* init_queue(size_t size)
{
	Queue* q = (Queue* ) malloc(sizeof(Queue));
	if (q == NULL)
	{
		return NULL;
	}

	q->q_list = init();
	q->size = size;
	return q;
}

Queue** init_queues_arr(size_t size, unsigned int count)
{
	Queue** q_arr = (Queue** ) malloc(count * sizeof(Queue* ) );
	if (q_arr == NULL)
	{
		return NULL;
	}

	Queue** ans = q_arr;
	for (unsigned int i = 0; i < count; i++, q_arr++)
	{
		*q_arr = init_queue(size);
	}

	return ans;
}

Queue* shift_elem_in_queues_arr(Queue** q_arr, unsigned int count)
{
	if (count == 1)
	{
		return (*q_arr);
	}

	Queue* m = (*q_arr);
	Queue* k = (*q_arr);
	k++;

	int i = 1;
	void* elem;
	while (i < count)
	{
		elem = pop_queue(k);
		if (elem != NULL)
		{
			push_queue(m, elem);
		}
		i++;
		k++;
	}
}

short push_queue(Queue *q, void *elem)
{
	if (q == NULL)
	{
		return 1;
	}

	return add( &(q->q_list) , elem);
}

void* pop_queue(Queue* q)
{
	return del_front( &(q->q_list) );
}

void* get_queue_top(Queue* q)
{
	if (is_queue_empty(q))
	{
		return NULL;
	}

	return q->q_list->last->next->data;
}

void clear_queues_arr(Queue** q_arr, unsigned int count)
{
	if (q_arr == NULL)
	{
		return;
	}

	Queue** k = q_arr;
	for (unsigned int i = 0; i < count; i++, k++)
	{
		clear_queue(*k);
	}

	free(q_arr);
}

void clear_queue(Queue* q)
{
	clear( &(q->q_list) );
	free(q);
}

char is_queue_empty(Queue* q)
{
	return (q->q_list->last == NULL);
}

char is_queue_full(Queue* q)
{
	return 0; // Whein queue on the list - we can't fill it
}
