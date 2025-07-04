import matplotlib.pyplot as plt #导入matplotlib.pyplot
import pandas as pd
from pandas import Series
#支持中文显示
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.figure(figsize=(9,6))
#%%
data=Series([41.3,48.9,54.0,59.5,64.4,68.9,74.4,82.1,90.0, 
98.7,101.6], index=['2010','2011','2012','2013','2014',
'2015','2016','2017','2018','2019','2020'])   
#%%
#例4-3 pandas绘图，matplotlib添加图元
data.plot(title='2010-2020 GDP',LineWidth=2, marker='o', color='k',linestyle='dashed',grid=True,alpha=0.9)
#xy箭头位置，xytext文字起始位置，值为（横坐标序号，纵坐标数值）
plt.annotate('拐点',xy=(9,98.3),xytext=(7,96), arrowprops=dict(arrowstyle='->'),fontsize=14)
plt.text(1.5,84,'GDP 持续增长突破100万亿!',fontsize=16)
plt.xlabel('年',fontsize=12)
plt.ylabel('GDP: 万亿',fontsize=12)

#将绘制图形保存到文件
plt.savefig("2010-2020GDP.png",dpi=200,bbox_inches='tight')

plt.show()  #注意保存文件需在显示之前
