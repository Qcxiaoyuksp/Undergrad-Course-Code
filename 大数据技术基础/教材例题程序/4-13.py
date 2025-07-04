#%%
#绘制柱状图展示四个直辖市近10年来的GDP。
#1）移动鼠标查看各个柱高对应的值
#2）单击标签，选择显示或不显示该类值


#数据准备
import pandas as pd
from pandas import Series, DataFrame
proGDP = pd.read_excel('data/ProvinceGDP.xlsx','GDP-4',index_col=0)

#将DaaFame、Series类型数据转换为python的数据结构，dict、List等
year = proGDP.columns.tolist()
vGDP = proGDP.values.tolist()

#引入pyecharts绘图相关库
from pyecharts.charts import Bar  #柱状图
from pyecharts.globals import ThemeType #基础库，主题配色
import pyecharts.options as opts  #基础库，选项

#定义绘制的图形
gdpBar = (
    #柱状图初始化
    Bar({"theme": ThemeType.MACARONS})
    #设置横轴坐标值
    .add_xaxis(year)
    #设置每个纵轴的标签，数值，以及是否显示值
    .add_yaxis("北京", vGDP[0], label_opts=opts.LabelOpts(is_show=False))
    .add_yaxis("天津", vGDP[1], label_opts=opts.LabelOpts(is_show=False))
    .add_yaxis("上海", vGDP[2], label_opts=opts.LabelOpts(is_show=False))
    .add_yaxis("重庆", vGDP[3], label_opts=opts.LabelOpts(is_show=False))
    #设置图元
    .set_global_opts(
        title_opts={"text": "2010-2019年直辖市GDP", "subtext": "GDP：亿元"}
    )
)

#绘制图形，生成html文件
gdpBar.render("2000-2019直辖市GDP.html")  
