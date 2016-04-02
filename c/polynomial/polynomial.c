/*
 * =====================================================================================
 *
 *       Filename:  polynomial.c
 *
 *    Description:  implementations of polynomial arithmetic.
 *
 *        Version:  1.0
 *        Created:  04/01/2016 09:13:15 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  robot527 (), 
 *
 * =====================================================================================
 */

#ifndef _POLYNOMIAL_C_
#define _POLYNOMIAL_C_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "../lib/common_def.h"
#include "polynomial.h"

#define TEST	0

#if (TEST == 0)
int nodes1[][2] = {{10, 1000}, {5, 14}, {1, 0}};
int nodes2[][2] = {{3, 1990}, {-2, 1492}, {11, 1}, {5, 0}};
#elif (TEST == 1)
int nodes1[][2] = {{2, 5}, {5, 3}, {7, 2}, {6, 0}};
int nodes2[][2] = {{3, 4}, {-2, 3}, {9, 1}, {8, 0}};
#elif (TEST == 2)
int nodes1[][2] = {{2, 5}, {5, 3}, {4, 2}, {1, 0}};
int nodes2[][2] = {{-3, 5}, {6, 4}, {7, 1}};
#elif (TEST == 3)
int nodes1[][2] = {{11, 3}, {-3, 1}, {7, 0}};
int nodes2[][2] = {{2, 5}, {5, 2}, {3, 1}, {-12, 0}};
#else
int nodes1[][2] = {{7, 3}, {5, 2}, {9, 0}};
int nodes2[][2] = {{3, 3}, {-2, 2}};
#endif

poly_head *polynomial_generate(int node[][2], int rows)
{
	poly_head *poly;
	poly_node *pNew, *pTail = NULL;
	int i;

	if(rows < 2) return NULL;
	poly = malloc(sizeof(poly_head));
	if(NULL == poly) return NULL;
	poly->next = NULL;
	poly->count = 0;
	for(i = 0; i < rows; i++)
	{
		pNew = malloc(sizeof(poly_node));
		if(NULL == pNew)
		{
			return NULL;
		}
		pNew->coefficient = node[i][0];
		pNew->exponent = node[i][1];
		if(NULL == pTail)
			poly->next = pNew;
		else
			pTail->next = pNew;
		pTail = pNew;
		pNew->next = NULL;
		poly->count++;
	}

	return poly;
}

poly_head *polynomial_add(poly_head *poly1, poly_head *poly2)
{
	poly_head *poly_resu;
	poly_node *p1, *p2;
	poly_node *pNew, *pTail = NULL;
	
	if(poly1 != NULL && NULL == poly2) return poly1;
	if(poly2 != NULL && NULL == poly1) return poly2;

	poly_resu = malloc(sizeof(poly_head));
	if(NULL == poly_resu) return NULL;
	poly_resu->next = NULL;
	poly_resu->count = 0;
	p1 = poly1->next;
	p2 = poly2->next;
	while(p1 != NULL || p2 != NULL)
	{
		pNew = malloc(sizeof(poly_node));
		if(NULL == pNew)
		{
			polynomial_destory(poly_resu);
			return NULL;
		}
		pNew->next = NULL;
		if(p1 != NULL && p2 != NULL)
		{
			if(p1->exponent > p2->exponent)
			{
				pNew->exponent = p1->exponent;
				pNew->coefficient = p1->coefficient;
				p1 = p1->next;
			}
			else if(p1->exponent < p2->exponent)
			{
				pNew->exponent = p2->exponent;
				pNew->coefficient = p2->coefficient;
				p2 = p2->next;
			}
			else
			{
				pNew->exponent = p1->exponent;
				pNew->coefficient = p1->coefficient + p2->coefficient;
				p1 = p1->next;
				p2 = p2->next;
			}
		}
		else if(p1 != NULL)
		{
			pNew->exponent = p1->exponent;
			pNew->coefficient = p1->coefficient;
			p1 = p1->next;
		}
		else
		{
			pNew->exponent = p2->exponent;
			pNew->coefficient = p2->coefficient;
			p2 = p2->next;
		}
		if(NULL == pTail)
			poly_resu->next = pNew;
		else
			pTail->next = pNew;
		pTail = pNew;
		poly_resu->count++;
	}

	return poly_resu;
}

void polynomial_negate(poly_head *poly)
{
	poly_node *p;

	assert(poly != NULL);
	if(poly->count < 1) return;
	p = poly->next;
	while(p != NULL)
	{
		p->coefficient = -(p->coefficient);
		p = p->next;
	}
}

poly_head *polynomial_subtract(poly_head *poly1, poly_head *poly2)
{
	poly_head *poly_resu;

	if(poly1 != NULL && NULL == poly2) return poly1;
	polynomial_negate(poly2);
	poly_resu = polynomial_add(poly1, poly2);
	
	return poly_resu;
}

poly_head *polynomial_multiply(poly_head *poly1, poly_head *poly2)
{
	poly_head *poly_resu;


	return poly_resu;
}


void show_polynomial(poly_head *poly)
{
	poly_node *p;

	if(NULL == poly || poly->count < 1)
	{
		printf("Invalid polynomial !\n\n");
		return;
	}
	p = poly->next;
	//printf("The polynomial is: \n");
	printf("%dX^%d", p->coefficient, p->exponent);
	while(p->next != NULL)
	{
		p = p->next;
		if(1 == p->exponent)
			printf("%+dX", p->coefficient);
		else if(p->exponent != 0)
			printf("%+dX^%d", p->coefficient, p->exponent);
		else
			printf("%+d", p->coefficient);
	}
	printf("\n\n");
}

void polynomial_destory(poly_head *poly)
{
	poly_node *p, *temp;

	assert(poly != NULL);
	p = poly->next;
	poly->next = NULL;
	while(p != NULL)
	{
		temp = p->next;
		free(p);
		p = temp;
	}
	poly->count = 0;
	free(poly);
	poly = NULL;
}

int main(void)
{
	printf("Start testing polynomial arithmetic: \n");

	poly_head *poly1, *poly2;
	poly_head *poly_sum;
	poly_head *poly_sub;

	poly1 = polynomial_generate(nodes1, sizeof(nodes1) / sizeof(nodes1[0]));
	poly2 = polynomial_generate(nodes2, sizeof(nodes2) / sizeof(nodes2[0]));

	printf("The polynomial-1 is: \n");
	show_polynomial(poly1);
	printf("The polynomial-2 is: \n");
	show_polynomial(poly2);

	poly_sum = polynomial_add(poly1, poly2);
	printf("The polynomial-sum is: \n");
	show_polynomial(poly_sum);

	poly_sub = polynomial_subtract(poly1, poly2);
	printf("The polynomial-sub is: \n");
	show_polynomial(poly_sub);

	polynomial_destory(poly1);
	polynomial_destory(poly2);

	printf("\nAll tests done.\n");
	exit(EXIT_SUCCESS);
}


#endif  /* _POLYNOMIAL_C_ */

