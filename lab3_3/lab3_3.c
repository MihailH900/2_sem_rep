#include <stdio.h>
#include "hash_table.h"
#include "input_funcs.h"

int main()
{
	Hash_table* h = NULL;
	size_t capacity = 0;
	char flag = set_size_t_item_numb(&capacity, "Enter max hash_table size: ");

	if (flag == INPUT_ERROR)
	{
		return INPUT_ERROR;
	}
	else if (flag == BAD_INPUT)
	{
		printf("Sorry, too big numb of wrong input\n");
		return BAD_INPUT;
	}

	h = hash_table_init(capacity);

	if (h == NULL)
	{
		printf("Memory error\n");
		return HASH_TABLE_MEMORY_ERROR;
	}

	flag = menu(h);
	if (flag == HASH_TABLE_MEMORY_ERROR)
	{
		printf("Memory error\n");
		
		return HASH_TABLE_MEMORY_ERROR;
	}

	hash_table_free(h);

	return 0;
}
