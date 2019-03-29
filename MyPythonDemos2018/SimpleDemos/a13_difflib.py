#!usr/bin/env python
#coding:utf-8
"""
比较两个字串，输出结果到html文件 result.html
"""

import difflib

text1 = """
abc def ghi
klm nop qrs
tuw vxy z

123 456 
morning
789
tasdf asdfas 
"""

text2 = """
abc deq ghi
klm nop qrs
hello 
tuw vxy z

123 456 
789

tasdf asdfas 
"""

lines1 = text1.splitlines()
lines2 = text2.splitlines()
diff = difflib.HtmlDiff()    # 创建HtmlDiff 对象

result = diff.make_file(lines1, lines2) # 通过make_file 方法输出 html 格式的对比结果 
# 将结果写入到result_comparation.html文件中 
try: 
    with open('a13_difflib_result.html', 'w') as result_file: 
        result_file.write(result) 
        print("Success.\n")
except IOError as error: 
    print('Fail to write file {0}'.format(error))

print("game over")

