#ifndef MATRIX_H
#define MATRIX_H

typedef struct Line
{
	int size;
	int* arr;
} Line;

typedef struct Matrix
{
	int lines;
	Line* arrOfLines;
} Matrix;

int* transform(Matrix m);
void help(int* line, int size, int* count, int* ans);
short getMatrix(Matrix* m);
int inputLine(int* ptr, int size);
void printMatrix(Matrix m);
void clear(Matrix* m);
int cmp(const int* a, const int* b);

#endif
