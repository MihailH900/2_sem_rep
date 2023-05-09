#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "BST.h"

#define TESTS 100

int cmp(const unsigned int* a, const unsigned int* b);

int main()
{
	srand(time(NULL));
	BST* tree = BST_init( (int (*) (const void*, const void*))cmp);
	
	int n;
	printf("Input numb of elems: ");
	scanf("%d", &n);
	
	Key k;
	Data d;
	
	Key k_1;
	Data d_1;

	Data* ans_1;
	char tree_flag;
	
	k.key_ptr = malloc(sizeof(unsigned int));
	d.data_ptr = malloc(sizeof(unsigned int));
	k.key_size = sizeof(unsigned int);
	d.data_size = sizeof(unsigned int);
	
	k_1.key_ptr = malloc(sizeof(unsigned int));
	d_1.data_ptr = malloc(sizeof(unsigned int));
	k_1.key_size = sizeof(unsigned int);
	d_1.data_size = sizeof(unsigned int);
	for (int i = 0; i < n; i++)
	{	
		*( (unsigned int*) k.key_ptr) = rand();
		*( (unsigned int*) d.data_ptr) = rand();
		
		BST_add(tree, &k, &d);
	}

	set_tree_depth(tree, tree->root, 1);
	
	printf("tree size: %zu, tree depth: %zu\nlog2(size) - %.10lf\ndepth/log2 - %.10lf\n", tree->size, tree->depth, log2(tree->size), ((double)(tree->depth))/log2(tree->size));

	double elapsed = 0;
	for (int i = 0; i < TESTS; i++)
	{		
		*( (unsigned int*) k.key_ptr) = rand();
		*( (unsigned int*) d.data_ptr) = rand();

		clock_t start = clock();
		BST_add(tree, &k, &d);
		clock_t stop = clock();	
		elapsed += (double) (stop-start)*1000.0/CLOCKS_PER_SEC;
	}

	printf("ADD: %.10lf\n", elapsed/TESTS);
	
	elapsed = 0;
	for (int i = 0; i < TESTS; i++)
	{		
		*( (unsigned int*) k.key_ptr) = rand();
		*( (unsigned int*) d.data_ptr) = rand();

		clock_t start = clock();
		BST_delete(tree, &k);
		clock_t stop = clock();	
		elapsed += (double) (stop-start)*1000.0/CLOCKS_PER_SEC;
	}

	printf("Delete: %.10lf\n", elapsed/TESTS);
	
	elapsed = 0;
	for (int i = 0; i < TESTS; i++)
	{		
		*( (unsigned int*) k_1.key_ptr) = rand();

		clock_t start = clock();
		ans_1 = BST_search(tree, &k_1, &tree_flag);
		clock_t stop = clock();	
		elapsed += (double) (stop-start)*1000.0/CLOCKS_PER_SEC;
	}
	
	printf("Search: %.10lf\n", elapsed/TESTS);

	elapsed = 0;
	for (int i = 0; i < TESTS; i++)
	{		
		*( (unsigned int*) k_1.key_ptr) = rand();

		clock_t start = clock();
		const Key* ans_1 = BST_find_next(tree, &k_1, &tree_flag);
		clock_t stop = clock();	
		elapsed += (double) (stop-start)*1000.0/CLOCKS_PER_SEC;
	}

	printf("Search next: %.10lf\n", elapsed/TESTS);
	
	BST_free(tree);
	free(k.key_ptr);
	free(d.data_ptr);
	free(k_1.key_ptr);
	free(d_1.data_ptr);
	
	return 0;
}

int cmp(const unsigned int* a, const unsigned int* b)
{
	return (*a) < (*b);
}
