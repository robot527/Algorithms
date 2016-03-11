/*
 * =====================================================================================
 *
 *       Filename:  sl_list.h
 *
 *    Description:  definitions of singly linked list
 *
 *        Version:  1.0
 *        Created:  03/09/2016 04:59:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  robot527 (), 
 *
 * =====================================================================================
 */

#ifndef _SL_LIST_H_
#define _SL_LIST_H_

#include "../lib/type_rename.h"


typedef struct _sl_list_node_
{
	element_type          data;
	struct _sl_list_node_ *next;
}NODE;

typedef struct _sl_list_head_
{
	NODE   *next;
	uint32 count;
}HEAD;

#define IS_EMPTY(p_head) (NULL == (p_head)->next)
#define IS_LAST(p_node) (NULL == (p_node)->next)


/* Return number of nodes in the list.
 * if param list is null, returns -1. */
int list_len(HEAD *list);

/* Create an empty list with a head.
 * Return the head of new list, or NULL if failed. */
HEAD *create_empty_list(void);

/* Return the position of x in list, or NULL if not found. */
NODE *find_element(element_type x, HEAD *list);

/* Return the position of node before x, or NULL if not found.
 * If x is in the list, assume x isn't in the first node after list head */
NODE *find_previous(element_type x, HEAD *list);

/* Insert a new node with x before pNode to the list.
 * If list is empty, append new node after the list head.
 * Return OK, or ERROR if failed. */
int insert_before_node(element_type x, NODE *pNode, HEAD *list);

/* Delete the first occurrence of x from the list.
 * Return OK, or ERROR if not found. */
int delete_element(element_type x, HEAD *list);

/* Delete node in the list by address.
 * Return OK, or ERROR if not found. */
int delete_node(NODE *pNode, HEAD *list);

/* Delete all nodes in the list. */
void empty_list(HEAD *list);

/* Delete all nodes in the list and free the list head. */
void destroy_list(HEAD *list);

/* Print all nodes content of list to stdout */
void print_list(HEAD *list);


#endif /* _SL_LIST_H_ */
