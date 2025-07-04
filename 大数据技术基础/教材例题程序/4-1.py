import matplotlib.pyplot as plt #导入matplotlib.pyplot
import pandas as pd

# 例4-1：pandas 绘图
from pandas import DataFrame
#%%
gdp = [41.3,48.9,54.0,59.5,64.4,68.9,74.4,82.1,90.0,99.1,101.6]
data = DataFrame({'GDP: Trillion':gdp}, index=['2010','2011','2012', 
            '2013','2014','2015','2016','2017','2018','2019', '2020']) 
data.plot() 
# plt.show()  #显示图形，关闭本次绘图
#%%
# pandas绘图参数设置
data.plot(title='2010—2020 GDP',LineWidth=2, marker='o', linestyle=   
           'dashed',color='r', grid=True,alpha=0.9,use_index=True, 
           # yticks=[30,40,50,60,70,80,90,100,110])
           yticks=[0,10,20,30,40,50,60,70,80,90,100,110])
# plt.show()
