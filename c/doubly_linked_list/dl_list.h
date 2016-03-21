/*
 * =====================================================================================
 *
 *       Filename:  dl_list.h
 *
 *    Description:  definitions of doubly linked list
 *
 *        Version:  1.0
 *        Created:  2016年03月20日 22时45分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  luoyz , NULL
 *        Company:  NULL
 *
 * =====================================================================================
 */

#ifndef _DL_LIST_H_
#define _DL_LIST_H_

#include "../lib/type_rename.h"


typedef struct _dl_list_entry_
{
	element_type          data;
	struct _dl_list_entry_ *prev;
	struct _dl_list_entry_ *next;
}ENTRY;


/* Create an list with a head entry.
 * Return the entry of new list, or NULL if failed. */
ENTRY *create_new_list(void);

/* Return number of entries in the list.
 * if param list is null, returns 0. */
int list_len(ENTRY *list);

/* Return the position of first x in list, or NULL if not found. */
ENTRY *list_find_data(ENTRY *list, element_type x);

/* Get the entry at a specified index in the list.
 * Return entry point at the specified index, or NULL if out of range. */
ENTRY *list_get_nth_entry(ENTRY *list, uint32 n);

/* Insert a new entry with x before head entry to the list.
 * Return the new entry, or NULL if failed. */
ENTRY *list_prepend(ENTRY *list, element_type x);

/* Create a list with n entries who's data is random.
 * Return the head entry of new list, or NULL if failed. */
ENTRY *create_list_with_random_data(uint32 n);

/* Delete all entries in the list. */
void destroy_list(ENTRY *list);

/* Print all entries content of list to stdout */
void print_list(ENTRY *list);


#endif  /* _DL_LIST_H_ */

