#include "input_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

char menu(Table* t)
{
	char command = 0, flag;
	unsigned int key, parent_key, data;
	while (command != 6)
	{
		print_menu();
		command = get_numb_greater_zero(&flag);
		
		if (flag == -2)
		{
			printf("End of input\n");
			return 1;
		}
		else if (command == 1)
		{
			if (get_params_for_add(&key, &parent_key, &data) == 1)
			{
				return 1;
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
				return 1;
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
				return 1;
			}

			Item ans = get_elem_with_this_key(t, key);
			
			if (ans.data == NULL)
			{
				printf("Bad key, there is no elem in thos table\n");
			}
			else
			{
				printf("Elem - %d\n", *ans.data);
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
				return 1;
			}

			Table* ans = table_search_by_parent_key(t, parent_key);
			table_print(ans);
			table_free(ans);
		}
		printf("\n");
	}

	return 0;

}

void print_menu()
{
	printf("1 - add element\n");
	printf("2 - delete element\n");
	printf("3 - search by key\n");
	printf("4 - show table\n");
	printf("5 - search all elems with parent key\n");
	printf("6 - exit\n\n");
	printf("input command: ");
}

char get_params_for_add(unsigned int* key, unsigned int* parent_key, unsigned int* data)
{
	if (set_item_numb(key, "input key: ") == 1)
	{
		return 1;
	}

	if (set_item_numb(parent_key, "input parent key: ") == 1)
	{
		return 1;
	}

	if (set_item_numb(data, "input data: ") == 1)
	{
		return 1;
	}

	return 0;
}

char set_item_numb(unsigned int* item, const char* s)
{
	char flag;
	printf("%s", s);
	(*item) = get_numb_greater_zero(&flag);
	while ( flag < 0)
	{
		if (flag == -2)
		{
			printf("End of input\n");
			return 1;
		}
		else if (flag == -1)
		{
			printf("Bad input, try again\n");
		}

		printf("%s", s);
		(*item) = get_numb_greater_zero(&flag);
	}

	return 0;
}

size_t get_numb_greater_zero(char* flag)
{
	char c;
	size_t ans = 0;
	while ( (c = getchar()) != EOF)
	{
		if ( (c != '\n') && (c < '0' || c > '9') )
		{
			while (c != '\n')
			{
				c = getchar();
			}
			
			*flag = -1;
			return 0;
		}
		else if (c == '\n')
		{
			*flag = 0;
			return ans/10;
		}
		else
		{
			ans += (c - '0');
			ans *= 10;	
		}
	}

	*flag = -2;
	return ans;
}
