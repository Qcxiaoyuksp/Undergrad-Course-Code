#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm> 
#include<sstream>
using namespace std;
const string DATA_FILE = "data.txt";

// �����Ʒ��
class Product 
{
public:
    int id; // ��ƷID
    double x1, x2;
    string color;
    int x3,price;// ��Ʒ����
};

// ����ģ��
class Model 
{
public:
    double a0, a1, a2; // ģ�Ͳ���
};

// ��ȡ��Ʒ����
vector<Product> readProductsFromFile(const string& filename)
{
    vector<Product> products;
    ifstream file(filename);
    if (file.is_open()) {
        Product product;
        while (file >> product.id >> product.x1 >> product.x2 >>product.x3>>product.color>>product.price) 
        {
            products.push_back(product);
        }
        file.close();
    }
    return products;
}

// д�������ļ�
void writeResultToFile(const string& result)
{
    ofstream file(DATA_FILE, ios::app);
    if (file.is_open()) 
    {
        file << result << endl;
        file.close();
    }
}

// ����ģ��
Model buildModel(const vector<Product>& products)
{
    double sumX1 = 0, sumX2 = 0, sumY = 0, sumX1Y = 0, sumX2Y = 0;
    for (const auto& product : products)
    {
        sumX1 += product.x1;
        sumX2 += product.x2;
        sumY += product.x3;
        sumX1Y += product.x1 * product.x3;
        sumX2Y += product.x2 * product.x3;
    }
    double n = products.size();
    double a1 = (n * sumX1Y - sumX1 * sumY) / (n * sumX1 * sumX1 - sumX1 * sumX1);
    double a2 = (n * sumX2Y - sumX2 * sumY) / (n * sumX2 * sumX2 - sumX2 * sumX2);
    double a0 = (sumY - a1 * sumX1 - a2 * sumX2) / n;
    return { a0, a1, a2 };
}

// ����Ʒ�Ƿ�ϸ�
bool checkProduct(const Product& product, const Model& model) 
{
    double y = model.a0 + model.a1 * product.x1 + model.a2 * product.x2;
    return y >= 0;
}

// ���������
double calculateErrorRate(const vector<Product>& products, const Model& model) {
    double errorSum = 0, ySum = 0;
    for (const auto& product : products) 
    {
        double y = model.a0 + model.a1 * product.x1 + model.a2 * product.x2;
        errorSum += abs(y - product.x3);
        ySum += product.x3;
    }
    double meanY = ySum / products.size();
    return errorSum / (products.size() * meanY);
}

