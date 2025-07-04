#!/usr/bin/python3.6
# -*- coding: UTF-8 -*-
from operator import itemgetter
from itertools import groupby
import sys
def read_mapper_output(file, separator = '\t'):
    for line in file:
        yield line.rstrip().split(separator, 1)
def main(separator = '\t'):
    data = read_mapper_output(sys.stdin, separator = separator)
    #data = sorted(data, key=itemgetter(0))
    #这里用到了groupby，该对象利用迭代器按关键字输出word-count对，
    #groupby有利于按照关键字进行分组数据处理。
    for current_word, group in groupby(data, itemgetter(0)):
        try:
            total_count = sum(int(count) for word, count in group)
            print("%s%s%d" % (current_word, separator, total_count))
        except valueError:
            pass
if __name__ == "__main__":
    main()
