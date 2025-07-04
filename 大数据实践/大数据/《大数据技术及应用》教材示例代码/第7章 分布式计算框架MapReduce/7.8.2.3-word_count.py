#!/usr/bin/python3
# -*- coding: UTF-8 -*-
from mrjob.job import MRJob
from mrjob.protocol import JSONValueProtocol
from mrjob.step import MRStep

class KittiesJob(MRJob):
    OUTPUT_PROTOCOL = JSONValueProtocol
    def test_for_kitty(self, _, value):
        yield None, 0  				# 确保总是有数据输出
        if 'kitty' not in value:  	#当kitty不在value中出现时才输出<None, 1>
            yield None, 1

    def sum_missing_kitties(self, _, values):
        yield None, sum(values)

    def steps(self):
        return [
            MRStep(mapper_pre_filter='grep "kitty"',
                   mapper=self.test_for_kitty,
                   reducer=self.sum_missing_kitties)]

if __name__ == '__main__':
    KittiesJob.run()
