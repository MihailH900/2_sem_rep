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

	list->last = NULL;

	return list;
}

short add(List** list, void* data)
{
	if ( (*list) == NULL)
	{
		return LIST_POINTER_ERROR;
	}

	if ( (*list)->last == NULL)
	{
		Node* vert = (Node* ) malloc(sizeof(Node));
		if(vert == NULL)
		{
			return MEMORY_ERROR;
		}

		vert->data = data;
		vert->next = vert;

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
		vert->next = (*list)->last->next;

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

	if ( (*list)->last == NULL)
	{
		return NULL;
	}

	void* ans;
	if ( (*list)->last == (*list)->last->next)
	{
		
		ans = (*list)->last->data;
		free( (*list)->last);
		(*list)->last = NULL;
		return ans;
	}

	ans = (*list)->last->next->data;

	Node* tmp = (*list)->last->next;
	(*list)->last->next = (*list)->last->next->next;
	free(tmp);

	return ans;
}

void clear(List** list)
{
	if ( (*list)->last == NULL)
	{
		free(*list);
		return;
	}

	Node* help = (*list)->last->next;
	while ( (*list)->last->next != (*list)->last )
	{
		(*list)->last->next = (*list)->last->next->next;
		free(help);
		help = (*list)->last->next;
	}

	(*list)->last = NULL;
	free(*list);
	*list = NULL;
}
