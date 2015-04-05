#! /usr/bin/python


def generate_random_integer_list(n, stop=100):
    from random import randrange
    lst = []
    for i in range(n):
        lst.append(randrange(stop))
    return lst


def merge_sort(lst):
    if len(lst) <= 1:
        return lst

    def merge_list(left, right):
        """merge two sorted list"""
        temp = []
        while left and right:
            temp.append(left.pop(0) if left[0] <= right[0]\
                else right.pop(0))
        """while left:
            temp.append(left.pop(0))
        while right:
            temp.append(right.pop(0))"""
        temp += left + right
        return temp

    middle = int(len(lst) / 2)
    left = merge_sort(lst[:middle])
    right = merge_sort(lst[middle:])
    return merge_list(left, right)


if __name__ == '__main__':
    num = 30
    list1 = generate_random_integer_list(num, num * 10)
    print "Data are as follows:"
    print list1
    list2 = merge_sort(list1)
    print "After sorting: "
    print list2
