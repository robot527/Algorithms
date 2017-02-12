/*
 * =====================================================================================
 *
 *       Filename:  queue.h
 *
 *    Description:  definitions of queue
 *
 *        Version:  1.0
 *        Created:  2017-02-12 15:21:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  luoyz , NULL
 *
 * =====================================================================================
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "../lib/type_rename.h"

typedef struct _queue_record_
{
	uint32 max_size; /* Max num of elements until queue is full */
	uint32 front;
	uint32 rear;
	uint32 size;     /* Current num of elements in queue */
	element_type *array;
}queue_record;

typedef queue_record *QUEUE;


int queue_is_empty(QUEUE q);
int queue_is_full(QUEUE q);
QUEUE queue_create(uint32 max_num);
uint32 calc_queque_pos(uint32 val, QUEUE q);
int enqueue(element_type x, QUEUE q);
element_type queue_front(QUEUE q);
int dequeue(QUEUE q);
void destroy_queue(QUEUE q);


#endif /* _QUEUE_H_ */

