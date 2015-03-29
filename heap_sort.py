#!/usr/bin/env python
 

def heap_sort(lst):
    def sift_down(start, end):
        """max-heapify"""
        root = start
        while True:
            child = 2 * root + 1
            if child > end:
                break
            if child + 1 <= end and lst[child] < lst[child + 1]:
                child += 1
            if lst[root] < lst[child]:
                lst[root], lst[child] = lst[child], lst[root]
                root = child
            else:
                break
 
    # build max-heap 
    for start in range(int((len(lst) - 2) / 2), -1, -1):
        sift_down(start, len(lst) - 1)
 
    # heap sort
    for end in range(len(lst) - 1, 0, -1):
        lst[0], lst[end] = lst[end], lst[0]
        sift_down(0, end - 1)
    return lst


def generate_random_integer_list(n, stop=100):
    from random import randrange
    lst = []
    for i in range(n):
        lst.append(randrange(stop))
    return lst


def main():
    num = raw_input('Input the length of list-> ')
    try:
        num = int(num)
    except ValueError:
        print "Input para error! we will run with default para."
        num = 0
    if num < 1:
        num = 20 #default para
    list1 = generate_random_integer_list(num, num * 10)
    print "Data are as follows:"
    print list1
    list2 = heap_sort(list1)
    print "After sorting: "
    print list2 

if __name__ == "__main__":
    main()
