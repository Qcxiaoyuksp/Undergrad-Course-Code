//#include <iostream>
//#include <string>
//
//using namespace std;
//
//// 定义病人信息类
//class Patient {
//public:
//    string name;
//    string gender;
//    int age;
//    Patient *next;
//
//    Patient(string name, string gender, int age) {
//        this->name = name;
//        this->gender = gender;
//        this->age = age;
//        this->next = nullptr;
//    }
//};
//
//// 定义单链表类
//class PatientList {
//public:
//    Patient *head;
//
//    PatientList() {
//        head = nullptr;
//    }
//
//    // 在单链表后面插入一个元素
//    void enqueue(Patient *patient) {
//        if (head == nullptr) {
//            head = patient;
//        } else {
//            Patient *current = head;
//            while (current->next != nullptr) {
//                current = current->next;
//            }
//            current->next = patient;
//        }
//    }
//
//    // 删除单链表的第一个元素
//    void dequeue() {
//        if (head != nullptr) {
//            Patient *temp = head;
//            head = head->next;
//            delete temp;
//        }
//        else{
//        	cout << "没有元素" << endl; 
//        	cout << endl;
//		}
//    }
//
//    // 按姓名查找患者
//    Patient* find(string name) {
//        Patient *current = head;
//        while (current != nullptr) {
//            if (current->name == name) {
//                return current;
//            }
//            current = current->next;
//        }
//        return nullptr;
//    }
//
//    // 显示所有患者信息
//    void display() {
//        Patient *current = head;
//        while (current != nullptr) {
//            cout << "姓名：" << current->name << "，性别：" << current->gender << "，年龄：" << current->age << endl;
//            current = current->next;
//        }
//    }
//};
//
//int main() {
//    PatientList patientList;
//    int choice;
//    string name, gender;
//    int age;
//
//    while (true) {
//        cout << "医院排队看病系统" << endl;
//        cout << "1. 添加患者" << endl;
//        cout << "2. 删除下一个患者" << endl;
//        cout << "3. 查找患者" << endl;
//        cout << "4. 显示所有患者" << endl;
//        cout << "5. 退出" << endl;
//        cout << "请选择操作：";
//        cin >> choice;
//
//        switch (choice) 
//		{
//            case 1:{
//            	cout << "输入患者姓名：";
//                cin >> name;
//                cout << "输入患者性别：";
//                cin >> gender;
//                cout << "输入患者年龄：";
//                cin >> age;
//                patientList.enqueue(new Patient(name, gender, age));
//				break;
//			}
//            case 2:{
//            	patientList.dequeue();
//				break;
//			}
//            case 3:{
//            	cout << "输入要查找的患者姓名：";
//                cin >> name;
//                Patient *found = patientList.find(name);
//                if (found != nullptr) {
//                    cout << "找到患者：" << found->name << "，性别：" << found->gender << "，年龄：" << found->age << endl;
//                } else {
//                    cout << "未找到患者。" << endl;
//                }
//				break;
//			}
//            case 4:{
//            	patientList.display();
//				break;
//			}
//            case 5:{
//            	return 0;
//				break;
//			}
//            default:{
//            	cout << "无效选择，请重新输入。" << endl;
//				break;
//			}
//        }
//    }
//
//    return 0;
//}

#include <iostream>
#include <string>

using namespace std;

// 病人结构体
struct Patient {
    string name;
    string condition;
    int waitTime;
};

// 链表节点结构体
struct ListNode {
    Patient* patient;
    ListNode* next;
};

// 链表类
class LinkedList {
public:
    LinkedList() {
        head = nullptr;
        length = 0;
    }

    ~LinkedList() {
        ListNode* p = head;
        while (p != nullptr) {
            ListNode* temp = p;
            p = p->next;
            delete temp->patient;
            delete temp;
        }
    }

    void addPatient(Patient* patient) {
        ListNode* newNode = new ListNode();
        newNode->patient = patient;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
        } else {
            ListNode* p = head;
            while (p->next != nullptr) {
                p = p->next;
            }
            p->next = newNode;
        }
        length++;
    }

    Patient* removePatient() {
        if (head == nullptr) {
            return nullptr;
        }
        ListNode* temp = head;
        head = head->next;
        Patient* patient = temp->patient;
        delete temp;
        length--;
        return patient;
    }

    int getLength() {
        return length;
    }

    Patient* getPatient(int index) {
        if (index < 0 || index >= length) {
            return nullptr;
        }
        ListNode* p = head;
        for (int i = 0; i < index; i++) {
            p = p->next;
        }
        return p->patient;
    }

    void printPatients() {
        ListNode* p = head;
        while (p != nullptr) {
            cout << "Name: " << p->patient->name << ", Condition: " << p->patient->condition << ", Wait Time: " << p->patient->waitTime << endl;
            p = p->next;
        }
    }

private:
    ListNode* head;
    int length;
};

int main() {
    LinkedList queue;

    while (true) {
        cout << "Enter command (add, remove, length, show, exit): ";
        string command;
        cin >> command;

        if (command == "add") {
            cout << "Enter name: ";
            string name;
            cin >> name;
            cout << "Enter condition: ";
            string condition;
            cin >> condition;
            Patient* patient = new Patient();
            patient->name = name;
            patient->condition = condition;
            patient->waitTime = queue.getLength();
            queue.addPatient(patient);
        } else if (command == "remove") {
            Patient* patient = queue.removePatient();
            if (patient == nullptr) {
                cout << "Queue is empty" << endl;
            } else {
                cout << "Name: " << patient->name << ", Condition: " << patient->condition << ", Wait Time: " << patient->waitTime << endl;
                delete patient;
            }
        } else if (command == "length") {
            cout << "Queue length: " << queue.getLength() << endl;
        } else if (command == "show") {
            queue.printPatients();
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
