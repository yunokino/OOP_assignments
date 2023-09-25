/* 2152041 王浩 信07 */
#include <iostream>
#include <iomanip>
#include<windows.h>


using namespace std;

/* ----具体要求----
   1、不允许添加其它头文件
   2、不允许定义全局变量、静态局部变量
   3、允许添加用于输入层数、起始/目标柱的函数，函数中允许使用循环处理错误输入
   4、如果输入用函数进行，则main中不允许出现任何形式的循环
	  如果输入在main中进行，则main中允许出现循环
   --------------------------------------------------------------------- */

   /***************************************************************************
	 函数名称：
	 功    能：打印n层汉诺塔的移动顺序
	 输入参数：int n：层数
			   char src：起始柱
			   char tmp：中间柱
			   char dst：目标柱
	 返 回 值：
	 说    明：1、函数名、形参、返回类型均不准动
			   2、本函数不允许出现任何形式的循环
   ***************************************************************************/
int step = 1;
int a, b, c;
int src[10];
int tmp[10];
int dst[10];
void print()
{
	for (int i = 9; i >= 0; i--)
	{
		if (src[i] == 0)
			cout << setw(12) << " ";
		else
			cout << setw(12) << src[i];
		if (tmp[i] == 0)
			cout << setw(10) << " ";
		else
			cout << setw(10) << tmp[i];
		if (dst[i] == 0)
			cout << setw(10) << " ";
		else
			cout << setw(10) << dst[i];
		cout << endl;
	}
	cout << "         " << setw(25) << setfill('=') << '=' << setfill(' ') << endl;;
	cout << setw(12) << 'A' << setw(10) << 'B' << setw(10) << 'C' << endl;
	cout << endl << endl << endl;
	if (sleep == 0)
		getchar();
}

