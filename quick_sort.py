#! /usr/bin/python


def generate_random_integer_list(n, stop=100):
    from random import randrange
    lst = []
    for i in range(n):
        lst.append(randrange(stop))
    return lst


def quick_sort(lst):
    if len(lst) <= 1:
        return lst
    else:
        pivot = lst[0]
        return quick_sort([item for item in lst[1:] if item < pivot])\
            + [pivot]\
            + quick_sort([item for item in lst[1:] if item >= pivot])


if __name__ == '__main__':
    num = 20
    list1 = generate_random_integer_list(num, num * 10)
    print "Data are as follows:"
    print list1
    list2 = quick_sort(list1)
    print "After sorting: "
    print list2
