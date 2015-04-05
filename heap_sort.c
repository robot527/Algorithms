#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM 10000

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

static void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

static void create_random_array(int *arr, int n)
{
	int i;
	srand(time(0));
	for (i = 0; i < n; i ++)
		arr[i] = rand() % (n * 10);
	printf("生成的数组如下：\n");
	show_array(arr, n);
}

void max_heapify(int *arr, int idx, int len)
{
	int root = idx;
	int child = root * 2 + 1;

	while (child < len)
	{
		if (child + 1 < len && arr[child] < arr[child + 1])
			child ++;
		if (arr[root] < arr[child])
		{
			swap(&arr[root], &arr[child]);
			root = child;
			child = root * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void heap_sort(int *arr, int len)
{
	int i;

	for (i = (len - 2) / 2; i >= 0; i --)
		max_heapify(arr, i, len);
	for (i = 0; i < len; i ++)
	{
		swap(&arr[0], &arr[len - i - 1]);
		max_heapify(arr, 0, len - i - 1);
	}
}

int main(void)
{
	int a[NUM] = {0};
	int n = NUM;

	printf("Input the length(not more than %d) of array:", NUM);
	scanf("%d", &n);
	if (n > NUM || n < 1)
	{
		printf("Input para error!\n");
		return 0;
	}
	create_random_array(a, n);
	heap_sort(a, n);
	printf("\n堆排序后:\n");
	show_array(a, n);

	return 0;
}

