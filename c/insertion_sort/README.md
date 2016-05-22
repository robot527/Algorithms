#插入排序

##基本思想  
**直接插入排序**：每一步将一个待排序的元素，按其关键字的大小插入前面已经排好序的序列中适当位置上，直到全部插入完为止。  
直接插入排序的工作流程：

1. 设置监视哨 temp，将待插入元素的值赋值给 temp
2. 设置开始查找的位置 j
3. 在数组中进行搜索，搜索中将第 j 个纪录后移，直到 arr[j] ≤ temp 为止
4. 将 temp 插入 arr[j + 1] 的位置上
5. 重复步骤 1 到 4 直到将最后一个待插入元素插入适当位置为止

**折半插入排序**：将直接插入排序中寻找 temp 的插入位置的方式由顺序查找改为折半查找，就得到了折半插入排序算法。  
折半插入排序的工作流程：

1. 计算已排好序序列左边界到右边界的中间点，将 temp 与中间点元素比较，如果 temp 较大，则说明 temp 要插入中间点到右边界之间，否则就要插入左边界到中间点之间，这样经过一次比较即可排除一半位置，完成了折半
2. 在相应一半的范围里面找插入的位置时，不断的用步骤 1 缩小范围，不停的折半，范围依次缩小为 1/2， 1/4， 1/8 ... 快速的确定出 temp 要插入的位置
3. 确定位置之后，将相应元素后移，并将 temp 插入到相应位置

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

折半查找的伪代码：  
```
BINARY-FIND-POSITION(A, left, right, temp)
	pos = (left + right) / 2
	while pos > left
		if temp > A[pos]
			left = pos + 1
		else
			right = pos - 1
		pos = (left + right) / 2
	// compare temp to A[pos + 1]
	return final_pos
```
