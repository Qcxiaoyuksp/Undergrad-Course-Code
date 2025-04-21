// ConsoleApplication27.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include<sstream>
#include <algorithm>

using namespace std;

// 声明City类
class City {
private:
	string countryName;
	string cityName;
	int newCases;
	int currentCases;
	int totalCases;
	int recoveredCases;
	int deathCases;
	int predictCases;

public:
	// 构造函数
	City(string name, int newCases, int currentCases, int totalCases, int recoveredCases, int deathCases, int predictCases) {
		cityName = name;
		this->newCases = newCases;
		this->currentCases = currentCases;
		this->totalCases = totalCases;
		this->recoveredCases = recoveredCases;
		this->deathCases = deathCases;
		this->predictCases = predictCases;
	}

	// 获取城市名称
	string getCityName() const {
		return cityName;
	}

	// 获取新增病例数
	int getNewCases() const {
		return newCases;
	}

	// 获取现有病例数
	int getCurrentCases() const {
		return currentCases;
	}

	// 获取累计病例数
	int getTotalCases() const {
		return totalCases;
	}

	// 获取治愈病例数
	int getRecoveredCases() const {
		return recoveredCases;
	}

	// 获取死亡病例数
	int getDeathCases() const {
		return deathCases;
	}

	// 获取预测病例数
	int getPredictCases() const {
		return predictCases;
	}

	// 更新城市信息
	void update(int newCases, int currentCases, int totalCases, int recoveredCases, int deathCases) {
		this->newCases = newCases;
		this->currentCases = currentCases;
		this->totalCases = totalCases;
		this->recoveredCases = recoveredCases;
		this->deathCases = deathCases;
	}

	// 预测疫情发展趋势
	void predict(string country1) {
		ifstream infile("data.txt");
		if (!infile) {
			cout << "文件不存在！" << endl;
			return;
		}
		string line;
		vector<double> x, y; // 存储城市的历史数据
		while (getline(infile, line)) {
			if (line.empty()) {
				continue;
			}
			stringstream ss(line);
			string countryName, cityName;
			int newCases, currentCases, totalCases, recoveredCases, deathCases, predictCases;
			ss >> countryName >> cityName >> newCases >> currentCases >> totalCases >> recoveredCases >> deathCases >> predictCases;

			if (countryName == country1 && cityName == this->cityName) {
				x.push_back(x.size() + 1); 
				y.push_back(currentCases); // y轴为现有病例数
			}
		}
		infile.close();
		if (x.empty() || y.empty()) {
			cout << "该城市没有历史数据！" << endl;
			return;
		}

		int n = x.size(); // 历史数据个数
		int order = 2; // 多项式拟合的阶数，这里假设为2
		double A[3][4] = { 0 }; // 扩展系数矩阵
		double coeff[3] = { 0 }; // 解向量
		for (int i = 0; i < order + 1; i++) {
			for (int j = 0; j < order + 1; j++) {
				for (int k = 0; k < n; k++) {
					A[i][j] += pow(x[k], i + j); // 计算系数矩阵的元素
				}
			}
			for (int k = 0; k < n; k++) {
				A[i][order + 1] += pow(x[k], i) * y[k]; // 计算常数矩阵的元素
			}
		}

		// 高斯消元法求解线性方程组
		for (int i = 0; i < order + 1; i++) {
			int maxRow = i;
			for (int j = i + 1; j < order + 1; j++) {
				if (abs(A[j][i]) > abs(A[maxRow][i])) {
					maxRow = j;
				}
			}
			if (maxRow != i) {
				for (int j = i; j < order + 2; j++) {
					swap(A[maxRow][j], A[i][j]);
				}
			}
			for (int j = i + 1; j < order + 1; j++) {
				double factor = A[j][i] / A[i][i];
				for (int k = i; k < order + 2; k++) {
					A[j][k] -= factor * A[i][k];
				}
			}
		}
		for (int i = order; i >= 0; i--) {
			coeff[i] = A[i][order + 1];
			for (int j = i + 1; j < order + 1; j++) {
				coeff[i] -= A[i][j] * coeff[j];
			}
			coeff[i] /= A[i][i];
		}

		double next_x = x.back() + 1; // 预测下一个时间点的x值
		double next_y = 0; // 预测下一个时间点的y值
		for (int i = 0; i < order + 1; i++) {
			next_y += coeff[i] * pow(next_x, i); // 计算多项式函数的值
		}
		cout << "城市名称：" << cityName << endl;
		cout << "预测下一个时间点的现有病例数：" << next_y << endl;
		this->predictCases = next_y;
	}

