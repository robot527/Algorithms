/*
 * =====================================================================================
 *
 *       Filename:  test_dl_list.c
 *
 *    Description:  test doubly linked list
 *
 *        Version:  1.0
 *        Created:  2016-03-20 23:55:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  luoyz , NULL
 *
 * =====================================================================================
 */

#ifndef _TEST_DL_LIST_C_
#define _TEST_DL_LIST_C_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <sys/time.h>

#include "../lib/common_def.h"
#include "dl_list.h"


int test_creation(void)
{
	ENTRY *list;

	list = create_list_with_random_data(10);
	if(NULL == list) return ERROR;

	if(list_len(list) != 10) printf("Creation encountered some errors !\n\n");
	print_list(list);
	list_destroy(&list);

	return OK;
}

int test_find(void)
{
	ENTRY  *list;
	ENTRY  *p;
	uint32 n;

	list = create_list_with_random_data(9);
	if(NULL == list) return ERROR;

	print_list(list);
	p = list_find_data(list, 25);
	if(p != NULL)
	{
		printf("List item : addr(%p) | prev(%9p) | data(%3d) | next(%9p)\n\n",
			p, p->prev, p->data, p->next);
	}
	else
		printf("data 25 was not found!\n\n");

	n = 5;
	p = list_get_nth_entry(list, n);
	if(p != NULL)
	{
		printf("Found the %dth entry!\n", n);
		printf("List item : addr(%p) | prev(%9p) | data(%3d) | next(%9p)\n\n",
			p, p->prev, p->data, p->next);
	}
	else
		printf("The %dth entry was not found!\n", n);

	n = 10;
	p = list_get_nth_entry(list, n);
	if(p != NULL)
		printf("List (addr %p) has some errors !\n\n", list);
	else
		printf("The %dth entry was not found!\n\n", n);

	p = list_tail(&list);
	if(p != NULL)
	{
		printf("List tail : addr(%p) | prev(%9p) | data(%3d) | next(%9p)\n\n",
			p, p->prev, p->data, p->next);
	}
	else
		printf("The tail entry was not found!\n");
	list_destroy(&list);

	return OK;
}

int test_delete(void)
{
	ENTRY  *list;
	ENTRY  *p;
	uint32 n, len = 13;
	element_type data;

	list = create_list_with_random_data(len);
	if(NULL == list) return ERROR;
	print_list(list);

	/* test NULL, first, last, middle entries */
	list_delete_entry(&list, NULL);

	n = 1;
	p = list_get_nth_entry(list, n);
	if(list_delete_entry(&list, p) == OK)
	{
		printf("Delete the %dth entry!\n", n);
		if(list_len(list) != (len - 1)) printf("Deletion encountered some errors !\n\n");
	}
	print_list(list);

	n = list_len(list);
	p = list_get_nth_entry(list, n);
	if(list_delete_entry(&list, p) == OK)
	{
		printf("Delete the %dth entry!\n", n);
		if(list_len(list) != (n - 1)) printf("Deletion encountered some errors !\n\n");
	}
	print_list(list);

	len = list_len(list);
	n = len / 2 + 1;
	p = list_get_nth_entry(list, n);
	if(list_delete_entry(&list, p) == OK)
	{
		printf("Delete the %dth entry!\n", n);
		if(list_len(list) != (len - 1)) printf("Deletion encountered some errors !\n\n");
	}
	print_list(list);

	list_destroy(&list);
	if(list_len(list) != 0) printf("list_destroy encountered some errors !\n");
	print_list(list);

	list = create_list_with_random_data(27);
	if(NULL == list) return ERROR;
	print_list(list);

	n = 0;
	data = list_get_nth_element(list, n);
	printf("Deleted %d entries(data = %d)\n\n",
		list_delete_data(&list, data), data);
	//print_list(list);

	n = list_len(list);
	data = list_get_nth_element(list, n);
	printf("Deleted %d entries(data = %d)\n\n",
		list_delete_data(&list, data), data);
	//print_list(list);

	n = list_len(list) / 2;
	data = list_get_nth_element(list, n);
	printf("Deleted %d entries(data = %d)\n\n",
		list_delete_data(&list, data), data);
	//print_list(list);

	n = 1;
	data = list_get_nth_element(list, n);
	printf("Deleted %d entries(data = %d)\n\n",
		list_delete_data(&list, data), data);
	print_list(list);

	list_destroy(&list);

	return OK;
}

int main(void)
{
	printf("Start testing doubly linked list: \n");
	//test_creation();
	test_find();
	test_delete();

	printf("\nAll tests done.\n");
	exit(EXIT_SUCCESS);
}

#endif  /* _TEST_DL_LIST_C_ */

