import jieba # 结巴分词
import wordcloud # 词云图
import imageio # 读取本地图片，修改词云图形

img = imageio.imread('热气球.jpg')

# 1.读取弹幕数据
fp = open('弹幕.txt', encoding='utf-8')
text = fp.read()

# 2.分词，把一句话分割成很多分词
text_list = jieba.lcut(text)

# 列表转成字符串
text_str = ' '.join(text_list)
print(text_str)

# 3.词云图配置
wc = wordcloud.WordCloud(
    width=500,
    height=500,
    background_color='white',
    mask=img,
    stopwords={'我','你','了','的','啊','这','是','都','也','就','有'},
    font_path='msyh.ttc'
)

wc.generate(text_str)
wc.to_file('词云.jpg')
