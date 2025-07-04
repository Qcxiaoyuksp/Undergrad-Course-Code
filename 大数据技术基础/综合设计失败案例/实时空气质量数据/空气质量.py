import csv
import os
import requests
from bs4 import BeautifulSoup


def get_city_aqi(city_pinyin):
    url = "http://www.pm25.in/" + city_pinyin
    r = requests.get(url, timeout=30)
    soup = BeautifulSoup(r.text, "html.parser")
    div_list = soup.find_all("div", {"class": "span1"})
    city_aqi = []
    livetime = soup.find_all("div", {"class": "live_data_time"})
    city_aqi.append(livetime[0].text.strip()[7:])
    for i in range(8):
        div_content = div_list[i]
        value = div_content.find("div", {"class": "value"}).text.strip()
        caption = div_content.find("div", {"class": "caption"}).text.strip()
        city_aqi.append(value)
    # print(city_aqi)
    return city_aqi


def get_all_cities():
    url = "http://www.pm25.in/"
    r = requests.get(url, timeout=30)
    soup = BeautifulSoup(r.text, "html.parser")
    city_list = []
    city_div_list = soup.find_all("div", {"class": "bottom"})

    if len(city_div_list) > 1:
        city_div = city_div_list[1]
        city_link_list = city_div.find_all("a")
        for city_link in city_link_list:
            city_name = city_link.text
            city_pinyin = city_link["href"][1:]
            city_list.append((city_name, city_pinyin))
    return city_list


def main():
    city_list = get_all_cities()
    header = ["city", "time", "AQI", "PM2.5/1h", "PM10/1h", "CO/1h", "NO2/1h", "O3/1h", "O3/8h", "SO2/1h"]
    with open("city_air_quality_aqi.csv", "w", encoding="utf-8", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(header)
        for i, city in enumerate(city_list):
            if (i + 1) % 10 == 0:
                print("Saving {} Data (Total {} Data)".format(i + 1, len(city_list)))
            city_name = city[0]
            city_pinyin = city[1]
            city_aqi = get_city_aqi(city_pinyin)
            row = [city_name] + city_aqi
            writer.writerow(row)


if __name__ == "__main__":
    main()