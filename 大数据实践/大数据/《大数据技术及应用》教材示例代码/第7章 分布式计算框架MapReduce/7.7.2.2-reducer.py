#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys
def read_input(inputs):
    for line in inputs:
        yield line.strip().split('\t')  #利用生成器，逐个读取数据
def main(separator='\t'):
    current_city = None
    time = []
    city = None
    wd = read_input(sys.stdin)
    for data in wd:
        city = data[0]
        if(city == current_city):
            time.append(data[2])  #把所有日期和时刻组成一个列表
        else:
            if current_city:   #城市变化时，输出上一个城市列表，并初始
                output = "{1}{0}{2}{0}{3}".format(separator, current_city, data[1], time)
                print(output)
                time=[]
            current_city = city
            time.append(data[2])
    if(city == current_city):  #输出最后一个城市数据
        output = "{1}{0}{2}{0}{3}".format(separator, city, data[1], time)
        print(output)

if __name__ == "__main__":
    main()
