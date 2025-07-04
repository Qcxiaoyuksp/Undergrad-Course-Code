/*exp6-1 maxLoadingBB MaxLoading,分支限界法*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<queue>

using namespace std;


template<class Type>
class QNode
{
	template<class T>
	friend Type MaxLoading(Type*, Type, int, int*);
	template<class U>
	friend void EnQueue(queue<QNode<Type>*>& Q, Type wt, int i, int n, Type bestw, QNode<Type>* E, QNode<Type>* &bestE, int* bestx, bool ch);
public:
	QNode* parent;
	bool LChind;
	Type weight;
};

template<class Type>
void EnQueue(queue<QNode<Type>*>& Q, Type wt, int i, int n, Type bestw, QNode<Type>* E, QNode<Type>* &bestE, int* bestx, bool ch)
{
	if (i == n)
	{
		if (wt == bestw)
		{
			bestE = E;
			bestx[n] = ch;
		}
		return;
	}
	QNode<Type>* b;
	b = new QNode<Type>;
	b->weight = wt;
	b->parent = E;
	b->LChind = ch;
	Q.push(b);
}

template<class Type>
Type MaxLoading(Type* w, Type c, int n, int* bestx)
{
	queue<QNode<Type>*> Q;
	Q.push(nullptr);
	int i = 1;
	Type cw = 0,
		bestw = 0,
		r = 0;
	for (int i = 2; i <= n; i++)
		r += w[i];
	QNode<Type>* Ew = nullptr,//Ew这里作为一个中间量，连接parent和child, 赋0是因为树的根的值是0，while刚开始的时候其代表root
		*bestE = nullptr;//bestE的作用是：结束while循环后，bestE指向最优解的叶子节点，然后通过bestE->parent找到装入了哪些物品
	while (true)
	{
		Type wt = cw + w[i];
		if (wt <=  c) //首先检测当前扩展结点的左儿子结点是否为可行结点。如果是，则将其加入到活结点队列Q中
		{
			if (wt >  bestw) // 可行结点
				bestw =  wt;  //提前更新bestW,注意更新条件
			EnQueue(Q, wt, i, n, bestw, Ew, bestE, bestx, true);// 加入活结点队列
		}
		if (cw + r >= bestw)//将其右儿子结点加入到活结点队列中(右儿子结点一定是可行结点)。
			EnQueue(Q, cw, i, n, bestw, Ew, bestE, bestx, false);
		Ew = Q.front();//活结点队列中，队首元素被取出作为当前扩展结点。
		Q.pop();// 取下一扩展结点
		if (!Ew)  //如果取得的数是0，代表该处理下一层
		{
			if (Q.empty())//活结点队列已空，算法终止。
				break;
			Q.push(nullptr); //如果队列中还有数据，表示循环还没结束。在该层的末尾加一个nullptr标识符,相当于讲稿中-1
			Ew = Q.front();
			Q.pop();
			i++;
			r -= w[i];//计算剩余的重量
		}
		cw = Ew->weight;//更新最新节点的值
	}
	for (int j = n - 1; j > 0; j--)
	{
		bestx[j] = bestE->LChind;
		bestE = bestE->parent;
	}
	
	cout << "第一艘船装载的方案为：";
	for (int i = 1; i <= n; i++)
		cout << bestx[i] << " ";
	cout << endl;
	cout << "第一艘船装载情况为：" ;
	for (int i = 1; i <= n; i++)
	if (bestx[i] == 1)
	{
		cout << "装第" << i << "个集装箱" << "(该物品重量为" << w[i] << ")"<< endl;
	}

	return  bestw;
}


int main()
{
	int w[4] = { 0, 20, 40, 40 };
	int c = 100;
	int n = 3;
	int* bestx = new int[4];

	cout << "第一艘船的装载总重量：" << MaxLoading<int>(w, c, n, bestx) << endl;
	
	system("PAUSE");
	return 0;
}