int main() 
{
    vector<Product> products; // �洢��Ʒ����
    Model model = { 0, 0, 0 }; // �洢ģ�Ͳ���

    while (true) 
    {
        // ����˵�
        cout << "��ӭ������Ʒ������������������ѡ��" << endl;
        cout << "1. ���ļ��ж�ȡ��Ʒ����" << endl;
        cout << "2. ��Ӳ�Ʒ����" << endl;
        cout << "3. ��ʾ��Ʒ����" << endl;
        cout << "4. �޸Ļ�ɾ����Ʒ����" << endl;
        cout << "5. ����ģ��" << endl;
        cout << "6. ����Ʒ�Ƿ�ϸ�" << endl;
        cout << "7. ���������" << endl;
        cout << "8. ��ʾ���в��ϸ�Ĳ�Ʒ" << endl;
        cout << "9. �˳�����" << endl;
        int operation;
        cin >> operation;

        if (operation == 1)
        {
            products = readProductsFromFile(DATA_FILE);
            cout << "�Ѷ�ȡ " << products.size() << " ����Ʒ���ݡ�" << endl;
        }
        else if (operation == 2)
        {
            Product product;
            cout << "�������ƷID��";
            cin >> product.id;
            cout << "�������Ʒ���� x1, x2, ��ɫ, �۸�";
            cin >> product.x1 >> product.x2 >>product.color >> product.price;
            product.x3 =checkProduct(product, model);
            products.push_back(product);
            cout << "����Ӳ�Ʒ��" << endl;
            ofstream outfile("data.txt", ios::app); // ���ļ���ios::appΪ�Ը���ģʽ��
            if (!outfile.is_open())
            {
                cerr << "�޷����ļ���" << endl;
                return 1;
            }
            outfile << product.id << ' ' << product.x1 << ' ' << product.x2 << ' '<<product.x3<<' '
                << product.color << ' ' << product.price << endl; // д������
            outfile.close(); // �ر��ļ�

        }

       
        else if (operation == 3)
        {
            if (products.empty())
            {
                cout << "û�в�Ʒ���ݡ�" << endl;
            }
            else 
            {
                cout << "��ƷID\t  ���� x1\t  ���� x2\t���� ��ɫ\t���� �۸�" << endl;
                for (const auto& product : products)
                {
                    cout << product.id << "\t" << product.x1 << "\t" << product.x2
                        << "\t" << product.color << "\t" << "\t"<<product.price << endl;
                }
            }
        }
        else if (operation == 4) 
        {
            if (products.empty())
            {
                cout << "û�в�Ʒ���ݡ�" << endl;
            }
            else
            {
                int id;
                cout << "������Ҫ�޸Ļ�ɾ���Ĳ�ƷID��";
                cin >> id;
                auto it = find_if(products.begin(), products.end(),
                    [id](const Product& p) {return p.id == id;});
                if (it == products.end()) 
                {
                    cout << "û���ҵ��ò�Ʒ��" << endl;
                    continue;
                }
                cout << "��ѡ�������" << endl;
                cout << "1. ɾ����Ʒ" << endl;
                cout << "2. �޸Ĳ�Ʒ" << endl;
                int subOperation;
                cin >> subOperation;
                if (subOperation == 1)
                {
                    products.erase(remove_if(products.begin(), products.end(),
                        [id](const Product& p) {return p.id == id;}), products.end());
                    ofstream out("data.txt");
                    if (out)
                    {
                        for (const auto& p : products) 
                        {
                            out << p.id << " " << p.x1 << " " << p.x2 << " " <<p.x3<<" " << p.color << " " << p.price << endl;
                        }
                        out.close();
                        cout << "��ɾ����Ʒ��" << endl;
                    }

                }
                else if (subOperation == 2)
                {
                    cout << "�������µĲ�ƷID��";
                    cin >> it->id;
                    cout << "�������µ����� x1, x2,��ɫ, �۸�";
                    cin >> it->x1 >> it->x2 >> it->color >> it->price;
                    it->x3 = checkProduct(*it,model);
                    ofstream out("data.txt");
                    if (out) 
                    {
                        for (const auto& p : products) 
                        {
                            out << p.id << " " << p.x1 << " " << p.x2 << " " << p.color<< " " << p.price << endl;
                        }
                        out.close();
                        cout << "���޸Ĳ�Ʒ��" << endl;
                    }
                }
            }
        }

        else if (operation == 5) 
        {
            if (products.size() < 3) 
            {
                cout << "������Ҫ3����Ʒ���ݲ��ܹ���ģ�͡�" << endl;
            }
            else 
            {
                model = buildModel(products);
                cout << "�ѹ���ģ�ͣ�" <<"y="<< model.a0 << " + " << model.a1 << "x1 + " << model.a2 << "x2" << endl;
            }
        }
        else if (operation == 6) 
        {
            if (model.a0 == 0 && model.a1 == 0 && model.a2 == 0) 
            {
                cout << "���ȹ���ģ�͡�" << endl;
            }
            else {
                int id;
                cout << "������Ҫ���Ĳ�ƷID��";
                cin >> id;
                auto it = find_if(products.begin(), products.end(),
                    [id](const Product& p) {return p.id == id;});
                if (it == products.end()) 
                {
                    cout << "û���ҵ��ò�Ʒ��" << endl;
                }
                else 
                {
                    bool result = checkProduct(*it, model);
                    if (result) 
                    {
                        cout << "�ò�Ʒ�ϸ�" << endl;
                    }
                    else 
                    {
                        cout << "�ò�Ʒ���ϸ�" << endl;
                    }
                }
            }
        }
        else if (operation == 7) 
        {
            if (model.a0 == 0 && model.a1 == 0 && model.a2 == 0) 
            {
                cout << "���ȹ���ģ�͡�" << endl;
            }
            else
            {
                double errorRate = calculateErrorRate(products, model);
                cout << "�����Ϊ��" << errorRate <<'%'<<endl;
            }
        }
        else if (operation == 8) 
        {
            if (model.a0 == 0 && model.a1 == 0 && model.a2 == 0) 
            {
                cout << "���ȹ���ģ�͡�" << endl;
            }
            else 
            {
                cout << "���ϸ�Ĳ�ƷID��" << endl;
                for (const auto& product : products) 
                {
                    if (!checkProduct(product, model)) 
                    {
                        cout << product.id << endl;
                    }
                }
            }
        }
        else if (operation == 9)
        {
            break;
        }
        else
        {
            cout << "��Ч�Ĳ�����" << endl;
        }
    }

    return 0;
}
