#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import sys  # 引入sys模块

# 从标准输入sys.stdin中读取输入数据 
for myline in sys.stdin: 
   # 消除读入数据两端的空白字符，包括空格，回车，Tab键等 
   myline = myline.strip() 

   # 把读入数据分割为单词List并存储与words中 
   words = myline.split() 

   # 对words列表迭代操作，逐个处理其中分割出的单词
   for myword in words:
      # 把<单词，1>组成的键值对输出到标准输出中，中间用Tab键隔开 
      print('%s\t%s' % (myword, 1))
