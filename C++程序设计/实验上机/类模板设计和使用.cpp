#include <iostream>
using namespace std;
template<class T>
class LinkStack
{
private:
	struct Node // ��������ڵ�ṹ��
	{
		T data; // �ڵ�洢������
		Node* next; // ָ����һ���ڵ��ָ��
		Node(const T& d = T(), Node* n = nullptr) : data(d), next(n) {}
	};
	Node* top; // ջ��ָ��
public:
	LinkStack(); // ���캯��
	~LinkStack(); // ��������
	bool IsEmpty() const; // �ж�ջ�Ƿ�Ϊ��
	void Push(const T& x); // ��ջ����
	T Pop(); // ��ջ����
};

template<class T>
LinkStack<T>::LinkStack() : top(nullptr) {}

template<class T>
LinkStack<T>::~LinkStack()
{
	if (top != nullptr) {
		Node* p;
		p = top;
		top = top->next;
		delete p;
	}
}

template<class T>
bool LinkStack<T>::IsEmpty() const
{
	return top == nullptr;
}

template<class T>
void LinkStack<T>::Push(const T& x)
{
	Node* p;
	p = new Node;
	p->data = x;
	if (top) p->next = top;
	top = p;
}

template<class T>
T LinkStack<T>::Pop()
{
	Node* p;
	T i;
	i = top->data;
	p = top;
	top = top->next;
	delete p;
	return i;
}

int main()
{
	LinkStack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	while (!s.IsEmpty())
	{
		cout << s.Pop() << " ";
	}
	cout << endl;
	LinkStack<char> m;
	m.Push('a');
	m.Push('b');
	m.Push('c');
	while (!m.IsEmpty())
	{
		cout << m.Pop() << " ";
	}
	cout << endl;
	return 0;
}

