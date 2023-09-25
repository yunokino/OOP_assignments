/* 2152041 ���� �ƿ� */
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include "../include/cmd_console_tools.h"
#include "90-01-b1-hanoi.h"
using namespace std;
/* ----------------------------------------------------------------------------------

	 ���ļ����ܣ�
	1����ű� hanoi_main.cpp �и��ݲ˵�����ֵ���õĸ��˵����Ӧ��ִ�к���

	 ���ļ�Ҫ��
	1�����������ⲿȫ�ֱ�����const��#define�������Ʒ�Χ�ڣ�
	2�������徲̬ȫ�ֱ�����������Ҫ��������Ҫ�����ĵ���ʾ��ȫ�ֱ�����ʹ��׼���ǣ����á����á��ܲ��þ������ã�
	3����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	4���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */
int step = 1;
int speed;
int a, b, c;//��¼Բ��������Բ�̵�����
int src[10], tmp[10], dst[10];
/***************************************************************************
  �������ƣ�move
  ��    �ܣ��ƶ�����
  ���������n,x,y,_1,_2,_3,_4,_8,_9
  �� �� ֵ��
  ˵    ����ǰ��������������ĸı䶼������ʵ�֣���Ϊһ�������Ĳ��豻�ݹ麯
			������,Ĭ�ϲ�����ʼ����ͷ�ļ���
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
			cout << "��ʼ:";
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
			cout << "��" << setw(4) << step << " ��(" << setw(2) << n << "#: " << x << "-->" << y << ")";
		if (_3)
		{
			if (_4)
			{
				cct_setcursor(CURSOR_INVISIBLE);
				print_vertical();
				cout << "��" << setw(4) << step << " ��(" << setw(2) << n << "#: " << x << "-->" << y << ")";
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
		cout << "��" << setw(4) << step << " ��(" << setw(2) << n << "#: " << x << "-->" << y << ")";
		print_horizontal();
	}
	step++;
	if (!_4)
		cout << endl;
}
/***************************************************************************
  �������ƣ�sleep1
  ��    �ܣ�������ʱ����
  ���������speed
  �� �� ֵ��
  ˵    ������ʱ�����ж�ε��ã����Ե����г�Ϊһ������
			Ϊ�˱���speedΪ��ʱ��Բ���ƶ���Ҫ�س����ƶ������⣬�г�������ʱ����
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
  �������ƣ�sleep2
  ��    �ܣ�������ʱ����
  ���������speed
  �� �� ֵ��
  ˵    ������ʱ�����ж�ε��ã����Ե����г�Ϊһ������
			Ϊ�˱���speedΪ��ʱ��Բ���ƶ���Ҫ�س����ƶ������⣬�г�������ʱ����
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
  �������ƣ�print_horizontal
  ��    �ܣ���ӡ��������
  ���������
  �� �� ֵ��
  ˵    ����Ϊ������ո񣬷������������Ϊ�˶��룬�Ե�һ�������������⴦��
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
  �������ƣ�print_vertical
  ��    �ܣ���ӡ��������
  ���������
  �� �� ֵ��
  ˵    ����Ϊ������ո񣬷��������������겻�ɼ��Ļ��Ӿ�Ч������
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
  �������ƣ�print_column
  ��    �ܣ���ӡ����
  ���������
  �� �� ֵ��
  ˵    ������demo��ͬ�������ȴ��µ��ϴ�ӡһ�У��ٸı�x�����ӡ��һ�У���겻�ɼ�����
			��Ч������
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
  �������ƣ�print_disk
  ��    �ܣ���ӡԲ��
  ���������num��start_column
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�move_disk
  ��    �ܣ��ƶ�Բ��
  ���������num,start_column,end_column
  �� �� ֵ��
  ˵    ������������ƽ�ƣ�������
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
  �������ƣ�play_game
  ��    �ܣ�ִ�еھ�������Ϸ
  ���������num goal_column
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void play_game(int num,char goal_column)
{
	speed = 5;
	while (1)
	{
		cct_gotoxy(34, 34);
		cout << "\n�������ƶ�������(������ʽ��AC=A���˵������ƶ���C��Q=�˳�) ��";
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
				cout << "\nԴ������Ϊ��!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			if ((src[a - 1] > tmp[b - 1]) && (b >= 1))
			{
				cout << "\n���̲���ѹС��!";
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
				cout << "\nԴ������Ϊ��!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			if ((src[a - 1] > dst[c - 1]) && (c>= 1))
			{
				cout << "\n���̲���ѹС��!";
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
				cout << "\nԴ������Ϊ��!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			if ((tmp[b - 1] > src[a - 1]) && (a >= 1))
			{
				cout << "\n���̲���ѹС��!";
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
				cout << "\nԴ������Ϊ��!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			if ((tmp[b - 1] > dst[c - 1]) && (c >= 1))
			{
				cout << "\n���̲���ѹС��!";
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
				cout << "\nԴ������Ϊ��!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			if ((dst[c - 1] > src[a - 1]) && (a >= 1))
			{
				cout << "\n���̲���ѹС��!";
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
				cout << "\nԴ������Ϊ��!";
				Sleep(2000);
				cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                 ";
				continue;
			}
			if ((dst[c - 1] > tmp[b - 1]) && (b >= 1))
			{
				cout << "\n���̲���ѹС��!";
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
	cout << "\n\n��Ϸ����!!!!!\n";
}
/***************************************************************************
  �������ƣ�honoi
  ��    �ܣ��ݹ������������
  ���������n, src, tmp, dst,  _1,_2,_3,  _4,_8,_9
  �� �� ֵ��
  ˵    ����Ψһ��һ���ݹ麯��������ֻ�а��У�Ĭ�ϲ�����ʼ����ͷ�ļ���
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
  �������ƣ�in_put
  ��    �ܣ�������������ĺ���
  ���������num,*x,* f, * g, * h,* speed
  �� �� ֵ��
  ˵    ������ָ�������Ҫ������
***************************************************************************/
void in_put(int num, int* x, char* f, char* g, char* h, int* speed)
{

	while (1) {
		cout << "�����뺺ŵ���Ĳ���(1-10)��\n";
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
		cout << "��������ʼ��(A-C)��\n";
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
		cout << "������Ŀ����(A-C)��\n";
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
			cout << "Ŀ����(" << *h << ")��������ʼ��(" << *f << ")��ͬ\n";
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
			cout << "�������ƶ��ٶ�(0-5: 0-���س�������ʾ 1-��ʱ� 5-��ʱ���)\n";
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
  �������ƣ�act_honoi
  ��    �ܣ�ִ�и��ֲ���,ָ��ͬѡ��
  ���������num
  �� �� ֵ��
  ˵    ����
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
			cout << "�� " << f << " �ƶ��� " << h << "���� " << x << " �㣬��ʱ����Ϊ " << speed << endl;
			hanoi(x, f, g, h, 0, 1, 1, 1);
			cct_setcursor(CURSOR_VISIBLE_NORMAL);
			for (int i = 0; i <= 20; i++)
				cout << endl;
			break;
		case 5:
			print_column();
			break;
		case 6:
			cout << "�� " << f << " �ƶ��� " << h << "���� " << x << " ��" << endl;
			print_column();
			print_disk(x, f);
			break;
		case 7:
			cout << "�� " << f << " �ƶ��� " << h << "���� " << x << " ��" << endl;
			print_column();
			print_disk(x, f);
			move_disk(1, f, (num % 2 == 0 ? h : g));
			break;
		case 8:
			cout << "�� " << f << " �ƶ��� " << h << "���� " << x << " �㣬��ʱ����Ϊ " << speed << endl;
			print_column();
			print_disk(x, f);
			hanoi(x, f, g, h, 0, 1, 1, 1, 1);
			cct_gotoxy(0, 34);
			break;
		case 9:
			cout << "�� " << f << " �ƶ��� " << h << "���� " << x << " ��" << endl;
			print_column();
			print_disk(x, f);
			print_vertical();
			cout << "��ʼ : ";
			print_horizontal();
			play_game(x,h);
			break;
		default:
			break;
	}
}