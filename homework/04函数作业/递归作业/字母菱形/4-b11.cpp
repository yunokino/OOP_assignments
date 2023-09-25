/* 2152041 王浩 信07 */
#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;

/* -----------------------------------------------------------------------------------
		允许   ：1、按需增加一个或多个函数，但是所有增加的函数中不允许任何形式的循环
				 2、定义符号常量
				 3、定义const型变量

		不允许 ：1、定义全局变量
   ----------------------------------------------------------------------------------- */

int print_dash(char ch)
{
	int a = (int)(ch);
	return ((a - 64) * 2 - 1);
}


/***************************************************************************
  函数名称：
  功    能：打印菱形
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void fun1(int n, int i);
void fun2(int m, int j);
void fun3(int i, int j);
void fun4(int m, int j);
void fun5(int n, int i);

void print_diamond(char start_ch, char end_ch)
{
	/* 按需实现，函数中不允许任何形式的循环，但允许定义静态局部变量 */
	fun1((int)(end_ch)-64, 1);
	fun5((int)(end_ch)-64, (int)(end_ch)-65);
}

void fun1(int n, int i)
{
	if (n - i >= 0)
	{
		fun2(n - i, 1);
		fun3(i, i);
		fun4(i - 1, 1);
		cout << endl;
		fun1(n, i + 1);
	}
}
void fun2(int m, int j)
{
	if (m - j >= 0)
	{
		cout << " ";
		fun2(m, j + 1);
	}
}
void fun3(int i, int j)
{
	if (i > 0)
	{
		cout << char(j + 64);
		j--;
		fun3(i - 1, j);
	}
}
void fun4(int m, int j)
{
	if (m > 0)
	{
		cout << char(j + 65);
		j++;
		fun4(m - 1, j);
	}
}

void fun5(int n, int i)
{
	if (i >= 1)
	{
		fun2(n - i, 1);
		fun3(i, i);
		fun4(i - 1, 1);
		if (i >= 1)
			cout << endl;
		fun5(n, i - 1);
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数中两处...允许修改，其余位置不准修改
***************************************************************************/
int main()
{
	char end_ch;

	/* 键盘输入结束字符(仅大写有效) */
	cout << "请输入结束字符(A~Z)" << endl;
	end_ch = getchar();

	/* 菱形(中间为A) */
	cout << setw(print_dash(end_ch)) << setfill('=') << '=' << endl; /* 按菱形最大宽度输出=(不允许用循环) */
	cout << "菱形(" << end_ch << "->A)" << endl;
	cout << setw(print_dash(end_ch)) << setfill('=') << '=' << endl; /* 按菱形最大宽度输出=(不允许用循环) */
	print_diamond('A', end_ch);
	cout << endl;

	return 0;
}