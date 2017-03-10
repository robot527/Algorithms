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
#include <assert.h>
#include <sys/time.h>

#include "../lib/common_def.h"
#include "sl_list.h"


//typedef HEAD  (*LIST_FUNC)(HEAD *); /* Parameter passed error ! */
typedef void (*LIST_FUNC)(HEAD *);

void test_consumed_time(LIST_FUNC func, HEAD *list)
{
	struct timeval start, end;
	double t;

	if(NULL == func) return;
	assert(list != NULL);
	gettimeofday(&start, NULL);
	//printf("%s -> para list: %p\n", __FUNCTION__, list);
	func(list);
	gettimeofday(&end, NULL);
	t = end.tv_sec - start.tv_sec\
		+ (double)(end.tv_usec - start.tv_usec) / 1000000;
	printf("consumed time: %.6f seconds.\n\n", t);
}

int test_insert(void)
{
	uint32 i;
	HEAD   *list, *list1;
	NODE   *p;
	element_type data;

	printf("==============================================================\n");
	printf("Testing list insert functions:\n");
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
	if(list_len(list) != 10) printf("insert_before_node encountered some errors !\n");

	print_list(list);

	list1 = create_empty_list();
	if(NULL == list1) return ERROR;
	for(i = 0; i < 8; i++)
	{
		data = rand() % 10;
		printf("%3d ", data);
		insert_after_node(data, list1->next, list1);
	}
	printf("\nInsertion of list1 was completed.\n\n");
	print_list(list1);
	p = find_element(5, list1);
	if(p != NULL)
	{
		insert_after_node(99, p, list1);
		print_list(list1);
	}
	else
		printf("element 5 was not found!\n\n");

	empty_list(list);
	for(i = 0; i < 7; i++)
	{
		data = rand() % 20;
		printf("%3d ", data);
		list_append(data, list);
	}
	printf("\nAppend nodes to list was completed.\n\n");
	print_list(list);
	destroy_list(list);
	destroy_list(list1);

	return OK;
}

int test_delete(void)
{
	HEAD   *list;
	NODE   *pNode;
	uint32 n, len = 11;

	printf("==============================================================\n");
	printf("Testing list delete functions:\n");
	list = create_list_with_random_data(len);
	if(NULL == list) return ERROR;
	print_list(list);

	/* test NULL */
	if(delete_node(NULL, list) == OK)
		printf("Function delete_node was designed unreasonable !\n");

	n = 1; /* test the first node */
	pNode = get_nth_node(list, n);
	if(delete_node(pNode, list) == OK)
	{
		printf("Deleted the %uth node!\n", n);
		if(list_len(list) != (len - 1))
			printf("delete_node encountered some errors !\n");
	}
	print_list(list);

	n = list_len(list); /* test the last node */
	pNode = get_nth_node(list, n);
	if(delete_node(pNode, list) == OK)
	{
		printf("Deleted the %uth node!\n", n);
		if(list_len(list) != (n - 1))
			printf("delete_node encountered some errors !\n");
	}
	print_list(list);

	len = list_len(list);
	n = len / 2 + 1; /* test the middle node */
	pNode = get_nth_node(list, n);
	if(delete_node(pNode, list) == OK)
	{
		printf("Deleted the %uth node!\n", n);
		if(list_len(list) != (len - 1))
			printf("delete_node encountered some errors !\n");
	}
	print_list(list);

	n = list_len(list); /* test the last element */
	pNode = get_nth_node(list, n);
	if(pNode != NULL)
	{
		printf("Delete the node who's data is %d!\n", pNode->data);
		if(delete_element(pNode->data, list) != OK)
			printf("delete_element encountered some errors !\n");
	}
	print_list(list);

	pNode = get_nth_node(list, 1); /* test the first element */
	if(pNode != NULL)
	{
		printf("Delete the node who's data is %d!\n", pNode->data);
		if(delete_element(pNode->data, list) != OK)
			printf("delete_element encountered some errors !\n");
	}
	print_list(list);

	n = list_len(list) / 2; /* test the middle element */
	pNode = get_nth_node(list, n);
	if(pNode != NULL)
	{
		printf("Delete the node who's data is %d!\n", pNode->data);
		if(delete_element(pNode->data, list) != OK)
			printf("delete_element encountered some errors !\n");
	}
	print_list(list);

	if(delete_element(-1, list) == OK)
		printf("delete_element encountered some errors !\n");

	empty_list(list);
	if(list_len(list) != 0) printf("empty_list encountered some errors !\n");
	destroy_list(list);
	
	return OK;
}

int test_reverse(void)
{
	HEAD *list;

	printf("==============================================================\n");
	printf("Testing list reverse functions:\n");
	list = create_list_with_random_data(2000);
	if(NULL == list) return ERROR;

	if(list->count < 50) print_list(list);
	//list_reverse1(list);

	printf("The reversion of list(%u nodes) by list_reverse1:\n", list->count);
	test_consumed_time((LIST_FUNC)list_reverse1, list);
	if(list->count < 50) print_list(list);

	printf("The reversion of list(%u nodes) by list_reverse2:\n", list->count);
	test_consumed_time((LIST_FUNC)list_reverse2, list);
	if(list->count < 50) print_list(list);

	printf("The reversion of list(%u nodes) by list_reverse:\n", list->count);
	test_consumed_time((LIST_FUNC)list_reverse, list);
	if(list->count < 50) print_list(list);

	printf("The reversion of list was completed.\n");
	destroy_list(list);

	return OK;
}

int main(void)
{
	printf("Start testing singly linked list: \n");
	test_insert();
	test_delete();
	//test_copy();
	test_reverse();

	printf("\nAll tests done.\n");
	exit(EXIT_SUCCESS);
}

#endif  /* _SL_LIST_TEST_C_ */

