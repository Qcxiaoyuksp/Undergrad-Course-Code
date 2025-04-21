// ConsoleApplication27.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include<sstream>
#include <algorithm>

using namespace std;

// ����City��
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
	// ���캯��
	City(string name, int newCases, int currentCases, int totalCases, int recoveredCases, int deathCases, int predictCases) {
		cityName = name;
		this->newCases = newCases;
		this->currentCases = currentCases;
		this->totalCases = totalCases;
		this->recoveredCases = recoveredCases;
		this->deathCases = deathCases;
		this->predictCases = predictCases;
	}

	// ��ȡ��������
	string getCityName() const {
		return cityName;
	}

	// ��ȡ����������
	int getNewCases() const {
		return newCases;
	}

	// ��ȡ���в�����
	int getCurrentCases() const {
		return currentCases;
	}

	// ��ȡ�ۼƲ�����
	int getTotalCases() const {
		return totalCases;
	}

	// ��ȡ����������
	int getRecoveredCases() const {
		return recoveredCases;
	}

	// ��ȡ����������
	int getDeathCases() const {
		return deathCases;
	}

	// ��ȡԤ�ⲡ����
	int getPredictCases() const {
		return predictCases;
	}

	// ���³�����Ϣ
	void update(int newCases, int currentCases, int totalCases, int recoveredCases, int deathCases) {
		this->newCases = newCases;
		this->currentCases = currentCases;
		this->totalCases = totalCases;
		this->recoveredCases = recoveredCases;
		this->deathCases = deathCases;
	}

	// Ԥ�����鷢չ����
	void predict(string country1) {
		ifstream infile("data.txt");
		if (!infile) {
			cout << "�ļ������ڣ�" << endl;
			return;
		}
		string line;
		vector<double> x, y; // �洢���е���ʷ����
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
				y.push_back(currentCases); // y��Ϊ���в�����
			}
		}
		infile.close();
		if (x.empty() || y.empty()) {
			cout << "�ó���û����ʷ���ݣ�" << endl;
			return;
		}

		int n = x.size(); // ��ʷ���ݸ���
		int order = 2; // ����ʽ��ϵĽ������������Ϊ2
		double A[3][4] = { 0 }; // ��չϵ������
		double coeff[3] = { 0 }; // ������
		for (int i = 0; i < order + 1; i++) {
			for (int j = 0; j < order + 1; j++) {
				for (int k = 0; k < n; k++) {
					A[i][j] += pow(x[k], i + j); // ����ϵ�������Ԫ��
				}
			}
			for (int k = 0; k < n; k++) {
				A[i][order + 1] += pow(x[k], i) * y[k]; // ���㳣�������Ԫ��
			}
		}

		// ��˹��Ԫ��������Է�����
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

		double next_x = x.back() + 1; // Ԥ����һ��ʱ����xֵ
		double next_y = 0; // Ԥ����һ��ʱ����yֵ
		for (int i = 0; i < order + 1; i++) {
			next_y += coeff[i] * pow(next_x, i); // �������ʽ������ֵ
		}
		cout << "�������ƣ�" << cityName << endl;
		cout << "Ԥ����һ��ʱ�������в�������" << next_y << endl;
		this->predictCases = next_y;
	}

	// ���������Ϣ
	void print() {
		cout << "�������ƣ�" << cityName << endl;
		cout << "������������" << newCases << endl;
		cout << "���в�������" << currentCases << endl;
		cout << "�ۼƲ�������" << totalCases << endl;
		cout << "������������" << recoveredCases << endl;
		cout << "������������" << deathCases << endl;
		cout << "Ԥ�ⲡ������" << predictCases << endl << endl;
	}
};

// ����Country��
class Country {
private:
	vector<City> cities;

public:
	string countryName;
	// ���캯��
	Country(string name) {
		countryName = name;
	}

	// ��ȡ��������
	string getCountryName() {
		return countryName;
	}

	// ��ȡ�����б�
	vector<City>& getCities() {
		return cities;
	}

