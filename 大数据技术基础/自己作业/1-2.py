'''
l = []
for i in range(5):
    print("请输入第",i+1,"个学生的姓名：")
    s = input()
    l.append(s)
print(l)

n = input("请输入一位同学的姓名:")
if n in l:
    print("Yes")
else:
    print("No")
'''

s = input("请输入若干姓名（使用，隔开）：")
names = s.split("，")
#length = len(names)
find = input("请输入查找姓名：")
flag = 0
for i in names:
    if i == find:
        flag = 1
        print('列表中存在！')
    #else:
        #length -= 1
        #if length == 0:
            #print('列表中不存在！')
if(flag == 0):
    print('列表中不存在！')