/* 2152041 王浩 信07 */
#include <iostream>
#include <iomanip>
using namespace std;

/* ----具体要求----
   1、不允许添加其它头文件
   2、不允许定义全局变量、静态局部变量
   3、允许添加用于输入层数、起始/目标柱的函数，函数中允许使用循环处理错误输入
   4、如果输入用函数进行，则main中不允许出现任何形式的循环
	  如果输入在main中进行，则main中允许出现循环
   --------------------------------------------------------------------- */
void move(int n, char x, char y)
{
	cout << setw(2) << n << "# " << x << "-->" << y << endl;
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
		cout << "请输入汉诺塔的层数(1-16)\n";
		cin >> x;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if (x >= 1 && x <= 16)
		{
			cin.ignore(65536, '\n');
			break;
		}
	}
	while (1) {
		cout << "请输入起始柱(A-C)\n";
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
		cout << "请输入目标柱(A-C)\n";
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
	cout << "移动步骤为:\n";
	hanoi(x, f, g, h);
	return 0;
}