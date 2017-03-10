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


poly_head *polynomial_generate(int node[][2], uint32 rows)
{
	poly_head *poly;
	poly_node *pNew, *pTail = NULL;
	uint32 i;

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
			polynomial_destory(poly);
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

void init_two_dimensional_array_with_random_data(int arr[][2], uint32 rows)
{
	uint32 i;
	
	srand(time(0) / rows);
	for(i = 0; i < rows; i++)
	{
		arr[i][0] = rand() % 301 - 150; /* [-150, 150] */
		arr[i][1] = rand() % 12;
	}
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
		if(pNew->coefficient != 0)
		{
			if(NULL == pTail)
				poly_resu->next = pNew;
			else
				pTail->next = pNew;
			pTail = pNew;
			poly_resu->count++;
		}
		else
			free(pNew);
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
	poly_node *p1, *p2;
	poly_node *pNew, *pTail = NULL;

	if(NULL == poly1 || NULL == poly2) return NULL;

	poly_resu = malloc(sizeof(poly_head));
	if(NULL == poly_resu) return NULL;
	poly_resu->next = NULL;
	poly_resu->count = 0;
	p2 = poly2->next;
	while(p2 != NULL)
	{
		p1 = poly1->next;
		while(p1 != NULL)
		{
			pNew = malloc(sizeof(poly_node));
			if(NULL == pNew)
			{
				polynomial_destory(poly_resu);
				return NULL;
			}
			pNew->next = NULL;
			pNew->coefficient = p1->coefficient * p2->coefficient;
			pNew->exponent = p1->exponent + p2->exponent;
			if(NULL == pTail)
				poly_resu->next = pNew;
			else
				pTail->next = pNew;
			pTail = pNew;
			poly_resu->count++;
			p1 = p1->next;
		}
		p2 = p2->next;
	}
	polynomial_similar_items_merge(poly_resu);
	polynomial_sort(poly_resu);

	return poly_resu;
}

/* test is a divisible by b. */
int is_divisible(int a, int b)
{
	int temp;

	if(0 == b) return false;
	temp = a / b;
	if((b * temp) == a)
		return true;
	else
		return false;
}

/* poly1 divided by poly2 */
poly_head *polynomial_division(poly_head *poly1, poly_head *poly2)
{
	poly_head *poly_resu;
	poly_head *poly_sn = NULL; /* polynomial with one node */
	poly_head *poly1_new = NULL, *poly1_new_last;
	poly_head *poly2_m = NULL;
	poly_node *p1H, *p2H, *quotientNode;
	poly_node *pTail = NULL;

	if(NULL == poly1 || NULL == poly2 || NULL == poly1->next
		|| NULL == poly2->next)
		return NULL;

	poly_resu = malloc(sizeof(poly_head));
	if(NULL == poly_resu) return NULL;
	poly_resu->next = NULL;
	poly_resu->count = 0;
	poly_sn = malloc(sizeof(poly_head));
	if(NULL == poly_sn)
	{
		goto FAILED;
	}
	poly_sn->next = NULL;
	poly_sn->count = 1;
	p2H = poly2->next; /* max exponent node of poly2 */
	poly1_new = poly1;
	p1H = poly1_new->next; /* max exponent node of poly1_new */
	while(p1H != NULL && p1H->exponent != 0)
	{
		if(is_divisible(p1H->coefficient, p2H->coefficient) != true)
		{
			printf("The poly1 is not divisible by poly2!\n");
			goto FAILED;
		}
		quotientNode = malloc(sizeof(poly_node));
		if(NULL == quotientNode)
		{
			goto FAILED;
		}
		quotientNode->next = NULL;
		quotientNode->coefficient = p1H->coefficient / p2H->coefficient;
		quotientNode->exponent = p1H->exponent - p2H->exponent;
		poly_sn->next = quotientNode;
		if(NULL == pTail)
			poly_resu->next = quotientNode;
		else
			pTail->next = quotientNode;
		pTail = quotientNode;
		poly_resu->count++;
		if(0 == quotientNode->exponent)
		{
			printf("last node is %d\n", quotientNode->coefficient);
			break;
		}
		poly2_m = polynomial_multiply(poly2, poly_sn);
		if(NULL == poly2_m)
		{
			goto FAILED;
		}
		poly1_new_last = poly1_new;
		poly1_new = polynomial_subtract(poly1_new, poly2_m);
		if(poly1_new_last != poly1)
		{
			polynomial_destory(poly1_new_last);
		}
		if(NULL == poly1_new)
		{
			goto FAILED;
		}
		polynomial_destory(poly2_m);
		p1H = poly1_new->next;
	}
	free(poly_sn);
	if(poly1_new != poly1)
	{
		polynomial_destory(poly1_new);
	}

	return poly_resu;

FAILED:
	polynomial_destory(poly_resu);
	free(poly_sn);
	if(poly1_new != poly1)
	{
		polynomial_destory(poly1_new);
	}
	polynomial_destory(poly2_m);
	return NULL;
}

void polynomial_similar_items_merge(poly_head *poly)
{
	poly_node *p, *prev, *temp;

	if(NULL == poly || poly->count < 2)
	{
		printf("Invalid polynomial !\n\n");
		return;
	}
	p = poly->next;
	while(p != NULL)
	{
		prev = p;
		temp = p->next;
		while(temp != NULL)
		{
			if(temp->exponent == p->exponent)
			{
				p->coefficient += temp->coefficient;
				prev->next = temp->next;
				free(temp);
				poly->count--;
				temp = prev->next;
			}
			else
			{
				prev = temp;
				temp = temp->next;
			}
		}
		p = p->next;
	}
	p = poly->next;
	while(p != NULL && 0 == p->coefficient)
	{
		/* delete nodes which coefficient is 0 at the first position. */
		poly->next = p->next;
		free(p);
		poly->count--;
		p = poly->next;
	}
	p = poly->next;
	while(p != NULL && p->next != NULL)
	{
		if(0 == p->next->coefficient)
		{
			/* delete nodes which coefficient is 0 at follow position. */
			temp = p->next;
			p->next = temp->next;
			free(temp);
			poly->count--;
		}
		p = p->next;
	}
}

void polynomial_sort(poly_head *poly)
{
	poly_node *p, *prev, *temp;
	poly_node *sorted_end;
	int flag = 1;

	if(NULL == poly || poly->count < 2)
	{
		printf("Invalid polynomial !\n\n");
		return;
	}
	/* direct insert sort */
	sorted_end = poly->next;
	while(sorted_end != NULL)
	{
		temp = sorted_end->next;
		if(NULL == temp) break; /* sequence is done */
		flag = 0;
		p = poly->next; /* from start */
		prev = p;
		while(p != NULL && p != sorted_end->next) /* to sorted end */
		{
			if(temp->exponent > p->exponent)
			{
				flag = 1;
				//printf("insert %d before %d\n", temp->exponent, p->exponent);
				sorted_end->next = temp->next;
				temp->next = p;
				if(p != prev)
					prev->next = temp;
				else
					poly->next = temp;
				break;
			}
			else
			{
				prev = p;
				p = p->next;
			}
		}
		if(0 == flag) sorted_end = sorted_end->next;
	}
}

void test_merge_and_sort()
{
	int nodes[20][2];
	poly_head *poly;
	uint32 row;

	srand(time(0));
	row = rand() % 19 + 2;
	init_two_dimensional_array_with_random_data(nodes, row);
	printf("Testing polynomial merge similar items and sort:\n");
	poly = polynomial_generate(nodes, row);
	show_polynomial(poly);

	polynomial_similar_items_merge(poly);
	show_polynomial(poly);
	printf("Merged done.\n\n");

	polynomial_sort(poly);
	show_polynomial(poly);
	printf("Sorted done.\n\n");
	polynomial_destory(poly);
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
	if(1 == p->coefficient)
	{
		if(1 == p->exponent)
			printf("X");
		else if(p->exponent != 0)
			printf("X^%d", p->exponent);
		else /* if(p->exponent == 0) */
			printf("1");
	}
	else if(p->coefficient != 0)
	{
		if(1 == p->exponent)
			printf("%dX", p->coefficient);
		else if(p->exponent != 0)
			printf("%dX^%d", p->coefficient, p->exponent);
		else /* if(p->exponent == 0) */
			printf("%d", p->coefficient);
	}
	while(p->next != NULL)
	{
		p = p->next;
		if(1 == p->coefficient)
		{
			if(1 == p->exponent)
				printf("+X");
			else if(p->exponent != 0)
				printf("+X^%d", p->exponent);
			else /* if(p->exponent == 0) */
				printf("+1");
		}
		else if(p->coefficient != 0)
		{
			if(1 == p->exponent)
				printf("%+dX", p->coefficient);
			else if(p->exponent != 0)
				printf("%+dX^%d", p->coefficient, p->exponent);
			else /* if(p->exponent == 0) */
				printf("%+d", p->coefficient);
		}
	}
	printf("\t(%d items)\n", poly->count);
	printf("\n");
}

void polynomial_destory(poly_head *poly)
{
	poly_node *p, *temp;

	if(NULL == poly) return;
	p = poly->next;
	while(p != NULL)
	{
		temp = p->next;
		free(p);
		p = temp;
	}
	poly->count = 0;
	free(poly);
}

static void test_polynomial_division()
{
#define ROW_NUM 1000

	poly_head *poly1, *poly2, *poly_m;
	poly_head *poly_div;
	int nodes1[][2] = {{1, 2}, {-2, 1}, {1, 0}};
	int nodes2[ROW_NUM][2];
	int i;

	srand(time(0));
	for(i = 0; i < ROW_NUM; i++)
	{
		nodes2[i][0] = rand() % 101 - 50;
		nodes2[i][1] = ROW_NUM - i;
	}

	poly1 = polynomial_generate(nodes1, sizeof(nodes1) / sizeof(nodes1[0]));
	poly2 = polynomial_generate(nodes2, sizeof(nodes2) / sizeof(nodes2[0]));
	poly_m = polynomial_multiply(poly1, poly2);

	printf("Testing polynomial division:\n");
	printf("The polynomial-A is: \n");
	show_polynomial(poly_m);
	printf("The polynomial-B is: \n");
	show_polynomial(poly1);
	printf("The polynomials' quotient is: \n");
	poly_div = polynomial_division(poly_m, poly1);
	show_polynomial(poly_div);

	polynomial_destory(poly1);
	polynomial_destory(poly2);
	polynomial_destory(poly_m);
	polynomial_destory(poly_div);
}

int main(void)
{
	printf("Start testing polynomial arithmetic: \n");

	poly_head *poly1, *poly2;
	poly_head *poly_sum;
	poly_head *poly_sub;
	poly_head *poly_mul;

#if 0
	int nodes1[][2] = {{10, 1000}, {5, 14}, {1, 0}};
	int nodes2[][2] = {{3, 1990}, {-2, 1492}, {11, 1}, {5, 0}};

	poly1 = polynomial_generate(nodes1, sizeof(nodes1) / sizeof(nodes1[0]));
	poly2 = polynomial_generate(nodes2, sizeof(nodes2) / sizeof(nodes2[0]));
#else
	int nodes1[10][2];
	int nodes2[10][2];
	uint32 row1, row2;

	srand(time(0));
	row1 = rand() % 9 + 2;
	init_two_dimensional_array_with_random_data(nodes1, row1);
	poly1 = polynomial_generate(nodes1, row1);
	polynomial_similar_items_merge(poly1);
	polynomial_sort(poly1);
	srand(time(0) / row1);
	row2 = rand() % 9 + 2;
	init_two_dimensional_array_with_random_data(nodes2, row2);
	poly2 = polynomial_generate(nodes2, row2);
	polynomial_similar_items_merge(poly2);
	polynomial_sort(poly2);
#endif

	printf("The polynomial-1 is: \n");
	show_polynomial(poly1);
	printf("The polynomial-2 is: \n");
	show_polynomial(poly2);
	printf("==============================================================\n");

	poly_sum = polynomial_add(poly1, poly2);
	printf("The polynomials' sum is: \n");
	show_polynomial(poly_sum);

	poly_mul = polynomial_multiply(poly1, poly2);
	printf("The polynomials' product is: \n");
	show_polynomial(poly_mul);

	poly_sub = polynomial_subtract(poly1, poly2);
	printf("The polynomials' difference is: \n");
	show_polynomial(poly_sub);

	printf("==============================================================\n");
	test_merge_and_sort();

	printf("==============================================================\n");
	test_polynomial_division();
	{
		poly_head *poly_div;

		printf("The polynomial-1 is: \n");
		show_polynomial(poly1);
		printf("The polynomial-2 is: \n");
		show_polynomial(poly2);
		poly_div = polynomial_division(poly1, poly2);
		if(poly_div != NULL)
		{
			printf("The polynomials' quotient is: \n");
			show_polynomial(poly_div);
			polynomial_destory(poly_div);
		}
	}

	polynomial_destory(poly1);
	polynomial_destory(poly2);
	polynomial_destory(poly_sum);
	polynomial_destory(poly_sub);
	polynomial_destory(poly_mul);

	printf("\nAll tests done.\n");
	exit(EXIT_SUCCESS);
}


#endif  /* _POLYNOMIAL_C_ */

