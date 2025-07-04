import urllib.request

url = 'https://www.baidu.com'

headers = {
   'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36 Edg/117.0.2045.60'
}

#因为urlopen方法不能存储字典，所以headers不能传递进去
#请求对象的定制
#因为参数顺序的问题 不能直接写 yrl 和 headers   中间还有一个data 所以要关键字传参
request = urllib.request.Request(url = url, headers=headers)

response = urllib.request.urlopen(request)

content = response.read().decode('utf-8')

print(content)




#get()请求方式：urllib.parse.quote()   可以将汉族转化成unicode编码
#get()请求方式：urllib.parse.urlencode()    可以将多个汉族以字典的形式转化成unicode编码