#include "input_funcs.h"
#include <stdio.h>

char menu(Table* t)
{
	char flag, count;
	char command = 0;
	unsigned int key, parent_key, data;
	while (command != 7)
	{
		print_menu();
		command = get_size_t_numb(&flag);

		if (flag == INPUT_ERROR)
		{
			printf("End of input\n");
			return INPUT_ERROR;
		}
		else if (command == 1)
		{
			flag = 1;
			count = 1;
			flag = get_params_for_add(t, &key, &parent_key, &data);
			while (flag != OK && count < 3)
			{
				if (flag == INPUT_ERROR)
				{
					return INPUT_ERROR;
				}
				
				flag = get_params_for_add(t, &key, &parent_key, &data);
				count++;
			}
			if (count == 3)
			{
				printf("Too big numb of wrong input\nReturn to menu\n\n");
				continue;
			}

			flag = table_add(t, key, parent_key, data);
			if (flag == TABLE_ADD_SIZE_ERROR)
			{
				printf("\nCan't add this element, table if full\n\n");
				continue;
			}
			
			printf("\nElement added\n");
		}
		else if(command == 2)
		{
			flag = 1;
			count = 1;
			flag = set_unsigned_item_numb(&key, "Input key: ");
			while (count < 3)
			{
				if (flag == INPUT_ERROR)
				{
					return INPUT_ERROR;
				}

				if (flag == BAD_INPUT)
				{
					flag = set_unsigned_item_numb(&key, "Input_key: ");
					count++;
					continue;
				}

				if ( table_search_by_key(t, key) == t->size && t->base_key != key)
				{
					printf("Can't find this key in table. Try again\n");
					flag = set_unsigned_item_numb(&key, "Input key: ");
					count++;
					continue;
				}

				break;
			}
			if (count == 3)
			{
				printf("Too big numb of wrong input\nReturn to menu\n\n");
				continue;
			}
			
			table_delete_by_key(t, key);

			printf("\nElement deleted\n");
		}
		else if (command == 3)
		{
			flag = 1;
			count = 1;
			flag = set_unsigned_item_numb(&key, "Input key: ");
			while (count < 3)
			{
				if (flag == INPUT_ERROR)
				{
					return INPUT_ERROR;
				}

				if (flag == BAD_INPUT)
				{
					flag = set_unsigned_item_numb(&key, "Input_key: ");
					count++;
					continue;
				}

				break;
			}
			if (count == 3)
			{
				printf("Too big numb of wrong input\nReturn to menu\n\n");
				continue;
			}

			Item ans = get_elem_with_this_key(t, key);
			
			if (ans.data == NULL)
			{
				printf("\nBad key, there is no elem in thos table\n");
			}
			else
			{
				printf("\nElem - %d\n", *ans.data);
				free(ans.data);
			}
		}
		else if (command == 4)
		{
			printf("\n");
			table_print(t);
		}
		else if (command == 5)
		{
			flag = 1;
			count = 1;
			flag = set_unsigned_item_numb(&parent_key, "Input parent key: ");
			while (count < 3)
			{
				if (flag == INPUT_ERROR)
				{
					return INPUT_ERROR;
				}

				if (flag == BAD_INPUT)
				{
					flag = set_unsigned_item_numb(&parent_key, "Input parent key: ");
					count++;
					continue;
				}

				break;
			}
			if (count == 3)
			{
				printf("Too big numb of wrong input\nReturn to menu\n\n");
				continue;
			}

			Table* ans = table_search_by_parent_key(t, parent_key);
			
			table_print(ans);
			table_free(ans);
		}
		else if (command == 6)
		{
			char* file_name = readline("Input file name: ");

			if (file_name == NULL)
			{
				return INPUT_ERROR;
			}

			flag = set_size_t_item_numb( &(t->size), "Enter table size: ");
			if (flag == INPUT_ERROR)
			{
				return INPUT_ERROR;
			}
			else if (flag == BAD_INPUT)
			{
				printf("Sorry, too big numb of wrong input\n");
				return 0;
			}
			
			if (get_table_elements_from_file(t, file_name) == TABLE_FILE_ERROR)
			{
				printf("Bad file name\n");
			}

			free(file_name);
		}
		else
		{
			printf("Bad input\n");
		}
	}

	return OK;
}

void print_menu()
{
	printf("\n");
	printf("1 - add element\n");
	printf("2 - delete element\n");
	printf("3 - search by key\n");
	printf("4 - show table\n");
	printf("5 - search all elems with parent key\n");
	printf("6 - import from file\n");
	printf("7 - exit\n\n");
	printf("input command: ");
}

char get_params_for_add(Table* t, unsigned int* key, unsigned int* parent_key, unsigned int* data)
{
	char flag;
	char count = 1;

	flag = set_unsigned_item_numb(key, "Input key: ");
	while (count < 3)
	{
		if (flag == INPUT_ERROR)
		{
			printf("End of input\n");
			return INPUT_ERROR;
		}
		else if (flag == BAD_INPUT)
		{
			flag = set_unsigned_item_numb(key, "Input key: ");
			count++;
			continue;
		}

		if (table_search_by_key(t, *key) != t->size)
		{
			printf("Bad input, there is a same key in table, try again\n");
			flag = set_unsigned_item_numb(key, "Input key: ");
			count++;
			continue;
		}

		break;
	}
	if (count == 3)
	{
		printf("Bad key\n\n");
		return BAD_INPUT;
	}

	count = 1;
	flag = set_unsigned_item_numb(parent_key, "Input parent key: ");
	while (count < 3)
	{
		if (flag == INPUT_ERROR)
		{
			return flag;
		}
		else if (flag == BAD_INPUT)
		{
			flag = set_unsigned_item_numb(parent_key, "Input parent key: ");
			count++;
			continue;
		}
		
		if (table_search_by_key(t, *parent_key) == t->size && *parent_key != 0 && *parent_key != t->base_key)
		{
			printf("Bad input, there is no this parent key or this key isn't base key. Try again\n");
			flag = set_unsigned_item_numb(parent_key, "Input parent key: ");
			count++;
			continue;
		}

		break;
	}
	if (count == 3)
	{
		printf("Bad parent key\n\n");
		return BAD_INPUT;
	}

	count = 1;
	flag = set_unsigned_item_numb(data, "Input data: ");
	while (count < 3)
	{
		count++;
		if (flag == INPUT_ERROR)
		{
			return flag;
		}
		
		if (flag == BAD_INPUT)
		{
			printf("Bad input, try again\n");
			flag = set_unsigned_item_numb(data, "Input data: ");
			count++;
			continue;
		}

		break;
	}
	if (count == 3)
	{
		printf("Bad data\n\n");
		return BAD_INPUT;
	}

	return OK;
}
