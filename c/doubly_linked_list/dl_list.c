/*
 * =====================================================================================
 *
 *       Filename:  dl_list.c
 *
 *    Description:  implementations of doubly linked list
 *
 *        Version:  1.0
 *        Created:  2016-03-20 22:55:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  luoyz , NULL
 *
 * =====================================================================================
 */

#ifndef _DL_LIST_C_
#define _DL_LIST_C_


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "../lib/common_def.h"
#include "dl_list.h"


int list_len(ENTRY *list)
{
	ENTRY *p;
	uint32 i = 0;

	if(NULL == list) return 0;

	assert(list->prev == NULL);
	p = list;
	while(p != NULL)
	{
		p = p->next;
		i++;
	}

	return i;
}

ENTRY *list_find_data(ENTRY *list, element_type x)
{
	ENTRY *p;

	assert(list != NULL && list->prev == NULL);
	p = list;
	while(p != NULL && p->data != x)
		p = p->next;

	return p;
}

ENTRY *list_get_nth_entry(ENTRY *list, uint32 n)
{
	ENTRY  *p;
	uint32 i = 1;

	assert(list != NULL && list->prev == NULL);
	if(n < 1) return NULL;
	p = list;
	while(p != NULL && i < n)
	{
		p = p->next;
		i++;
	}

	return p;
}

element_type list_get_nth_element(ENTRY *list, uint32 n)
{
	ENTRY *p;

	assert(list != NULL && list->prev == NULL);
	p = list_get_nth_entry(list, n);
	if(NULL == p) return LIST_INVALID_DATA;

	return p->data;
}

ENTRY *list_prepend(ENTRY **list, element_type x)
{
	ENTRY *newEntry;

	assert(list != NULL);
	newEntry = malloc(sizeof(ENTRY));
	if(NULL == newEntry) return NULL;
	newEntry->data = x;
	newEntry->prev = NULL;

	if(*list != NULL) (*list)->prev = newEntry;
	newEntry->next = *list;
	*list = newEntry;

	return newEntry;
}

ENTRY *list_tail(ENTRY **list)
{
	ENTRY *p;

	assert(list != NULL);
	if(NULL == *list) return NULL;
	p = *list;
	while(p->next != NULL)
		p = p->next;

	return p;
}

ENTRY *list_append(ENTRY **list, element_type x)
{
	ENTRY *newEntry;
	ENTRY *tail;

	assert(list != NULL);
	newEntry = malloc(sizeof(ENTRY));
	if(NULL == newEntry) return NULL;
	newEntry->data = x;
	newEntry->next = NULL;

	if(*list != NULL)
	{
		tail = list_tail(list);
		assert(NULL == tail->next);
		tail->next = newEntry;
		newEntry->prev = tail;
	}
	else
	{
		*list = newEntry;
		newEntry->prev = NULL;
	}

	return newEntry;
}

ENTRY *create_list_with_random_data(uint32 n)
{
	uint32 i;
	element_type data;
	ENTRY *list = NULL;

	assert(n > 0);
	srand(time(0));
	for(i = 0; i < n; i++)
	{
		data = rand() % (n + 30);
		printf("%3d ", data);
		if(list_append(&list, data) == NULL)
		{
			list_destroy(&list);
			return NULL;
		}
	}
	printf("\nCreation of list was completed.\n\n");

	return list;
}

int list_delete_entry(ENTRY **list, ENTRY *entry)
{
	ENTRY *p;

	/* If the list is empty, or entry is NULL, always fail */
	if(NULL == list || NULL == *list || NULL == entry) return ERROR;
	if(*list == entry)
	{
		*list = entry->next;
		if(entry->next != NULL) entry->next->prev = NULL;
	}
	else
	{
		p = *list;
		while(p->next != NULL && p->next != entry)
			p = p->next;
		if(NULL == p) return ERROR; /* did not find matching entry */
		p->next = entry->next;
		if(entry->next != NULL) entry->next->prev = p;
	}
	free(entry);

	return OK;
}

uint32 list_delete_data(ENTRY **list, element_type data)
{
	uint32 count = 0;
	ENTRY  *p, *temp;

	if(NULL == list || NULL == *list) return 0;
	p = *list;
	do
	{
		temp = p->next;
		if(p->data == data)
		{
			if(NULL == p->prev)
				*list = p->next;
			else
				p->prev->next = p->next;
			if(p->next != NULL) p->next->prev = p->prev;

			free(p);
			count++;
		}
		p = temp;
	}while(p != NULL);

	return count;
}

void list_destroy(ENTRY **list)
{
	ENTRY *p, *temp;

	if(NULL == list || NULL == *list || (*list)->prev != NULL) return;
	p = *list;
	while(p != NULL)
	{
		temp = p->next;
		free(p);
		p = temp;
	}
	*list = NULL;
}


void print_list(ENTRY *list)
{
	uint32 index = 1;
	ENTRY  *p;

	if(NULL == list)
	{
		printf("Empty list !\n\n");
		return;
	}
	printf("The list has %u entries: \n", list_len(list));
	p = list;
	do
	{
		printf("List item(%2u) : addr(%p) | prev(%9p) | data(%3d) | next(%9p)\n",
			index, p, p->prev, p->data, p->next);
		p = p->next;
		index++;
	} while (p != NULL);
	printf("\n");
}


#endif /* _DL_LIST_C_ */

