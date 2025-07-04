#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys

def main():
    presiteid=None
    dataType=None
    curr_site=['impossibleID']
    for line in sys.stdin:
        fields = line.strip().split('\t')
        key=fields[0]
        if key[-1]=='A':  #site 
            curr_site=fields[1:]
        else:  #data
            if curr_site[0]==fields[4]:
               output="%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s"%\
(curr_site[0],curr_site[1],curr_site[2],curr_site[3],curr_site[4],\
fields[0],fields[1],fields[2],fields[3],fields[4])
               print(output)
if __name__ == "__main__":
    main()
