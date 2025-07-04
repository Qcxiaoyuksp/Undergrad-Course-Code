/**
//分支限界法-旅行商(TSP)问题
输入
4
6
1 2 30
1 3 6
1 4 4
2 3 5
2 4 10
3 4 20
*/


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
#include <queue>
#define NoEdge -1
#define NN 50 // 可执行的最大的顶点个数
using namespace std;
int n;                 // 图的顶点个数
int adjMatrix[NN][NN]; // 图的邻接矩阵
int v[50];             // 最优解
int bestC;             // 最优值
int num = 0;           // 节点序号

/*****************************************************************
* 函数描述： 数据输入以及内存的初始化
*****************************************************************/
void input()
{
	cin >> n; // 输入顶点个数
	int k;
	memset(adjMatrix, NoEdge, sizeof(adjMatrix)); // 邻接矩阵的内存初始化
	cin >> k;                                     // 输入边的个数;
	int p, q, len;
	// 初始化邻接矩阵
	for (int i = 1; i <= k; ++i)
	{
		cin >> p >> q >> len;
		adjMatrix[p][q] = len;
		adjMatrix[q][p] = len;
	}
}

/*****************************************************************
* 函数描述： 格式化打印结果
* 参数描述： res，最优值
*****************************************************************/
void printTravel(int res)
{
	if (res == NoEdge)
		cout << "======= 无法形成回路 =======" << endl;
	else
	{
		cout << "\n=================================\n最短路径为：" << res << endl;
		for (int i = 1; i <= n; i++)
			cout << v[i] << " ---> ";
		cout << v[1];
	}
}

/*****************************************************************
* 类描述：最小堆（队列中元素类型）
* 参数描述：
x，用于记录当前解；
s，表示节点在排列树中的层次，从排列树的根节点到该节点的路径为x[0:s]，
需要进一步搜索的顶点是x[s+1:n-1]。
cc，表示当前费用，
rcost，是子树费用的下界，
lcost，是x[x:n-1]中顶点最小出边费用和。
*****************************************************************/
class MinHeapNode
{
public:
	char name; // 节点的序号
	int lcost, // x[s:n-1]中顶点最小出边费用和
		rcost, // 子树费用的下界
		cc;    // 当前费用
	int s,     // 根节点到当前节点的路径为x[0:s]
		*x;    // 需要进一步搜索的顶点是x[s+1:n-1]

	// 构造节点并递增序号
	MinHeapNode()
	{
		num += 1;
		name = num + 'A';
	}

	// 最小堆中使用下界排序
	bool operator<(const MinHeapNode &MH) const
	{
		return rcost > MH.rcost;
	}

	// 打印节点信息
	void printNode(priority_queue<MinHeapNode> pq)
	{
		cout << "============== Node: " << name << " ==============" << endl;
		cout << "最小出边和(lcost)：" << lcost << "\t子树费用的下界(lcost)：" << rcost
			<< "\t当前费用(cc)：" << cc << "  \t节点所在层(s)：" << s << endl;
		cout << "当前解是(x)：";
		for (int i = 0; i < n - 1; ++i)
			cout << x[i] << "-";
		cout << x[n - 1] << endl;
		// 输出优先级队列
		if (!pq.empty())
		{
			cout << "-- 当前优先队列：";
			for (int i = 0; i < pq.size(); ++i)
			{
				cout << pq.top().name << "(" << pq.top().rcost << ")-";
				pq.pop();
			}
		}
		else
		{
			cout << "(优先级队列为空)" << endl;
		}
		cout << "-- 当前最优值（bestC）：" << bestC << endl;
	}
};

