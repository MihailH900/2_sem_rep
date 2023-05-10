#include <stdio.h>
#include "input_funcs.h"
#include "B_tree.h"

int cmp(const unsigned int* a, const unsigned int* b);

int main()
{
	B_tree* tree = B_tree_init( (int (*) (const void*, const void*) ) cmp);
	if (tree == NULL)
	{
		return B_TREE_MEMORY_ERROR;
	}

	char flag = menu(tree);
	if (flag == B_TREE_MEMORY_ERROR)
	{
		printf("Memory error\n");
		
		return B_TREE_MEMORY_ERROR;
	}
	else if (flag == BAD_INPUT)
	{
		printf("Sorry, too big numb of wrong input\n");
		B_tree_free(tree);
		return BAD_INPUT;
	}

	B_tree_free(tree);

	return 0;
}

int cmp(const unsigned int* a, const unsigned int* b)
{
	return (*a) < (*b);
}
