/* 2152041 ���� ��07 */
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;

const int MAX_X = 69;	//����*��ɵı߿�Ŀ��
const int MAX_Y = 17;	//����*��ɵı߿�ĸ߶�

/***************************************************************************
  �������ƣ�
  ��    �ܣ������system("cls")һ���Ĺ��ܣ���Ч�ʸ�
  ���������
  �� �� ֵ��
  ˵    �������������Ļ���������������ǿɼ���������(ʹ�õ�ǰ��ɫ)
***************************************************************************/
void cls(const HANDLE hout)
{
	COORD coord = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO binfo; /* to get buffer info */
	DWORD num;

	/* ȡ��ǰ��������Ϣ */
	GetConsoleScreenBufferInfo(hout, &binfo);
	/* ����ַ� */
	FillConsoleOutputCharacter(hout, (TCHAR)' ', binfo.dwSize.X * binfo.dwSize.Y, coord, &num);
	/* ������� */
	FillConsoleOutputAttribute(hout, binfo.wAttributes, binfo.dwSize.X * binfo.dwSize.Y, coord, &num);

	/* ���ص�(0,0) */
	SetConsoleCursorPosition(hout, coord);
	return;
}

/***************************************************************************
  �������ƣ�gotoxy
  ��    �ܣ�������ƶ���ָ��λ��
  ���������HANDLE hout ������豸���
			int X       ��ָ��λ�õ�x����
			int Y       ��ָ��λ�õ�y����
  �� �� ֵ����
  ˵    �����˺�����׼�޸�
***************************************************************************/
void gotoxy(const HANDLE hout, const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}

/***************************************************************************
  �������ƣ�showch
  ��    �ܣ���ָ��λ�ô���ӡһ��ָ�����ַ�
  ���������HANDLE hout ������豸���
			int X       ��ָ��λ�õ�x����
			int Y       ��ָ��λ�õ�y����
			char ch     ��Ҫ��ӡ���ַ�
  �� �� ֵ����
  ˵    �����˺�����׼�޸�
***************************************************************************/
void showch(const HANDLE hout, const int X, const int Y, const char ch)
{
	gotoxy(hout, X, Y);
	putchar(ch);
}

/***************************************************************************
  �������ƣ�init_border
  ��    �ܣ���ʾ��ʼ�ı߿�����ַ�
  ���������HANDLE hout������豸���
  �� �� ֵ����
  ˵    �����˺�����׼�޸�
***************************************************************************/
void init_border(const HANDLE hout)
{
	gotoxy(hout, 0, 0);	//����ƻ����Ͻ�(0,0)
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

	/* �����ʾ20����д��ĸ����ĸ��ֵ��XY���궼�����ʾ
	   rand()�����Ĺ��ܣ��������һ���� 0-32767 ֮�������
	   ˼������ʲô����£��������ѭ��ִ�����ɺ��㿴����ʵ����ĸ��������20���� */
	int i;
	for (i = 0; i < 20; i++)
		showch(hout, rand() % MAX_X + 1, rand() % MAX_Y + 1, 'A' + rand() % 26);

	return;
}

/* -- �������ӵ����ɺ������Է��ڴ˴� --*/
int menu()
{
	cout << "1.��I��J��K��L��������������(��Сд���ɣ��߽�ֹͣ)" << endl;
	cout << "2.��I��J��K��L��������������(��Сд���ɣ��߽����)" << endl;
	cout << "3.�ü�ͷ�������������ң��߽�ֹͣ" << endl;
	cout << "4.�ü�ͷ�������������ң��߽����" << endl;
	cout << "5.��I��J��K��L��������������(��Сд���ɣ��߽�ֹͣ)" << endl;
	cout << "6.��I��J��K��L��������������(��Сд���ɣ��߽����)" << endl;
	cout << "0.�˳�" << endl;
	cout << "[��ѡ��0 - 6] ";
	int x;
	while (1)
	{
		const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //ȡ��׼����豸��Ӧ�ľ��
		x = _getche();
		if (x == 48 || x == 49 || x == 50 || x == 51 || x == 52 || x == 53 || x == 54)
			break;
		else
		{
			cls(hout);
			cout << "1.��I��J��K��L��������������(��Сд���ɣ��߽�ֹͣ)" << endl;
			cout << "2.��I��J��K��L��������������(��Сд���ɣ��߽����)" << endl;
			cout << "3.�ü�ͷ�������������ң��߽�ֹͣ" << endl;
			cout << "4.�ü�ͷ�������������ң��߽����" << endl;
			cout << "5.��I��J��K��L��������������(��Сд���ɣ��߽�ֹͣ)" << endl;
			cout << "6.��I��J��K��L��������������(��Сд���ɣ��߽����)" << endl;
			cout << "0.�˳�" << endl;
			cout << "[��ѡ��0 - 6] ";
		}
	}
	return x;
}

int move_by_arrow(int a);

int move_by_ijkl(int a)
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //ȡ��׼����豸��Ӧ�ľ��

	/* ����α����������ӣ�ֻ���ڳ���ʼʱִ��һ�μ��� */
	srand((unsigned int)(time(0)));

	/* �˾�������ǵ���ϵͳ��cls�������� */
	cls(hout);

	/* ��ʾ��ʼ�ı߿����е�����ַ� */
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
		cout << "��Ϸ���������س����˳�." << endl;

		//��ͣ(�˴���ҵҪ����ֻ�ܰ��س��˳���Ŀǰ��getcharʾ���������������+�س��˳�������������������Ļ��
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
		cout << "��Ϸ���������س����˳�." << endl;

		//��ͣ(�˴���ҵҪ����ֻ�ܰ��س��˳���Ŀǰ��getcharʾ���������������+�س��˳�������������������Ļ��)
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
		cout << "��Ϸ���������س����˳�." << endl;

		//��ͣ(�˴���ҵҪ����ֻ�ܰ��س��˳���Ŀǰ��getcharʾ���������������+�س��˳�������������������Ļ��)
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
		cout << "��Ϸ���������س����˳�." << endl;

		//��ͣ(�˴���ҵҪ����ֻ�ܰ��س��˳���Ŀǰ��getcharʾ���������������+�س��˳�������������������Ļ��)
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
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //ȡ��׼����豸��Ӧ�ľ��

	/* ����α����������ӣ�ֻ���ڳ���ʼʱִ��һ�μ��� */
	srand((unsigned int)(time(0)));

	/* �˾�������ǵ���ϵͳ��cls�������� */
	cls(hout);

	/* ��ʾ��ʼ�ı߿����е�����ַ� */
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
		cout << "��Ϸ���������س����˳�." << endl;

		//��ͣ(�˴���ҵҪ����ֻ�ܰ��س��˳���Ŀǰ��getcharʾ���������������+�س��˳�������������������Ļ��
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
		cout << "��Ϸ���������س����˳�." << endl;

		//��ͣ(�˴���ҵҪ����ֻ�ܰ��س��˳���Ŀǰ��getcharʾ���������������+�س��˳�������������������Ļ��)
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main���������ڳ�ʼ��ʾ�����԰���ĿҪ��ȫ���Ʒ���д
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
//��һ�����ɶ�ʮ����ĸ���п��ܣ���Ϊ������ɵ�������ܻ��ص���������ĸ�ͻ����ڶ�ʮ�� 
