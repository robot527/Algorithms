#! /usr/bin/python


def quick_sort(lst):
    if len(lst) <= 1:
        return lst
    else:
        pivot = lst[0]
        return quick_sort([item for item in lst[1:] if item < pivot])\
            + [pivot]\
            + quick_sort([item for item in lst[1:] if item >= pivot])


list1 = [5, 3, 7, 4, 1, 9, 8, 6, 2]
list2 = quick_sort(list1)


print "Before: ", list1
print "After: ", list2

