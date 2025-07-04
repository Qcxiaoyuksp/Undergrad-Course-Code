#【例8.8】判断客户拖欠贷款可能性的逻辑回归分析模型

#逻辑回归示例代码
import pandas as pd
from sklearn.linear_model import LogisticRegression as LR
from sklearn.metrics import mean_squared_error, r2_score
data = pd.read_excel('bankloan.xls')
x = data.iloc[:, :-1]
y = data.iloc[:, -1]         #标签
lr = LR(solver='liblinear')  #建立逻辑回归模型
lr.fit(x, y)                 #训练模型
#模型评价
print('模型的平均准确度为：%s' % lr.score(x, y))
y_pred = lr.predict(x)    #预测
print('均方误差为: %.2f'%mean_squared_error(y, y_pred))  #误差
#交叉验证
from sklearn.model_selection import train_test_split,cross_val_score,cross_validate
import numpy as np
X_train, X_test, y_train, y_test = train_test_split(x,y)  
scores = cross_val_score(lr, X_train, y_train, cv=5)  
print ('准确率：',np.mean(scores), scores) 