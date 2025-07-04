#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys
import heapq
K=1000
def getTopK(inputs, separator):
    topk=[]
    counter=0
    for line in inputs:
        city, value=line.strip().split(separator)
        key=-1* int(value)
        if counter<=K:
            heapq.heappush(topk, [key, city, value])
        else:
            heapq.heappush(topk, [key, city, value])
            heapq.heappop(topk)
        counter+=1
    return topk

def main(separator='\t'):
    data = getTopK(sys.stdin, separator)
    for words in data:
        print('%s%s%s'%(words[1],separator, words[2])) 
if __name__ =='__main__':
main()
