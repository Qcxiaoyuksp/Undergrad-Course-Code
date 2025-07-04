#!/usr/bin/python3
# -*- coding: UTF-8 -*-
from mrjob.job import MRJob
from mrjob.step import MRStep
import re
WORD_RE=re.compile(r'\w+\b')
class MRWordFreqCount(MRJob):
    def init_get_words(self):
        self.words = {}  #初始化一个words字典，用于存储words出现的次数
    def get_words(self, _, line):
        for word in WORD_RE.findall(line):
            word = word.lower()
            self.words.setdefault(word, 0)
            self.words[word] = self.words[word] + 1   #统计word出现次数
    def final_get_words(self):
        for word, val in self.words.iteritems():  #在final中输出<key, value>
            yield word, val
    def sum_words(self, word, counts):        #作为reducer统计<key, values>中values之和
        yield word, sum(counts)
def steps(self):
    #设置每个处理步骤对应的方法
        return [MRStep(mapper_init=self.init_get_words,  
                       mapper=self.get_words,
                       mapper_final=self.final_get_words,
                       combiner=self.sum_words,
                       reducer=self.sum_words)]
if __name__ == '__main__':
    MRWordFreqCount.run()
