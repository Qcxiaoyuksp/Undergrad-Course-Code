#!/usr/bin/python3
# -*- coding: UTF-8 -*-
from mrjob.job import MRJob
from mrjob.protocol import JSONValueProtocol
class KittyJob(MRJob):
    OUTPUT_PROTOCOL = JSONValueProtocol
    #用shell命令”grep kitty”处理输入数据，输出含有kitty的数据行。
    def mapper_cmd(self): 
        return "grep kitty"
    def reducer(self, key, values):
        yield None, sum(1 for _ in values)
if __name__ == '__main__':
    KittyJob.run()
