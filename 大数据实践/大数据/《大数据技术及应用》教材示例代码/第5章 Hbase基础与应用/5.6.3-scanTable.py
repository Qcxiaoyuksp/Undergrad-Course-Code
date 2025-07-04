import java.lang
from org.apache.hadoop.HBase import TableName, HBaseConfiguration
from org.apache.hadoop.HBase.client import Connection, ConnectionFactory, Result
from org.apache.hadoop.HBase.client import ResultScanner, Table, Admin
from org.apache.hadoop.conf import Configuration

conf = HBaseConfiguration.create()
connection = ConnectionFactory.createConnection(conf)
admin = connection.getAdmin()

tableName = TableName.valueOf('wiki')
table = connection.getTable(tableName)

cf = "title"   #列族名称
attr = "attr"  #列限定符
scanner = table.getScanner(cf)  #利用table的getScanner获取数据
while 1:
    result = scanner.next()     #利用scanner的next进行数据的逐条访问
    if not result:              #访问结束后跳出循环
       break
    #打印数据，包括行键值和具体”列族:列限定符”指定的数据值
    print java.lang.String(result.row), java.lang.String(result.getValue(cf, attr))
