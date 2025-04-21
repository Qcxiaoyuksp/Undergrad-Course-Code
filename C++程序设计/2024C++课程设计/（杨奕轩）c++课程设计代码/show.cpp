#include "show.h"

void show1()
{
	cout << "////////////////////////////////////////////////////////////////" << endl;
	cout << "//*********欢迎使用沈阳建筑大学教师档案管理系统***************//" << endl;
	cout << "//*                                                          *//" << endl;
	cout << "//*      请输入数字1-9实现相应功能                           *//" << endl;
	cout << "//*      1.显示教师管理系统内的教师信息                      *//" << endl;
	cout << "//*      2.增加教师信息                                      *//" << endl;
	cout << "//*      3.更改教师信息                                      *//" << endl;
	cout << "//*      4.删除教师信息                                      *//" << endl;
	cout << "//*      5.精确查找教师信息（输入姓名/教师号查询）           *//" << endl;
	cout << "//*      6.范围查找(应发工资、实发工资、公积金处于指定范围)  *//" << endl;
	cout << "//*      7.模糊查找(输入名字、学院、电话的部分信息)          *//" << endl;
	cout << "//*      8.统计分析某学院平均工资及标准差                    *//" << endl;
	cout << "//*      9.按照实发工资进行排序                              *//" << endl;
	cout << "//************************************************************//" << endl;
	cout << "//*      0.退出                                              *//" << endl;
	cout << "//************************************************************//" << endl;
	cout << "////////////////////////////////////////////////////////////////" << endl;
}

void show2(Management &s)
{
	int op, k;
	s.add_from_file();  //读取文件的信息并加入vector容器中
	while (1) 
	{
		cin >> op;
		switch (op)
		{
			case 1: //显示系统内已有教师信息
				s.displaysys(); 
				break;    
			case 2: //增加教师信息
				s.addition(); 
				break;       
			case 3: //更改教师信息
				s.modify(); 
				break;            
			case 4: //删除教师信息
				s.deletion(); 
				break;           
			case 5: //精确查找教师信息（输入姓名/教师号查询）
				s.find(); 
				break;             
			case 6: //范围查找(应发工资、实发工资、公积金处于指定范围)
				s.find_range(); 
				break;     
			case 7: //模糊查找(输入名字、学院、电话的部分信息)
				s.fuzzyfind(); 
				break;         
			case 8: //统计分析某学院平均工资及标准差
				s.average(); 
				break;             
			case 9: //按照实发工资进行排序，并输出到SortData.txt文件
				s.SectionSort(); 
				break;  
			case 0:
				exit(0);
				break;
			default:
				break;
		}
//		cout << "是否退出教师档案管理系统，退出请按0，否则请按1。" << endl;
//		cin >> k;
//		if (k == 0)
//			break;
//		else
//		{
//			show1();
//		}			
	}	
}


