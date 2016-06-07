#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define NUM 1000000
#define MILLION 1000000
#define OK	1
#define ERROR	-1

void show_array(int arr[], int len)
{
	int i;
	if (len > 65535) return;
	for (i = 0; i < len; i ++)
	{
		printf("%-7d", arr[i]);
		if ((i % 10) == 9) printf("\n");
	}
	printf("\n");
}

void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void create_random_array(int *arr, int n)
{
	int i;
	srand(time(0));
	for (i = 0; i < n; i ++)
		arr[i] = rand() % (n * 10);
	printf("生成的数组如下：\n");
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
	if (NULL == left || NULL == right)
	{
		if (left != NULL) free(left);
		if (right != NULL) free(right);
		return ERROR;
	}
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

// According to <<Introduction to Algorithms Third Edition>> section 7.1 
int partition_v1(int *arr, int p, int r)
{
	int x = arr[r];
	int i = p - 1, j;
	
	for (j = p; j < r; j ++)
	{
		if (arr[j] <= x)
		{
			i ++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[j]);
	return i + 1;
}

void quick_sort_v2(int *arr, int p, int r)
{
	int q = 0;
	if (p >= r) return;
	q = partition_v1(arr, p, r);
	quick_sort_v2(arr, p, q - 1);
	quick_sort_v2(arr, q + 1, r);
}

int main(void)
{
	int a[NUM] = {0};
	int n = NUM;
	struct timeval start, end;
	double t;

	printf("Input the length(not more than %d) of array:", NUM);
	scanf("%d", &n);
	if (n > NUM || n < 1)
	{
		printf("Input para error!\n");
		return 0;
	}
	create_random_array(a, n);
	gettimeofday(&start, NULL);
#if	0
	if (quick_sort_v1(a, n) == OK)
	{
		printf("\n快速排序后:\n");
	}
	else printf("排序失败！\n");
#else
	quick_sort_v2(a, 0, n - 1);
	printf("\n快速排序后:\n");
#endif

	gettimeofday(&end, NULL);
	t = end.tv_sec - start.tv_sec\
		+ (double)(end.tv_usec - start.tv_usec) / MILLION;
	show_array(a, n);
	printf("排序耗时： %.6f seconds\n", t);

	return 0;
}

