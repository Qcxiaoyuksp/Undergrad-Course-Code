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

// 定义产品类
class Product 
{
public:
    int id; // 产品ID
    double x1, x2;
    string color;
    int x3,price;// 产品属性
};

// 定义模型
class Model 
{
public:
    double a0, a1, a2; // 模型参数
};

// 读取产品数据
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

// 写入结果到文件
void writeResultToFile(const string& result)
{
    ofstream file(DATA_FILE, ios::app);
    if (file.is_open()) 
    {
        file << result << endl;
        file.close();
    }
}

// 构建模型
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

// 检查产品是否合格
bool checkProduct(const Product& product, const Model& model) 
{
    double y = model.a0 + model.a1 * product.x1 + model.a2 * product.x2;
    return y >= 0;
}

// 计算误差率
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
    vector<Product> products; // 存储产品数据
    Model model = { 0, 0, 0 }; // 存储模型参数

    while (true) 
    {
        // 输出菜单
        cout << "欢迎来到产品分析程序，请输入您的选择：" << endl;
        cout << "1. 从文件中读取产品数据" << endl;
        cout << "2. 添加产品数据" << endl;
        cout << "3. 显示产品数据" << endl;
        cout << "4. 修改或删除产品数据" << endl;
        cout << "5. 构建模型" << endl;
        cout << "6. 检查产品是否合格" << endl;
        cout << "7. 计算误差率" << endl;
        cout << "8. 显示所有不合格的产品" << endl;
        cout << "9. 退出程序" << endl;
        int operation;
        cin >> operation;

        if (operation == 1)
        {
            products = readProductsFromFile(DATA_FILE);
            cout << "已读取 " << products.size() << " 条产品数据。" << endl;
        }
        else if (operation == 2)
        {
            Product product;
            cout << "请输入产品ID：";
            cin >> product.id;
            cout << "请输入产品属性 x1, x2, 颜色, 价格：";
            cin >> product.x1 >> product.x2 >>product.color >> product.price;
            product.x3 =checkProduct(product, model);
            products.push_back(product);
            cout << "已添加产品。" << endl;
            ofstream outfile("data.txt", ios::app); // 打开文件，ios::app为以附加模式打开
            if (!outfile.is_open())
            {
                cerr << "无法打开文件！" << endl;
                return 1;
            }
            outfile << product.id << ' ' << product.x1 << ' ' << product.x2 << ' '<<product.x3<<' '
                << product.color << ' ' << product.price << endl; // 写入数据
            outfile.close(); // 关闭文件

        }

       
        else if (operation == 3)
        {
            if (products.empty())
            {
                cout << "没有产品数据。" << endl;
            }
            else 
            {
                cout << "产品ID\t  属性 x1\t  属性 x2\t属性 颜色\t属性 价格" << endl;
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
                cout << "没有产品数据。" << endl;
            }
            else
            {
                int id;
                cout << "请输入要修改或删除的产品ID：";
                cin >> id;
                auto it = find_if(products.begin(), products.end(),
                    [id](const Product& p) {return p.id == id;});
                if (it == products.end()) 
                {
                    cout << "没有找到该产品。" << endl;
                    continue;
                }
                cout << "请选择操作：" << endl;
                cout << "1. 删除产品" << endl;
                cout << "2. 修改产品" << endl;
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
                        cout << "已删除产品。" << endl;
                    }

                }
                else if (subOperation == 2)
                {
                    cout << "请输入新的产品ID：";
                    cin >> it->id;
                    cout << "请输入新的属性 x1, x2,颜色, 价格：";
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
                        cout << "已修改产品。" << endl;
                    }
                }
            }
        }

        else if (operation == 5) 
        {
            if (products.size() < 3) 
            {
                cout << "至少需要3条产品数据才能构建模型。" << endl;
            }
            else 
            {
                model = buildModel(products);
                cout << "已构建模型：" <<"y="<< model.a0 << " + " << model.a1 << "x1 + " << model.a2 << "x2" << endl;
            }
        }
        else if (operation == 6) 
        {
            if (model.a0 == 0 && model.a1 == 0 && model.a2 == 0) 
            {
                cout << "请先构建模型。" << endl;
            }
            else {
                int id;
                cout << "请输入要检查的产品ID：";
                cin >> id;
                auto it = find_if(products.begin(), products.end(),
                    [id](const Product& p) {return p.id == id;});
                if (it == products.end()) 
                {
                    cout << "没有找到该产品。" << endl;
                }
                else 
                {
                    bool result = checkProduct(*it, model);
                    if (result) 
                    {
                        cout << "该产品合格。" << endl;
                    }
                    else 
                    {
                        cout << "该产品不合格。" << endl;
                    }
                }
            }
        }
        else if (operation == 7) 
        {
            if (model.a0 == 0 && model.a1 == 0 && model.a2 == 0) 
            {
                cout << "请先构建模型。" << endl;
            }
            else
            {
                double errorRate = calculateErrorRate(products, model);
                cout << "误差率为：" << errorRate <<'%'<<endl;
            }
        }
        else if (operation == 8) 
        {
            if (model.a0 == 0 && model.a1 == 0 && model.a2 == 0) 
            {
                cout << "请先构建模型。" << endl;
            }
            else 
            {
                cout << "不合格的产品ID：" << endl;
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
            cout << "无效的操作。" << endl;
        }
    }

    return 0;
}
