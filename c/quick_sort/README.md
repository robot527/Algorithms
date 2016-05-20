#快速排序

##基本思想  
任取待排序对象序列中的某个对象(例如取第一个对象)作为枢轴(pivot)，通过一趟排序将要排序的对象按关键字大小划分成左右两个子序列，  
- 左侧子序列中所有对象的关键字都小于或等于枢轴对象的关键字
- 右侧子序列中所有对象的关键字都大于枢轴对象的关键字
- 枢轴对象则排在这两个子序列中间

然后再按此方法对左右两个子序列分别进行快速排序，整个排序过程可以递归进行，以此达到整个序列变成递增序列。

##算法描述  
简单版本的伪代码：  
```
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
```

《算法导论》版本的伪代码：  
```
PARTITION(A, p, r)
	x = A[r]
	i = p - 1
	for j = p to r - 1
		if A[j] ≤ x
			i = i + 1
			exchange A[i] with A[j]
	exchange A[i + 1] with A[r]
	return i + 1

QUICKSORT(A, p, r)
	if p < r
		q = PARTITION(A, p, r)
		QUICKSORT(A, p, q - 1)
		QUICKSORT(A, q + 1, r)
```
