#!usr/bin/env python
#coding:utf-8


"""
filter(function, iterable)
"""

# ref http://joequery.me/code/python-builtin-functions/#filter
def starts_with_vowel(the_str):
    vowels = ['a', 'e', 'i', 'o', 'u']
    if len(the_str) == 0:
        return False
    return the_str[0].lower() in vowels


words = ["hello", "apple", "excellent", "dictionary", "our"]
iter= filter(starts_with_vowel, words)
try:
    while(True):
        print(iter.__next__())
except StopIteration:
    pass





