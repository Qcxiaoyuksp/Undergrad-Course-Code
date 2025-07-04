#e10.3CalThreeKingdoms.py
import jieba
import matplotlib.pyplot as plt
from wordcloud import WordCloud

excludes = {}#{"将军","却说","丞相"}
txt = open("三国演义.txt", "r", encoding='utf-8').read()
words  = jieba.lcut(txt)
counts = {}
for word in words:
    if len(word) == 1:  #排除单个字符的分词结果
        continue
    else:
        counts[word] = counts.get(word,0) + 1
for word in excludes:
    del(counts[word])
items = list(counts.items())
items.sort(key=lambda x:x[1], reverse=True) 
for i in range(15):
    word, count = items[i]
    print ("{0:<10}{1:>5}".format(word, count))

# 根据字典生成词云图
#font_path = 'simkai.ttf'   #simhei.ttf SIMYOU.TTF STHUPO.TTF simli.ttf simkai.ttf simsun.ttc
font_path = 'STHUPO.TTF'

word_cloud = WordCloud(font_path=font_path,  # 设置字体
                   background_color="white",  # 背景颜色
                   max_words=200,  # 词云显示的最大词数
                   max_font_size=100,  # 字体最大值
                   random_state=42,
                   width=600, height=400, margin=2,# 设置图片默认的大小,但是如果使用背景图片的话,那么保存的图片大小将会按照其大小保存,margin为词语边缘距离
        )
word_cloud.generate_from_frequencies(counts)
plt.figure()
plt.imshow(word_cloud)
plt.axis("off")

plt.show()
