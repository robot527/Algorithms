/*
 * =====================================================================================
 *
 *       Filename:  dl_list.h
 *
 *    Description:  definitions of doubly linked list
 *
 *        Version:  1.0
 *        Created:  2016-03-20 22:45:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  luoyz , NULL
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

#define LIST_INVALID_DATA  2147483647


/* Return number of entries in the list.
 * if param list is null, returns 0. */
int list_len(ENTRY *list);

/* Return the position of first x in list, or NULL if not found. */
ENTRY *list_find_data(ENTRY *list, element_type x);

/* Get the entry at a specified index in the list.
 * Return entry point at the specified index, or NULL if out of range. */
ENTRY *list_get_nth_entry(ENTRY *list, uint32 n);

/* Get the element at a specified index in the list.
 * Return the data at the specified index, or LIST_INVALID_DATA if failed. */
element_type list_get_nth_element(ENTRY *list, uint32 n);

/* Insert a new entry with x before head entry to the list.
 * Return the new entry, or NULL if failed. */
ENTRY *list_prepend(ENTRY **list, element_type x);

/* Return the tail entry of the list, or NULL if list is empty. */
ENTRY *list_tail(ENTRY **list);

/* Append a new entry with x to the end of the list.
 * Return the new entry, or NULL if failed. */
ENTRY *list_append(ENTRY **list, element_type x);

/* Create a list with n entries who's data is random.
 * Return the head entry of new list, or NULL if failed. */
ENTRY *create_list_with_random_data(uint32 n);

/* Delete an entry from the list.
 * Return OK, or ERROR if not failed. */
int list_delete_entry(ENTRY **list, ENTRY *entry);

/* Delete all occurrences of data from the list.
 * Return the number of entries deleted from the list, or 0 if not found. */
uint32 list_delete_data(ENTRY **list, element_type data);

/* Delete all entries in the list. */
void list_destroy(ENTRY **list);

/* Print all entries content of list to stdout */
void print_list(ENTRY *list);

/* Reverse data of the list. */
void list_reverse(ENTRY **list);


#endif  /* _DL_LIST_H_ */

