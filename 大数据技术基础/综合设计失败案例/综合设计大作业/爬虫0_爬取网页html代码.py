import urllib.request

#定义一个url 也就是要访问的网址
url = 'http://www.baidu.com'

#模拟浏览器向服务器发送请求
response = urllib.request.urlopen(url)

#获取响应中页面的源码
#read()方法返回的是字节形式的二进制数据
#将二进制数据转化成字符串：解码，decode('编码的格式')
content = response.read().decode('utf-8')

#打印数据
print(content)



# 一个类型
# HTTPResponse
# 六个方法
# read
# readline 读取一行
# readlines 读取多行
# getcode 返回状态码（200就是正确的）
# geturl 返回url地址
# getheaders 获取一个状态信息




