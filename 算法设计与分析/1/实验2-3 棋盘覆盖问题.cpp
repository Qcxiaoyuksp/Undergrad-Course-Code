#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stdlib.h"
#include <iostream>


#include<iomanip>  
//setw(n)是c++中在输出操作中使用的字段宽度设置，n表示字段宽度。
using namespace std;

int matrix[100][100];
int num = 0;
void chessBoard(int x, int y, int a, int b, int length);

int main()
{
	int a, b, length;
	cout << "请输入棋盘的行列号";
	cin >> length;
	cout << "请输入特殊方格的行列号";
	cin >> a >> b;
	matrix[a][b] = -1;

	chessBoard(1, 1, a, b, length);

	for (int i = 1; i <= length; i++){
		for (int j = 1; j <= length; j++){
			cout << setw(4) << matrix[i][j];
		}
		cout << endl;
	}

	system("PAUSE");

	return 0;
}
void chessBoard(int x, int y, int a, int b, int length) {
	//如果棋盘上只有一个方格，且该方格为一特殊方格
	if (length == 1){
		return;
	}
	int h = length / 2;   //分割棋盘
//	int t = ++num;        //L型骨牌号(从1开始)
	int t = num++;        //L型骨牌号(从0开始)
	/*左上角*/
	if (a < x + h && b < y + h){   //特殊方格在此棋盘中则划分
		chessBoard(x, y, a, b, h);
	}
	else{   //否则先覆盖右下角的方格(用t号L型骨牌)，再划分
		matrix[x + h - 1][y + h - 1] = t;
		chessBoard(x, y, x + h - 1, y + h - 1, h);
	}
	/*右上角*/
	if (a < x + h && b >= y + h){   //特殊方格在此棋盘中则划分
		chessBoard(x, y + h, a, b, h);
	}
	else{   //否则先覆盖左下角的方格(用t号L型骨牌)，再划分
		matrix[x + h - 1][y + h] = t;
		chessBoard(x, y + h, x + h - 1, y + h, h);
	}

	/*右下角*/
	if (a >= x + h && b >= y + h){   //特殊方格在此棋盘中则划分
		chessBoard(x + h, y + h, a, b, h);
	}
	else{   //否则先覆盖左上角的方格(用t号L型骨牌)，再划分
		matrix[x + h][y + h] = t;
		chessBoard(x + h, y + h, x + h, y + h, h);
	}


	/*左下角*/
	if (a >= x + h && b < y + h){   //特殊方格在此棋盘中则划分
		chessBoard(x + h, y, a, b, h);
	}
	else{   //否则先覆盖右上角的方格(用t号L型骨牌)，再划分
		matrix[x + h][y + h - 1] = t;
		chessBoard(x + h, y, x + h, y + h - 1, h);
	}

}

