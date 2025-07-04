#使用决策树对iris数据集进行分类
import pandas as pd
from sklearn import tree
import pydotplus
import os     
os.environ["PATH"] += os.pathsep + 'D:/Python64/Lib/graphviz-2.38/bin'
#需要先安装graphviz，再加到搜索路径中
data = pd.read_csv('iris.csv')     						#导入iris数据集
x = data.iloc[:,0:-1]
y = data.iloc[:,-1]               						#标签
clf = tree.DecisionTreeClassifier(criterion='entropy') 	#使用信息熵，默认criterion='gini'
clf = clf.fit(x, y)
#将决策树以pdf格式可视化
dot_data = tree.export_graphviz(clf, out_file=None)
graph = pydotplus.graph_from_dot_data(dot_data)
graph.write_pdf("iris.pdf")               
#评估决策树分类算法的性能
from sklearn.model_selection import train_test_split
# 导入评估指标模块
from sklearn.metrics import accuracy_score, auc, confusion_matrix, f1_score, precision_score, recall_score, roc_curve
import numpy as np
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size = 0.2)
clf.fit(x_train, y_train)
answer = clf.predict(x_train)
print('训练集上的准确率：', np.mean( answer == y_train))
score = print('测试集上的准确率：', clf.score(x_test, y_test))
# f1-score
pre_y_test = clf.predict(x_test)
f1_s =f1_score(y_test, pre_y_test, average='weighted')
print('f1_score：', f1_s)
