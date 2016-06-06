/*
 * =====================================================================================
 *
 *       Filename:  test_stack.c
 *
 *    Description:  test stack api
 *
 *        Version:  1.0
 *        Created:  2016-07-18 20:14:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  robot527 (), 
 *
 * =====================================================================================
 */

#ifndef _TEST_STACK_C_
#define _TEST_STACK_C_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "../lib/common_def.h"
#include "stack.h"


int main(int argc, char *argv[])
{
	uint32 i;
	STACK s;
	element_type x;
	uint32 num = 10;

	printf("Start testing stack: \n");
	srand(time(0));
	s = stack_create();
	if(NULL == s)
	{
		printf("Create empty stack failed!\n");
		exit(EXIT_FAILURE);
	}
	
	switch(argc)
	{
		case 1:
			printf("argc(%d), exec file(%s).\n", argc, argv[0]);
			break;

		case 2:
			num = atoi(argv[1]);
			break;

		default:
			printf("Parameter num(%d) error.\n", argc);
			exit(EXIT_FAILURE);
			break;
	}
	printf("stack push element: ");
	for(i = 1; i < num; i++)
	{
		x = rand() % 1001 - 500;
		if(stack_push(x, s) != OK) break;
		printf("%-5d ", x);
	}
	printf("\n\n");
	printf("stack pop element: ");
	while(stack_is_empty(s) == false)
	{
		printf("%-5d ", stack_top(s));
		stack_pop(s);
	}
	printf("\n");

	if(s != NULL) free(s);
	printf("\nAll tests done.\n");

	exit(EXIT_SUCCESS);
}


#endif  /* _TEST_STACK_C_ */

