#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "parse_input.h"

char set_size_t_item_numb(size_t* data, const char* s)
{
	char flag;
	char count = 1;
	printf("%s", s);
	(*data) = get_size_t_numb(&flag);
	while (count < 3 )
	{
		if (flag == INPUT_ERROR)
		{
			printf("End of input\n");
			return INPUT_ERROR;
		}
		else if (flag == BAD_INPUT)
		{
			printf("Bad input, try again\n");
			
			printf("%s", s);
			(*data) = get_size_t_numb(&flag);
			count++;
			continue;
		}

		break;
	}

	if (count == 3)
	{
		printf("Too big numb of bad input\n\n");
		return BAD_INPUT;
	}

	return OK;
}

char set_unsigned_item_numb(unsigned int* data, const char* s)
{
	char flag;
	char count = 1;
	printf("%s", s);
	(*data) = get_unsigned_numb(&flag);
	while (count < 3 )
	{
		if (flag == INPUT_ERROR)
		{
			printf("End of input\n");
			return INPUT_ERROR;
		}
		else if (flag == BAD_INPUT)
		{
			printf("Bad input, try again\n");
			
			printf("%s", s);
			(*data) = get_unsigned_numb(&flag);
			count++;
			continue;
		}

		break;
	}

	if (count == 3)
	{
		printf("Too big numb of bad input\n\n");
		return BAD_INPUT;
	}

	return OK;
}

size_t get_size_t_numb(char* flag)
{
	char c;
	size_t ans = 0;
	size_t size = log10(ULLONG_MAX)+1;
	size_t help = ULLONG_MAX;

	char mass_1[21];
	for (int i = size-1; i >= 0; i--)
	{
		mass_1[i] = help%10;
		help /= 10;
	}

	size_t i = 0, count = 0, s = 0;
	while ( (c = getchar()) != EOF)
	{
		if ( (c != '\n') && (c < '0' || c > '9') )
		{
			while (c != '\n')
			{
				c = getchar();
			}
			
			(*flag) = BAD_INPUT;
			return 0;
		}
		else if (c == '\n')
		{

			if (count > size)
			{
				(*flag) = BAD_INPUT;
				return ans;
			}
			else if (count == size)
			{
				if (s == 1)
				{
					return BAD_INPUT;
				}
			}

			(*flag) = OK;
			return ans;
		}
		else
		{
			ans *= 10;
			if ( (c-'0') > mass_1[i])
			{
				s = 1;
			}
			
			count++;
			ans += (c - '0');
		}
	}

	(*flag) = INPUT_ERROR;
	return ans;
}

unsigned int get_unsigned_numb(char* flag)
{
	char c;
	unsigned int ans = 0;
	
	size_t size = log10(UINT_MAX);
	size_t help = UINT_MAX;

	char mass_2[21];
	for (int i = size-1; i >= 0; i--)
	{
		mass_2[i] = help%10;
		help /= 10;
	}
	size_t i = 0, count = 0, s = 0;
	while ( (c = getchar()) != EOF)
	{
		if ( (c != '\n') && (c < '0' || c > '9') )
		{
			while (c != '\n')
			{
				c = getchar();
			}
			
			(*flag) = BAD_INPUT;
			return 0;
		}
		else if (c == '\n')
		{
			if (count > size)
			{
				(*flag) = BAD_INPUT;
				return ans;
			}
			else if (count == size)
			{
				if (s == 1)
				{
					return BAD_INPUT;
				}
			}
			
			(*flag) = OK;
			return ans;
		}
		else
		{

			ans *= 10;
			if ( (c-'0') > mass_2[i])
			{
				s = 1;
			}
			
			count++;
			ans += (c - '0');
		}
	}

	(*flag) = INPUT_ERROR;
	return ans;
}

char* readline(char* in, char* flag)
{
	printf("%s", in);	

	char* ptr = (char*) malloc(1);
	
	if (ptr == NULL)
	{
		(*flag) = MEMORY_ERROR;
		return NULL;
	}
	
	char buf[81];
	int n, len = 0;
	*ptr = '\0';
	
	do
	{
		n = scanf("%80[^\n]", buf);

		if (n < 0)
		{
			(*flag) = INPUT_ERROR;
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
				(*flag) == MEMORY_ERROR;
				return NULL;
			}
			
			ptr = strcat(ptr, buf);
		}
	}
	while (n > 0);

	return ptr;
}
