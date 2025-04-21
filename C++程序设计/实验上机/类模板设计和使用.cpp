#include <iostream>
using namespace std;
template<class T>
class LinkStack
{
private:
	struct Node // 定义链表节点结构体
	{
		T data; // 节点存储的数据
		Node* next; // 指向下一个节点的指针
		Node(const T& d = T(), Node* n = nullptr) : data(d), next(n) {}
	};
	Node* top; // 栈顶指针
public:
	LinkStack(); // 构造函数
	~LinkStack(); // 析构函数
	bool IsEmpty() const; // 判断栈是否为空
	void Push(const T& x); // 入栈操作
	T Pop(); // 出栈操作
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

