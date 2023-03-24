#include "list.h"
#include <stdio.h>
#include <string.h>

List* init()
{
	List* list = (List* ) malloc(sizeof(List));
	if (list == NULL)
	{
		return NULL;
	}

	list->head = NULL;
	list->last = NULL;

	return list;
}

short add(List** list, void* data)
{
	if ( (*list) == NULL)
	{
		return LIST_POINTER_ERROR;
	}

	if ( (*list)->head == NULL)
	{
		Node* vert = (Node* ) malloc(sizeof(Node));
		if(vert == NULL)
		{
			return MEMORY_ERROR;
		}

		vert->data = data;
		vert->next = NULL;

		(*list)->head = vert;
		(*list)->last = vert;

		return NO_ERRORS;
	}
	else
	{
		Node* vert = (Node* ) malloc(sizeof(Node));
		if(vert == NULL)
		{
			return MEMORY_ERROR;
		}

		vert->data = data;
		vert->next = NULL;

		(*list)->last->next = vert;
		(*list)->last = vert;

		return NO_ERRORS;
	}
}

void* del_front(List** list)
{
	if ( (*list) == NULL)
	{
		return NULL;
	}

	if ( (*list)->head == NULL)
	{
		return NULL;
	}

	void* ans;
	if ( (*list)->head->next == NULL)
	{
		
		ans = (*list)->head->data;
		free( (*list)->head );
		(*list)->head = NULL;
		(*list)->last = NULL;
		return ans;
	}

	ans = (*list)->head->data;

	Node* tmp = (*list)->head;
	(*list)->head = (*list)->head->next;
	free(tmp);

	return ans;
}

void clear(List** list)
{
	Node* help = (*list)->head;
	while ( (*list)->head != NULL )
	{
		(*list)->head = (*list)->head->next;
		free(help);
		help = (*list)->head;
	}

	(*list)->last = NULL;
	free(*list);
	*list = NULL;
}
