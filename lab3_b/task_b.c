#include "table.h"
#include "input_funcs.h"
#include <stdio.h>

int main()
{
	Table* t = table_load();
	
	if (t == NULL)
	{
		return 0;
	}

	char flag = 0;	

	char c = 2;
	while (c != OK && c != INPUT_ERROR)
	{
		c = menu(&t);
	}

	table_free(t);

	return 0;
}
