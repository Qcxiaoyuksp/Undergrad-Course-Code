# -*- coding: utf-8 -*-
"""
Created on Thu Sep 21 08:12:00 2023

@author: 张清晨
"""

import pandas as pd
import numpy as np

#1)
bankpep_data = pd.read_csv('E:/大数据技术基础/教材例题程序/bankpep.csv')

#2)
print(bankpep_data['id'].count())

print(bankpep_data.groupby('region')['id'].count())

#3)
print(bankpep_data.groupby('sex').aggregate({'income':[np.mean,np.var]}))

#4)
print(bankpep_data[['pep','sex','region']].groupby(['sex','region']).count())

#5)
bankpep_data[['save_act','pep']] = np.where(bankpep_data[['save_act','pep']] =='YES',1,0)
print(bankpep_data)

#6)
print(bankpep_data[['income','save_act','pep']].corr().round(2)) 