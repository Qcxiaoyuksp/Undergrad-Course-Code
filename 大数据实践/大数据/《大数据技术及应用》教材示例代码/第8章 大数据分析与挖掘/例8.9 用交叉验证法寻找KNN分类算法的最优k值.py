#交叉验证法确定kNN算法的k值
from sklearn.datasets import load_iris
from sklearn.model_selection  import cross_val_score
from matplotlib import pyplot as plt
from sklearn.neighbors import KNeighborsClassifier
#读取鸢尾花数据集
iris = load_iris()   #自动从sklearn库中下载数据集
x = iris.data
y = iris.target
k_range = range(1, 18)
k_accuracy = []
#循环，取k=1到k=17，查看误差效果
for k in k_range:
    knn = KNeighborsClassifier(n_neighbors = k)
    #cv参数决定数据集划分比例，这里是按照5:1划分训练集和测试集
    scores = cross_val_score(knn, x, y, cv=6, scoring='accuracy')
    k_accuracy.append(scores.mean())
#画图，x轴为k值，y值为精度
plt.figure(dpi=300)
plt.plot(k_range, k_accuracy)
plt.xlabel('Value of K for KNN')
plt.ylabel('accuracy')
plt.show()