/*
 * =====================================================================================
 *
 *       Filename:  sl_list.c
 *
 *    Description:  implementations of singly linked list
 *
 *        Version:  1.0
 *        Created:  03/09/2016 05:46:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  robot527 (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef _SL_LIST_C_
#define _SL_LIST_C_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../lib/common_def.h"
#include "sl_list.h"


int list_len(HEAD *list)
{
	if(NULL == list) return -1;

	return list->count;
}

HEAD *create_empty_list(void)
{
	HEAD *list = malloc(sizeof(HEAD));

	if(NULL == list) return NULL;
	list->next = NULL;
	list->count = 0;

	return list;
}

NODE *find_element(element_type x, HEAD *list)
{
	NODE *p;

	assert(list != NULL);
	p = list->next;
	while(p != NULL && p->data != x)
		p = p->next;

	return p;
}

NODE *find_previous(element_type x, HEAD *list)
{
	NODE *p;

	assert(list != NULL);
	p = list->next;
	while(p->next != NULL && p->next->data != x)
		p = p->next;
	if(NULL == p->next) return NULL;

	return p;
}

NODE *get_nth_node(HEAD *list, uint32 n)
{
	NODE   *p;
	uint32 index = 1;

	assert(list != NULL);
	if(n < 1) return NULL;
	p = list->next;
	while(p != NULL && index < n)
	{
		p = p->next;
		index++;
	}

	return p;
}

int insert_before_node(element_type x, NODE *pNode, HEAD *list)
{
	NODE *pNew;
	NODE *p, *pPrev = NULL;

	assert(list != NULL);
	pNew = malloc(sizeof(NODE));
	if(NULL == pNew) return ERROR;
	if(IS_EMPTY(list))
	{
		/* ignore pNode */
		list->next = pNew;
		pNew->next = NULL;
	}
	else
	{
		p = list->next;
		while(p != pNode && p != NULL)
		{
			pPrev = p;
			p = p->next;
		}
		if(NULL == p) /* did not find matching node */
		{
			free(pNew);
			return ERROR;
		}
		if(NULL == pPrev) /* pNode is the first node */
		{
			list->next = pNew;
		}
		else
		{
			pPrev->next = pNew;
		}
		pNew->next = pNode;
	}
	pNew->data = x;
	list->count++;

	return OK;
}

int insert_after_node(element_type x, NODE *pNode, HEAD *list)
{
	NODE *pNew;
	NODE *p;

	assert(list != NULL);
	pNew = malloc(sizeof(NODE));
	if(NULL == pNew) return ERROR;
	if(IS_EMPTY(list))
	{
		/* ignore pNode */
		list->next = pNew;
		pNew->next = NULL;
	}
	else
	{
		p = list->next;
		while(p != pNode && p != NULL)
			p = p->next;
		if(NULL == p) /* did not find matching node */
		{
			free(pNew);
			return ERROR;
		}
		pNew->next = p->next;
		p->next = pNew;
	}
	pNew->data = x;
	list->count++;

	return OK;
}

int delete_element(element_type x, HEAD *list)
{
	NODE *p, *temp;

	assert(list != NULL);
	if(IS_EMPTY(list)) return ERROR;
	p = list->next;
	if(x == p->data) /* x is in the first node after list head */
	{
		list->next = p->next;
		free(p);
		list->count--;
		printf("\t%s line %d\n", __FUNCTION__, __LINE__);
		return OK;
	}

	p = find_previous(x, list);
	if(NULL == p) return ERROR;
	temp = p->next; /* record position of x */
	if(IS_LAST(temp))
		p->next = NULL;
	else
		p->next = temp->next; /* bypass the node to be deleted */
	free(temp);
	list->count--;

	return OK;
}

int delete_node(NODE *pNode, HEAD *list)
{
	NODE *p;

	if(NULL == pNode) return ERROR;
	assert(list != NULL);
	if(IS_EMPTY(list)) return ERROR;
	if(list->next == pNode)
	{
		list->next = pNode->next;
	}
	else
	{
		p = list->next;
		while(p->next != NULL && p->next != pNode)
			p = p->next;
		if(NULL == p)
		{
			return ERROR;
		}
		p->next = pNode->next;
	}
	free(pNode);
	list->count--;

	return OK;
}

void empty_list(HEAD *list)
{
	NODE *p, *temp;

	assert(list != NULL);
	p = list->next;
	list->next = NULL;
	while(p != NULL)
	{
		temp = p->next;
		free(p);
		p = temp;
	}
	list->count = 0;
}

void destroy_list(HEAD *list)
{
	assert(list != NULL);
	empty_list(list);
	free(list);
	list = NULL;
}

void print_list(HEAD *list)
{
	uint32 index = 1;
	NODE   *p;

	if(NULL == list)
	{
		printf("Invalid list head !\n\n");
		return;
	}
	if(IS_EMPTY(list))
	{
		printf("Empty list !\n");
		return;
	}
	p = list->next;
	do
	{
		printf("List item(%2u) : addr(%p) -> data(%3d) next(%p)\n",
			index, p, p->data, p->next);
		p = p->next;
		index++;
	} while (p != NULL);
	printf("\n");
}

NODE *list_tail(HEAD *list)
{
	NODE *p;

	assert(list != NULL);
	p = list->next;
	if(NULL == p) return NULL;
	while(p->next != NULL)
		p = p->next;

	return p;	
}

int list_append(element_type x, HEAD *list)
{
	NODE *pNew;
	NODE *tail;

	assert(list != NULL);
	pNew = malloc(sizeof(NODE));
	if(NULL == pNew) return ERROR;
	pNew->data = x;
	tail = list_tail(list);
	if(NULL == tail)
	{
		list->next = pNew;
	}
	else
	{
		tail->next = pNew;
	}
	pNew->next = NULL;
	return OK;
}


#endif  /* _SL_LIST_C_ */

