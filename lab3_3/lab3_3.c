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
		return 0;
	}

	h = hash_table_init(capacity);

	char c = 2;
	while (c != OK && c != INPUT_ERROR && c != HASH_TABLE_MEMORY_ERROR)
	{
		c = menu(h);
	}

	hash_table_free(h);

	return 0;
}
