/* 2152041 王浩 信07 */
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;

const int MAX_X = 69;	//定义*组成的边框的宽度
const int MAX_Y = 17;	//定义*组成的边框的高度

/***************************************************************************
  函数名称：
  功    能：完成与system("cls")一样的功能，但效率高
  输入参数：
  返 回 值：
  说    明：清除整个屏幕缓冲区，不仅仅是可见窗口区域(使用当前颜色)
***************************************************************************/
void cls(const HANDLE hout)
{
	COORD coord = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO binfo; /* to get buffer info */
	DWORD num;

	/* 取当前缓冲区信息 */
	GetConsoleScreenBufferInfo(hout, &binfo);
	/* 填充字符 */
	FillConsoleOutputCharacter(hout, (TCHAR)' ', binfo.dwSize.X * binfo.dwSize.Y, coord, &num);
	/* 填充属性 */
	FillConsoleOutputAttribute(hout, binfo.wAttributes, binfo.dwSize.X * binfo.dwSize.Y, coord, &num);

	/* 光标回到(0,0) */
	SetConsoleCursorPosition(hout, coord);
	return;
}

/***************************************************************************
  函数名称：gotoxy
  功    能：将光标移动到指定位置
  输入参数：HANDLE hout ：输出设备句柄
			int X       ：指定位置的x坐标
			int Y       ：指定位置的y坐标
  返 回 值：无
  说    明：此函数不准修改
***************************************************************************/
void gotoxy(const HANDLE hout, const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}

/***************************************************************************
  函数名称：showch
  功    能：在指定位置处打印一个指定的字符
  输入参数：HANDLE hout ：输出设备句柄
			int X       ：指定位置的x坐标
			int Y       ：指定位置的y坐标
			char ch     ：要打印的字符
  返 回 值：无
  说    明：此函数不准修改
***************************************************************************/
void showch(const HANDLE hout, const int X, const int Y, const char ch)
{
	gotoxy(hout, X, Y);
	putchar(ch);
}

/***************************************************************************
  函数名称：init_border
  功    能：显示初始的边框及随机字符
  输入参数：HANDLE hout：输出设备句柄
  返 回 值：无
  说    明：此函数不准修改
***************************************************************************/
void init_border(const HANDLE hout)
{
	gotoxy(hout, 0, 0);	//光标移回左上角(0,0)
	cout << "***********************************************************************" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "***********************************************************************" << endl;

	/* 随机显示20个大写字母，字母的值、XY坐标都随机显示
	   rand()函数的功能：随机生成一个在 0-32767 之间的整数
	   思考：在什么情况下，下面这个循环执行生成后，你看到的实际字母个数不足20个？ */
	int i;
	for (i = 0; i < 20; i++)
		showch(hout, rand() % MAX_X + 1, rand() % MAX_Y + 1, 'A' + rand() % 26);

	return;
}

/* -- 按需增加的若干函数可以放在此处 --*/
int menu()
{
	cout << "1.用I、J、K、L键控制上下左右(大小写均可，边界停止)" << endl;
	cout << "2.用I、J、K、L键控制上下左右(大小写均可，边界回绕)" << endl;
	cout << "3.用箭头键控制上下左右，边界停止" << endl;
	cout << "4.用箭头键控制上下左右，边界回绕" << endl;
	cout << "5.用I、J、K、L键控制上下左右(大小写均可，边界停止)" << endl;
	cout << "6.用I、J、K、L键控制上下左右(大小写均可，边界回绕)" << endl;
	cout << "0.退出" << endl;
	cout << "[请选择0 - 6] ";
	int x;
	while (1)
	{
		const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
		x = _getche();
		if (x == 48 || x == 49 || x == 50 || x == 51 || x == 52 || x == 53 || x == 54)
			break;
		else
		{
			cls(hout);
			cout << "1.用I、J、K、L键控制上下左右(大小写均可，边界停止)" << endl;
			cout << "2.用I、J、K、L键控制上下左右(大小写均可，边界回绕)" << endl;
			cout << "3.用箭头键控制上下左右，边界停止" << endl;
			cout << "4.用箭头键控制上下左右，边界回绕" << endl;
			cout << "5.用I、J、K、L键控制上下左右(大小写均可，边界停止)" << endl;
			cout << "6.用I、J、K、L键控制上下左右(大小写均可，边界回绕)" << endl;
			cout << "0.退出" << endl;
			cout << "[请选择0 - 6] ";
		}
	}
	return x;
}

