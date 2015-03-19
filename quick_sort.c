#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM 100
#define OK	1
#define ERROR	-1

void show_array(int arr[], int len)
{
	int i;
	for (i = 0; i < len; i ++)
	{
		printf("%-7d", arr[i]);
		if ((i % 10) == 9) printf("\n");
	}
	printf("\n");
}

void create_random_array(int *arr, int n)
{
	int i;
	srand(time(0));
	for (i = 0; i < n; i ++)
		arr[i] = rand() % (NUM * 10);
	printf("生产的数组如下：\n");
	show_array(arr, n);
}

/*
简单版本的伪代码：
 function quicksort(q)
     var list less, pivotList, greater
     if length(q) ≤ 1 {
         return q
     } else {
         select a pivot value pivot from q
         for each x in q except the pivot element
             if x < pivot then add x to less
             if x ≥ pivot then add x to greater
         add pivot to pivotList
         return concatenate(quicksort(less), pivotList, quicksort(greater))
     }
*/
int quick_sort_v1(int *arr, int len)
{
	int *left, *right;
	int lnum = 0, rnum = 0;
	int pivot, i, j = 0;
	int ret = ERROR;

	if (len < 2) return OK;
	left = (int *)calloc(len, sizeof(int));
	right = (int *)calloc(len, sizeof(int));
	if (NULL == left || NULL == right) return ERROR;
	pivot = arr[0];
	for (i = 1; i < len; i ++)
	{
		if (arr[i] < pivot)
		{
			left[lnum ++] = arr[i];
		}
		else
		{
			right[rnum ++] = arr[i];
		}
	}
	if (quick_sort_v1(left, lnum) == OK\
		&& quick_sort_v1(right, rnum) == OK)
	{
		i = 0;
		while (i < lnum)
		{
			arr[i] = left[i];
			i ++;
		}
		arr[i ++] = pivot;
		while (j < rnum)
			arr[i ++] = right[j ++];
		ret = OK;
	}
	if (left != NULL) free(left);
	if (right != NULL) free(right);
	return ret;
}

int main(void)
{
	int a[NUM] = {0};
	int n = NUM;

	create_random_array(a, n);
	if (quick_sort_v1(a, n) == OK)
	{
		printf("\n快速排序后:\n");
		show_array(a, n);
	}
	else printf("排序失败！\n");

	return 0;
}

