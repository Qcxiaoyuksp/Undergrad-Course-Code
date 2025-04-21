#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
const string filename = "input.txt";
const string usersFile = "users.txt";

class Room {
public:
    string name;    // ��������
    int capacity;   // ��������

    // ����С�ںţ���������
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

// ���ҹ�����
class RoomManager {
private:
    vector<Room> rooms; // �����б�

public:
    // ���캯��
    RoomManager() {}

    // ��ӽ���
    void addRoom(const Room &room) {
        rooms.push_back(room);
    }

    // �����Ʋ��ҽ���
    Room *findRoom(const string &name) {
        for (auto &room : rooms) {
            if (room.name == name) {
                return &room;
            }
        }
        return nullptr;
    }

    // ����������
    void sortRoomsByCapacity() {
        sort(rooms.begin(), rooms.end());
    }

    // ɾ������
    void removeRoom(const string &name) {
        auto it = rooms.begin();
        for (; it != rooms.end(); it++) {
            if (it->name == name) {
                break;
            }
        }
        if (it == rooms.end()) {
            cout << "û�иý���" << endl;
        } else {
            rooms.erase(it);
            cout << "��ɾ���ý���" << endl;
        }
    }

    // ��ʾ�����б�
    void displayRooms() {
        for (auto &room : rooms) {
            cout << "���ƣ�" << room.name << "��������" << room.capacity << endl;
        }
    }

    // ��������б��ļ�
    void saveToFile(const string &filename) {
        ofstream ofs(filename);
        if (ofs) {
            for (auto &room : rooms) {
                ofs << room.name << "," << room.capacity << endl;
            }
            cout << "�ɹ����浽�ļ� " << filename << "��" << endl;
        } else {
            cout << "�����ļ� " << filename << " ʧ�ܡ�" << endl;
        }
    }

    // ���ļ���������б�
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
            cout << "�ļ� " << filename << " ��ȡ�ɹ���" << endl;
        } else {
            cout << "�ļ� " << filename << " ��ȡʧ�ܡ�" << endl;
        }
    }
};

// ��¼����
bool login() {
    system("cls");
    string username;
    string password;
    cout << "*******                                         �������û�����";
    cin >> username;
    cout << "*******                                           ���������룺";
    cin >> password;
    // ��ȡ�û���Ϣ
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
        cout << "��ȡ�û���Ϣʧ�ܡ�" << endl;
        return false;
    }
}

// ע�����û�
void registerUser() {
    system("cls");
    string username;
    string password;
    cout << "*******                                         �������û�����";
    cin >> username;
    cout << "*******                                           ���������룺";
    cin >> password;
    // �����û���Ϣ
    ofstream ofs(usersFile, ios::app);
    if (ofs) {
        ofs << username << "," << password << endl;
        cout << "ע��ɹ���" << endl;
    } else {
        cout << "�����û���Ϣʧ�ܡ�" << endl;
    }
}

// ��ʾ�˵�
void displayMenu() {
    system("cls");
    cout<<"                                           �x�x�y�y�z�z�|�|�}�}�~�~�~�~�~�~�}�}�|�|�z�z�y�y�x�x"<<endl;
    cout << "<<<<<<----------------------------------------��ӭ�������ҹ���ϵͳ--------------------------------------------->>>>>>>>" << endl;
    cout << "*******                                            1. ��ӽ���                                                ********" << endl;
    cout << "*******                                            2. ɾ������                                                ********" << endl;
    cout << "*******                                            3. ���ҽ���                                                ********" << endl;
    cout << "*******                                            4. �������������                                          ********" << endl;
    cout << "*******                                            5. ��ʾ�����б�                                            ********" << endl;
    cout << "*******                                            0. �˳�                                                    ********" << endl;
    cout << "<<<<<<-------------------------------------------------------------------------------------------------------->>>>>>>>" << endl;
}

int main() {
    RoomManager roomManager;
    system("COLOR f0");  //�˴���д������Ϊ�׵׺��� 
    roomManager.readFromFile(filename);
    system("pause");
    cout << "�����ⰴť����" << endl;

    while (true) {
    	system("cls");
        int choice;
        cout<<endl; 
        cout << "*******                                            1. ��¼                                                    ********" << endl;
        cout << "*******                                            2. ע��                                                    ********" << endl;
        cout << "*******                                            0. �˳�                                                    ********" << endl;
        cin >> choice;

        switch (choice) {
            case 1: {
                if (login()) {
                    system("cls");
                    cout << "��¼�ɹ���" << endl;
                    system("pause");
                    bool exitFlag = false;
                    while (!exitFlag) {
                        displayMenu();
                        cin >> choice;
                        switch (choice) {
                            case 1: {
                                system("cls");
                                cout << "<<<<<<----------------------------------------������µĽ�����Ϣ----------------------------------------------->>>>>>>>" << endl;
                                cout << "*******                                            ������������ƣ�";
                                string name;
                                cin >> name;
                                cout << "*******                                            ���������������";
                                int capacity;
                                cin >> capacity;
                                Room room{name, capacity};
                                roomManager.addRoom(room);
                                roomManager.saveToFile(filename);
                                cout << "��ӳɹ���" << endl;
                                system("pause");
                                break;
                            }
                            case 2: {
                                system("cls");
                                cout << "<<<<<<----------------------------------------��ɾ��������Ϣ----------------------------------------------->>>>>>>>" << endl;
                                cout << "*******                                            ������������ƣ�";
                                string name;
                                cin >> name;
                                roomManager.removeRoom(name);
                                roomManager.saveToFile(filename);
                                system("pause");
                                break;
                            }
                            case 3: {
                                system("cls");
                                cout << "<<<<<<----------------------------------------����ҽ�����Ϣ----------------------------------------------->>>>>>>>" << endl;
                                cout << "*******                                            ������������ƣ�";
                                string name;
                                cin >> name;
                                Room *room = roomManager.findRoom(name);
                                if (room) {
                                    cout << "���ƣ�" << room->name << "��������" << room->capacity << endl;
                                } else {
                                    cout << "δ�ҵ��ý���" << endl;
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
                                cout << "��Ч��ѡ��" << endl;
                                break;
                        }
                    }
                } else {
                    cout << "��¼ʧ�ܣ������û��������롣" << endl;
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
                cout << "<<<<<<---------------------------------------------��ӭ�´ι���---------------------------------------------->>>>>>>>" << endl;
                cout<<endl;                return 0;
            }
            default:
                cout << "��Ч��ѡ��" << endl;
                break;
        }
    }
}

