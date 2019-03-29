#!usr/bin/env python
#coding:utf-8

"""
compile(source, filename, mode, flags=0, dont_inherit=False, optimize=-1)

source，包含代码的字串或AST obj
filename， source的出处
mode，   
    'exec': indicates compliation is intended for an entire Python module
    'single': indicates compilation is intended for a single statement
    'eval': indicates compilation is intended for a single expression
"""
#若a04_bytearray.py是utf-8 BOM格式时，会无法识别首字符，how???
with open('a04_bytearray.py', encoding='UTF-8') as f:
    source = f.read()

codeObj = compile(source, 'a04_bytearray.py', 'exec')
exec(codeObj)
