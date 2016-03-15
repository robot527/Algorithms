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
	HEAD   *list, *list1;
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
	printf("\nInsertion of list was completed.\n\n");
	print_list(list);

	list1 = create_empty_list();
	if(NULL == list1) return ERROR;
	for(i = 0; i < 5; i++)
	{
		data = rand() % 100;
		printf("%3d ", data);
		insert_after_node(data, list1->next, list1);
	}
	printf("\nInsertion of list1 was completed.\n\n");
	print_list(list1);

	empty_list(list);
	for(i = 0; i < 7; i++)
	{
		data = rand() % 100;
		printf("%3d ", data);
		list_append(data, list);
	}
	printf("\nAppend nodes to list was completed.\n\n");
	print_list(list);

	return OK;
}

int test_delete(void)
{
	int    ret;
	uint32 i;
	HEAD   *list;
	NODE   *pNode;
	element_type data;

	list = create_empty_list();
	if(NULL == list) return ERROR;

	srand(time(0));
	for(i = 0; i < 10; i++)
	{
		data = rand() % 21;
		printf("%3d ", data);
		insert_before_node(data, list->next, list);
	}
	printf("\nInsertion was completed.\n\n");
	print_list(list);

	data = 10;
	ret = delete_element(data, list);
	if(ret != OK)
		printf("element %d was not found!\n", data);
	else
		printf("Delete the node who's data is %d!\n", data);
	print_list(list);

	pNode = get_nth_node(list, 5);
	if(pNode != NULL)
	{
		printf("Delete the 5th node(%d)!\n", pNode->data);
		delete_node(pNode, list);		
	}
	print_list(list);
	
	return OK;
}

int main(void)
{
	printf("Start testing singly linked list: \n");
	test_insert();
	//test_delete();

	printf("Test was completed.\n\n");
	exit(EXIT_SUCCESS);
}

#endif  /* _SL_LIST_TEST_C_ */

