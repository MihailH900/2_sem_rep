#include <stdio.h>
#include "input_funcs.h"
#include "BST.h"

int cmp(const unsigned int* a, const unsigned int* b);

int main()
{
	BST* tree = BST_init( (int (*) (const void*, const void*))cmp);
	if (tree == NULL)
	{
		return BST_MEMORY_ERROR;
	}

	char flag = menu(tree);
	if (flag == BST_MEMORY_ERROR)
	{
		printf("Memory error\n");
		
		return BST_MEMORY_ERROR;
	}
	else if (flag == BAD_INPUT)
	{
		printf("Sorry, too big numb of wrong input\n");
		BST_free(tree);
		return BAD_INPUT;
	}

	BST_free(tree);

	return 0;
}

int cmp(const unsigned int* a, const unsigned int* b)
{
	return (*a) < (*b);
}
