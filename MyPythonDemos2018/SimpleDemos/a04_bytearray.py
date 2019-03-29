#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
class bytearray([source[, encoding[, errors]]])
source字符串时,需要给定encoding;
source整数时，是这个整数所指定长度的空字节数组
source为实现了buffer接口的object对象时，那么将使用只读方式将字节读取到字节数组后返回
source参数是一个可迭代对象，那么这个迭代对象的元素都必须符合0 <= x < 256，以便可以初始化到数组里
"""
b = bytearray('你好', 'utf-8')
print(b)

b = bytearray(6)
print(b)

b = bytearray([1,2,3,4,5])
print(b)

b[1] = 12
print(b)