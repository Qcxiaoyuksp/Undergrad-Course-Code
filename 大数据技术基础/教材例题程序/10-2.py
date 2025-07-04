#实例：中国大学排名定向爬虫
import requests
from bs4 import BeautifulSoup
#从beautifulsoup4库中引入BeautifulSoup类，注意大小写
import bs4
#注意这里需要再引入bs4库，因为后面有bs4.element.Tag语句，不引入会报错
 
def getHTMLText(url):
#定义获取网页源代码文本内容的函数
    try:
        r=requests.get(url,timeout=30)
        r.raise_for_status()
        r.encoding=r.apparent_encoding
        return r.text
    except:
        print('获取网页信息失败')
 
def fillUnivList(ulist,html):
#定义获取大学排名信息的函数
    soup=BeautifulSoup(html,'html.parser')
    #使用html.parser解析器解析返回的html源代码文本
    for tr in soup.find('tbody').children:
    #使用for循环查找tbody标签，并遍历其子孙节点
        if isinstance(tr,bs4.element.Tag):
        #检测是否为tag标签不是则过滤
            tds=tr('td')
            #查找tr标签下所有的td标签，并将其内容保存为tds
            a=tr('a','name-cn')
            #由于新版的排名中，td下的大学名称信息还包括中英文校名、LOGO等，这些又分别封装在a标签中，所以这里需要具体到查找属性为'name-cn'的a标签并存储其字符串，即大学的中文名称
            ulist.append([tds[0].string.strip(),a[0].string.strip(),tds[2].text.strip(),tds[4].string.strip()])
            #依次将大学排名、大学名称、省市（这个用string会报错）、总分信息保存到列表中，使用.strip()删除结尾的字符
 
def printUnivList(ulist,num):
#定义打印大学排名信息的函数，这里的num值打印大学的数量
    printmode='{0:^10}\t{1:{4}^10}\t{2:{4}^10}\t{3:^10}'
    #引入一个输出模板的变量这里的{4}指代中文空格chr(12288)，用以填充大学名称其余空格，使得输出的字符能够对齐,并且这里选择把字符长度都设置为10，否则表头和打印内容总是对不齐
    print(printmode.format('排名','大学名称','省市','总分',chr(12288)))
    #打印表头的信息并设置打印格式
    for i in range(num):
        u=ulist[i]
        #使用for循环依次打印ulist列表中存储的大学排名信息，用变量u代表每所大学的信息
        print(printmode.format(u[0],u[1],u[2],u[3],chr(12288)))
        #设置打印格式依次打印每所大学的排名、大学名称、省市、总分信息
 
def main():
    uinfo=[]
    #定义一个空列表用于填充装取大学排名信息
    url='https://www.shanghairanking.cn/rankings/bcur/2023'
    #给出大学排名网页
    html=getHTMLText(url)
    #调用函数获取网页源代码文本
    fillUnivList(uinfo,html)
    #调用函数获取大学排名信息并填充到列表中
    printUnivList(uinfo,30)
    #调用打印大学排名信息的函数，并打印排名前30的大学信息
 
main()