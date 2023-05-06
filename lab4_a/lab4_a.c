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

	return 0;
}

int cmp(const unsigned int* a, const unsigned int* b)
{
	return (*a) < (*b);
}
