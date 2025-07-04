#!/usr/bin/python3.6
# -*- coding: UTF-8 -*-
import sys
def read_input(file):
    for line in file:
        #采用生成器按行进行数据获取
        yield line.split()
def main(separator='\t'):
#输入来自于STDIN，传递给read_input函数
    data = read_input(sys.stdin)
    for words in data:
       #把结果输出到STDOUT，
       for word in words:
           print("%s%s%d" % (word, separator, 1))
if __name__ == "__main__":
    main()
