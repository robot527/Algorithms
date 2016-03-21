/*
 * =====================================================================================
 *
 *       Filename:  dl_list.c
 *
 *    Description:  implementations of doubly linked list
 *
 *        Version:  1.0
 *        Created:  2016年03月20日 22时55分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  luoyz , NULL
 *        Company:  NULL
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


ENTRY *create_new_list(void)
{
	ENTRY *list = malloc(sizeof(ENTRY));

	if(NULL == list) return NULL;
	list->next = NULL;
	list->prev = NULL;
	list->data = 0;

	return list;
}

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

ENTRY *list_prepend(ENTRY *list, element_type x)
{
	ENTRY *newEntry;

	assert(list != NULL && list->prev == NULL);
	//printf("prev(%p) \n", list->prev);
	//assert(list->prev == NULL);
	newEntry = malloc(sizeof(ENTRY));
	if(NULL == newEntry) return NULL;
	newEntry->data = x;
	newEntry->prev = NULL;
	newEntry->next = list;
	list->prev = newEntry;

	return newEntry;
}

ENTRY *create_list_with_random_data(uint32 n)
{
	uint32 i;
	element_type data;
	ENTRY *list;

	assert(n > 0);
	list = create_new_list();
	if(NULL == list) return NULL;

	srand(time(0));
	list->data = rand() % (n + 50);
	printf("%3d ", list->data);
	//printf("list(%p), prev(%p)\n", list, list->prev);
	for(i = 1; i < n; i++)
	{
		data = rand() % (n + 50);
		printf("%3d ", data);
		if((list = list_prepend(list, data)) == NULL)
		{
			destroy_list(list);
			return NULL;
		}
	}
	printf("\nCreation of list was completed.\n\n");

	return list;
}

void destroy_list(ENTRY *list)
{
	ENTRY *p, *temp;

	assert(list != NULL && list->prev == NULL);
	p = list;
	while(p != NULL)
	{
		temp = p->next;
		free(p);
		p = temp;
	}
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
	printf("The list has %u nodes: \n", list_len(list));
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

