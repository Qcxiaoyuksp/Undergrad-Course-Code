#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys
counter=0
sum_value=0
for line in sys.stdin:
    idx, v=line.strip().split('\t',1)
    try:
        v=float(v)
    except valueError:
        continue
    counter+=1
    sum_value+=v
pi=sum_value/counter
print(pi)
