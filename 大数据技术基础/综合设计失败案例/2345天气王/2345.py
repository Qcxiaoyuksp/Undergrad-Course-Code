import requests
import pandas as pd
import re

def get_2345weather(city, year, month):
    index_ = ['最高温度','最低温度', '风向', '风力', '天气','AQI']
    data = pd.DataFrame(columns=index_)
    #请求头信息
    headers = {
        'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36 Edg/117.0.2045.60'
    }
    for y in years:
        for m in months:
            for c in city:
                url = "http://tianqi.2345.com/t/wea_history/js/"+str(y)+str(m)+'/'+str(c)+"_"+str(y)+str(m)+".js"
                
                response = requests.get(url=url,headers=headers)
                response.encoding = 'gbk'
                #print(url)
                if response.status_code == 200:
                    response2 = response.text.replace("'", '"')
                    date = re.findall("[0-9]{4}-[0-9]{2}-[0-9]{2}", response2)[:-2]
                    mintemp = re.findall('yWendu:"(.*?)℃', response2)
                    maxtemp = re.findall('bWendu:"(.*?)℃', response2)
                    winddir = re.findall('fengxiang:"([\u4E00-\u9FA5]+)', response2)
                    wind = re.findall('fengli:"(\d)[\u4E00-\u9FA5]+', response2)
                    weather = re.findall('tianqi:"([\u4E00-\u9FA5]+)~?', response2)
                    aqi=re.findall('aqi:"(\d{2})', response2)
                    data_spider = pd.DataFrame([maxtemp,mintemp, winddir, wind, weather,aqi]).T
                    data_spider.columns = index_
                    data_spider.index = date
                    data = pd.concat((data,data_spider), axis=0)
                    print('%s年%s月的数据抓取成功' % (y, m))
                else:
                    print('%s年%s月的数据抓取失败' % (y, m))
                    break
    data.to_excel('weather.xlsx')

months = ["01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"]
years = ["2023"]
city = [58362]  # 上海

get_2345weather(city, years, months)
