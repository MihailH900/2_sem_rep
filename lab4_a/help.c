#include <stdio.h>
#include <stdlib.h>

typedef struct Key
{
	void* ptr;
	int k;
} Key;

int main()
{
	Key* ptr = (Key*) malloc(sizeof(Key));
	const Key* obj = ptr;
	free(obj->ptr);

	return 0;
}
