#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
class C:
    @classmethod
    def f(cls, arg1, arg2, ...): ...

类方法传入的第一个参数不是instance的self，而是类cls.    
"""

class C:
    @classmethod
    def createC(cls, value):
        obj= cls(value)
        return obj
    def __init__(self, value):
        self.v= value

    def output(self):
        print("value= {0:d}".format(self.v))

c = C.createC(3)
c.output()