int move_by_arrow(int a);

int move_by_ijkl(int a)
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄

	/* 生成伪随机数的种子，只需在程序开始时执行一次即可 */
	srand((unsigned int)(time(0)));

	/* 此句的作用是调用系统的cls命令清屏 */
	cls(hout);

	/* 显示初始的边框及其中的随机字符 */
	init_border(hout);
	int x, y;
	x = 35;
	y = 9;
	gotoxy(hout, x, y);
	if (a == 49)
	{
		while (1)
		{
			char b = _getch();
			if ((b == 73 || b == 105) && y >= 2)
				y--;
			gotoxy(hout, x, y);
			if ((b == 75 || b == 107) && y <= 16)
			{
				y++;
				gotoxy(hout, x, y);
			}
			if ((b == 74 || b == 106) && x >= 2)
			{
				x--;
				gotoxy(hout, x, y);
			}
			if ((b == 108 || b == 76) && x <= 68)
			{
				x++;
				gotoxy(hout, x, y);
			}
			if (b == 81 || b == 113)
				break;
			if (b == 32 && y >= 1 && y <= 17 && x >= 1 && x <= 69)
				cout << char(127) << char(8);
		}

		gotoxy(hout, 0, 23);
		cout << "游戏结束，按回车键退出." << endl;

		//暂停(此处作业要求是只能按回车退出，目前的getchar示例，是允许按任意键+回车退出，且任意键会出现在屏幕上
		while (1)
		{
			char d = _getch();
			if (d == char(13))
			{
				cls(hout);
				int x = menu();
				if (x == 49 || x == 50)
					move_by_ijkl(x);
				else if (x == 51 || x == 52)
					move_by_arrow(x);
				else if (x == 53 || x == 54)
					move_by_ijkl(x);
				else;
				break;
			}
			else
			{
				continue;
			}
		}
	}
	else if (a == 50)
	{
		while (1)
		{
			char c = _getch();
			if ((c == 73 || c == 105) && y >= 1)
			{
				y--;
				gotoxy(hout, x, y);
			}
			if ((c == 73 || c == 105) && y == 0)
			{
				y = 17;
				gotoxy(hout, x, y);
			}
			if ((c == 75 || c == 107) && y <= 17)
			{
				y++;
				if (y <= 17)
					gotoxy(hout, x, y);
			}
			if ((c == 75 || c == 107) && y == 18)
			{
				y = 1;
				gotoxy(hout, x, y);
			}
			if ((c == 74 || c == 106) && x >= 1)
			{
				x--;
				if (x >= 1)
					gotoxy(hout, x, y);
			}
			if ((c == 74 || c == 106) && x == 0)
			{
				x = 68;
				gotoxy(hout, x, y);
			}
			if ((c == 108 || c == 76) && x <= 69)
			{
				x++;
				if (x <= 69)
					gotoxy(hout, x, y);
			}
			if ((c == 108 || c == 76) && x == 70)
			{
				x = 1;
				gotoxy(hout, x, y);
			}
			if (c == 81 || c == 113)
				break;
			if (c == 32 && y >= 1 && y <= 17 && x >= 1 && x <= 69)
				cout << char(127) << char(8);
		}

		gotoxy(hout, 0, 23);
		cout << "游戏结束，按回车键退出." << endl;

		//暂停(此处作业要求是只能按回车退出，目前的getchar示例，是允许按任意键+回车退出，且任意键会出现在屏幕上)
		while (1)
		{
			char d = _getch();
			if (d == char(13))
			{
				cls(hout);
				int x = menu();
				if (x == 49 || x == 50)
					move_by_ijkl(x);
				else if (x == 51 || x == 52)
					move_by_arrow(x);
				else if (x == 53 || x == 54)
					move_by_ijkl(x);
				else;
				break;
			}
			else
			{
				continue;
			}
		}
	}
	else if (a == 53)
	{
		while (1)
		{
			int c, d;
			c = _getch();
			if (c == 224)
				d = _getch();
			else
			{
				if ((c == 73 || c == 105) && y >= 2)
				{
					y--;
					gotoxy(hout, x, y);
				}

				if ((c == 75 || c == 107) && y <= 17)
				{
					y++;
					if (y <= 17)
						gotoxy(hout, x, y);
				}

				if ((c == 74 || c == 106) && x >= 1)
				{
					x--;
					if (x >= 1)
						gotoxy(hout, x, y);
				}

				if ((c == 108 || c == 76) && x <= 69)
				{
					x++;
					if (x <= 69)
						gotoxy(hout, x, y);
				}

				if (c == 81 || c == 113)
					break;
				if (c == 32 && y >= 1 && y <= 17 && x >= 1 && x <= 69)
					cout << char(127) << char(8);
			}
		}



		gotoxy(hout, 0, 23);
		cout << "游戏结束，按回车键退出." << endl;

		//暂停(此处作业要求是只能按回车退出，目前的getchar示例，是允许按任意键+回车退出，且任意键会出现在屏幕上)
		while (1)
		{
			char d = _getch();
			if (d == char(13))
			{
				cls(hout);
				int x = menu();
				if (x == 49 || x == 50)
					move_by_ijkl(x);
				else if (x == 51 || x == 52)
					move_by_arrow(x);
				else if (x == 53 || x == 54)
					move_by_ijkl(x);
				else;
				break;
			}
			else
			{
				continue;
			}
		}
	}

	else if (a == 54)
	{
		while (1)
		{
			int b, c;
			c = _getch();
			if (c == 224)
				b = _getch();
			else
			{
				if ((c == 73 || c == 105) && y >= 1)
				{
					y--;
					gotoxy(hout, x, y);
				}
				if ((c == 73 || c == 105) && y == 0)
				{
					y = 17;
					gotoxy(hout, x, y);
				}
				if ((c == 75 || c == 107) && y <= 17)
				{
					y++;
					if (y <= 17)
						gotoxy(hout, x, y);
				}
				if ((c == 75 || c == 107) && y == 18)
				{
					y = 1;
					gotoxy(hout, x, y);
				}
				if ((c == 74 || c == 106) && x >= 1)
				{
					x--;
					if (x >= 1)
						gotoxy(hout, x, y);
				}
				if ((c == 74 || c == 106) && x == 0)
				{
					x = 68;
					gotoxy(hout, x, y);
				}
				if ((c == 108 || c == 76) && x <= 69)
				{
					x++;
					if (x <= 69)
						gotoxy(hout, x, y);
				}
				if ((c == 108 || c == 76) && x == 70)
				{
					x = 1;
					gotoxy(hout, x, y);
				}
				if (c == 81 || c == 113)
					break;
				if (c == 32 && y >= 1 && y <= 17 && x >= 1 && x <= 69)
					cout << char(127) << char(8);
			}
		}

		gotoxy(hout, 0, 23);
		cout << "游戏结束，按回车键退出." << endl;

		//暂停(此处作业要求是只能按回车退出，目前的getchar示例，是允许按任意键+回车退出，且任意键会出现在屏幕上)
		while (1)
		{
			char d = _getch();
			if (d == char(13))
			{
				cls(hout);
				int x = menu();
				if (x == 49 || x == 50)
					move_by_ijkl(x);
				else if (x == 51 || x == 52)
					move_by_arrow(x);
				else if (x == 53 || x == 54)
					move_by_ijkl(x);
				else;
				break;
			}
			else
			{
				continue;
			}
		}
	}
	return 0;
}

