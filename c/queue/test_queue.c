/*
 * =====================================================================================
 *
 *       Filename:  test_queue.c
 *
 *    Description:  test queue api
 *
 *        Version:  1.0
 *        Created:  2017-02-12 17:13:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  luoyz , NULL
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "../lib/common_def.h"
#include "queue.h"

#define QUEUE_ELEM_MAX_NUM 100


int main(int argc, char *argv[])
{
	uint32 i;
	QUEUE q;
	element_type x;
	uint32 num = 10;

	printf("Start testing queue: \n");
	srand(time(0));
	q = queue_create(QUEUE_ELEM_MAX_NUM);
	if(NULL == q)
	{
		printf("Create empty queue failed!\n");
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
	printf("Element enqueue: ");
	for(i = 0; i < num; i++)
	{
		x = rand() % 1001 - 500;
		if(enqueue(x, q) != OK) break;
		printf("%-5d ", x);
	}
	printf("\n\n");
	printf("Element dequeue: ");
	while(queue_is_empty(q) == false)
	{
		printf("%-5d ", queue_front(q));
		dequeue(q);
	}
	printf("\n");

	destroy_queue(q);
	printf("\nAll tests done.\n");

	exit(EXIT_SUCCESS);
}
