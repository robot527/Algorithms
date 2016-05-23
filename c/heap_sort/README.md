#堆排序

##基本思想  
  
用**大根堆**排序的工作流程：

1. 先将初始序列 A[1..n] 构建成一个大根堆，此堆为初始的无序区
2. 再将最大的元素 A[1] （即堆顶）和无序区的最后一个元素 A[n] 交换，由此得到新的无序区 A[1..n-1] 和有序区 A[n] ，且满足任一 A[1..n-1] ≤ A[n]
3. 由于交换后新的堆顶 A[1] 可能违反大根堆的性质，故应将当前无序区 A[1..n-1] 调整为大根堆。然后再次将 A[1..n-1] 中最大的元素 A[1] 和该区间的最后一个元素 A[n-1] 交换，由此得到新的无序区 A[1..n-2] 和有序区 A[n-1..n] ，且仍满足关系任一 A[1..n-2] 小于等于任一 A[n-1..n]，同理要将 A[1..n-2] 调整为大根堆
4. 重复步骤 3 直到无序区只有一个元素为止

##算法描述  
《算法导论》版本的伪代码：  
```
PARENT(i)
	return i / 2

LEFT(i)
	return 2i

RIGHT(i)
	return 2i + 1

MAX-HEAPIFY(A, i)
	l = LEFT(i)
	r = RIGHT(i)
	if l ≤ A.heap-size and A[l] > A[i]
		largest = l
	else largest = i
	if r ≤ A.heap-size and A[r] > A[largest]
		largest = r
	if largest ≠ i
		exchange A[i] with A[largest]
		MAX-HEAPIFY(A, largest)

BUILD-MAX-HEAP(A)
	for i = (A.length / 2) downto 1
		MAX-HEAPIFY(A, i)

HEAPSORT(A)
	BUILD-MAX-HEAP(A)
	A.heap-size = A.length
	for i = A.length downto 2
		exchange A[1] with A[i]
		A.heap-size = A.heap-size - 1
		MAX-HEAPIFY(A, 1)
```	
