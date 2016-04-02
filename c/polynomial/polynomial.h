/*
 * =====================================================================================
 *
 *       Filename:  polynomial.h
 *
 *    Description:  declarations of polynomial
 *
 *        Version:  1.0
 *        Created:  04/01/2016 09:11:48 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  robot527 (), 
 *
 * =====================================================================================
 */

#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

#include "../lib/type_rename.h"


typedef struct _polynomial_node_
{
	int coefficient;
	int exponent;
	struct _polynomial_node_ *next;
}poly_node; /* keep nodes sorted by exponent */

typedef struct _polynomial_head_
{
	poly_node *next;
	uint32    count;
}poly_head;


/* Generate a polynomial by a two dimensional array,
 * Return the head of the new polynomial list, or NULL if failed. */
poly_head *polynomial_generate(int node[][2], int rows);

/* Add the two polynomials,
 * Return the head of the sum polynomial list, or NULL if failed. */
poly_head *polynomial_add(poly_head *poly1, poly_head *poly2);

/* Negate the polynomial */
void polynomial_negate(poly_head *poly);

/* polynomial 1 subtract polynomial 2,
 * Return the head of the result polynomial. */
poly_head *polynomial_subtract(poly_head *poly1, poly_head *poly2);

/* Print the polynomial	to stdout */
void show_polynomial(poly_head *poly);

/* Free the polynomial list. */
void polynomial_destory(poly_head *poly);

#endif  /* _POLYNOMIAL_H_ */

