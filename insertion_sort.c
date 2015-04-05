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

void create_random_array(int *arr, int n)
{
	int i;
	srand(time(0));
	for (i = 0; i < n; i ++)
		arr[i] = rand() % (n * 10);
	printf("生成的数组如下：\n");
	show_array(arr, n);
}

void direct_insert_sort(int *arr, int first, int last)
{
	int i, j, temp;
	for (i = first + 1; i <= last; i ++)
	{
		temp = arr[i];
		for (j = i - 1; j >= first && arr[j] > temp; j --)
			arr[j + 1] = arr[j];
		arr[j + 1] = temp;
	}
}

int binary_find_pos(int *sorted, int first, int last, int value)
{
	int pos = last + 1;
	int left = first, right = last;
	
	if (first > last) return pos;
	if (value >= sorted[last]) return pos;
	/* show_array(sorted, last - first + 1);*/
	pos = left + (right - left) / 2;
	while (pos > left)
	{
		if (sorted[pos] <= value)
		{
			if (value <= sorted[pos + 1])
				return pos + 1;
			else
			{
				left = pos + 1;
				pos = left + (right - left) / 2;
			}
		}
		else
		{
			right = pos;
			pos = left + (right - left) / 2;
		}
	}
	return sorted[left] > value ? left : (left + 1);
}

void binary_insert_sort(int *arr, int len)
{
	int i, j, temp, pos;
	for (i = 1; i < len; i ++)
	{
		temp = arr[i];
		pos = binary_find_pos(arr, 0, i - 1, temp);
		/* printf("find %d pos %d\n", temp, pos);*/
		for (j = i - 1; j >= pos; j --)
			arr[j + 1] = arr[j];
		arr[pos] = temp;
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
#if	0
	direct_insert_sort(a, 0, n - 1);
	printf("\n直接插入排序后:\n");
#else
	binary_insert_sort(a, n);
	printf("\n二分插入排序后:\n");
#endif
	show_array(a, n);

	return 0;
}
