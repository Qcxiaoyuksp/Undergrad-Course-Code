#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import sys
def read_input(inputs):
    new_list=[]
    for words in inputs:
        words=words.strip().split(',')
        #if (words[1]=='6')&(words[2]=='AQI')&(words[3]==b'\xe5\x8c\x97\xe4\xba\xac'):
        if (words[1] == '6') & (words[2] == 'AQI') & (words[3] == '北京') & (float(words[4])<=50):
            new_list.append(words)
    return new_list
def main(separator='\t'):
    data = read_input(sys.stdin)
    for words in data:
        print('%s\t%s\t%s\t%s\t%s'%(words[0],words[1],words[2],words[3],words[4]))
if __name__ =='__main__':
    main()
