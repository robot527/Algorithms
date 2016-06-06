/*
 * =====================================================================================
 *
 *       Filename:  stack.h
 *
 *    Description:  definitions of stack
 *
 *        Version:  1.0
 *        Created:  2016-07-18 12:44:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  robot527 (), 
 *
 * =====================================================================================
 */

#ifndef _STACK_H_
#define _STACK_H_

#include "../lib/type_rename.h"


typedef struct _stack_node_
{
	element_type          data;
	struct _stack_node_   *next;
}NODE;

typedef NODE *STACK;


int stack_is_empty(STACK s);
STACK stack_create(void);
int stack_push(element_type x, STACK s);
element_type stack_top(STACK s);
void stack_pop(STACK s);


#endif /* _STACK_H_ */

