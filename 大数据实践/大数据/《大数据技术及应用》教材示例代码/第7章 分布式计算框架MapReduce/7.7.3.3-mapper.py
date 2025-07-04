#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys
def main(seperator='\t'):
    for line in sys.stdin:
        if line:
            print(line)  #mapper中直接把输入数据输出
if __name__ == "__main__":
    main()
