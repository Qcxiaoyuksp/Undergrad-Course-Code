import matplotlib.pyplot as plt #导入matplotlib.pyplot
import pandas as pd

#例4-11：绘制各类广告投入的箱须图

data = pd.read_csv('data\Advertising.csv')
advData = data[['TV','Weibo','WeChat']]
advData.plot(kind='box', figsize=(6,6), title='Advertising Expenditure')
plt.show()
#%%
#按性别绘制学生体重的箱须图
stData = pd.read_csv('data\students.csv')
gendaData = stData[['Gender','Score']]
gendaData.boxplot(by='Gender',figsize=(6,6))
plt.show()
