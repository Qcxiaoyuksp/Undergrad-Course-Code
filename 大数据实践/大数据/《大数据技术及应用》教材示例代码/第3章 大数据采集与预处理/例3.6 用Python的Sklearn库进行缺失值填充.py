#数据预处理：缺失值填充
import pandas as pd 
from sklearn.impute import SimpleImputer
from numpy import nan as NA
data = pd.read_csv('labor.csv')
x = data.iloc[:, 2:3]           									#取第3列数据
imp_mean = SimpleImputer(missing_values=NA, strategy=‘mean’)  	#均值填充
imp_mean.fit(x)
print( imp_mean.transform(x) ) 								#通过接口导出结果
