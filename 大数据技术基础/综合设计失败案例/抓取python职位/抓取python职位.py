import re  # 正则表达式，进行文字匹配
from urllib.request import Request
from urllib.request import urlopen  # 制定URL，获取网页数据
from urllib.error import URLError as error
import json
import xlwt
import sqlite3


def main():
    baseurl = "https://search.51job.com/list/000000,000000,0000,00,9,99,python,2,{}.html?lang=c&postchannel=0000&workyear=99&cotype=99&degreefrom=99&jobterm=99&companysize=99&ord_field=0&dibiaoid=0&line=&welfare="
    # 1.爬取网页
    datalist = getData(baseurl)
    savepath = "E:\\大数据技术基础\\抓取python职位\\51job.xls"
    # 保存数据到表格
    saveData(datalist, savepath)


#获取网页内容
def askURL(url):
    try:
        response = urlopen(url)
        html = response.read()
        return html
    except Exception as e:
        print("Error while making request:", e)
        return None

# 爬取网页
def getData(baseurl):
    datalist = []
    for page in range(0, 30):
        url1 = baseurl.format(page + 1)
        html = askURL(url1)  # 保存获取到的网页源码
        # 2.逐一解析数据
        html_data = re.findall('window.__SEARCH_RESULT__ =(.*?)</script>', html, re.S)
        html_data = ''.join(html_data)
        infodict = json.loads(html_data)  # 将str类型的数据转换为dict类型
        engine_jds = infodict['engine_jds']
        for item in engine_jds:
            data = []
            job_href = item["job_href"]  # 工作链接
            name = item['job_name']

            temp1 = re.sub('\t', '', name)
            # 去掉括号中的内容，英文的括号要加反斜杠
            temp2 = re.sub('\(.*?\)', '', temp1)
            # 去掉括号中的内容，中文括号
            job_name = re.sub('（.*?）', '', temp2)

            job_company = item['company_name']
            job_salary1 = item['providesalary_text']
            if job_salary1:
                job_salary = get_avgsalary(job_salary1)
            else:
                job_salary = ""
            area = item["workarea_text"]  # 工作地点
            newarea = re.findall('(.*?)-', area, re.S)
            job_area = ''.join(newarea)
            demand = item['attribute_text'][1:]
            job_requirements = ' '.join(demand)
            if job_requirements.find(' ') != -1:
                job_experience, job_education = job_requirements.split(' ')
            else:
                job_experience = job_requirements
            job_fuli = item['jobwelf'] if item['jobwelf'] else '无'
            if job_salary == "" or job_area == "" or job_education == "":
                continue
            else:
                data.append(job_href)
                data.append(job_name)
                data.append(job_company)
                data.append(job_salary)
                data.append(job_area)
                # data.append(job_requirements)
                data.append(job_experience)
                data.append(job_education)
                data.append(job_fuli)
                datalist.append(data)
        # print(datalist)
    return datalist


# 对薪资进行数据清洗
def get_avgsalary(salary):
    global avg_salary
    if '-' in salary:  # 针对10-20千/月或者10-20万/年的情况，包含-
        low_salary = re.findall(re.compile('(\d*\.?\d+)'), salary)[0]
        high_salary = re.findall(re.compile('(\d?\.?\d+)'), salary)[1]
        avg_salary = (float(low_salary) + float(high_salary)) / 2
        avg_salary = ('%.2f' % avg_salary)
        if u'万' in salary and u'年' in salary:  # 单位统一成万/月的形式
            avg_salary = float(avg_salary) / 12
            avg_salary = ('%.2f' % avg_salary)  # 保留两位小数
        elif u'千' in salary and u'月' in salary:
            avg_salary = float(avg_salary) / 10
    else:  # 针对20万以上/年和100元/天这种情况，不包含-，取最低工资，没有最高工资
        avg_salary = re.findall(re.compile('(\d*\.?\d+)'), salary)[0]
        if u'万' in salary and u'年' in salary:  # 单位统一成万/月的形式
            avg_salary = float(avg_salary) / 12
            avg_salary = ('%.2f' % avg_salary)
        elif u'千' in salary and u'月' in salary:
            avg_salary = float(avg_salary) / 10
        elif u'元' in salary and u'天' in salary:
            avg_salary = float(avg_salary) / 10000 * 21  # 每月工作日21天

    avg_salary = str(avg_salary) + '万/月'  # 统一薪资格式
    return avg_salary


def saveData(datalist, savepath):
    print("sava....")
    book = xlwt.Workbook(encoding="utf-8", style_compression=0)  # 创建work对象
    sheet = book.add_sheet('python', cell_overwrite_ok=True)  # 创建工作表
    col = ("工作链接", "工作名称", "公司", "薪资", "工作地区", "工作经验", "学历", "员工福利")
    for i in range(0, 8):
        sheet.write(0, i, col[i])  # 列名
    for i in range(0, 1000):
        # print("第%d条" %(i+1))
        data = datalist[i]
        for j in range(0, 8):
            sheet.write(i + 1, j, data[j])  # 数据

    book.save(savepath)  # 保存数据


