# 导入各种相关包
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from xgboost import XGBClassifier
from sklearn.preprocessing import LabelEncoder
from pandas import DataFrame

# 读取数据集
data = pd.read_csv('wine.data',header=None)
# 从数据集中读取特征和标签
X = data.iloc[:, 1:]
y = data.iloc[:, 0]
#针对 XGBoost 的训练集与测试集进行单独处理
lblEncoder = LabelEncoder()
y_xg = lblEncoder.fit_transform(y)
# 将数据集分为训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3,random_state=42)
X_train, X_test, y_xg_train, y_xg_test = train_test_split(X, y_xg,test_size=0.3, random_state=42)
# 决策树
tree = DecisionTreeClassifier(random_state=21)
tree.fit(X_train, y_train)
treeScore = tree.score(X_test, y_test)
# 随机森林
forest = RandomForestClassifier(random_state=21)
forest.fit(X_train, y_train)
forestScore = forest.score(X_test, y_test)
#xgBoost
xgb = XGBClassifier(random_state=21)
xgb.fit(X_train, y_xg_train)
xgbScore = xgb.score(X_test, y_xg_test)
# 将各个模型的性能输出对比
print('决策树性能：', treeScore)
print('随机森林性能：', forestScore)
print('XGBoost 性能:', xgbScore)

import matplotlib.pyplot as plt
plt.figure()
data = [treeScore,forestScore,xgbScore]
f = DataFrame(data,columns=['score'],index=['dtc','rfc','xgb'])
f.plot(kind='bar',title='decisionscoreontestset',use_index=True,rot=45)
plt.show()