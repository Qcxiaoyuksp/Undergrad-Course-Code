#!/usr/bin/python3.6
# -*- coding: UTF-8 -*-

import sys
import numpy as np

def Distance(instance, center):                     #计算对象与簇中心距离
    i = np.array(eval(instance)).astype(np.float)
    c = np.array(center).astype(np.float)
    ans = np.sqrt(np.sum(np.square(i - c)))
    return ans

def Mapper(d, k, separator = '\n'):     #d:属性数,k:类别数,separator:行分隔符
    minDis = float('inf')  
    centers = []
    for i in range(k):                  #随机生成k个簇中心
        arr = np.random.randint(0,10,d)  #生成界于0到10的d维随机数组,应根据数据集调整上下界
        centers.append(arr)
    #centers = [(4,5,2,3), (2,4,1,1),(5,4,4,3)]  #人为设定K个初始簇中心  
    index = -1
    for line in sys.stdin:
        instances = line.split(separator)           #取一行数据,删除回车符
        instance = instances[0].strip()             #删除头尾空格等字符   
        for i in range(0, len(centers)):
            dis = Distance(instance, centers[i])    #遍历寻找距离最近的簇中心
            if dis < minDis:
                minDis = dis
                index = i
        print("%s\t%s" % (index, instance))               #输出<Key:value>(<簇中心编号:数据点>）       

if __name__ == "__main__":
    Mapper(d=4, k=3)
