#!usr/bin/env python
#coding:utf-8


"""
map(function, iterable, ...)
"""

def product(x,y):
    return x*y

print(list(map(product, [1,2,3,4,5,6,7], [2,3,4,5,6])))

