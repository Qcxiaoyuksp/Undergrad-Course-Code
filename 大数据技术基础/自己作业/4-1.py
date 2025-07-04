# -*- coding: utf-8 -*-
"""
Created on Thu Sep 28 08:58:16 2023

@author: 张清晨
"""

import matplotlib.pyplot as plt
import pandas as pd
data = pd.read_csv('E:/大数据技术基础/教材例题程序/bankpep.csv')
#1)
data['age'].plot(kind = 'hist',bins = 10,density= True,title = 'Customer Age')
data['age'].plot(kind = 'kde',style = 'k-')
plt.xlabel('Age')
plt.ylabel('Density')
plt.show()

#2)
data[['age','income']].plot(kind = 'scatter',x = 'age',y = 'income',marker = 's',s = 8,title = 'Customer Income',label = '(age,income)',grid = True, xlim = [0,80])     #s设置点大小
plt.xlabel('Age')
plt.ylabel('Income')
plt.show()

#3)
pd.plotting.scatter_matrix(data[['age','income','children']],c = 'm')   #c用来设置颜色：m为红紫色
plt.show()


#4)
import numpy as np
mean = data.groupby(['region']).agg({'income':np.mean})
std = data.groupby(['region']).agg({'income':np.std})
mean.plot(kind = 'bar',yerr = std ,rot = 45,title = 'Customer Income',legend = False,color = 'r')
plt.xlabel('Region')
plt.show()
 
#5)
#方法一：Series.plot绘图，fig.add_subplot()函数，Series类型的可不加ax=ax1,ax2,ax3
sex_data = data.groupby(['sex'])['sex'].count()
car_data = data[data['car'] =='YES'].groupby(['sex'])['sex'].count()
children_data = data.groupby(['children'])['children'].count()
fig = plt.figure(figsize = (7,6))
fig.add_subplot(2,2,1)
sex_data.plot(kind = 'pie',title ='Customer Sex',startangle = 60,autopct = '%1.1f%%')
fig.add_subplot(2,2,2)
car_data.plot(kind = 'pie',title = 'Customer Car Sex',startangle = 60,autopct = '%1.1f%%')
fig.add_subplot(2,2,3)
children_data.plot(kind = 'pie',title = 'Customer Children',startangle = 60,autopct = '%1.1f%%')
plt.savefig('饼图.jpg',dpi = 400,bbox_inches = 'tight')
plt.show()

#6)
data[['income','sex']].boxplot(by = 'sex',figsize = (6,6))
plt.show()






原文链接：https://blog.csdn.net/m0_51474486/article/details/123500848