#!/usr/bin/python3.6
# -*- coding: UTF-8 -*-
import sys
def read_input(inputs):    #利用生成器
    for line in inputs:
        if line.find('PM2.5,')>=0:  #利用find过滤非PM2.5数据
            yield line.strip().split(',')
def main(separator='\t'):
    wd = read_input(sys.stdin)
    for word in wd:  #20140513,0,AQI,北京,81，word[2]为指标类型
        output = "{0}{2}{1}{2}{1}{2}{1}{2}1".format(word[3], word[4], separator)
        print(output)
if __name__ == "__main__":
    main()
