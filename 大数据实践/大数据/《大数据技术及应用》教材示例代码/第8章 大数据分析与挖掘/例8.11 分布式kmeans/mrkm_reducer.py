#!/usr/bin/python3.6
# -*- coding: UTF-8 -*-

import sys
import numpy as np

def Reducer(d=4,separator='\t'):
    Num = {}
    keys = []
    values = {}
    for line in sys.stdin:
        line = line.strip()
        #print("line:",line)
        key, value, num = line.split(separator, 2)      #分为2+3个字符串
        value = np.array(eval(value))                   #样本字符串->向量化
        num = int(num)                                  #计数->整数化
        keys.append(key)
        values[key] = values.get(key, 0) + value
        Num[key] = Num.get(key, 0) + num
    for key in keys:
        center = values[key] / Num[key]
        print('%s%s(' % (key, separator), end='')
        for i in range(d):
            print('%.2f' % (center[i]), end='')
        print(')')

if __name__ == '__main__':
    Reducer(4)
