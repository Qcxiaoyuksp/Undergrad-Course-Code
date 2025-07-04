#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys
from random import random
times=100
hits=0
for i in range(times):
    x=random()
    y=random()
    if x*x+y*y<=1:
        hits+=1
print("1\t%f"%(4.0*hits/times))	
