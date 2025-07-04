import urllib.request

#下载网页
# url_page = "http://www.baidu.com"
#
# # url 代表下载的路径  filename 代表生成文件的名字
# urllib.request.urlretrieve(url = url_page, filename='baidu.html')

#下载图片
# url_img = 'https://th.bing.com/th/id/OIP.Zte3ljd4g6kqrWWyg-8fhAHaEo?w=262&h=180&c=7&r=0&o=5&dpr=1.3&pid=1.7'
#
# urllib.request.urlretrieve(url_img,'img.jpg')

#下载视频
url_video = 'https://haokan.baidu.com/7603a033-ce7e-43e7-8c31-e662ce34a90b' #没成功

urllib.request.urlretrieve(url_video,'video.mp4')