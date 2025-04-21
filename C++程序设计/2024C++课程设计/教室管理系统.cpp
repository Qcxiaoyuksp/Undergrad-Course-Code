#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
const string filename = "input.txt";
const string usersFile = "users.txt";

class Room {
public:
    string name;    // 教室名称
    int capacity;   // 教室容量

    // 重载小于号，用于排序
    bool operator<(const Room &other) const {
        return capacity < other.capacity;
    }
};

class User {
public:
    string username;
    string password;

    User(const string &username, const string &password) : username(username), password(password) {}
};

// 教室管理类
class RoomManager {
private:
    vector<Room> rooms; // 教室列表

public:
    // 构造函数
    RoomManager() {}

    // 添加教室
    void addRoom(const Room &room) {
        rooms.push_back(room);
    }

    // 按名称查找教室
    Room *findRoom(const string &name) {
        for (auto &room : rooms) {
            if (room.name == name) {
                return &room;
            }
        }
        return nullptr;
    }

    // 按容量排序
    void sortRoomsByCapacity() {
        sort(rooms.begin(), rooms.end());
    }

    // 删除教室
    void removeRoom(const string &name) {
        auto it = rooms.begin();
        for (; it != rooms.end(); it++) {
            if (it->name == name) {
                break;
            }
        }
        if (it == rooms.end()) {
            cout << "没有该教室" << endl;
        } else {
            rooms.erase(it);
            cout << "已删除该教室" << endl;
        }
    }

    // 显示教室列表
    void displayRooms() {
        for (auto &room : rooms) {
            cout << "名称：" << room.name << "，容量：" << room.capacity << endl;
        }
    }

    // 保存教室列表到文件
    void saveToFile(const string &filename) {
        ofstream ofs(filename);
        if (ofs) {
            for (auto &room : rooms) {
                ofs << room.name << "," << room.capacity << endl;
            }
            cout << "成功保存到文件 " << filename << "。" << endl;
        } else {
            cout << "保存文件 " << filename << " 失败。" << endl;
        }
    }

    // 从文件读入教室列表
    void readFromFile(const string &filename) {
        ifstream ifs(filename);
        if (ifs) {
            string line;
            while (getline(ifs, line)) {
                size_t comma_pos = line.find(",");
                if (comma_pos != string::npos) {
                    string name = line.substr(0, comma_pos);
                    int capacity = stoi(line.substr(comma_pos + 1));
                    rooms.push_back({name, capacity});
                }
            }
            cout << "文件 " << filename << " 读取成功。" << endl;
        } else {
            cout << "文件 " << filename << " 读取失败。" << endl;
        }
    }
};

// 登录界面
bool login() {
    system("cls");
    string username;
    string password;
    cout << "*******                                         请输入用户名：";
    cin >> username;
    cout << "*******                                           请输入密码：";
    cin >> password;
    // 读取用户信息
    ifstream ifs(usersFile);
    if (ifs) {
        string line;
        while (getline(ifs, line)) {
            size_t comma_pos = line.find(",");
            if (comma_pos != string::npos) {
                string stored_username = line.substr(0, comma_pos);
                string stored_password = line.substr(comma_pos + 1);
                if (stored_username == username && stored_password == password) {
                    return true;
                }
            }
        }
        return false;
    } else {
        cout << "读取用户信息失败。" << endl;
        return false;
    }
}

// 注册新用户
void registerUser() {
    system("cls");
    string username;
    string password;
    cout << "*******                                         请输入用户名：";
    cin >> username;
    cout << "*******                                           请输入密码：";
    cin >> password;
    // 保存用户信息
    ofstream ofs(usersFile, ios::app);
    if (ofs) {
        ofs << username << "," << password << endl;
        cout << "注册成功！" << endl;
    } else {
        cout << "保存用户信息失败。" << endl;
    }
}

