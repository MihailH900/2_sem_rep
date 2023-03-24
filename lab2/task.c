#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "input_funcs.h"
#include "./queue.h"
#include <math.h>


unsigned int solve(Queue** q_arr, int** ans, int* indexes, Process* k, unsigned int time_step, unsigned int count_of_queues);
void fill_queues_arr(Queue** q_arr, Process* k, size_t size);
void print_ans(int** ans, size_t size, unsigned int max, unsigned int time_step, Process* k);
int cmp(const Process* a, const Process* b);

int main()
{
	printf("Ener size of queue: ");
	char* s = readline();

	unsigned int queue_size;
	if (get_queue_size(s, &queue_size) == 1)
	{
		printf("Bad input, can't read queue size from input string\n");
		return 0;
	}

	printf("Enter input: ");
	char* in = readline();

	size_t size = check_format(in);
	if (size == 0)
	{
		return 0;
	}

	Process* p = (Process *) malloc(size * sizeof(Process) );
	if (p == NULL)
	{
		printf("Memory Error");
		return 0;
	}
	unsigned int time_step;
	parse_input(in, p,  &time_step);

	qsort(p, size, sizeof(Process), (int(*) (const void* , const void* )) cmp);
	
	int** ans = (int**) malloc(size * sizeof(int *) );
	if (ans == NULL)
	{
		printf("Memory Error");
		return 0;
	}
	int** a = ans;

	int* indexes = (int* ) malloc(size * sizeof(int) );
	if (indexes == NULL)
	{
		return 0;
	}
	int* b = indexes;

	Process* k = p;
	for (size_t i = 0; i < size; i++, a++, k++, b++)
	{
		*a = (int* ) malloc( (k->te + time_step - 1) / time_step * 2 * sizeof(int));
		if (*a == NULL)
		{
			printf("Memory Error");
			return 0;
		}
		*b = 0;
	}

	unsigned int count_of_queues = (size + queue_size - 1) / queue_size;
	Queue** q_arr = init_queues_arr(queue_size, count_of_queues);
	if (q_arr == NULL)
	{
		printf("Memory Error");
		return 0;
	}

	k = p;
	fill_queues_arr(q_arr, k, size);

	k = p;
	unsigned int max = solve(q_arr, ans, indexes, k, time_step, count_of_queues);

	k = p;
	print_ans(ans, size, max, time_step, k);

	clear_queues_arr(q_arr, count_of_queues);
	free(indexes);
	a = ans;
	for (size_t i = 0; i < size; i++, a++)
	{
		free(*a);
	}
	free(ans);
	free(p);
	free(in);
	free(s);

	return 0;
}

unsigned int solve(Queue** q_arr, int** ans, int* indexes, Process* k, unsigned int time_step, unsigned int count_of_queues)
{
	int ind = 0;
	unsigned int time = k->tc;
	unsigned int max = 0;
	while (is_queue_empty(*q_arr) != 1)
	{
		Process* item = (Process* ) ( pop_queue(*q_arr) );
		ans[item->id-1][ indexes[item->id - 1] ] = time;
		Queue* help;
		if (item->te >= time_step)
		{
			ans[item->id-1][ indexes[item->id - 1] + 1 ] = time+time_step-1;
			if (max < time+time_step-1)
			{
				max = time+time_step-1;
			}

			indexes[item->id - 1] += 2;
			item->te -= time_step;

			if (item->te == 0)
			{
				help = shift_elem_in_queues_arr(q_arr, count_of_queues);
				time += time_step;
				continue;
			}

			time += time_step;
			
			help = shift_elem_in_queues_arr(q_arr, count_of_queues);
			push_queue(help, item);
		}
		else
		{
			ans[item->id-1][ indexes[item->id - 1] + 1] = time+item->te-1;
			if (max < time+item->te-1)
			{
				max = time+item->te-1;
			}

			indexes[item->id - 1] += 2;
			time += item->te;

			help = shift_elem_in_queues_arr(q_arr, count_of_queues);
		}
		
	}

	return max;
}

void fill_queues_arr(Queue** q_arr, Process* k, size_t size)
{
	Queue** h = q_arr;
	for (size_t i = 0; i < size; i++, k++)
	{
		if ( push_queue(*h, k) )
		{
			h++;
			push_queue(*h, k);
		}
	}
}

void print_ans(int** ans, size_t size, unsigned int max, unsigned int time_step, Process* k)
{
	printf("ID ");
	for (unsigned int i = 0; i <= max; i++)
	{
		printf("%d ", i);
	}
	printf("\n");

	int** a = ans;
	for (size_t i = 0; i < size; i++, a++, k++)
	{
		printf("%ld  ", i+1);
		int* b = *a;
		int x = 0, y = 0;
		for (size_t j = 0; j < (k->te_copy + time_step - 1) / time_step * 2; j++, b++)
		{
			if (j % 2 == 0)
			{
				for (size_t d = y; d < *b; d++)
				{
					printf(" ");
					if (d == 0)
					{
						printf(" ");
						continue;
					}
					for (int f = 0; f < (int)(log10(d)) + 1; f++)
					{	
						printf(" ");
					}
				}
				x = *b;
			}
			else
			{
				for (size_t d = x; d <= *b; d++)
				{
					printf("*");
					if (d == 0)
					{
						printf(" ");
						continue;
					}
					for (int f = 0; f < (int)(log10(d)) + 1; f++)
					{
						printf(" ");
					}
				}
				y = *b+1;
			}
		}
		printf("\n");
	}
}

int cmp(const Process* a, const Process* b)
{
	return a->tc - b->tc;
}
