import matplotlib.pyplot as plt #导入matplotlib.pyplot
import pandas as pd

##例4-5：绘制散点图观察学生身高和体重之间的关系。
import pandas as pd
stData = pd.read_csv('data\students.csv')      #读文件
stData.plot(kind='scatter',x='Height',y='Weight',title='Students Body Shape', marker='*',grid=True, xlim=[150,200], ylim=[40,80], label='(Height,Weight)')    #绘图
plt.show()
#%%
#将数据按性别分组，分别绘制散点图
#将数据按男生和女生分组
dataMale= stData[stData['Gender'] == 'male']  #筛选出男生
dataFemale= stData[stData['Gender'] == 'female']  #筛选出女生
#分组绘制男生、女生的散点图
plt.figure()
plt.scatter(dataMale['Height'],dataMale['Weight'],c='r',marker='s',label='Male')   
plt.scatter(dataFemale['Height'],dataFemale['Weight'],c='b',marker='^',label='Female') 
plt.xlim(150,200)                 #x轴范围
plt.ylim(40,80)              #y轴范围
plt.title('Student Body Shape')    #标题
plt.xlabel('Height')             #x轴标题
plt.ylabel('Weight')             #y轴标题
plt.grid()                         #网格线
plt.legend(loc='upper right')  #图例显示位置
plt.show()
#%%
#例4-6: 绘制散点图矩阵观察学生各项信息
data = stData[['Height', 'Weight','Age','Score']]  #准备数据
pd.plotting.scatter_matrix(data,diagonal='kde',color='k')  #绘图
plt.show()
