import java.lang
from org.apache.hadoop.HBase import HBaseConfiguration, HTableDescriptor
from org.apache.hadoop.HBase import HColumnDescriptor, TableName
from org.apache.hadoop.HBase.client import Admin, Connection, ConnectionFactory
from org.apache.hadoop.HBase.client import Get, Put, Result, Table
from org.apache.hadoop.conf import Configuration

# 首先获取conf下your HBase-的配置文件，并且利用配置文件中的HBase的配置信息# 进行连接的设置，建立与HBase master节点的连接。
conf = HBaseConfiguration.create()
connection = ConnectionFactory.createConnection(conf)
admin = connection.getAdmin()

# 创建数据表“test”对象
tableName = TableName.valueOf("test")
table = connection.getTable(tableName)
# 把列族content添加到数据表对象“test”中
desc = HTableDescriptor(tableName)
desc.addFamily(HColumnDescriptor("content"))

# 判断数据表是否存在，若存在，则先删除该数据表
if admin.tableExists(tableName):
    admin.disableTable(tableName)
    admin.deleteTable(tableName)

# 调用createTable创建数据表，即把test对象提交HBase数据库
admin.createTable(desc)

# 构造所要添加的数据单元，并利用table的put操作实现数据添加操作
row = 'row_x'     #设置行键值
put = Put(row)    #利用行键构造put对象
put.addColumn("content", "qual", "some content")  #指定列族、列限定符和单元值
table.put(put)     #提交数据

# 利用行键值构造Get对象
get = Get(row)

result = table.get(get)   #利用table的get操作获取行键对应数据，数据格式为Bytes
data = java.lang.String(result.getValue("content", "qual"), "UTF8")  #获取其中值

#最后打印结果
print "The fetched row contains the value '%s'" % data
