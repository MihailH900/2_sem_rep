#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "input_check.h"

void printAns(Matrix m, int* arr);

int main()
{
	Matrix m = {0, NULL};

	short c = getMatrix(&m);
	if (c == 1)
	{
		printf("End of input");
		return 0;
	}
	else if (c == 2)
	{
		printf("Memory error");
		return 0;
	}

	printMatrix(m);

	int* ans = transform(m);
	printAns(m, ans);
	
	clear(&m);
	free(ans);

	return 0;
}


void printAns(Matrix m, int* arr)
{
	printf("\n");

	int* helpPtr = arr;
	for (int i = 0; i < m.lines; i++, helpPtr++)
	{
		printf("%d ", *helpPtr);
	}
	printf("\n");
	printf("\n");

	printMatrix(m);
}
