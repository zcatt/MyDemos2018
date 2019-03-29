#!usr/bin/env python
#coding:utf-8

"""
eval(expression, globals=None, locals=None)

eval自动k可见built-in的namespace。globals和locals可以指定可见的namepsace.
"""
x = 1
print(eval('x+y',None,{'y':3}))

