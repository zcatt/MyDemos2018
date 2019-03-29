#!usr/bin/env python
#coding:utf-8

"""
dir([object])
"""

class C:
    def __dir__(self):
        return['hello', 'world']

c = C()
print(dir(c))