/*****************************************************************
* 算法描述：核心算法
算法开始时创建一个最小堆，表示活节点优先队列。堆中每个节点的lcost
值是优先队列的优先级。接着计算出图中每个顶点的最小费用出边并用Minout记录。
如果所给的有向图中某个顶点没有出边，则该图不可能有回路，算法即告结束。
如果每个顶点都有出边，则根据计算出的Minout作算法初始化。
*****************************************************************/
int BBTSP()
{
	priority_queue<MinHeapNode> pq; // 优先级队列
	MinHeapNode E;                  // 最小堆节点

	int cc, lcost, MinSum, *MinOut, lb;
	int i, j;

	MinSum = 0;              // 最小出边费用和
	MinOut = new int[n + 1]; // 计算 MinOut[i] = 顶点i的最小出边费用
	for (i = 1; i <= n; i++)
	{
		MinOut[i] = NoEdge; // 所有的出边初始化为无连接
		// 遍历找出 MinOut[i] = 顶点i的最小出边费用
		for (j = 1; j <= n; j++)
		if (adjMatrix[i][j] != NoEdge && (adjMatrix[i][j] < MinOut[i] || MinOut[i] == NoEdge))
			MinOut[i] = adjMatrix[i][j];
		// 不存在与这个顶点相连接的边
		if (MinOut[i] == NoEdge)
			return NoEdge;
		MinSum += MinOut[i];
	}

	// 初始化最小堆
	E.s = 0;          // 根节点到当前节点的路径为x[0:s]
	E.cc = 0;         // 当前费用为0
	E.lcost = MinSum; // x[s:n-1]中顶点最小出边费用和
	E.x = new int[n]; // 需要进一步搜索的顶点是x[s+1:n-1]
	// 初始化为顺序搜索
	for (i = 0; i < n; i++)
		E.x[i] = i + 1;
	bestC = NoEdge; // 初始化最优值为 NoEdge

	E.printNode(pq);
	//搜索排列空间树
	while (E.s < n - 1) //非叶节点
	{
		if (E.s == n - 2) // 当前扩展节点是叶节点的父节点，判断构成的回路是否最优
		{
			if (adjMatrix[E.x[n - 2]][E.x[n - 1]] != NoEdge && adjMatrix[E.x[n - 1]][1] != NoEdge &&
				(E.cc + adjMatrix[E.x[n - 2]][E.x[n - 1]] + adjMatrix[E.x[n - 1]][1] < bestC || bestC == NoEdge))
			{ // 如果更优，则更新费用更小的路
				cout << "\n||||||||||||||||||||| 到达叶子节点的父节点 ---- 并更新最优解 |||||||||||||||||||||"
					<< endl;
				E.printNode(pq);
				bestC = E.cc + adjMatrix[E.x[n - 2]][E.x[n - 1]] + adjMatrix[E.x[n - 1]][1];
				E.cc = bestC;
				E.rcost = bestC;
				E.s++;
				pq.push(E);
			}
			else
			{
				cout << "\n||||||||||||||||||||||| 到达叶子节点的父节点 ---- 不更新 |||||||||||||||||||||||"
					<< endl;
				E.printNode(pq);
				delete[] E.x; // 舍弃需要进一步搜索的节点
			}
		}
		else // 产生当前扩展节点儿子节点
		{
			cout << "\n*************** 开始一个新节点扩展 ***************\n"
				<< endl;
			for (i = E.s + 1; i < n; i++)
			{ // 广度优先搜索，进行子节点的扩展
				MinHeapNode N;
				if (adjMatrix[E.x[E.s]][E.x[i]] != NoEdge)   // E.x[E.s] 是当前要扩展的父节点，E.x[i] 是被遍历的子节点
				{                                            // 可行儿子节点
					cc = E.cc + adjMatrix[E.x[E.s]][E.x[i]]; // 当前费用 = 之前费用 + 新增费用
					lcost = E.lcost - MinOut[E.x[E.s]];      // 更新最小出边费用和
					lb = cc + lcost;                          // 下界（限界函数）
					if (lb < bestC || bestC == NoEdge)        // 子树可能含最优解 节点插入最小堆
					{
						N.s = E.s + 1; // 进入下一层
						N.cc = cc;
						N.rcost = lb;
						N.lcost = lcost;
						N.x = new int[n];
						for (j = 0; j < n; j++)
							N.x[j] = E.x[j];
						// 获得新的路径【换位】
						N.x[E.s + 1] = E.x[i];
						N.x[i] = E.x[E.s + 1];
						pq.push(N); // 加入优先队列
						N.printNode(pq);
					}
				}
			}
			delete[] E.x; //完成节点扩展
		}
		if (pq.empty()) // 堆已空
			break;
		E = pq.top(); // 取下一扩展节点
		pq.pop();
	}

	if (bestC == NoEdge) // 无回路
		return NoEdge;
	for (i = 0; i < n; i++) // 将最优解复制到v[1:n]
		v[i + 1] = E.x[i];
	while (pq.size()) // 释放最小堆中所有节点
	{
		E = pq.top();
		pq.pop();
		delete[] E.x;
	}
	return bestC;
}

int main()
{
	input();
	int res = BBTSP();
	printTravel(res);
	system("PAUSE");
	return 0;
}


