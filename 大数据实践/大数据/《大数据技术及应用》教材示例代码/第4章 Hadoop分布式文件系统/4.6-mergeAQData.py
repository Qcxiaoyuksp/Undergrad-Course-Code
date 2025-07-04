#!/usr/bin/python3.6
import pyhdfs
import os
client = pyhdfs.HdfsClient(hosts="localhost:9870", user_name="hadoop")
def read(dir):
    root=r'/home/hadoop/bigdata/pyhdfsTest/data/CityAQ'
    dir=os.path.join(root,dir)
    for files in os.listdir(dir):
        files=os.path.join(dir,files)
        with open(files,'r',encoding='utf-8') as data:
            for line in data.readlines():
                client.append('/user/Hadoop/CityAQ/city-data.csv',\
line.encode("utf-8").decode("latin-1"))
def main():
    dir='20200101'   #指定的日期
    read(dir)

if __name__ == "__main__":
    main()
