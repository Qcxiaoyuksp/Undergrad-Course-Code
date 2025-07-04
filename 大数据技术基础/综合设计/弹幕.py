import requests #数据请求模块
import re #正则表达式模块

# 1.发送请求
url_old = 'https://api.bilibili.com/x/v1/dm/list.so?oid=%d'
oid = int(input('请输入弹幕地址的oid号：'))
url = format(url_old%oid)

# headers 请求头 作用是把python代码进行伪装，模拟成浏览器去发送请求
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36 Edg/117.0.2045.60'
}

# 通过requests模块里面get请求方法，对于url地址发送请求，并用response变量去接收返回数据
response = requests.get(url=url, headers=headers)
response.encoding = response.apparent_encoding

# 2.获取数据response.text 返回数据是html字符串数据
page_text = response.text

# 3.解析数据 re正则解析式：可以直接对于字符串数据进行提取
data_list = re.findall('<d p=".*?">(.*?)</d>', page_text)  # ()是精确匹配，表示想要的数据  不加括号是泛匹配：.*?

# 4.保存数据为txt文档
with open('弹幕.txt', mode='w', encoding='utf-8') as fp:
    for index in data_list:
        fp.write(index)
        fp.write('\n')
        print(index)