	// 输出城市信息
	void print() {
		cout << "城市名称：" << cityName << endl;
		cout << "新增病例数：" << newCases << endl;
		cout << "现有病例数：" << currentCases << endl;
		cout << "累计病例数：" << totalCases << endl;
		cout << "治愈病例数：" << recoveredCases << endl;
		cout << "死亡病例数：" << deathCases << endl;
		cout << "预测病例数：" << predictCases << endl << endl;
	}
};

// 声明Country类
class Country {
private:
	vector<City> cities;

public:
	string countryName;
	// 构造函数
	Country(string name) {
		countryName = name;
	}

	// 获取国家名称
	string getCountryName() {
		return countryName;
	}

	// 获取城市列表
	vector<City>& getCities() {
		return cities;
	}

	// 添加城市
	void addCity(string countryName, string cityName, int newCases, int currentCases, int totalCases, int recoveredCases, int deathCases, int predictCases) {
		City city(cityName, newCases, currentCases, totalCases, recoveredCases, deathCases, predictCases);
		cities.push_back(city);
	}

	// 更新城市信息
	void updateCity(string cityName, int newCases, int currentCases, int totalCases, int recoveredCases, int deathCases) {
		for (int i = 0; i < cities.size(); i++) {
			if (cities[i].getCityName() == cityName) {
				cities[i].update(newCases, currentCases, totalCases, recoveredCases, deathCases);
				return;
			}
		}
		cout << "该城市不存在！" << endl;
	}

	// 删除城市
	void deleteCity(string cityName) {
		for (int i = 0; i < cities.size(); i++) {
			if (cities[i].getCityName() == cityName) {
				cities.erase(cities.begin() + i);
				return;
			}
		}
		cout << "该城市不存在！" << endl;
	}

	// 计算全国疫情情况
	void calculateCases() {
		int totalNewCases = 0;
		int totalCurrentCases = 0;
		int totalTotalCases = 0;
		int totalRecoveredCases = 0;
		int totalDeathCases = 0;
		for (int i = 0; i < cities.size(); i++) {
			totalNewCases += cities[i].getNewCases();
			totalCurrentCases += cities[i].getCurrentCases();
			totalTotalCases += cities[i].getTotalCases();
			totalRecoveredCases += cities[i].getRecoveredCases();
			totalDeathCases += cities[i].getDeathCases();
		}
		cout << "国家名称：" << countryName << endl;
		cout << "新增病例数：" << totalNewCases << endl;
		cout << "现有病例数：" << totalCurrentCases << endl;
		cout << "累计病例数：" << totalTotalCases << endl;
		cout << "治愈病例数：" << totalRecoveredCases << endl;
		cout << "死亡病例数：" << totalDeathCases << endl;
	}

	// 预测疫情发展趋势
	void predictCases(string cityName) {
		for (int i = 0; i < cities.size(); i++) {
			if (cities[i].getCityName() == cityName) {
				cities[i].predict(this->countryName);
				return;
			}
		}
	}


	// 输出国家信息
	void print() {
		cout << "国家名称：" << countryName << endl;
		for (int i = 0; i < cities.size(); i++) {
			cities[i].print();
		}
	}
};

// 从文件中读取疫情信息
vector<Country> readFromFile() {
	vector<Country> countries;
	ifstream infile("data.txt");
	if (!infile) {
		cout << "文件不存在！" << endl;
		return countries;
	}
	string line;
	while (getline(infile, line)) {
		if (line.empty()) {
			continue;
		}
		stringstream ss(line);
		string countryName, cityName;
		int newCases, currentCases, totalCases, recoveredCases, deathCases, predictCases;
		ss >> countryName >> cityName >> newCases >> currentCases >> totalCases >> recoveredCases >> deathCases >> predictCases;

		bool hasCountry = false;
		for (auto& country : countries) {
			if (country.countryName == countryName) {
				bool cityExist = false;

				auto cities = country.getCities();
				for (auto city : cities) {
					if (city.getCityName() == cityName) {
						cityExist = true;
						city.update(newCases, currentCases, totalCases, recoveredCases, deathCases);
					}
				}
				if (!cityExist) {
					country.addCity(countryName, cityName, newCases, currentCases, totalCases, recoveredCases, deathCases, predictCases);
				}
				hasCountry = true;
				break;
			}
		}
		if (!hasCountry) {
			Country country(countryName);
			country.addCity(countryName, cityName, newCases, currentCases, totalCases, recoveredCases, deathCases, predictCases);
			countries.push_back(country);
		}
	}
	infile.close();
	return countries;
}
// 将疫情信息写入文件
void writeToFile(vector<Country> countries) {
	ofstream outfile("data.txt");
	for (int i = 0; i < countries.size(); i++) {
		vector<City> cities = countries[i].getCities();
		for (int j = 0; j < cities.size(); j++) {
			outfile << countries[i].getCountryName() << " " << cities[j].getCityName() << " "
				<< cities[j].getNewCases() << " " << cities[j].getCurrentCases() << " "
				<< cities[j].getTotalCases() << " " << cities[j].getRecoveredCases() << " "
				<< cities[j].getDeathCases() << " " << cities[j].getPredictCases() << endl;
		}
	}
	outfile.close();
}


