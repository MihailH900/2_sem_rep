#include "table.h"
#include "input_funcs.h"
#include <stdio.h>

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
	printf("\n");

	t = table_init(capacity, 0);

	char c = 2;
	while (c != OK && c != INPUT_ERROR)
	{
		c = menu(t);
	}

	table_free(t);

	/*
	char command = 0;
	unsigned int key, parent_key, data;
	while (command != 6)
	{

		print_menu();
		command = get_numb_greater_zero(&flag);
		
		if (flag == -2)
		{
			printf("End of input\n");
			return 0;
		}
		else if (command == 1)
		{
			if (get_params_for_add(&key, &parent_key, &data) == 1)
			{
				return 0;
			}

			if (table_add(t, key, parent_key, data) == 2)
			{
				printf("Can't add this elem\n");
			}
		}
		else if(command == 2)
		{
			if (set_item_numb(&key, "input key: ") == 1)
			{
				return 0;
			}
			
			if (table_delete_by_key(t, key) == 2)
			{
				printf("Can't remove this elem\n");
			}
		}
		else if (command == 3)
		{
			if (set_item_numb(&key, "input key: ") == 1)
			{
				return 0;
			}

			Item ans = get_elem_with_this_key(t, key);
			
			if (ans.data == NULL)
			{
				printf("Bad key, there is no elem in thos table\n");
				getchar();
			}
			else
			{
				printf("Elem - %d\n", *ans.data);
				getchar();
			}
		}
		else if (command == 4)
		{
			printf("\n");
			table_print(t);
		}
		else if (command == 5)
		{
			if (set_item_numb(&parent_key, "input parent key: ") == 1)
			{
				return 0;
			}

			Table* ans = table_search_by_parent_key(t, parent_key);
			table_print(ans);
			table_free(ans);
		}
		printf("\n");
	}

	table_free(t);
	*/

	return 0;
}