int move_by_arrow(int a)
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄

	/* 生成伪随机数的种子，只需在程序开始时执行一次即可 */
	srand((unsigned int)(time(0)));

	/* 此句的作用是调用系统的cls命令清屏 */
	cls(hout);

	/* 显示初始的边框及其中的随机字符 */
	init_border(hout);
	int x, y;
	x = 35;
	y = 9;
	gotoxy(hout, x, y);
	if (a == 51)
	{
		while (1)
		{
			int c = _getch();
			if (c == 224)
			{
				int b = _getch();
				if ((b == 72) && y >= 2)
				{
					y--;
					gotoxy(hout, x, y);
				}
				if ((b == 80) && y <= 16)
				{
					y++;
					gotoxy(hout, x, y);
				}
				if ((b == 75) && x >= 2)
				{
					x--;
					gotoxy(hout, x, y);
				}
				if ((b == 77) && x <= 68)
				{
					x++;
					gotoxy(hout, x, y);
				}
			}
			if (c == 81 || c == 113)
				break;
			if (c == 32 && y >= 1 && y <= 16 && x >= 2 && x <= 68)
				cout << char(127) << char(8);
		}

		gotoxy(hout, 0, 23);
		cout << "游戏结束，按回车键退出." << endl;

		//暂停(此处作业要求是只能按回车退出，目前的getchar示例，是允许按任意键+回车退出，且任意键会出现在屏幕上
		while (1)
		{
			char d = _getch();
			if (d == char(13))
			{
				cls(hout);
				int x = menu();
				if (x == 49 || x == 50)
					move_by_ijkl(x);
				else if (x == 51 || x == 52)
					move_by_arrow(x);
				else if (x == 53 || x == 54)
					move_by_ijkl(x);
				else;
				break;
			}
			else
			{
				continue;
			}
		}
	}
	if (a == 52)
	{
		while (1)
		{
			int d = _getch();
			if (d == 224)
			{
				int c = _getch();
				if ((c == 72) && y >= 1)
				{
					y--;
					gotoxy(hout, x, y);
				}
				if ((c == 72) && y == 0)
				{
					y = 17;
					gotoxy(hout, x, y);
				}
				if ((c == 80) && y <= 17)
				{
					y++;
					if (y <= 17)
						gotoxy(hout, x, y);
				}
				if ((c == 80) && y == 18)
				{
					y = 1;
					gotoxy(hout, x, y);
				}
				if ((c == 75) && x >= 1)
				{
					x--;
					if (x >= 1)
						gotoxy(hout, x, y);
				}
				if ((c == 75) && x == 0)
				{
					x = 68;
					gotoxy(hout, x, y);
				}
				if ((c == 77) && x <= 69)
				{
					x++;
					if (x <= 69)
						gotoxy(hout, x, y);
				}
				if ((c == 77) && x == 70)
				{
					x = 1;
					gotoxy(hout, x, y);
				}
			}
			else
			{
				if (d == 81 || d == 113)
					break;
				if (d == 32 && y >= 1 && y <= 17 && x >= 1 && x <= 69)
					cout << char(127) << char(8);
			}
		}

		gotoxy(hout, 0, 23);
		cout << "游戏结束，按回车键退出." << endl;

		//暂停(此处作业要求是只能按回车退出，目前的getchar示例，是允许按任意键+回车退出，且任意键会出现在屏幕上)
		while (1)
		{
			char d = _getch();
			if (d == char(13))
			{
				cls(hout);
				int x = menu();
				if (x == 49 || x == 50)
					move_by_ijkl(x);
				else if (x == 51 || x == 52)
					move_by_arrow(x);
				else if (x == 53 || x == 54)
					move_by_ijkl(x);
				else;
				break;
			}
			else
			{
				continue;
			}
		}
	}
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数仅用于初始演示，可以按题目要求全部推翻重写
***************************************************************************/
int main()
{
	int x = menu();
	if (x == 49 || x == 50)
		move_by_ijkl(x);
	else if (x == 51 || x == 52)
		move_by_arrow(x);
	else if (x == 53 || x == 54)
		move_by_ijkl(x);
	else;
	return 0;
}
//不一定生成二十个字母，有可能，因为随机生成的坐标可能会重叠，这样字母就会少于二十个 
