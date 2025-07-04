import requests
import pandas as pd
from bs4 import BeautifulSoup
import re

if __name__ == '__main__':
    index = ['日期', '最高温', '最低温', '天气', '风向', '风力', 'AQI']
    data = pd.DataFrame(columns=index)

    url = 'https://tianqi.2345.com/wea_history/54342.htm'

    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36 Edg/117.0.2045.60'
    }

    #.text对应的是字符串数据
    response = requests.get(url=url, headers=headers)
    response.encoding = 'utf-8'
    page_text = response.text

    page_text2 = page_text.replace("'", '"')

    # 使用 BeautifulSoup 解析页面内容
    soup = BeautifulSoup(page_text, 'html.parser')

    # 找到包含天气数据的<table>标签
    weather_table = soup.find('table', {'class': 'history-table'})

    # 如果找到了表格
    if weather_table:
        # 创建一个空的数据列表
        weather_data = []

        # 遍历表格中的每一行（<tr>标签）
        for row in weather_table.find_all('tr'):
            # 创建一个空的行数据列表
            row_data = []

            # 遍历每一列（<td>标签）
            for cell in row.find_all('td'):
                # 获取列的文本内容
                cell_text = cell.get_text(strip=True)
                row_data.append(cell_text)

            # 将行数据添加到数据列表中
            weather_data.append(row_data)

        # 打印或处理天气数据
        for row in weather_data:
            print(row)
    else:
        print("未找到表格")

    #print(page_text2)
    #print(response.status_code)