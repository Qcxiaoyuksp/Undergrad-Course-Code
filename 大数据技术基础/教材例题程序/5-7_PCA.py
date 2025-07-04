# # 鸢尾花数据聚类与降维分析
# 鸢尾花数据集，包括4个特征项，1个分类标签。数据集共150条记录，每个种类各50条。

#从数据集中读入数据
import pandas as pd
filename = 'data/iris.data'
data = pd.read_csv(filename, header = None)
data.columns = ['sepal length','sepal width','petal length','petal width','class']
data.iloc[0:5,:]
#%%

#绘制散点图矩阵，观察特征维度的区分度
import matplotlib.pyplot as plt
pd.plotting.scatter_matrix(data, diagonal='hist')
plt.show()
#%%

#将类名转换为整数值
data.loc[ data['class'] == 'Iris-setosa', 'class' ] = 0
data.loc[ data['class'] == 'Iris-versicolor', 'class' ] = 1
data.loc[ data['class'] == 'Iris-virginica', 'class' ] = 2
y = data['class']
X = data.iloc[:,0:4]
#%%
# ### 例5-7 将4维特征降为2维
from sklearn.decomposition import PCA
#设定保留的特征维度
pca = PCA(n_components=2)
pca.fit(X)
print("explained ration:", pca.explained_variance_ratio_ )
print("explained_variance:",pca.explained_variance_)
#%%
#数据变换，将4维数据变换为2维数据
newX = pca.transform(X)
#%%
#绘制降维后的特征散点图

import matplotlib.pyplot as plt
colors = ['b','c' ,'g']
for i in range(0,3):
    cl = newX[y == i]
    plt.scatter( cl[:,0], cl[:,1], c=colors[i] )
plt.show()
    
#c0 = newX[y==0]
#c1 = newX[y==1]
#c2 = newX[y==2]
#plt.scatter( c0[:,0], c0[:,1], c='b' )
#plt.scatter( c1[:,0], c1[:,1], c='c' )
#plt.scatter( c2[:,0], c2[:,1], c='g' )





