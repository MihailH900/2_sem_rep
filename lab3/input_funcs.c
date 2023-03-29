#include "input_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

char* readline()
{
	char* ptr = (char*) malloc(1);
	char buf[81];
	int n, len = 0;
	*ptr = '\0';

	do
	{
		n = scanf("%80[^\n]", buf);

		if (n < 0)
		{
			free(ptr);
			ptr = NULL;
			continue;
		}

		if (n == 0)
		{
			scanf("%*c");
		}
		else
		{
			len += strlen(buf);
			ptr = (char*) realloc(ptr, len+1);
			if (ptr == NULL)
			{
				return NULL;
			}

			ptr = strcat(ptr, buf);
		}
	} while (n > 0);

	return ptr;
}

//char get_key(unsigned int* key)
//{
//	(*key) = get_numb_greater_zero();
//	if ( (*key) == -2)
//	{
//
//	}
//}

//char get_parent_key(unsigned int* parent_key)
//{
//	
//}

//char get_data(unsigned int* data)
//{
//
//}

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

			return -1;
		}
		else if (c == '\n')
		{
			return ans/10;
		}
		else
		{
			ans += (c - '0');
			ans *= 10;	
		}
	}

	return -2;
}
