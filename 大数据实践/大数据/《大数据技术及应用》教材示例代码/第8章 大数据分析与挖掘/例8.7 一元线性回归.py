#一元线性回归
import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
from sklearn.linear_model import LinearRegression
data = pd.read_csv('广告费与销售额.csv')
Model = LinearRegression()
x = data[['广告费']]
y = data[['销售额']]
Model.fit(x,y)            #训练模型
beta0 = Model.intercept_[0]
print('截距=',  beta0)
beta1 = Model.coef_[0][0]
print('斜率=', beta1)
#画散点图
plt.rcParams['font.family']='SimHei'
fig = plt.figure(dpi=300)  
ax = fig.add_subplot()
ax.scatter(x, y)
X = np.linspace(0, 16, 100)
Y = beta0 + beta1*X
ax.scatter(X,Y, s=1, color='black')
ax.set_xlabel('广告费(万元)', fontproperties='SimHei',fontsize=12)
ax.set_ylabel('销售额(万元)', fontproperties='SimHei',fontsize=12)
plt.show()
