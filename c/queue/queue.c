/*
 * =====================================================================================
 *
 *       Filename:  queue.c
 *
 *    Description:  implementations of queue
 *
 *        Version:  1.0
 *        Created:  2017-02-12 15:36:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  luoyz , NULL
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../lib/common_def.h"
#include "queue.h"


int queue_is_empty(QUEUE q)
{
	assert(q != NULL);

	return 0 == q->size;
}

int queue_is_full(QUEUE q)
{
	assert(q != NULL);

	return q->size == q->max_size;
}

QUEUE queue_create(uint32 max_num)
{
	QUEUE q;

	q = (QUEUE)malloc(sizeof(queue_record));
	if(NULL == q) return NULL;

	q->array = (element_type *)malloc(sizeof(element_type) * max_num);
	if(NULL == q->array)
	{
		free(q);
		return NULL;
	}

	/* make empty */
	q->max_size = max_num;
	q->front = 1;
	q->rear = 0;

	return q;
}

uint32 calc_queue_pos(uint32 val, QUEUE q)
{
	assert(q != NULL);
	val++;
	if(val == q->max_size)
	{
		val = 0;
	}

	return val;
}

int enqueue(element_type x, QUEUE q)
{
	if(queue_is_full(q))
	{
		printf("Full queue!\n");
		return ERROR;
	}
	else
	{
		q->size++;
		q->rear = calc_queue_pos(q->rear, q);
		q->array[q->rear] = x;

		return OK;
	}
}

element_type queue_front(QUEUE q)
{
	assert(queue_is_empty(q) == false);

	return q->array[q->front];
}

int dequeue(QUEUE q)
{
	if(queue_is_empty(q))
	{
		printf("Empty queue!\n");
		return ERROR;
	}
	else
	{
		q->size--;
		q->front = calc_queue_pos(q->front, q);

		return OK;
	}
}

void destroy_queue(QUEUE q)
{
	if(NULL != q)
	{
		free(q->array);
	}
	free(q);
}
