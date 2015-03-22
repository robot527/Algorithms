#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM 10000
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
		arr[i] = rand() % (n * 10);
	printf("生成的数组如下：\n");
	show_array(arr, n);
}

void merge_array(int *arr, int first, int mid, int last, int *temp)
{
	int i = first, j = mid + 1;
	int k = 0;
	
	if (NULL == arr || NULL == temp) return;
	while (i <= mid && j <= last)
	{
		if (arr[i] <= arr[j])
			temp[k ++] = arr[i ++];
		else
			temp[k ++] = arr[j ++];
	}
	while (i <= mid)
		temp[k ++] = arr[i ++];
	while (j <= last)
		temp[k ++] = arr[j ++];
	for (i = 0; i < k; i ++)
		arr[first + i] = temp[i];
}

void merge_sort(int *arr, int first, int last, int *temp)
{
	if (NULL == arr || NULL == temp) return;
	if (first < last)
	{
		int mid = first + (last - first) / 2;
		merge_sort(arr, first, mid, temp);
		merge_sort(arr, mid + 1, last, temp);
		merge_array(arr, first, mid, last, temp);
	}
}

int main(void)
{
	int a[NUM] = {0}, n = NUM;
	int *temp;

	printf("Input the length(not more than %d) of array:", NUM);
	scanf("%d", &n);
	if (n > NUM || n < 1)
	{
		printf("Input para error!\n");
		return 0;
	}
	create_random_array(a, n);
	temp = (int *)calloc(n, sizeof(int));
	if (NULL == temp) return 0;
	merge_sort(a, 0, n - 1, temp);
	printf("\n归并排序后:\n");
	show_array(a, n);
	if (temp != NULL) free(temp);
	
	return 0;
}
	
