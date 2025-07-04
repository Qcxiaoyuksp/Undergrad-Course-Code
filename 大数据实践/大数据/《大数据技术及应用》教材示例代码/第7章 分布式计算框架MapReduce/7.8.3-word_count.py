#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import json
from mrjob.job import MRJob
from mrjob.protocol import JSONValueProtocol
class JSONValueProtocol(object):
    def read(self, line):
        k_str, v_str = line.split('\t', 1)
        return json.loads(k_str), json.loads(v_str)
    def write(self, key, value):
        return 'the number of %s is  %s' % (json.dumps(key), json.dumps(value))
class MRWordCount(MRJob):
    OUTPUT_PROTOCOL = JSONValueProtocol
    def mapper(self, _, line):
        for word in line.split():
            yield(word, 1)

    def reducer(self, word, counts):
        yield(word, sum(counts))

if __name__ == '__main__':
    MRWordCount.run()
