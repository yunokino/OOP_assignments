/* 2152041 王浩 计科 */
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include "../include/cmd_console_tools.h"
#include "90-01-b1-hanoi.h"
using namespace std;
/* ----------------------------------------------------------------------------------

	 本文件功能：
	1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

	 本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */
int step = 1;
int speed;
int a, b, c;//记录圆柱上现有圆盘的数量
int src[10], tmp[10], dst[10];
/***************************************************************************
  函数名称：move
  功    能：移动柱子
  输入参数：n,x,y,_1,_2,_3,_4,_8,_9
  返 回 值：
  说    明：前四项的输出和数组的改变都在这里实现，作为一个单独的步骤被递归函
			数调用,默认参数初始化在头文件里
***************************************************************************/
void move(int n, char x, char y, int _1, int _2, int _3, int _4, int _8, int _9)
{
	if (_1)
		cout << setw(2) << n << "# " << x << "-->" << y;
	if (_2)
	{
		if (_4 && (step == 1) && !_9)
		{
			cct_gotoxy(0, _8 ? 17 : 1);
			print_vertical();
			cout << "初始:";
			print_horizontal();
			sleep1(speed);
			cct_gotoxy(0, _8 ? 17 : 1);
		}
		if (_8)
			move_disk(n, x, y);
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
		if (!_4)
			cout << "第" << setw(4) << step << " 步(" << setw(2) << n << "#: " << x << "-->" << y << ")";
		if (_3)
		{
			if (_4)
			{
				cct_setcursor(CURSOR_INVISIBLE);
				print_vertical();
				cout << "第" << setw(4) << step << " 步(" << setw(2) << n << "#: " << x << "-->" << y << ")";
			}
			print_horizontal();
		}
		if (_4)
		{
			sleep1(speed);
			cct_gotoxy(0, _8 ? 17 : 1);
		}
	}
	if (_9)
	{
		move_disk(n, x, y);
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
		print_vertical();
		cout << "第" << setw(4) << step << " 步(" << setw(2) << n << "#: " << x << "-->" << y << ")";
		print_horizontal();
	}
	step++;
	if (!_4)
		cout << endl;
}
/***************************************************************************
  函数名称：sleep1
  功    能：调用延时函数
  输入参数：speed
  返 回 值：
  说    明：延时函数有多次调用，所以单独列出为一个函数
			为了避免speed为零时，圆盘移动会要回车才移动的问题，列出两个延时函数
***************************************************************************/
void sleep1(int speed)
{
	switch (speed)
	{
		case 0:
			_getch();
			break;
		case 1:
			Sleep(100);
			break;
		case 2:
			Sleep(50);
			break;
		case 3:
			Sleep(30);
			break;
		case 4:
			Sleep(20);
			break;
		case 5:
			break;
		default:
			break;
	}
}
/***************************************************************************
  函数名称：sleep2
  功    能：调用延时函数
  输入参数：speed
  返 回 值：
  说    明：延时函数有多次调用，所以单独列出为一个函数
			为了避免speed为零时，圆盘移动会要回车才移动的问题，列出两个延时函数
***************************************************************************/
void sleep2(int speed)
{
	switch (speed)
	{
		case 0:
			Sleep(100);
			break;
		case 1:
			Sleep(80);
			break;
		case 2:
			Sleep(50);
			break;
		case 3:
			Sleep(30);
			break;
		case 4:
			Sleep(20);
			break;
		case 5:
			break;
		default:
			break;
	}
}
/***************************************************************************
  函数名称：print_horizontal
  功    能：打印横向数组
  输入参数：
  返 回 值：
  说    明：为零输出空格，非零正常输出，为了对齐，对第一个数进行了特殊处理
***************************************************************************/
void print_horizontal()
{
	cout << "  A:";
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
}
/***************************************************************************
  函数名称：print_vertical
  功    能：打印纵向数组
  输入参数：
  返 回 值：
  说    明：为零输出空格，非零正常输出，光标不可见的话视觉效果更好
***************************************************************************/
void print_vertical()
{
	cout << endl;
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
}
/***************************************************************************
  函数名称：print_column
  功    能：打印柱子
  输入参数：
  返 回 值：
  说    明：与demo不同，这里先从下到上打印一列，再改变x坐标打印另一列，光标不可见，视
			觉效果更好
***************************************************************************/
void print_column()
{
	int x = 1, y = 15;
	for (; x <= 86; x++)
	{
		cct_showch(x, y, ' ', 14, 1, 2);
		if (x == 22 || x == 54)
			x += 10;
	}
	cct_setcursor(CURSOR_INVISIBLE);
	for (int i = 12; i <= 76; i += 32)
		for (int j = 14; j >= 3; j--)
		{
			Sleep(20);
			cct_showch(i, j, ' ', 14, 1);
		}
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cct_gotoxy(0, 17);
}
/***************************************************************************
  函数名称：print_disk
  功    能：打印圆盘
  输入参数：num，start_column
  返 回 值：
  说    明：
***************************************************************************/
void print_disk(int num, char start_column)
{
	cct_setcursor(CURSOR_INVISIBLE);
	int x = 12 + (start_column - 65) * 32;
	int y = 14;
	for (; num >= 1; num--)
	{
		Sleep(30);
		cct_showch(x - num, y, ' ', 13 - num, 1, 2 * num + 1);
		y--;
	}
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cct_gotoxy(0, 17);
}
/***************************************************************************
  函数名称：move_disk
  功    能：移动圆盘
  输入参数：num,start_column,end_column
  返 回 值：
  说    明：先上移在平移，再下移
***************************************************************************/
void move_disk(int num, char start_column, char end_column)
{
	cct_setcursor(CURSOR_INVISIBLE);
	int x = 12 + (start_column - 65) * 32;
	int up_disk = a;
	int down_disk = a;
	if (start_column == 'B')
		up_disk = b;
	else if (start_column == 'C')
		up_disk = c;
	else;
	if (end_column == 'B')
		down_disk = b;
	else if (end_column == 'C')
		down_disk = c;
	else;
	int y = 14 - up_disk;
	int do_translate = int(fabs(end_column - start_column) * 32);
	while (y >= 1)
	{
		sleep2(speed);
		cct_showch(x - num, y, ' ', 13 - num, 1, 2 * num + 1);

		cct_showch(x - num, y + 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * num + 1);
		if (y >= 2)
			cct_showch(x, y + 1, ' ', 14, 1, 1);
		--y;
	}
	if (y == 0)
		y++;
	while (do_translate != 0)
	{
		sleep2(speed);
		if (end_column - start_column > 0)
		{
			cct_showch(x - num + 1, y, ' ', 13 - num, 1, 2 * num + 1);
			cct_showch(x - num, y, ' ', COLOR_BLACK, COLOR_WHITE, 1);
			x++;
		}
		else
		{
			cct_showch(x - num - 1, y, ' ', 13 - num, 1, 2 * num + 1);
			cct_showch(x + num, y, ' ', COLOR_BLACK, COLOR_WHITE, 1);
			x--;
		}
		do_translate--;
	}
	while (y <= 14 - down_disk)
	{
		sleep2(speed);
		cct_showch(x - num, y, ' ', 13 - num, 1, 2 * num + 1);
		if (y != 1)
			cct_showch(x - num, y - 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * num + 1);
		if (y >= 4)
			cct_showch(x, y - 1, ' ', 14, 1, 1);
		y++;
	}
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cct_gotoxy(0, 17);
}
/***************************************************************************
  函数名称：play_game
  功    能：执行第九项玩游戏
  输入参数：num goal_column
  返 回 值：
  说    明：
***************************************************************************/
void play_game(int num,char goal_column)
{
	speed = 5;
	while (1)
	{
		cct_gotoxy(34, 34);
		cout << "\n请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";
		for (int i = 0; i <= 20; i++)
			cout << " ";
		for (int i = 0; i <= 20; i++)
			cout << "\b";
		char start_column = _getch();
		if (start_column == 'A' || start_column == 'B' || start_column == 'C' || start_column == 'Q' || start_column == 'q')
		{
			cout << start_column;
			if (start_column == 'Q' || start_column == 'q')
			{
				while (getchar() != '\n');
				break;
			}
		}
		else if (start_column == 'a' || start_column == 'b' || start_column == 'c')
		{
			cout << start_column;
			if (start_column == 'a')
				start_column = 'A';
			else if (start_column == 'b')
				start_column = 'B';
			else
				start_column = 'C';
		}
		else
			continue;
		char end_column = _getch();
		if (end_column == 'A' || end_column == 'B' || end_column == 'C')
			cout << end_column;
		else if (end_column == 'a' || end_column == 'b' || end_column == 'c')
		{
			cout << end_column;
			if (end_column == 'a')
				end_column = 'A';
			else if (end_column == 'b')
				end_column = 'B';
			else
				end_column = 'C';
		}
		else
			continue;
		while (getchar() != '\n');
		if (start_column == end_column)
			continue;
		if (start_column == 'A' && end_column == 'B')
		{
			if (a == 0)
			{
				cout << "\n源柱不可为空!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			if ((src[a - 1] > tmp[b - 1]) && (b >= 1))
			{
				cout << "\n大盘不可压小盘!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			move(src[a - 1], start_column, end_column, 0, 0, 0, 0, 0, 1);
		}
		else if (start_column == 'A' && end_column == 'C')
		{
			if (a == 0)
			{
				cout << "\n源柱不可为空!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			if ((src[a - 1] > dst[c - 1]) && (c>= 1))
			{
				cout << "\n大盘不可压小盘!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			move(src[a - 1], start_column, end_column, 0, 0, 0, 0, 0, 1);
		}
		else if (start_column == 'B' && end_column == 'A')
		{
			if (b == 0)
			{
				cout << "\n源柱不可为空!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			if ((tmp[b - 1] > src[a - 1]) && (a >= 1))
			{
				cout << "\n大盘不可压小盘!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			move(tmp[b - 1], start_column, end_column, 0, 0, 0, 0, 0, 1);
		}
		else if (start_column == 'B' && end_column == 'C')
		{
			if (b == 0)
			{
				cout << "\n源柱不可为空!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			if ((tmp[b - 1] > dst[c - 1]) && (c >= 1))
			{
				cout << "\n大盘不可压小盘!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			move(tmp[b - 1], start_column, end_column, 0, 0, 0, 0, 0, 1);
		}
		else if (start_column == 'C' && end_column == 'A')
		{
			if (c == 0)
			{
				cout << "\n源柱不可为空!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			if ((dst[c - 1] > src[a - 1]) && (a >= 1))
			{
				cout << "\n大盘不可压小盘!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			move(dst[c - 1], start_column, end_column, 0, 0, 0, 0, 0, 1);
		}
		else
		{
			if (c == 0)
			{
				cout << "\n源柱不可为空!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			if ((dst[c - 1] > tmp[b - 1]) && (b >= 1))
			{
				cout << "\n大盘不可压小盘!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			move(dst[c - 1], start_column, end_column, 0, 0, 0, 0, 0, 1);
		}
		bool cmoplete_game = 0;
		switch (goal_column - 'A')
		{
			case 0:
				if (a == num)
					cmoplete_game = 1;
				break;
			case 1:
				if (b == num)
					cmoplete_game = 1;
				break;
			case 2:
				if (c == num)
					cmoplete_game = 1;
				break;
		}
		if (cmoplete_game)
			break;
	}
	cout << "\n\n游戏结束!!!!!\n";
}
/***************************************************************************
  函数名称：honoi
  功    能：递归调用其他函数
  输入参数：n, src, tmp, dst,  _1,_2,_3,  _4,_8,_9
  返 回 值：
  说    明：唯一的一个递归函数，内容只有八行，默认参数初始化在头文件里
***************************************************************************/
void hanoi(int n, char src, char tmp, char dst, int _1, int _2, int _3, int _4, int _8, int _9)
{
	if (n == 1)
		move(1, src, dst, _1, _2, _3, _4, _8, _9);
	else
	{
		hanoi(n - 1, src, dst, tmp, _1, _2, _3, _4, _8, _9);
		move(n, src, dst, _1, _2, _3, _4, _8, _9);
		hanoi(n - 1, tmp, src, dst, _1, _2, _3, _4, _8, _9);
	}
}
/***************************************************************************
  函数名称：in_put
  功    能：输入所需参数的函数
  输入参数：num,*x,* f, * g, * h,* speed
  返 回 值：
  说    明：用指针完成需要的输入
***************************************************************************/
void in_put(int num, int* x, char* f, char* g, char* h, int* speed)
{

	while (1) {
		cout << "请输入汉诺塔的层数(1-10)：\n";
		cin >> *x;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if (*x >= 1 && *x <= 10)
		{
			cin.ignore(65536, '\n');
			break;
		}
	}
	while (1) {
		cout << "请输入起始柱(A-C)：\n";
		cin >> *f;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if (*f == 'a' || *f == 'b' || *f == 'c' || *f == 'A' || *f == 'B' || *f == 'C')
		{
			cin.ignore(65536, '\n');
			break;
		}
	}
	while (1) {
		cout << "请输入目标柱(A-C)：\n";
		cin >> *h;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if (int(*f) == int(*h) || int(*f) == int(*h) - 32 || int(*f) == int(*h) + 32)
		{
			*h = (int(*h) > 90) ? char(int(*h) - 32) : *h;
			*f = (int(*f) > 90) ? char(int(*f) - 32) : *f;
			cout << "目标柱(" << *h << ")不能与起始柱(" << *f << ")相同\n";
			cin.ignore(65536, '\n');
			continue;
		}
		else if ((*h == 'a' || *h == 'b' || *h == 'c' || *h == 'A' || *h == 'B' || *h == 'C'))
		{
			cin.ignore(65536, '\n');
			break;
		}
	}
	bool _1 = 1, _2 = 1, _3 = 1;
	switch (int(*f))
	{
		case 65:
		case 97:
			_1 = 0;
			*f = 'A';
			break;
		case 66:
		case 98:
			_2 = 0;
			*f = 'B';
			break;
		case 67:
		case 99:
			_3 = 0;
			*f = 'C';
			break;
	}
	switch (int(*h))
	{
		case 65:
		case 97:
			_1 = 0;
			*h = 'A';
			break;
		case 66:
		case 98:
			_2 = 0;
			*h = 'B';
			break;
		case 67:
		case 99:
			_3 = 0;
			*h = 'C';
			break;
	}
	if (_1)
		*g = 'A';
	if (_2)
		*g = 'B';
	if (_3)
		*g = 'C';
	if (num == 4 || num == 8)
	{
		while (1) {
			cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)\n";
			cin >> *speed;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(65536, '\n');
				continue;
			}
			if (*speed >= 0 && *speed <= 5)
			{
				cin.ignore(65536, '\n');
				break;
			}
		}
	}
}
/***************************************************************************
  函数名称：act_honoi
  功    能：执行各种操作,指向不同选项
  输入参数：num
  返 回 值：
  说    明：
***************************************************************************/
void act_honoi(int num)
{
	int x;
	char f, g, h;
	cout << endl << endl;
	if (num == 1 || num == 2 || num == 3 || num == 4 || num == 6 || num == 7 || num == 8 || num == 9)
	{
		in_put(num, &x, &f, &g, &h, &speed);
		int j = x;
		if (f == 'A')
		{
			for (int i = 0; i <= x - 1; i++)
			{
				src[i] = j;
				j--;
			}
		}
		if (f == 'B')
		{
			for (int i = 0; i <= x - 1; i++)
			{
				tmp[i] = j;
				j--;
			}
		}
		if (f == 'C')
		{
			for (int i = 0; i <= x - 1; i++)
			{
				dst[i] = j;
				j--;
			}
		}
		a = (f == 'A' ? x : 0);
		b = (f == 'B' ? x : 0);
		c = (f == 'C' ? x : 0);
	}
	if (num == 0 || num == 4 || num == 5 || num == 6 || num == 7 || num == 8 || num == 9)
		cct_cls();
	switch (num)
	{
		case 0:
			break;
		case 1:
			hanoi(x, f, g, h, 1);
			break;
		case 2:
			hanoi(x, f, g, h, 0, 1);
			break;
		case 3:
			hanoi(x, f, g, h, 0, 1, 1);
			break;
		case 4:
			cout << "从 " << f << " 移动到 " << h << "，共 " << x << " 层，延时设置为 " << speed << endl;
			hanoi(x, f, g, h, 0, 1, 1, 1);
			cct_setcursor(CURSOR_VISIBLE_NORMAL);
			for (int i = 0; i <= 20; i++)
				cout << endl;
			break;
		case 5:
			print_column();
			break;
		case 6:
			cout << "从 " << f << " 移动到 " << h << "，共 " << x << " 层" << endl;
			print_column();
			print_disk(x, f);
			break;
		case 7:
			cout << "从 " << f << " 移动到 " << h << "，共 " << x << " 层" << endl;
			print_column();
			print_disk(x, f);
			move_disk(1, f, (num % 2 == 0 ? h : g));
			break;
		case 8:
			cout << "从 " << f << " 移动到 " << h << "，共 " << x << " 层，延时设置为 " << speed << endl;
			print_column();
			print_disk(x, f);
			hanoi(x, f, g, h, 0, 1, 1, 1, 1);
			cct_gotoxy(0, 34);
			break;
		case 9:
			cout << "从 " << f << " 移动到 " << h << "，共 " << x << " 层" << endl;
			print_column();
			print_disk(x, f);
			print_vertical();
			cout << "初始 : ";
			print_horizontal();
			play_game(x,h);
			break;
		default:
			break;
	}
}