// 显示菜单
void displayMenu() {
    system("cls");
    cout<<"                                           ▁▁▂▂▃▃▅▅▆▆▇▇▇▇▇▇▆▆▅▅▃▃▂▂▁▁"<<endl;
    cout << "<<<<<<----------------------------------------欢迎来到教室管理系统--------------------------------------------->>>>>>>>" << endl;
    cout << "*******                                            1. 添加教室                                                ********" << endl;
    cout << "*******                                            2. 删除教室                                                ********" << endl;
    cout << "*******                                            3. 查找教室                                                ********" << endl;
    cout << "*******                                            4. 按容量排序教室                                          ********" << endl;
    cout << "*******                                            5. 显示教室列表                                            ********" << endl;
    cout << "*******                                            0. 退出                                                    ********" << endl;
    cout << "<<<<<<-------------------------------------------------------------------------------------------------------->>>>>>>>" << endl;
}

int main() {
    RoomManager roomManager;
    system("COLOR f0");  //此处大写，设置为白底黑字 
    roomManager.readFromFile(filename);
    system("pause");
    cout << "按任意按钮继续" << endl;

    while (true) {
    	system("cls");
        int choice;
        cout<<endl; 
        cout << "*******                                            1. 登录                                                    ********" << endl;
        cout << "*******                                            2. 注册                                                    ********" << endl;
        cout << "*******                                            0. 退出                                                    ********" << endl;
        cin >> choice;

        switch (choice) {
            case 1: {
                if (login()) {
                    system("cls");
                    cout << "登录成功！" << endl;
                    system("pause");
                    bool exitFlag = false;
                    while (!exitFlag) {
                        displayMenu();
                        cin >> choice;
                        switch (choice) {
                            case 1: {
                                system("cls");
                                cout << "<<<<<<----------------------------------------请添加新的教室信息----------------------------------------------->>>>>>>>" << endl;
                                cout << "*******                                            请输入教室名称：";
                                string name;
                                cin >> name;
                                cout << "*******                                            请输入教室容量：";
                                int capacity;
                                cin >> capacity;
                                Room room{name, capacity};
                                roomManager.addRoom(room);
                                roomManager.saveToFile(filename);
                                cout << "添加成功！" << endl;
                                system("pause");
                                break;
                            }
                            case 2: {
                                system("cls");
                                cout << "<<<<<<----------------------------------------请删除教室信息----------------------------------------------->>>>>>>>" << endl;
                                cout << "*******                                            请输入教室名称：";
                                string name;
                                cin >> name;
                                roomManager.removeRoom(name);
                                roomManager.saveToFile(filename);
                                system("pause");
                                break;
                            }
                            case 3: {
                                system("cls");
                                cout << "<<<<<<----------------------------------------请查找教室信息----------------------------------------------->>>>>>>>" << endl;
                                cout << "*******                                            请输入教室名称：";
                                string name;
                                cin >> name;
                                Room *room = roomManager.findRoom(name);
                                if (room) {
                                    cout << "名称：" << room->name << "，容量：" << room->capacity << endl;
                                } else {
                                    cout << "未找到该教室" << endl;
                                }
                                system("pause");
                                break;
                            }
                            case 4: {
                                system("cls");
                                roomManager.sortRoomsByCapacity();
                                roomManager.displayRooms();
                                system("pause");
                                break;
                            }
                            case 5: {
                                system("cls");
                                roomManager.displayRooms();
                                system("pause");
                                break;
                            }
                            case 0: {
                                exitFlag = true;
                                break;
                            }
                            default:
                                cout << "无效的选项" << endl;
                                break;
                        }
                    }
                } else {
                    cout << "登录失败！请检查用户名和密码。" << endl;
                    system("pause");
                }
                break;
            }
            case 2: {
                registerUser();
                system("pause");
                break;
            }
            case 0: {
            	system("cls");
            	cout<<endl; 
                cout << "<<<<<<---------------------------------------------欢迎下次光临---------------------------------------------->>>>>>>>" << endl;
                cout<<endl;                return 0;
            }
            default:
                cout << "无效的选项" << endl;
                break;
        }
    }
}

