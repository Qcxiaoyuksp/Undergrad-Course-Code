#!/usr/bin/python3
# -*- coding: UTF-8 -*-

from operator import itemgetter 
import sys 

current_word = ""  #初始化相关变量
current_count = 0 
word = "" 

# 从标准输入sys.stdin中读取输入数据
for myline in sys.stdin: 
   # 消除读入数据两端的空白字符，包括空格，回车，Tab键等  
   myline = myline.strip() 

   # 把mapper输出的键值对分割为word和count两部分，他们以Tab键分割
   word, count = myline.split('\t', 1) 

   # 把其中的count转换为整数 
   try: 
      count = int(count) 
   except ValueError: 
      # 若分割出的count不能转换为整数，则忽略 
      continue

   #mapper输出由MapReducer框架进行排序，所以相同的key接连作为reduce输入，
   #所以可以利用前后单词是否相同来进行出现次数的统计。
   if current_word == word: 
      current_count += count 
   else: 
      if current_word: 
         # 若出现新单词，则说明已经统计完一个单词，从标准输出输出其出现次数 
         print('%s\t%s' % (current_word, current_count))
      current_count = count
      current_word = word

# 所有键值对处理结束后，把最后一个单词出现次数输出 
if current_word == word: 
   print('%s\t%s' % (current_word, current_count))