	// ��ӳ���
	void addCity(string countryName, string cityName, int newCases, int currentCases, int totalCases, int recoveredCases, int deathCases, int predictCases) {
		City city(cityName, newCases, currentCases, totalCases, recoveredCases, deathCases, predictCases);
		cities.push_back(city);
	}

	// ���³�����Ϣ
	void updateCity(string cityName, int newCases, int currentCases, int totalCases, int recoveredCases, int deathCases) {
		for (int i = 0; i < cities.size(); i++) {
			if (cities[i].getCityName() == cityName) {
				cities[i].update(newCases, currentCases, totalCases, recoveredCases, deathCases);
				return;
			}
		}
		cout << "�ó��в����ڣ�" << endl;
	}

	// ɾ������
	void deleteCity(string cityName) {
		for (int i = 0; i < cities.size(); i++) {
			if (cities[i].getCityName() == cityName) {
				cities.erase(cities.begin() + i);
				return;
			}
		}
		cout << "�ó��в����ڣ�" << endl;
	}

	// ����ȫ���������
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
		cout << "�������ƣ�" << countryName << endl;
		cout << "������������" << totalNewCases << endl;
		cout << "���в�������" << totalCurrentCases << endl;
		cout << "�ۼƲ�������" << totalTotalCases << endl;
		cout << "������������" << totalRecoveredCases << endl;
		cout << "������������" << totalDeathCases << endl;
	}

	// Ԥ�����鷢չ����
	void predictCases(string cityName) {
		for (int i = 0; i < cities.size(); i++) {
			if (cities[i].getCityName() == cityName) {
				cities[i].predict(this->countryName);
				return;
			}
		}
	}


	// ���������Ϣ
	void print() {
		cout << "�������ƣ�" << countryName << endl;
		for (int i = 0; i < cities.size(); i++) {
			cities[i].print();
		}
	}
};

