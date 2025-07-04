#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys
def main(seperator='\t'):
    pre_line=None
    for line in sys.stdin:
        if line==pre_line:
            pass
        else:
            print(line)
            pre_line=line
if __name__ == "__main__":
    main()
