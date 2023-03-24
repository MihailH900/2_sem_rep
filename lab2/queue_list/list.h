#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct Node
{
	void* data;
	struct Node* next;
} Node;

typedef struct List
{
	Node* head;
	Node* last;
} List;

enum Errors
{
	NO_ERRORS,
	MEMORY_ERROR,
	LIST_POINTER_ERROR
};

List* init();
short add(List** list, void* data);
void* del_front(List** list);
void clear(List** list);

#endif
