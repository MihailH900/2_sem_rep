#include "input_funcs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char command_type;

char menu(B_tree* tree)
{
	char flag, count, tree_flag;
	command_type command = 0;
	
	Key k;
	Data d;

	k.key_ptr = malloc(sizeof(unsigned int));
	if (k.key_ptr == NULL)
	{
		return B_TREE_MEMORY_ERROR;
	}
	d.data_ptr = malloc(sizeof(unsigned int));
	if (d.data_ptr == NULL)
	{
		return B_TREE_MEMORY_ERROR;
	}

	k.key_size = sizeof(unsigned int);
	d.data_size = sizeof(unsigned int);

	while (command != 6)
	{
		print_menu();
		command = get_size_t_numb(&flag);

		if (flag == INPUT_ERROR || command == 6)
		{
			printf("End of input\n");
			free(k.key_ptr);
			free(d.data_ptr);
			return INPUT_ERROR;
		}
		else if (command == 1)
		{
			flag = 1;
			count = 1;
			flag = get_params_for_add(tree, &k, &d);
			while (flag != OK && count < 3)
			{
				if (flag == INPUT_ERROR)
				{
					return INPUT_ERROR;
				}
				
				flag = get_params_for_add(tree, &k, &d);
				count++;
			}
			if (count == 3)
			{
				printf("Too big numb of wrong input\nReturn to menu\n\n");
				continue;
			}

			/*flag = BST_add(tree, &k, &d);
			if (flag == BST_MEMORY_ERROR)
			{
				return BST_MEMORY_ERROR;
			}
			*/

			printf("\nElement added\n");
		}
		else if(command == 2)
		{
			flag = 1;
			count = 1;
			flag = set_unsigned_item_numb(k.key_ptr, "Input key: ");
			while (count < 3)
			{
				if (flag == INPUT_ERROR)
				{
					printf("End of input\n");
					return INPUT_ERROR;
				}
				else if (flag == BAD_INPUT)
				{
					flag = set_unsigned_item_numb(k.key_ptr, "Input key: ");
					count++;
					continue;
				}

				break;
			}
			if (count == 3)
			{
				printf("Sorry, too big numb of wrong input\n");
				return BAD_INPUT;
			}

			/*flag = BST_delete(tree, &k);
			if (flag == BST_FIND_ERROR)
			{
				printf("\nCan't find this key\n");
				continue;
			}
			*/

			printf("\nElement deleted\n");
		}
		else if (command == 3)
		{
			flag = 1;
			count = 1;
			flag = set_unsigned_item_numb(k.key_ptr, "Input key: ");
			while (count < 3)
			{
				if (flag == INPUT_ERROR)
				{
					printf("End of input\n");
					return INPUT_ERROR;
				}
				else if (flag == BAD_INPUT)
				{
					flag = set_unsigned_item_numb(k.key_ptr, "Input key: ");
					count++;
					continue;
				}

				break;
			}
			if (count == 3)
			{
				printf("Sorry, too big numb of wrong input\n");
				return BAD_INPUT;
			}

			/*Data* ans = BST_search(tree, &k, &tree_flag);

			if (tree_flag == BST_NOT_INIT_ERROR)
			{
				printf("Tree not init\n");
				return BST_NOT_INIT_ERROR;
			}

			if (ans == NULL)
			{
				printf("\nCan't find this elem\n");
				continue;
			}

			printf("\nElem data: %u\n", *( (unsigned int*)(ans->data_ptr)));
			*/
		}
		else if (command == 4)
		{
			flag = 1;
			count = 1;
			flag = set_unsigned_item_numb(k.key_ptr, "Input key: ");
			while (count < 3)
			{
				if (flag == INPUT_ERROR)
				{
					printf("End of input\n");
					return INPUT_ERROR;
				}
				else if (flag == BAD_INPUT)
				{
					flag = set_unsigned_item_numb(k.key_ptr, "Input key: ");
					count++;
					continue;
				}

				break;
			}
			if (count == 3)
			{
				printf("Sorry, too big numb of wrong input\n");
				return BAD_INPUT;
			}

			/*const Key* ans = BST_find_next(tree, &k, &tree_flag);

			if (tree_flag == BST_NOT_INIT_ERROR)
			{
				printf("Tree not init\n");
				return BST_NOT_INIT_ERROR;
			}

			if (ans == NULL)
			{
				printf("\nCan't find next key\n");
				continue;
			}

			printf("\nNext key: %u\n", *( (unsigned int*)(ans->key_ptr)));
			*/
		}
		else if (command == 5)
		{
			//BST_print(tree->root, 0);
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
	printf("1 - add the element\n");
	printf("2 - delete the element\n");
	printf("3 - search the element\n");
	printf("4 - search the element, that is greater than the given\n");
	printf("5 - show tree\n");
	printf("6 - exit\n\n");
	printf("input command: ");
}

char get_params_for_add(B_tree* tree, Key* k, Data* d)
{
	char flag, tree_flag;
	char count = 1;
	Data* res;

	flag = set_unsigned_item_numb( (unsigned int*) k->key_ptr, "Input key: ");
	while (count < 3)
	{
		if (flag == INPUT_ERROR)
		{
			printf("End of input\n");
			return INPUT_ERROR;
		}
		else if (flag == BAD_INPUT)
		{
			flag = set_unsigned_item_numb( (unsigned int*) k->key_ptr, "Input key: ");
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
	flag = set_unsigned_item_numb( (unsigned int*) d->data_ptr, "Input data: ");
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
			flag = set_unsigned_item_numb(d->data_ptr, "Input data: ");
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
