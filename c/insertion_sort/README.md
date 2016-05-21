#插入排序

##基本思想  
每一步将一个待排序的元素，按其关键字的大小插入前面已经排好序的序列中适当位置上，直到全部插入完为止。  
直接插入排序的工作流程：

1. 设置监视哨 temp，将待插入元素的值赋值给 temp
2. 设置开始查找的位置 j
3. 在数组中进行搜索，搜索中将第 j 个纪录后移，直到 arr[j] ≤ temp 为止
4. 将 temp 插入 arr[j + 1] 的位置上
5. 重复步骤 1 到 4 直到将最后一个待插入元素插入适当位置为止

##算法描述  
直接插入排序-《算法导论》版本的伪代码：  
```
INSERTION-SORT(A)
	for j = 2 to A.length
		key = A[j]
		// Insert A[j] into the sorted sequence A[1 .. j - 1].
		i = j - 1
		while i > 0 and A[i] > key
			A[i + 1] = A[i]
			i = i - 1
		A[i + 1] = key
```
