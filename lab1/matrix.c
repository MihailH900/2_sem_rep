#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "input_check.h"

int* transform(Matrix m)
{
	Line* ptr_1 = m.arrOfLines;
	int* helpPtr;
	int count, ans;

	int* resArr = (int*) malloc(m.lines * sizeof(int));
	if (resArr == NULL)
	{
		return NULL;
	}
	int* resArrPtr = resArr;

	int* copyLine = NULL;
	int copyLineSize = 0;
	for (int i = 0; i < m.lines; i++, ptr_1++, resArrPtr++)
	{
		helpPtr = ptr_1->arr;
		count = 1;
		ans = *helpPtr;

		if (copyLineSize < ptr_1->size)
		{
			copyLineSize = ptr_1->size;
			copyLine = (int*) realloc(copyLine, ptr_1->size * sizeof(int));
			if (copyLine == NULL)
			{
				return NULL;
			}
		}
		int* p1 = copyLine;
		int* p2 = ptr_1->arr;

		for (int i = 0; i < ptr_1->size; i++, p1++, p2++)
		{
			*p1 = *p2;
		}	

		qsort(copyLine, ptr_1->size, sizeof(int), (int(*) (const void *, const void *)) cmp);
		help(copyLine, ptr_1->size, &count, &ans);
		*resArrPtr = ans;
	}

	free(copyLine);

	return resArr;
}

void help(int* line, int size, int* count, int* ans)
{
	int* helpPtr = line;
	line++;
	for (int j = 1; j < size; j++, line++)
	{
		int c = 1;
		while (*helpPtr == *line)
		{
			j++;
			c++;
			line++;
		}

		if (*count <= c)
		{
			*count = c;
			*ans = *helpPtr;
		}	

		helpPtr = line;
	}
}

short getMatrix(Matrix* m)
{
	printf("Enter number of lines: ");
	if (getCorrectValOfSize( &(m->lines)) == 1)
	{
		return 1;
	}

	m->arrOfLines = (Line*) malloc( (m->lines)*sizeof(Line));
	if (m->arrOfLines == NULL)
	{
		return 2;
	}

	Line* ptr_1 = m->arrOfLines;
	for (int i = 0; i < m->lines; i++, ptr_1++)
	{
		printf("Enter size of line: ");
		int c;
		if (getCorrectValOfSize(&c) == 1)
		{
			m->lines = i;
			clear(m);
			return 1;
		}

		ptr_1->size = c;
		ptr_1->arr = (int*) malloc(c*sizeof(int));
		if (ptr_1->arr == NULL)
		{
			return 2;
		}

		if (inputLine(ptr_1->arr, ptr_1->size) == 1)
		{
			m->lines = i+1;
			clear(m);
			return 1;
		}
	}

	return 0;
}

int inputLine(int* ptr, int size)
{
	for (int i = 0; i < size; i++, ptr++)
	{
		printf("Input element %d: ", i);
		if (getCorrectTypeOfIntegerNumb(ptr) == 1)
		{
			return 1;
		}
	}
	return 0;
}

void printMatrix(Matrix m)
{
	printf("%d\n", m.lines);
	Line* p = m.arrOfLines;
	for (int i = 0; i < m.lines; i++, p++)
	{
		int* ptr = p->arr;
		for (int j = 0; j < (m.arrOfLines+i)->size; j++, ptr++)
		{
			printf("%d ", *ptr);
		}
		printf("\n");
	}
}

void clear(Matrix* m)
{
	for (int i = 0; i < m->lines; i++)
	{
		free((*(m->arrOfLines + i)).arr);
	}
	free(m->arrOfLines);
	m->lines = 0;
	m->arrOfLines = NULL;
}

int cmp (const int* a, const int* b)
{
	return *a - *b;
}

