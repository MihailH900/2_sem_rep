#include "input_funcs.h"
#include <stdio.h>
#include <string.h>

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

char get_queue_size(char* in, unsigned int* size)
{
	(*size) = 0;
	while (*in != '\0')
	{	
		if ( (*in) < '0' || (*in) > '9')
		{
			printf("Bad input, a character not equal to a digit was found in a number entry\n");
			return 1;
		}

		(*size) += ( (*in) - '0');
		(*size) *= 10;

		in++;
	}

	(*size) /= 10;
	return 0;
}

size_t check_format(char* in)
{
	if (strchr(in, ' ') == NULL)
	{
		printf("Bad input, can't find space. Try again\n");
		return 0;
	}

	char* c = in;
	if ( shift(&c, ' ', '0') )
	{
		return 0;
	}
	c++;

	size_t ans = 0;
	while (*c != '\0')
	{
		for (short i = 0; i < 2; i++)
		{
			if ( shift(&c, '/', '0') )
			{
				return 0;
			}
			c++;
		}

		if ( shift(&c, ' ', '\0') )
		{
			return 0;
		}

		if (*c == '\0')
		{
			ans++;
			return ans;
		}

		c++;
		ans++;
	}

	return ans;
}

void parse_input(char* in, Process* p, unsigned int* time_step)
{
	char* c = in;
	(*time_step) = get_numb_in_str(&c, ' ', '0');

	Process* k = p;
	c++;
	while (*c != '\0')
	{
	
		k->id = get_numb_in_str(&c, '/', '0');
		c++;		
		k->tc = get_numb_in_str(&c, '/', '0');
		c++;
		k->te = get_numb_in_str(&c, ' ', '\0');
		k->te_copy = k->te;

		if (*c == '\0')
		{
			return;
		}

		c++;
		k++;
	}
}

unsigned int get_numb_in_str(char** c, char ch1, char ch2)
{
	unsigned int n = 0;
	if (ch2 == '0')
	{
		ch2 = ch1;
	}

	while ( *(*c) != ch1 && *(*c) != ch2)
	{
		n += ( *(*c) - '0');
		n *= 10;

		(*c)++;
	}

	return (n /= 10);
}

char shift(char** c, char ch1, char ch2)
{
	if (ch2 == '0')
	{
		ch2 = ch1;
	}

	while ( *(*c) != ch1 && *(*c) != ch2)
	{
		if ( *(*c) == '\0' && '\0' != ch2)
		{
			printf("Bad input, can't find delimiter character");
			return 1;
		}
		if ( *(*c) < '0' || *(*c) > '9')
		{
			printf("Bad input, a character not equal to a digit was found in a number entry\n");
			return 1;
		}

		(*c)++;
	}

	return 0;
}
