#（1）请求对象的定制
#（2）获取响应的数据
#（3）下载数据

import urllib.parse
import urllib.request

def create_request(page):
    base_url = 'https://movie.douban.com/j/chart/top_list?type=17&interval_id=100%3A90&action=&'

    data = {
        'start' : (page - 1) * 20,
        'limit' : 20
    }

    data = urllib.parse.urlencode(data)

    url = base_url + data

    headers = {
        'User - Agent':'Mozilla / 5.0(Windows NT 10.0;Win64;x64) AppleWebKit / 537.36(KHTML, likeGecko) Chrome / 117.0.0.0Safari / 537.36Edg / 117.0.2045.60',
        'Cookie':'gr_user_id=07544fea-e8a4-41b5-a880-e8797b06d1fc; douban-fav-remind=1; viewed="35680544"; bid=wb3tCfcsRUs; ll="108088"; ap_v=0,6.0Host:movie.douban.com'
    }

    request = urllib.request.Request(url = url,headers = headers)

    return request


def get_content(request):
    response = urllib.request.urlopen(request)
    content = response.read().decode('utf-8')
    return content


def down_load(page, content):
    with open('douban' + str(page) + '.json', 'w', encoding='utf-8') as fp:
        fp.write(content)

#程序的入口
if __name__ == '__main__':
    start_page = int(input('请输入起始的页面'))
    end_page = int(input('请输入结束的页面'))

    for page in range(start_page, end_page + 1):
# 请求对象的制定
        request = create_request(page)
# 获取响应的数据
        content = get_content(request)
# 下载数据
        #down_load(page, content)


