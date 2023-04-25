#include <stdio.h>
#include "table.h"
#include "input_funcs.h"

int main()
{
	Table* t = NULL;
	size_t capacity = 0;
	char flag = set_size_t_item_numb(&capacity, "Enter max table size: ");

	if (flag == INPUT_ERROR)
	{
		return INPUT_ERROR;
	}
	else if (flag == BAD_INPUT)
	{
		printf("Sorry, too big numb of wrong input\n");
		return 0;
	}

	t = table_init(capacity, 0);

	char c = 2;
	while (c != OK && c != INPUT_ERROR)
	{
		c = menu(t);
	}

	table_free(t);

	return 0;
}
