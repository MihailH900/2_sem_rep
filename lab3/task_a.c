#include "table.h"
#include "input_funcs.h"
#include <stdio.h>

void print_menu();

int main()
{
	Table* t = NULL;
	size_t capacity = 0;
	char flag;

	printf("Enter max table size: ");
	while ( (capacity = get_numb_greater_zero(&flag)) < 0)
	{
		if (capacity == -2)
		{
			printf("End of input\n");
			return 0;
		}
		else if (capacity == -1)
		{
			printf("Bad input, try again\n");
		}

		printf("Enter max table size: ");
	}

	t = table_init(capacity);
	char command = 0;
	while (command != 4)
	{
		print_menu();
		command = get_numb_greater_zero(&flag);
		
		if (command == -2)
		{
			printf("End of input\n");
			return 0;
		}
		else if (command == 1)
		{
			unsigned int key, parent_key, data;
			printf("Key, parent key, data\n");
			scanf("%u %u %u", &key, &parent_key, &data);
			if (table_add(t, key, parent_key, data) == 2)
			{
				printf("Can't add this elem\n");
			}
			getchar();
		}
		else if(command == 2)
		{
			unsigned int key;
			printf("Key\n");
			scanf("%u", &key);
			table_delete_by_key(t, key);
			getchar();
		}
		else if (command == 3)
		{
			table_print(t);
		}
	}

	table_free(t);

	return 0;
}

void print_menu()
{
	printf("1 - add element\n");
	printf("2 - delete element\n");
	printf("3 - show table\n");
	printf("input command: ");
}
