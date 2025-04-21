//#include <iostream>
//#include <string>
//
//using namespace std;
//
//// ���岡����Ϣ��
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
//// ���嵥������
//class PatientList {
//public:
//    Patient *head;
//
//    PatientList() {
//        head = nullptr;
//    }
//
//    // �ڵ�����������һ��Ԫ��
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
//    // ɾ��������ĵ�һ��Ԫ��
//    void dequeue() {
//        if (head != nullptr) {
//            Patient *temp = head;
//            head = head->next;
//            delete temp;
//        }
//        else{
//        	cout << "û��Ԫ��" << endl; 
//        	cout << endl;
//		}
//    }
//
//    // ���������һ���
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
//    // ��ʾ���л�����Ϣ
//    void display() {
//        Patient *current = head;
//        while (current != nullptr) {
//            cout << "������" << current->name << "���Ա�" << current->gender << "�����䣺" << current->age << endl;
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
//        cout << "ҽԺ�Ŷӿ���ϵͳ" << endl;
//        cout << "1. ��ӻ���" << endl;
//        cout << "2. ɾ����һ������" << endl;
//        cout << "3. ���һ���" << endl;
//        cout << "4. ��ʾ���л���" << endl;
//        cout << "5. �˳�" << endl;
//        cout << "��ѡ�������";
//        cin >> choice;
//
//        switch (choice) 
//		{
//            case 1:{
//            	cout << "���뻼��������";
//                cin >> name;
//                cout << "���뻼���Ա�";
//                cin >> gender;
//                cout << "���뻼�����䣺";
//                cin >> age;
//                patientList.enqueue(new Patient(name, gender, age));
//				break;
//			}
//            case 2:{
//            	patientList.dequeue();
//				break;
//			}
//            case 3:{
//            	cout << "����Ҫ���ҵĻ���������";
//                cin >> name;
//                Patient *found = patientList.find(name);
//                if (found != nullptr) {
//                    cout << "�ҵ����ߣ�" << found->name << "���Ա�" << found->gender << "�����䣺" << found->age << endl;
//                } else {
//                    cout << "δ�ҵ����ߡ�" << endl;
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
//            	cout << "��Чѡ�����������롣" << endl;
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

// ���˽ṹ��
struct Patient {
    string name;
    string condition;
    int waitTime;
};

// ����ڵ�ṹ��
struct ListNode {
    Patient* patient;
    ListNode* next;
};

// ������
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
