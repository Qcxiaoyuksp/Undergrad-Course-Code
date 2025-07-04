#!/usr/bin/python3
# -*- coding: UTF-8 -*-
from mrjob.job import MRJob
from mrjob.step import MRStep
import re
WORD_RE = re.compile(r"[\w']+")
class MRMostUsedWord(MRJob):
    def steps(self):                  			#定义mapReduce程序处理流程
        return [
            MRStep(mapper=self.mapper_get_words,
                   combiner=self.combiner_count_words,
                   reducer=self.reducer_count_words),
            MRStep(reducer=self.reducer_find_max_word)
        ]
    def mapper_get_words(self, _, line):
        for word in WORD_RE.findall(line):
            yield (word.lower(), 1)  			#为每个单词生成<word,1>输出
    def combiner_count_words(self, word, counts):
        yield (word, sum(counts))    		#在节点进行统计优化程序，减少通信
    def reducer_count_words(self, word, counts):
        yield None, (sum(counts), word) 		#输出<count,word>输出
    def reducer_find_max_word(self, _, word_count_pairs):
        yield max(word_count_pairs)   		#输出最大出现次数的word
if __name__ == '__main__':
    MRMostUsedWord.run()