int main() {
	vector<Country> countries = readFromFile();
	int choice;
	while (true) {
		cout << endl;
		cout << "                                                        疫情管理与预测系统                                     " << endl;
		cout << "                                                        1. 查看疫情信息                                        "<< endl;
		cout << "                                                        2. 更新城市疫情信息                                    " << endl;
		cout << "                                                        3. 删除城市                                           " << endl;
		cout << "                                                        4. 添加城市                                            " << endl;
		cout << "                                                        5. 计算全国疫情情况                                     "<< endl;
		cout << "                                                        6. 预测疫情发展趋势                                      "<< endl;
		cout << "                                                        7. 统计                                                  " << endl;
		cout << "                                                        8. 退出                                                  " << endl;
		cin >> choice;
		if (choice == 1) {
			for (int i = 0; i < countries.size(); i++) {
				countries[i].print();
			}
		}
		else if (choice == 2) {
			string countryName, cityName;
			int newCases, currentCases, totalCases, recoveredCases, deathCases;
			cout << "请输入国家名称：";
			cin >> countryName;
			cout << "请输入城市名称：";
			cin >> cityName;
			cout << "请输入新增病例数：";
			cin >> newCases;
			cout << "请输入现有病例数：";
			cin >> currentCases;
			cout << "请输入累计病例数：";
			cin >> totalCases;
			cout << "请输入治愈病例数：";
			cin >> recoveredCases;
			cout << "请输入死亡病例数：";
			cin >> deathCases;
			bool cityExist = false;
			for (int i = 0; i < countries.size(); i++) {
				if (countries[i].getCountryName() == countryName) {
					countries[i].updateCity(cityName, newCases, currentCases, totalCases, recoveredCases, deathCases);
					cityExist = true;
					break;
				}
			}
			if (!cityExist) {
				cout << "该国家不存在！" << endl;
			}
		}
		else if (choice == 3) {
			string countryName, cityName;
			cout << "请输入国家名称：";
			cin >> countryName;
			cout << "请输入城市名称：";
			cin >> cityName;
			bool cityExist = false;
			for (int i = 0; i < countries.size(); i++) {
				if (countries[i].getCountryName() == countryName) {
					countries[i].deleteCity(cityName);
					cityExist = true;
					break;
				}
			}
			if (!cityExist) {
				cout << "该国家不存在！" << endl;
			}
		}
		else if (choice == 4) {
			string countryName, cityName;
			int newCases, currentCases, totalCases, recoveredCases, deathCases, predictCases;
			cout << "请输入国家名称：";
			cin >> countryName;
			cout << "请输入城市名称：";
			cin >> cityName;
			cout << "请输入新增病例数：";
			cin >> newCases;
			cout << "请输入现有病例数：";
			cin >> currentCases;
			cout << "请输入累计病例数：";
			cin >> totalCases;
			cout << "请输入治愈病例数：";
			cin >> recoveredCases;
			cout << "请输入死亡病例数：";
			cin >> deathCases;
			cout << "请输入预测病例数：";
			cin >> predictCases;
			bool countryExist = false;
			for (int i = 0; i < countries.size(); i++) {
				if (countries[i].getCountryName() == countryName) {
					countries[i].addCity(countryName, cityName, newCases, currentCases, totalCases, recoveredCases, deathCases, predictCases);
					countryExist = true;
					break;
				}
			}
			if (!countryExist) {
				Country country(countryName);
				country.addCity(countryName, cityName, newCases, currentCases, totalCases, recoveredCases, deathCases, predictCases);
				countries.push_back(country);
			}
		}
		else if (choice == 5) {
			for (int i = 0; i < countries.size(); i++) {
				countries[i].calculateCases();
			}
		}
		else if (choice == 6) {
			string countryName, cityName;
			cout << "请输入国家名称：";
			cin >> countryName;
			cout << "请输入城市名称：";
			cin >> cityName;
			bool cityExist = false;
			for (int i = 0; i < countries.size(); i++) {
				if (countries[i].getCountryName() == countryName) {
					countries[i].predictCases(cityName);
					cityExist = true;
					break;
				}
			}
			if (!cityExist) {
				cout << "该城市不存在！" << endl;
			}
		}
		else if (choice == 8) {
			writeToFile(countries);
			cout << "程序已退出，疫情信息已保存至文件。" << endl;
			break;
		}
		else if (choice == 7) {
			int subchoice;
			cout << "请选择统计方式：" << endl;
			cout << "1. 按新增病例数排序" << endl;
			cout << "2. 按现有病例数排序" << endl;
			cout << "3. 按累计病例数排序" << endl;
			cout << "4. 按治愈病例数排序" << endl;
			cout << "5. 按死亡病例数排序" << endl;
			cout << "6. 按国家查看累计疫情数据" << endl;
			cin >> subchoice;
			if (subchoice == 1) {
				// 按新增病例数排序
				vector<City> allCities; // 存储所有城市
				for (int i = 0; i < countries.size(); i++) {
					vector<City> cities = countries[i].getCities();
					for (int j = 0; j < cities.size(); j++) {
						allCities.push_back(cities[j]);
					}
				}
				sort(allCities.begin(), allCities.end(), [](const City& a, const City& b) {return a.getNewCases() > b.getNewCases(); }); // 降序排序
				for (int i = 0; i < allCities.size(); i++) {
					allCities[i].print();
				}
			}
			else if (subchoice == 2) {
				// 按现有病例数排序
				vector<City> allCities; // 存储所有城市
				for (int i = 0; i < countries.size(); i++) {
					vector<City> cities = countries[i].getCities();
					for (int j = 0; j < cities.size(); j++) {
						allCities.push_back(cities[j]);
					}
				}
				sort(allCities.begin(), allCities.end(), [](const City& a, const City& b) {return a.getCurrentCases() > b.getCurrentCases(); }); // 降序排序
				for (int i = 0; i < allCities.size(); i++) {
					allCities[i].print();
				}
			}
			else if (subchoice == 3) {
				// 按累计病例数排序
				vector<City> allCities; // 存储所有城市
				for (int i = 0; i < countries.size(); i++) {
					vector<City> cities = countries[i].getCities();
					for (int j = 0; j < cities.size(); j++) {
						allCities.push_back(cities[j]);
					}
				}
				sort(allCities.begin(), allCities.end(), [](const City& a, const City& b) {return a.getTotalCases() > b.getTotalCases(); }); // 降序排序
				for (int i = 0; i < allCities.size(); i++) {
					allCities[i].print();
				}
			}
			else if (subchoice == 4) {
				// 按治愈病例数排序
				vector<City> allCities; // 存储所有城市
				for (int i = 0; i < countries.size(); i++) {
					vector<City> cities = countries[i].getCities();
					for (int j = 0; j < cities.size(); j++) {
						allCities.push_back(cities[j]);
					}
				}
				sort(allCities.begin(), allCities.end(), [](const City& a, const City& b) {return a.getRecoveredCases() > b.getRecoveredCases(); }); // 降序排序
				for (int i = 0; i < allCities.size(); i++) {
					allCities[i].print();
				}
			}
			else if (subchoice == 5) {
				// 按死亡病例数排序
				vector<City> allCities; // 存储所有城市
				for (int i = 0; i < countries.size(); i++) {
					vector<City> cities = countries[i].getCities();
					for (int j = 0; j < cities.size(); j++) {
						allCities.push_back(cities[j]);
					}
				}
				sort(allCities.begin(), allCities.end(), [](const City& a, const City& b) {return a.getDeathCases() > b.getDeathCases(); }); // 降序排序
				for (int i = 0; i < allCities.size(); i++) {
					allCities[i].print();
				}
			}
			else if (subchoice == 6) {
				// 按国家查看累计疫情数据
				string countryName;
				cout << "请输入国家名称：";
				cin >> countryName;
				bool countryExist = false;
				for (int i = 0; i < countries.size(); i++) {
					if (countries[i].getCountryName() == countryName) {
						countries[i].calculateCases();
						countryExist = true;
						break;
					}
				}
				if (!countryExist) {
					cout << "该国家不存在！" << endl;
				}
			}
			else {
				cout << "无效操作！请重新输入。" << endl;
			}
		}


		system("pause");
		system("cls");
	}
	return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

