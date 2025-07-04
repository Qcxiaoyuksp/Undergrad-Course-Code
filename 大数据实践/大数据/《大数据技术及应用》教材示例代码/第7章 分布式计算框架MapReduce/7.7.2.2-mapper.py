#!/usr/bin/python3.6
# -*- coding: UTF-8 -*-
import sys
def read_input(inputs):
    for line in inputs:
        yield line.strip().split(',')
def main(separator='\t'):
    year = 2020  # 指定的年份
    wd = read_input(sys.stdin)
    for word in wd:  #数据格式例：“20200513,0,AQI,北京,81”
        if ( int(word[0][:4]) == int(year) ):
            if(word[2] == 'AQI' and (int(word[4]) <= 50)):  #AQI小于50空气质量优
                date = word[0][4:]+word[1]  #去除年份，构造输出的日期和时刻
                year = int(word[0][:4])         #取出年份数据
                #构造输出数据，例如“北京, 2020, 05130”
                output = "{1}{0}{2}{0}{3}".format(separator, word[3], year, date)
                print(output)
if __name__ == "__main__":
    main()
