aaa = ""

# 封装get函数，供其他文件取值
def get_aaa():
    global aaa
    return aaa
# 封装set函数，供其他文件改值
def set_aaa(bbb):
    global aaa
    aaa = bbb