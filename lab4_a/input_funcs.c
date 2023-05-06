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
			flag = 1;
			count = 1;
			flag = get_params_for_add(&key, &data);
			while (flag != OK && count < 3)
			{
				if (flag == INPUT_ERROR)
				{
					return INPUT_ERROR;
				}
				
				flag = get_params_for_add(&key, &data);
				count++;
			}
			if (count == 3)
			{
				printf("Too big numb of wrong input\nReturn to menu\n\n");
				continue;
			}
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

		}
		else if (command == 6)
		{

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

char get_params_for_add(BST* tree,unsigned int* key, unsigned int* data)
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

		if (BST_search(tree, key, sizeof(*key)) != t->size)
		{
			printf("Bad input, there is a same key in tree, try again\n");
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
