#include "table.h"
#include "input_funcs.h"
#include <stdio.h>

int main()
{
	Table* t = NULL;
	size_t capacity = 0;
	char flag = 0;	

	char* file_name = readline("Enter file name: ");
	if ( (t = table_load_from_binary_file(file_name)) == NULL)
	{
		printf("Bad file name. We are goint to create new file and new table in this run of program");	
		
		size_t capacity = 0;
		flag = set_size_t_item_numb(&capacity, "Enter max table size: ");

		if (flag == INPUT_ERROR)
		{
			return INPUT_ERROR;
		}
		else if (flag == BAD_INPUT)
		{
			printf("Sorry, too big numb of wrong input\n");
			return 0;
		}
		
		t = create_new_table(file_name, capacity);
	}

	char c = 2;
	while (c != 1 && c != 0)
	{
		c = menu(*t);
	}

	table_free(*t);

	return 0;
}
