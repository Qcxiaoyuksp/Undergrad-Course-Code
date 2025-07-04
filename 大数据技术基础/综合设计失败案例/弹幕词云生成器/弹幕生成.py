import re
import csv
from PIL import Image
import numpy as np
import requests
import jieba
import wordcloud
import json

headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36 Edg/117.0.2045.60'
    }


# 获取视频的cid
def get_cid(bvid):
    # API地址
    API = 'https://api.bilibili.com/x/player/pagelist'

    # 参数
    params = {
        'bvid': bvid,
        'jsonp': 'jsonp',
    }

    # 发起请求
    response = requests.get(url=API, headers=headers, params=params)

    # 网页源代码
    html = response.text

    # html文档转换为字典
    dict = json.loads(html)

    result = dict["data"][0]["cid"]

    return result
a=input("输入BV号")
import globals
b=get_cid(globals.get_aaa())
c="https://api.bilibili.com/x/v1/dm/list.so?oid="+str(b)
r = requests.get(c, headers=headers)
html_text = r.content.decode('utf-8')
DM = re.compile("<d.*?>(.*?)</d>").findall(html_text)



print(DM)
remove = open('弹幕.csv', "r+")  # 或者'**.csv'
remove.truncate()
num = 1
for i in DM:
    if num >= 500:
        break
    num = num + 1
    with open(r'弹幕.csv',"a", newline='',encoding='utf-8-sig') as f:
        DM = []
        DM.append(i)
        writer= csv.writer(f)
        writer.writerow(DM)

# 设置中文停用词 从文件中读取屏蔽词
stopwords = set()
content = ['的','了','是','我','你','他','她','它','也','在','不','就','有','这','个','人','都','我们','和','就是','让','当','比','用','而','为','着','一部','一个','来','这个','那么','能','对','所','啦','哒','后','一场','因为','可能','还','吧','啊','没']
    #[line.strip(',') for line in open(r'static/txt/stopwords.txt', 'r', encoding="utf-8").readlines()]
stopwords.update(content)

f = open('弹幕.csv',encoding='utf-8')
txt = f.read()
txtlist = jieba.lcut(txt)
string = " ".join(txtlist)
print(string)

img = Image.open(r'./static/assets/img/tree.jpg')  # 打开遮罩图片，图片背景为白色
img_arr = np.array(img)  # 将图片转为数组格式
# mk = imageio.imread("YUQI.png")   //加形状
w = wordcloud.WordCloud(
                        mask=img_arr,
                        width=800,
                        height=600,
                        background_color='white',
                        font_path='msyh.ttc',
                        # mask=mk,
                        scale=15,
                        stopwords=stopwords,
                        contour_width=5,
                        #contour_color='red'
    )
w.generate(string)
w.to_file(r'./static/assets/img/word2.jpg')
class bilibili:
    imgsrc2 = "./static/assets/img/word2.jpg"












