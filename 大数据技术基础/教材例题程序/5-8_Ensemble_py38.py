# 例5-8 集成学习
# 采用数据集为bank-data.csv，共有600条数据，11个属性字段，其中’pep'为分类字段

#读入数据
import pandas as pd

filename = 'data/bankpep.csv'
data = pd.read_csv(filename, index_col = 'id')
print( data.iloc[0:5,:])

#%%
#将最数据中的‘YES’和‘NO'转换成代表分类的整数 1 和 0
seq = ['married', 'car', 'save_act', 'current_act', 'mortgage', 'pep']
for feature in seq :  # 逐个特征进行替换
    data.loc[ data[feature] == 'YES', feature ] =1
    data.loc[ data[feature] == 'NO', feature ] =0

#将性别转换为整数1和0
data.loc[ data['sex'] == 'FEMALE', 'sex'] =1
data.loc[ data['sex'] == 'MALE', 'sex'] =0

print(data[0:5])

#%%
#将离散特征数据进行独热编码，转换为dummies矩阵
dumm_reg = pd.get_dummies( data['region'], prefix='region' )
#print(dumm_reg[0:5])

dumm_child = pd.get_dummies( data['children'], prefix='children' )
#print(dumm_child[0:5])

#删除dataframe中原来的两列后再 jion dummies
df1 = data.drop(['region','children'], axis = 1)
#print( df1[0:5])
df2 = df1.join([dumm_reg,dumm_child], how='outer')
print( df2[0:2])

#%%
#准备训练输入变量
X = df2.drop(['pep'], axis=1)
#X = df2.iloc[:,:-1]
y = df2['pep']
print("X.shape", X.shape)
print(X[0:2])
print(y[0:2])

#%%
#将数据集拆分为训练集和测试集，在测试集上查看分类效果
from sklearn import model_selection

X_train, X_test, y_train, y_test = model_selection.train_test_split(X, y, test_size=0.3, random_state=1)


#采用决策树方法
from sklearn import model_selection
X_train, X_test, y_train, y_test = model_selection.train_test_split(X, y, test_size=0.3, random_state=1)
y_train=y_train.astype('int')
y_test=y_test.astype('int')
from sklearn import tree
clf = tree.DecisionTreeClassifier()

clf = clf.fit(X_train, y_train)
clf.score(X_test,y_test)  #计算分类器的Accuracy
#%%

#采用随机森林，数据无需归一化处理
from sklearn.ensemble import RandomForestClassifier

#固定决策树个数，搜索最大深度max_depth
d_scores = []
for i in range(1,10):
    RF = RandomForestClassifier(n_estimators=15, criterion='entropy', max_depth =i )
    RF.fit(X_train,y_train)
    d_scores.append( RF.score(X_test,y_test) )

depth = d_scores.index(max(d_scores) )   #列表求最大值的索引
print('树深度:', depth,',  最优值为： ', max(d_scores))    #列表求最大值
#%%
#搜索最优决策树个树n_estimators
n_scores = []
for i in range(1,21):
    RF = RandomForestClassifier(n_estimators=i, criterion='entropy', max_depth = depth )
    RF.fit(X_train,y_train)
    n_scores.append( RF.score(X_test,y_test) )
print('决策树数目： ',n_scores.index(max(n_scores)), ',  Accuracy准确性 最优值为： ', max(n_scores) ) 

#%%
#搜索每种深度下最优树的个数，记录相应的accuacy，然后比较找出最优的集成树
scores = [] #树深度0~9的最优accuracy
pos = []  #树深度0~9 最优accuracy 对应的树个数

for i in range(1, 10):  #树的深度从1~9
    d_scores = []
    for j in range(1, 21):  #树的个数从1~20
        RF = RandomForestClassifier(n_estimators=j, criterion='entropy', max_depth =i )
        RF.fit(X_train,y_train)
        d_scores.append( RF.score(X_test,y_test) )
    scores.append(max(d_scores) )          #保存当前深度最优的Accuracy
    pos.append(d_scores.index(max(d_scores)) )    #保存当前深度最优树的数目

print('Accuracy准确性 最优值为： ', max(scores)) 
num = scores.index(max(scores) )
depth = pos[num]
print('决策树数目： ',num, ', 树深度:', depth) 

#%%
# ## XGBoost

import xgboost as xgb
from xgboost import plot_importance
from matplotlib import pyplot as plt
from sklearn import model_selection

X_train, X_test, y_train, y_test = model_selection.train_test_split(X, y, test_size=0.3, random_state=1)
y_train=y_train.astype('bool')
X_train.sex=X_train.sex.astype('bool')
X_train.married=X_train.married.astype('bool')
X_train.car=X_train.car.astype('bool')
X_train.save_act=X_train.save_act.astype('bool')
X_train.current_act=X_train.current_act.astype('bool')
X_train.mortgage=X_train.mortgage.astype('bool')
# 训练模型
model = xgb.XGBClassifier(max_depth=8, learning_rate=0.1, n_estimators=40, silent=False)
model.fit(X_train, y_train)
#%%
# 对测试集进行预测
X_test.sex=X_test.sex.astype('bool')
X_test.married=X_test.married.astype('bool')
X_test.car=X_test.car.astype('bool')
X_test.save_act=X_test.save_act.astype('bool')
X_test.current_act=X_test.current_act.astype('bool')
X_test.mortgage=X_test.mortgage.astype('bool')
ans = model.predict(X_test)
#%%
# 计算准确率
cnt1 = 0
cnt2 = 0
for i in range(len(y_test)):
    if ans[i] == y_test[i]:
        cnt1 += 1
    else:
        cnt2 += 1

print("Accuracy: %.2f %% " % (100 * cnt1 / (cnt1 + cnt2)))
from sklearn import metrics
y_test=y_test.astype('bool')
print( metrics.classification_report(y_test, ans) )
#%%
# 画图显示各特征对分类模型的重要性
plot_importance(model)
plt.show()


