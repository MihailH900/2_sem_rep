#include "input_funcs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char menu(Hash_table* h)
{
	char flag, count;
	char command = 0;
	unsigned int key, parent_key, data;
	while (command != 9)
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
			char* key = readline("Input key: ");
			char* data = readline("Input data: ");

			flag = hash_table_add(h, key, strlen(key)+1, data, strlen(data)+1);
			if (flag == HASH_TABLE_ADD_SIZE_ERROR)
			{
				printf("Hash table is full\n");
				continue;
			}
			else if (flag == HASH_TABLE_MEMORY_ERROR)
			{
				printf("Memory error\n");
				return HASH_TABLE_MEMORY_ERROR;
			}

			printf("Element added\n");
			free(key);
			free(data);
		}
		/*
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
		*/
		else if (command == 4)
		{
			char* key = readline("Input key: ");
			
			Hash_table* ans = hash_table_init(h->capacity);
			flag = hash_table_search(h, key, strlen(key)+1, ans);
			if (flag == HASH_TABLE_FIND_ERROR)
			{
				printf("Can't find elems with this key\n");
			}

			if (flag == HASH_TABLE_MEMORY_ERROR)
			{
				printf("Memory error\n");
				return flag;
			}

			printf("\nTable with elems with this key\n\n");
			hash_table_print(ans);
			
			hash_table_free(ans);
			free(key);
		}
		/*
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
		*/
		else if (command == 6)
		{
			hash_table_print(h);
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
	printf("2 - delete all elements with this key\n");
	printf("3 - delete element with release\n");
	printf("4 - search all elements with this key\n");
	printf("5 - search elemetns with release\n");
	printf("6 - show table\n");
	printf("7 - search all elems with parent key\n");
	printf("8 - import from file\n");
	printf("9 - exit\n\n");
	printf("input command: ");
}
