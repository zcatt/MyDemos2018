#!usr/bin/env python
#coding:utf-8


"""
isinstance(object, classinfo)
"""

class A:
    pass

class B(A):
    pass

c=2
print(isinstance(c, int))
print(isinstance(c, (str, int, list)))

print(isinstance(A(), A))
print(isinstance(B(), A))

