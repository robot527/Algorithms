#! /usr/bin/python
# -*- coding: GB2312 -*-
# author: robot527
# created at 2016-4-10

'''
����һ��Ӣ�ľ��ӣ���ת�����е��ʵ�˳�򣬵��������ַ���˳�򲻱䣬�����е����Կո��������
Ϊ������������ź���ͨ��ĸһ������
���磬���롰I am a student.�����������student. a am I����
'''


def reverse_sentence(sentence):
    '''
    Reverse the order of words in a sentence,
    regard punctuation as ordinary letter.
    '''
    from string import join
    words = sentence.split(' ')
    words = list(reversed(words))
    result = join(words, ' ')
    return result


if __name__ == '__main__':
    print 'Please input a sentence.'
    s = raw_input("@> ")
    print reverse_sentence(s)
