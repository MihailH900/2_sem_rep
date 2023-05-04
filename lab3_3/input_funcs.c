#include "input_funcs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char command_type;

char menu(Hash_table* h)
{
	char flag, count;
	command_type command = 0;
	char* key;
	char* data;
	size_t release;
	while (command != 7)
	{
		print_menu();
		command = get_size_t_numb(&flag);

		if (flag == INPUT_ERROR || command == 7)
		{
			printf("End of input\n");
			return INPUT_ERROR;
		}
		else if (command == 1)
		{
			key = readline("Input key: ");
			data = readline("Input data: ");

			flag = hash_table_add(h, key, strlen(key)+1, data, strlen(data)+1);
			if (flag == HASH_TABLE_MEMORY_ERROR)
			{
				return HASH_TABLE_MEMORY_ERROR;
			}
			else if (flag == HASH_TABLE_ADD_SIZE_ERROR)
			{
				printf("Hash table is full\n");
			}
			else
			{
				printf("\nElement added\n");
			}

			free(key);
			free(data);
		}
		else if(command == 2)
		{
			key = readline("Input key: ");
		
			flag = hash_table_delete_by_key(h, key, strlen(key)+1);

			if (flag == HASH_TABLE_FIND_ERROR)
			{
				printf("Can't delete this elem - there is no this key\n");
			}
			else
			{
				printf("\nElement deleted\n");
			}

			free(key);
		}
		else if (command == 3)
		{
			key = readline("Input key: ");
			flag = 1;
			count = 1;
			flag = set_size_t_item_numb(&release, "Input release: ");
			while (count < 3)
			{
				if (flag == INPUT_ERROR)
				{
					return INPUT_ERROR;
				}

				if (flag == BAD_INPUT)
				{
					flag = set_size_t_item_numb(&release, "Input_key: ");
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

			flag = hash_table_delete_by_key_and_version(h, key, strlen(key)+1, release);

			if (flag == HASH_TABLE_FIND_ERROR)
			{
				printf("Can't delete this elem - there is no this key or release\n");
				continue;
			}
			else
			{
				printf("\nElement deleted\n");
			}

			free(key);
		}
		else if (command == 4)
		{
			key = readline("Input key: ");
			
			Hash_table* ans = hash_table_init(h->capacity);

			if (ans == NULL)
			{
				return HASH_TABLE_MEMORY_ERROR;
			}

			flag = hash_table_search_by_key(h, key, strlen(key)+1, ans);
			if (flag == HASH_TABLE_MEMORY_ERROR)
			{
				return HASH_TABLE_MEMORY_ERROR;
			}
			else if (flag == HASH_TABLE_FIND_ERROR)
			{
				printf("Can't find elems with this key\n");
			}
			else
			{
				printf("\nTable with elems with this key\n\n");
				hash_table_print(ans);
			}

			hash_table_free(ans);
			free(key);
		}
		else if (command == 5)
		{	
			key = readline("Input key: ");
			flag = 1;
			count = 1;
			flag = set_size_t_item_numb(&release, "Input release: ");
			while (count < 3)
			{
				if (flag == INPUT_ERROR)
				{
					return INPUT_ERROR;
				}

				if (flag == BAD_INPUT)
				{
					flag = set_size_t_item_numb(&release, "Input_key: ");
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
			
			Node* ans = (Node*) malloc(sizeof(Node));

			if (ans == NULL)
			{
				return HASH_TABLE_MEMORY_ERROR;
			}

			flag = hash_table_search_by_key_and_version(h, key, strlen(key)+1, release, ans);
			if (flag == HASH_TABLE_MEMORY_ERROR)
			{
				return HASH_TABLE_MEMORY_ERROR;
			}
			else if (flag == HASH_TABLE_FIND_ERROR)
			{
				printf("Can't find elem with this key and release\n");
				free(key);
				free(ans);
				continue;
			}
			else
			{
				printf("\nElem with this key:\n");
				printf("Data - %s, relese - %zu\n", (char*)ans->data->data_ptr, ans->release);
			}

			free(ans->data->data_ptr);
			free(ans->data);
			free(ans);
			free(key);
		}
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
	printf("5 - search element with release\n");
	printf("6 - show table\n");
	printf("7 - exit\n\n");
	printf("input command: ");
}
