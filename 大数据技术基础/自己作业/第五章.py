import urllib.request
from bs4 import BeautifulSoup
import re
import xlwt

# 匹配规则
# 电影详情
patlink = re.compile(r'a href="(.*?)">')
# 电影图片
patimg = re.compile(r'<img.*src="(.*?)"', re.S)  # re.S：让换行符也包含在字符串中
# 电影名称
pattitle = re.compile(r'<span class="title">(.*?)</span>')
# 电影评分
patscore = re.compile(r'<span class="rating_num" property="v:average">(.*?)</span>')
# 影评人数
patpeople = re.compile(r'<span>(\d*)人评价</span>')
# 电影概况
patdesc = re.compile(r'<span class="inq">(.*?)</span>')
# 电影背景
patbd = re.compile(r'<p class="">(.*?)</p>', re.S)

def getData(baseurl):
    """爬取网页"""
    datalist = []
    for i in range(0, 10):  # 遍历页数
        url = baseurl + str(i * 25)  # 拼接URL，指定开始位置
        html = askUrl(url)
        # 解析网页数据
        soup = BeautifulSoup(html, "html.parser")
        for item in soup.find_all("div", class_="item"):  # 遍历指定查找结果列表
            data = []  # 保存电影信息
            item = str(item)  # 将item转成字符串
            link = re.findall(patlink, item)[0]  # 查找电影详情链接
            data.append(link)
            imgstr = re.findall(patimg, item)[0]  # 电影图片
            data.append(imgstr)
            titles = re.findall(pattitle, item)  # 电影名称，有多个名字
            if len(titles) == 2:
                data.append(titles[0])  # 中文名
                data.append(titles[1].replace("/", ""))  # 外文名, 去掉多余/
            else:
                data.append(titles[0])
                data.append("")  # 外文名留空
            score = re.findall(patscore, item)[0]  # 评分
            data.append(score)
            num = re.findall(patpeople, item)[0]  # 评价人数
            data.append(num)
            desc = re.findall(patdesc, item)  # 一句话描述
            if len(desc) != 0:
                data.append(desc[0])
            else:
                data.append("")
            bd = re.findall(patbd, item)[0]  # 背景信息
            bd = re.sub("<br(\s+)?/>(\s+)?", "", bd.strip())  # 去除<br/>标签, strip()去空格
            data.append(bd)
            datalist.append(data)
    return datalist

def askUrl(baseurl):
    """获取指定URL网页数据"""
    # 设置headers来模拟正常用户请求
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36 Edg/117.0.2045.60'
    }
    #header = {'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:23.0) Gecko/20100101 Firefox/23.0'}
    req = urllib.request.Request(baseurl, headers=headers)
    response = urllib.request.urlopen(req)
    html = response.read().decode("utf-8")
    return html

def saveData(datalist, filepath):
    """保存数据到Excel文件中"""
    workbook = xlwt.Workbook(encoding="utf-8")  # 创建Workbook对象
    sheet = workbook.add_sheet("豆瓣电影TOP250", cell_overwrite_ok=True)  # 创建工作页
    col = ("详情链接", "图片链接", "影片中文名", "影片外文名", "影片评分", "评分人数", "影片概述", "相关信息")  # 标题
    for i in range(0, len(col)):
        sheet.write(0, i, col[i])  # 写入标题 参数：“行”， “列”， “内容”
    for i in range(0, 250):
        move = datalist[i]  # 遍历影片信息 "行"
        for j in range(0, len(col)):  # "列"
            sheet.write(i + 1, j, move[j])  # 注意：从第二行开始写入影片信息
    workbook.save(filepath)  # 保存到文件

baseurl = "https://movie.douban.com/top250?start=";
    # 1.爬取网页
datalist = getData(baseurl)
    # 2.保存数据到Excel中
filepath = "豆瓣电影TOP250.csv"
saveData(datalist, filepath)
print("爬取成功！")