// ���ļ��ж�ȡ������Ϣ
vector<Country> readFromFile() {
	vector<Country> countries;
	ifstream infile("data.txt");
	if (!infile) {
		cout << "�ļ������ڣ�" << endl;
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
// ��������Ϣд���ļ�
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
		cout << "                                                        ���������Ԥ��ϵͳ                                     " << endl;
		cout << "                                                        1. �鿴������Ϣ                                        "<< endl;
		cout << "                                                        2. ���³���������Ϣ                                    " << endl;
		cout << "                                                        3. ɾ������                                           " << endl;
		cout << "                                                        4. ��ӳ���                                            " << endl;
		cout << "                                                        5. ����ȫ���������                                     "<< endl;
		cout << "                                                        6. Ԥ�����鷢չ����                                      "<< endl;
		cout << "                                                        7. ͳ��                                                  " << endl;
		cout << "                                                        8. �˳�                                                  " << endl;
		cin >> choice;
		if (choice == 1) {
			for (int i = 0; i < countries.size(); i++) {
				countries[i].print();
			}
		}
		else if (choice == 2) {
			string countryName, cityName;
			int newCases, currentCases, totalCases, recoveredCases, deathCases;
			cout << "������������ƣ�";
			cin >> countryName;
			cout << "������������ƣ�";
			cin >> cityName;
			cout << "������������������";
			cin >> newCases;
			cout << "���������в�������";
			cin >> currentCases;
			cout << "�������ۼƲ�������";
			cin >> totalCases;
			cout << "������������������";
			cin >> recoveredCases;
			cout << "������������������";
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
				cout << "�ù��Ҳ����ڣ�" << endl;
			}
		}
		else if (choice == 3) {
			string countryName, cityName;
			cout << "������������ƣ�";
			cin >> countryName;
			cout << "������������ƣ�";
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
				cout << "�ù��Ҳ����ڣ�" << endl;
			}
		}
		else if (choice == 4) {
			string countryName, cityName;
			int newCases, currentCases, totalCases, recoveredCases, deathCases, predictCases;
			cout << "������������ƣ�";
			cin >> countryName;
			cout << "������������ƣ�";
			cin >> cityName;
			cout << "������������������";
			cin >> newCases;
			cout << "���������в�������";
			cin >> currentCases;
			cout << "�������ۼƲ�������";
			cin >> totalCases;
			cout << "������������������";
			cin >> recoveredCases;
			cout << "������������������";
			cin >> deathCases;
			cout << "������Ԥ�ⲡ������";
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
			cout << "������������ƣ�";
			cin >> countryName;
			cout << "������������ƣ�";
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
				cout << "�ó��в����ڣ�" << endl;
			}
		}
		else if (choice == 8) {
			writeToFile(countries);
			cout << "�������˳���������Ϣ�ѱ������ļ���" << endl;
			break;
		}
		else if (choice == 7) {
			int subchoice;
			cout << "��ѡ��ͳ�Ʒ�ʽ��" << endl;
			cout << "1. ����������������" << endl;
			cout << "2. �����в���������" << endl;
			cout << "3. ���ۼƲ���������" << endl;
			cout << "4. ����������������" << endl;
			cout << "5. ����������������" << endl;
			cout << "6. �����Ҳ鿴�ۼ���������" << endl;
			cin >> subchoice;
			if (subchoice == 1) {
				// ����������������
				vector<City> allCities; // �洢���г���
				for (int i = 0; i < countries.size(); i++) {
					vector<City> cities = countries[i].getCities();
					for (int j = 0; j < cities.size(); j++) {
						allCities.push_back(cities[j]);
					}
				}
				sort(allCities.begin(), allCities.end(), [](const City& a, const City& b) {return a.getNewCases() > b.getNewCases(); }); // ��������
				for (int i = 0; i < allCities.size(); i++) {
					allCities[i].print();
				}
			}
			else if (subchoice == 2) {
				// �����в���������
				vector<City> allCities; // �洢���г���
				for (int i = 0; i < countries.size(); i++) {
					vector<City> cities = countries[i].getCities();
					for (int j = 0; j < cities.size(); j++) {
						allCities.push_back(cities[j]);
					}
				}
				sort(allCities.begin(), allCities.end(), [](const City& a, const City& b) {return a.getCurrentCases() > b.getCurrentCases(); }); // ��������
				for (int i = 0; i < allCities.size(); i++) {
					allCities[i].print();
				}
			}
			else if (subchoice == 3) {
				// ���ۼƲ���������
				vector<City> allCities; // �洢���г���
				for (int i = 0; i < countries.size(); i++) {
					vector<City> cities = countries[i].getCities();
					for (int j = 0; j < cities.size(); j++) {
						allCities.push_back(cities[j]);
					}
				}
				sort(allCities.begin(), allCities.end(), [](const City& a, const City& b) {return a.getTotalCases() > b.getTotalCases(); }); // ��������
				for (int i = 0; i < allCities.size(); i++) {
					allCities[i].print();
				}
			}
			else if (subchoice == 4) {
				// ����������������
				vector<City> allCities; // �洢���г���
				for (int i = 0; i < countries.size(); i++) {
					vector<City> cities = countries[i].getCities();
					for (int j = 0; j < cities.size(); j++) {
						allCities.push_back(cities[j]);
					}
				}
				sort(allCities.begin(), allCities.end(), [](const City& a, const City& b) {return a.getRecoveredCases() > b.getRecoveredCases(); }); // ��������
				for (int i = 0; i < allCities.size(); i++) {
					allCities[i].print();
				}
			}
			else if (subchoice == 5) {
				// ����������������
				vector<City> allCities; // �洢���г���
				for (int i = 0; i < countries.size(); i++) {
					vector<City> cities = countries[i].getCities();
					for (int j = 0; j < cities.size(); j++) {
						allCities.push_back(cities[j]);
					}
				}
				sort(allCities.begin(), allCities.end(), [](const City& a, const City& b) {return a.getDeathCases() > b.getDeathCases(); }); // ��������
				for (int i = 0; i < allCities.size(); i++) {
					allCities[i].print();
				}
			}
			else if (subchoice == 6) {
				// �����Ҳ鿴�ۼ���������
				string countryName;
				cout << "������������ƣ�";
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
					cout << "�ù��Ҳ����ڣ�" << endl;
				}
			}
			else {
				cout << "��Ч���������������롣" << endl;
			}
		}


		system("pause");
		system("cls");
	}
	return 0;
}


// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�

