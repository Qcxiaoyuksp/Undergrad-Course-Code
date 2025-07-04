#!/usr/bin/python3.6
# -*- coding: UTF-8 -*-

import sys
import numpy as np

def Combiner(d, separator='\t'):        #d为样本属性数
    values = {}
    num = {}
    keys = []
    for line in sys.stdin:
        line = line.strip()
        key, value = line.split(separator, 1)           # 获取mapper簇中心索引与对象
        value = np.array(eval(value)).astype(np.float)  # 将样本字符串->数组->向量化       
        keys.append(key)
        p = np.zeros(d)            
        values[key] = values.get(key, p.astype(np.float)) + value  # 取字典中key应的值(不存在key，则取p值)，再相加      
        num[key] = num.get(key, 0) + 1
        
    for key in set(keys):
        print("%s%s%s%s%s" % (key, separator, str(tuple(values[key])), separator, num[key]))  #将向量->元组->字符串

    
if __name__ == '__main__':
    Combiner(d=4)
