#e10.4CalThreeKingdoms.py
import jieba
import matplotlib.pyplot as plt
from wordcloud import WordCloud,ImageColorGenerator
from PIL import Image
import numpy as np



excludes = {"将军","却说","荆州","二人","不可","不能","如此"}
txt = open("三国演义.txt", "r", encoding='utf-8').read()
words  = jieba.lcut(txt)
counts = {}
for word in words:
    if len(word) == 1:
        continue
    elif word == "诸葛亮" or word == "孔明曰":
        rword = "孔明"
    elif word == "关公" or word == "云长":
        rword = "关羽"
    elif word == "玄德" or word == "玄德曰":
        rword = "刘备"
    elif word == "孟德" or word == "丞相":
        rword = "曹操"
    else:
        rword = word
    counts[rword] = counts.get(rword,0) + 1
for word in excludes:
    del(counts[word])
items = list(counts.items())
items.sort(key=lambda x:x[1], reverse=True) 
for i in range(5):
    word, count = items[i]
    print ("{0:<10}{1:>5}".format(word, count))

# 根据字典生成词云图
#font_path = 'simkai.ttf'   #simhei.ttf SIMYOU.TTF STHUPO.TTF simli.ttf simkai.ttf simsun.ttc
font_path = 'STHUPO.TTF'
image= Image.open('./tim.jpg')
graph = np.array(image)
image_color = ImageColorGenerator(graph)

word_cloud = WordCloud(font_path=font_path,  # 设置字体
                   background_color="white",  # 背景颜色
                   max_words=200,  # 词云显示的最大词数
                   max_font_size=60,  # 字体最大值
                   random_state=42,
                   mask=graph,
                   width=300, height=200, margin=2,# 设置图片默认的大小,但是如果使用背景图片的话,那么保存的图片大小将会按照其大小保存,margin为词语边缘距离
        )
word_cloud.generate_from_frequencies(counts)
plt.figure()
plt.imshow(word_cloud)
plt.imshow(word_cloud.recolor(color_func=image_color))
plt.axis("off")
word_cloud.to_file('三国.png')
plt.show()
