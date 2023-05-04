#include "input_funcs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char command_type;

char menu(BST* tree)
{
	char flag, count;
	command_type command = 0;
	unsigned int key, data;
	while (command != 6)
	{
		print_menu();
		command = get_size_t_numb(&flag);

		if (flag == INPUT_ERROR || command == 6)
		{
			printf("End of input\n");
			return INPUT_ERROR;
		}
		else if (command == 1)
		{
			flag = 1;
			count = 1;
			flag = set_unsigned_item_numb(&key, "Input key: ");
			while (count < 3)
			{
				if (flag == INPUT_ERROR)
				{
					printf("End of input\n");
					return INPUT_ERROR;
				}
				else if (flag == BAD_INPUT)
				{
					flag = set_unsigned_item_numb(&key, "Input key: ");
					count++;
					continue;
				}

				if (BST_search(tree, &key, sizeof(unsigned int)) != NULL)
				{
					printf("Bad input, there is a same key in tree, try again\n");
					flag = set_unsigned_item_numb(&key, "Input key: ");
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

			flag = BST_add(tree, &key, sizeof(unsigned int));
			if (flag == BST_MEMORY_ERROR)
			{
				return BST_MEMORY_ERROR;
			}

			printf("\nElement added\n");
		}
		else if(command == 2)
		{

		}
		else if (command == 3)
		{

		}
		else if (command == 4)
		{

		}
		else if (command == 5)
		{
			BST_print(tree->root, 0);
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
