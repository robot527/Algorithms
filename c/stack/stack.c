/*
 * =====================================================================================
 *
 *       Filename:  stack.c
 *
 *    Description:  implementations of stack
 *
 *        Version:  1.0
 *        Created:  2016-07-18 12:47:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  robot527 (), 
 *
 * =====================================================================================
 */

#ifndef _STACK_C_
#define _STACK_C_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "../lib/common_def.h"
#include "stack.h"


int stack_is_empty(STACK s)
{
	assert(s != NULL);

	return NULL == s->next;
}

STACK stack_create(void)
{
	STACK s;

	s = (STACK)malloc(sizeof(NODE));
	if(NULL == s) return NULL;
	s->next = NULL;

	return s;
}

int stack_push(element_type x, STACK s)
{
	NODE *temp;

	temp = (NODE *)malloc(sizeof(NODE));
	if(NULL == temp) return ERROR;
	temp->data = x;
	temp->next = s->next;
	s->next = temp;	

	return OK;
}

element_type stack_top(STACK s)
{
	assert(stack_is_empty(s) == false);

	return s->next->data;
}

void stack_pop(STACK s)
{
	NODE *top;

	assert(stack_is_empty(s) == false);
	top = s->next;
	s->next = s->next->next;
	free(top);	
}


#endif /* _STACK_C_ */

