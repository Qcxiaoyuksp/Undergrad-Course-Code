#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys
import heapq   #利用堆，总是保留K个最优
K=1000
def getTopK(inputs):
    topk=[]
    counter=0
    for line in inputs:
        cdate, chour, aqtype, city, value=line.strip().split(',')
        if (aqtype=='AQI' and chour=='12'):
            key=-1* int(value)   #用小根堆，所以把key转为负数
            if counter<=K:
                heapq.heappush(topk, [key, cdate, chour, aqtype, city, value])
            else:
                heapq.heappush(topk, [key, cdate, chour, aqtype, city, value])
                heapq.heappop(topk) 
            counter+=1
    return topk

def main(separator='\t'):
    data = getTopK(sys.stdin)
    for words in data:
        print('%s%s%s'%(words[4],separator, words[5])) 
if __name__ =='__main__':
    main()
