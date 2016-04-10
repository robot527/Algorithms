#! /usr/bin/python
# -*- coding: GB2312 -*-
# author: robot527
# created at 2016-4-10

'''
输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变，句子中单词以空格符隔开。
为简单起见，标点符号和普通字母一样处理。
例如，输入“I am a student.”，则输出“student. a am I”。
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
