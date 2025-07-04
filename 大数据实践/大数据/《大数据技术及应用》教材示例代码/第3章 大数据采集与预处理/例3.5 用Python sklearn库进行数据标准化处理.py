import numpy as np
import pandas as pd
from sklearn import preprocessing
import matplotlib.pyplot as plt
import seaborn as sns

#设置中文字体
plt.rcParams["font.family"] = "SimHei"

np.random.seed(1)
# 构造left偏分布数据。
t1 = np.random.randint(1, 11, size=500)
t2 = np.random.randint(11, 21, size=100)
left_skew = np.concatenate([t1, t2])
# 构造右偏分布数据。
t1 = np.random.randint(1, 11, size=100)
t2 = np.random.randint(11, 21, size=500)
right_skew = np.concatenate([t1, t2])

# 绘制核密度图
plt.figure(2,(12,6))
plt.subplot(1,2,1)
plt.title('原始数据')
sns.kdeplot(left_skew, shade=True, label="左偏")
sns.kdeplot(right_skew, shade=True, label="右偏")

#进行标准化处理
zscore_scaler = preprocessing.StandardScaler()  # 建立StandardScaler对象
right_skew = zscore_scaler.fit_transform(right_skew.reshape(-1,1)) 
left_skew = zscore_scaler.fit_transform(left_skew.reshape(-1,1))

plt.subplot(1,2,2)
plt.title('Z-Score标准化')
sns.kdeplot(left_skew.reshape(-1,), shade=True)
sns.kdeplot(right_skew.reshape(-1,), shade=True)

plt.show()