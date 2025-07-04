#1)
import numpy as np
names = np.array(['大润发', '沃尔玛', '好德', '农工商'])
fruits = np.array(['苹果', '梨', '香蕉', '桔子', '芒果'])

#2)
price = np.random.randint(4, 11, size = (4, 5))
print(price)

#3)
a = price[(names == '大润发')|(names == '好德'), (fruits == '苹果')|(fruits == '香蕉')] + 1
print(a)

#4)
b = price[names == '农工商'] - 2
print(b)

#5)
c = price[:,(fruits == '苹果')|(fruits == '芒果')].mean(axis = 0)
print(c)

#6)
d = price[:, fruits == '桔子'].argmax()
print(names[d])