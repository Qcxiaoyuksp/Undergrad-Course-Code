#!/usr/bin/python3.6
# -*- coding: UTF-8 -*-
import sys
def read_input(inputs, separator):
    for line in inputs:
        yield line.strip().split(separator)
def main(separator='\t'):
    current_city = None
    maxv = minv = counter = sumv = 0
    wd = read_input(sys.stdin, separator)
    for words in wd:
        city = words[0]
        if(city == current_city):
            maxv = max(maxv, float(words[1]))
            minv = min(minv, float(words[2]))
            sumv += float(words[3])
            counter += int(words[4])
        else:
            if counter>0:   #用于排除第一条数据情况
                print("{0}{4}{1}{4}{2}{4}{3}".format(current_city, maxv, minv, sumv/counter, separator))
            maxv, minv, sumv, counter = float(words[1]), float(words[2]), float(words[3]), int(words[4])
            current_city = words[0]
    output = "{0}{4}{1}{4}{2}{4}{3}".format(current_city, maxv, minv, sumv/counter, separator)
    print(output)   #输出最后一个城市数据
if __name__ == "__main__":
    main()
