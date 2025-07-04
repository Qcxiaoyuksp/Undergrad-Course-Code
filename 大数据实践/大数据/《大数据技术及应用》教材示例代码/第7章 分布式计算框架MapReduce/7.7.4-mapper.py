#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys
def main():
    for line in sys.stdin:
        words=line.strip().split(',')
        if len(words)==6:  #sites，站点情况
            if words[2]!=b'\xe7\xa6\x8f\xe5\xb7\x9e':
                continue
            print("%sA\t%s\t%s\t%s\t%s\t%s"%(words[0], \
words[0],words[1],words[2],words[3],words[4]))
        else:  #data，监测数据
            print("%sB\t%s\t%s\t%s\t%s\t%s"%(words[3], \
words[0],words[1],words[2],words[3],words[4]))
if __name__ == "__main__":
    main()
