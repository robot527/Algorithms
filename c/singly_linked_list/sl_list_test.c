/*
 * =====================================================================================
 *
 *       Filename:  sl_list_test.c
 *
 *    Description:  test singly linked list
 *
 *        Version:  1.0
 *        Created:  03/10/2016 07:40:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  robot527 (), 
 *
 * =====================================================================================
 */

#ifndef _SL_LIST_TEST_C_
#define _SL_LIST_TEST_C_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/common_def.h"
#include "sl_list.h"


int test_insert(void)
{
	uint32 i;
	HEAD   *list;
	element_type data;

	list = create_empty_list();
	if(NULL == list) return ERROR;

	srand(time(0));
	for(i = 0; i < 10; i++)
	{
		data = rand() % 100;
		printf("%3d ", data);
		insert_before_node(data, list->next, list);
	}
	printf("\nInsertion was completed.\n\n");
	
	print_list(list);

	return OK;
}

int main(void)
{
	printf("Start testing singly linked list: \n");
	test_insert();

	printf("Test was completed.\n\n");
	exit(EXIT_SUCCESS);
}

#endif  /* _SL_LIST_TEST_C_ */