void move(int n, char x, char y)
{
	if (x == 'A' && y == 'B')
	{
		tmp[b++] = src[--a];
		src[a] = 0;
	}
	else if (x == 'A' && y == 'C')
	{
		dst[c++] = src[--a];
		src[a] = 0;
	}
	else if (x == 'B' && y == 'A')
	{
		src[a++] = tmp[--b];
		tmp[b] = 0;
	}
	else if (x == 'B' && y == 'C')
	{
		dst[c++] = tmp[--b];
		tmp[b] = 0;
	}
	else if (x == 'C' && y == 'A')
	{
		src[a++] = dst[--c];
		dst[c] = 0;
	}
	else
	{
		tmp[b++] = dst[--c];
		dst[c] = 0;
	}
/*	cct_cls();
	cout << "从 " << x<< " 移动到 " << y << "，共 " << n << " 层，延时设置为 " << sleep << "，" << (display == 0 ? "不" : "") << "显示内部数组值\n";
	print();
	if (display == 1)
		cout << "第" << setw(4) << step << "步" << "(" << n << "#: " << x << "-->" << y << ") ";
	step++;
	if (display == 1)
	{
		cout << " A:";
		for (int i = 0; i <= 9; i++)
		{
			if (src[i] == 0)
			{
				if (i == 0)
					cout << "   ";
				else
					cout << "  ";
			}
			else
			{
				if (i == 0)
					cout << setw(2) << src[i] << " ";
				else
					cout << src[i] << " ";
			}
		}
		cout << "B:";
		for (int i = 0; i <= 9; i++)
		{
			if (tmp[i] == 0)
			{
				if (i == 0)
					cout << "   ";
				else
					cout << "  ";
			}
			else
			{
				if (i == 0)
					cout << setw(2) << tmp[i] << " ";
				else
					cout << tmp[i] << " ";
			}
		}
		cout << "C:";
		for (int i = 0; i <= 9; i++)
		{
			if (dst[i] == 0)
			{
				if (i == 0)
					cout << "   ";
				else
					cout << "  ";
			}
			else
			{
				if (i == 0)
					cout << setw(2) << dst[i] << " ";
				else
					cout << dst[i] << " ";
			}
		}
	}*/
}
/***************************************************************************
  函数名称：
  功    能：打印n层汉诺塔的移动顺序
  输入参数：int n：层数
			char src：起始柱
			char tmp：中间柱
			char dst：目标柱
  返 回 值：
  说    明：1、函数名、形参、返回类型均不准动
			2、本函数不允许出现任何形式的循环
***************************************************************************/
void hanoi(int n, char src, char tmp, char dst)
{
	if (n == 1)
	{
		move(1, src, dst);
	}
	else
	{
		hanoi(n - 1, src, dst, tmp);
		move(n, src, dst);
		hanoi(n - 1, tmp, src, dst);
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：完成输入(或调用输入函数)、调用递归函数
***************************************************************************/
int main()
{
	int x;
	char f, g, h;
	g = '0';

	while (1) {
		cout << "请输入汉诺塔的层数(1-10)：\n";
		cin >> x;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if (x >= 1 && x <= 10)
		{
			cin.ignore(65536, '\n');
			break;
		}
	}
	while (1) {
		cout << "请输入起始柱(A-C)：\n";
		cin >> f;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if (f == 'a' || f == 'b' || f == 'c' || f == 'A' || f == 'B' || f == 'C')
		{
			cin.ignore(65536, '\n');
			break;
		}
	}
	while (1) {
		cout << "请输入目标柱(A-C)：\n";
		cin >> h;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if ((int)f == (int)h || (int)f == (int)h - 32 || (int)f == (int)h + 32)
		{
			h = (int(h) > 90) ? char(int(h) - 32) : h;
			f = (int(f) > 90) ? char(int(f) - 32) : f;
			cout << "目标柱(" << h << ")不能与起始柱(" << f << ")相同\n";
			cin.ignore(65536, '\n');
			continue;
		}
		else if ((h == 'a' || h == 'b' || h == 'c' || h == 'A' || h == 'B' || h == 'C'))
		{
			cin.ignore(65536, '\n');
			break;
		}
	}
	bool _1, _2, _3;
	_1 = _2 = _3 = 1;
	switch (int(f))
	{
		case 65:
		case 97:
			_1 = 0;
			f = 'A';
			break;
		case 66:
		case 98:
			_2 = 0;
			f = 'B';
			break;
		case 67:
		case 99:
			_3 = 0;
			f = 'C';
			break;
	}
	switch (int(h))
	{
		case 65:
		case 97:
			_1 = 0;
			h = 'A';
			break;
		case 66:
		case 98:
			_2 = 0;
			h = 'B';
			break;
		case 67:
		case 99:
			_3 = 0;
			h = 'C';
			break;
	}
	if (_1)
		g = 'A';
	if (_2)
		g = 'B';
	if (_3)
		g = 'C';
	a = (f == 'A' ? x : 0);
	b = (f == 'B' ? x : 0);
	c = (f == 'C' ? x : 0);
	while (1) {
		cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)\n";
		cin >> sleep;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if (sleep >= 0 && sleep <= 5)
		{
			cin.ignore(65536, '\n');
			break;
		}
	}
	while (1) {
		cout << "请输入是否显示内部数组值(0-不显示 1-显示)\n";
		cin >> display;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if (display == 0 || display == 1)
		{
			cin.ignore(65536, '\n');
			break;
		}
	}
	cout << endl;
	cct_cls();
	cout << "从 " << f << " 移动到 " << h << "，共 " << x<< " 层，延时设置为 " << sleep << "，" << (display == 0 ? "不" : "") << "显示内部数组值\n";
	for (int i = 0; i <= 14; i++)
		cout << endl;
	cout << "初始:                ";
	(x == 10 && f == 'A') ? cout << " A:" : cout << " A: ";
	int j = x;
	if (f == 'A') 
	{
		for (int i = 0; i <= x - 1; i++)
		{
			src[i] = j;
			j--;
			if(display==1)
				cout << src[i] << " ";
		}
		for (int i = 20 - 2 * x; i >= 1; i--)
		if (display == 1)
			cout << " ";
	}
	else
	{
		for (int i = 0; i <= 19; i++)
			if (display == 1)
				cout << " ";
	}
	(x == 10 && f == 'B') ? cout << "B:" : cout << "B: ";
	if (f == 'B')
	{
		for (int i = 0; i <= x - 1; i++)
		{
			tmp[i] = j;
			j--;
			if (display == 1)
				cout << tmp[i] << " ";
		}
		for (int i = 20 - 2 * x; i >= 1; i--)
			if (display == 1)
				cout << " ";
	}
	else
	{
		for (int i = 0; i <= 19; i++)
			if (display == 1)
				cout << " ";
	}
	(x == 10 && f == 'C') ? cout << "C:" : cout << "C: ";
	if (f == 'C')
	{
		for (int i = 0; i <= x - 1; i++)
		{
			dst[i] = j;
			j--;
			if (display == 1)
				cout << dst[i] << " ";
		}
		for (int i = 20 - 2 * x; i >= 1; i--)
			if (display == 1)
				cout << " ";
	}
	else
	{
		for (int i = 0; i <= 19; i++)
			if (display == 1)
				cout << " ";
	}
	hanoi(x, f, g, h);
	getchar();
	return 0;
}
