import random
import time
import shutil
import os
os.chdir("./") #切换工作路径为当前目录

#随机生成 IP地址
ip_slices = [132, 156, 124, 10, 29, 167, 143, 187, 30, 100]
def sample_ip():
    slice = random.sample(ip_slices, 4)
    return ".".join([str(item) for item in slice])

#随机生成 UserID
user_id = [
    "zhang",
    "li",
    "wang",
    "liu",
    "yan",
    "chen",
    "hu"
]
def sample_userid():
    return random.sample(user_id , 1)[0]

#随机生成 访问资源路径
url_paths = [
    "www/2",
    "www/1",
    "www/6",
    "www/4",
    "www/3",
    "pianhua/130",
    "toukouxu/821"
]

def sample_url():
    return random.sample(url_paths, 1)[0]

#随机生成 状态码
status_code = [404, 302, 200]
def sample_status():
    return random.sample(status_code, 1)[0]

#随机生成 来源地址
http_referers = [
    "https://www.baidu.com/s?wd={query}",
    "https://www.sogou.com/web?qu={query}",
    "http://cn.bing.com/search?q={query}",
    "https://www.so.com/s?q={query}"
]
search_keyword = [
    "teacher",
    "student",
    "file",
    "milk",
    "monkey"
]
def sample_referer():
    #if random.uniform(0, 1) > 0.2:
    #    return "-"
    refer_str = random.sample(http_referers, 1)
    # print refer_str[0]
    query_str = random.sample(search_keyword, 1)
    # print query_str[0]
    return refer_str[0].format(query=query_str[0])

#随机生成 浏览器信息
# 读取userAgentcopy.txt文件中的内容，生成一个userAgentlist列表

userAgentlist = []
with open("userAgentcopy.txt",'r',encoding="UTF-8") as f:
    for line in f.readlines():
        line = line.replace("\"","")
        line = line.replace("\n","")
        userAgentlist.append(line)
# 随机useragent
def useragent():
    return random.sample(userAgentlist,1)

# 产生log
def generate_log(count=100, filepath="log", filename="log.txt"):
    # 日志目录
    log_path = os.path.join(os.getcwd(), filepath)
    # 日志文件路径
    log_name = os.path.join(log_path, filename)
    # 判断日志所在目录是否存在
    if not os.path.exists(log_path):
        os.mkdir(log_path)
        print(log_path, "已创建")
    elif os.path.exists(log_path) and os.path.exists(log_name):
        # 如果日志存在，先删除
        print(log_name, "已存在")
        # os.remove(log_name)
        # shutil.rmtree(log_name)
    # 打开日志
    with open(log_name, "a+") as f:
        # 生成日志
        while count >= 1:
            # 获取当前时间
            t = time.localtime()
            # 定义日志格式
            #log_format = "{ip}\t{localtime}\t\"GET {url} HTTP/1.0\"\t{referece}\t{status1}\t{useragent}"
            log_format = "{userid}\t{ip}\t{date}\t{hour}\t{min}\t{sec}\t\"GET {url} HTTP/1.0\"\t{referece}\t{status1}\t{useragent}"
            # 生成日志信息
            query_log = log_format.format(
                userid=sample_userid(),
                ip=sample_ip(),
                url=sample_url(),
                status1=sample_status(),
                referece=sample_referer(),
                #localtime=time_str,
                date=time.strftime('%Y-%m-%d', t),
                hour=random.randint(0, 23),
                min=random.randint(0, 59),
                sec=random.randint(0, 59),
                useragent=useragent()
            )
            # 将日志写入文件
            f.write(query_log + "\n")
            count = count - 1;
            # 随机休眠
            #time.sleep(random.uniform(0, 2))
            # time.sleep(0.5)


if __name__ == '__main__':
    generate_log(count=1000, filepath="log", filename="log1.txt")