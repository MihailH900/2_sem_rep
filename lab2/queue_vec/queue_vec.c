#include "queue.h"
#include <stdio.h>

struct Queue
{
	void** arr;
	
	size_t head;
	size_t tail;

	size_t capacity;
	size_t size;
};

Queue* init_queue(size_t size)
{
	Queue* q = malloc(sizeof(Queue));
	if (q == NULL)
	{
		return NULL;
	}

	q->capacity = size;
	q->size = 0;

	q->arr = (void** ) malloc(size * sizeof(void*) );
	if (q->arr == NULL)
	{
		return NULL;
	}

	q->head = 0;
	q->tail = 0;

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
		if (*q_arr == NULL)
		{
			return NULL;
		}
	}

	return ans;
}

Queue* shift_elem_in_queues_arr(Queue** q_arr, unsigned int count)
{
	if (count == 1)
	{
		return (*q_arr);
	}


	Queue** m = q_arr;
	Queue** k = q_arr;

	int i = 1;
	void* elem;
	while (i < count)
	{
		k++;
		elem = pop_queue(*k);
		if (elem != NULL)
		{
			push_queue(*m, elem);
		}
		i++;
	}

	return *k;
}

short push_queue(Queue* q, void* elem)
{
	if (q->size != q->capacity)
	{
		*(q->arr+q->tail) = elem;
		q->tail = (q->tail + 1) % q->capacity;

		q->size++;

		return 0;
	}
	else
	{
		return 1;
	}
}

void* pop_queue(Queue* q)
{
	if (is_queue_empty(q))
	{
		return NULL;
	}
	else
	{
		void* elem = *(q->arr + q->head);

		q->head = (q->head + 1) % q->capacity;

		q->size--;

		return elem;
	}
}

void* get_queue_top(Queue* q)
{
	if (is_queue_empty(q))
	{
		return NULL;
	}

	return *(q->arr + q->head);
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
	if (q == NULL)
	{
		return;
	}

	if (q->arr != NULL)
	{
		free(q->arr);
	}

	free(q);
}

char is_queue_empty(Queue* q)
{
	return (q->size == 0);
}

char is_queue_full(Queue* q)
{
	return (q->size == q->capacity);
}
