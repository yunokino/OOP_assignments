/* 2152041 ���� ��07 */
#include <iostream>
#include <iomanip>
#include<windows.h>


using namespace std;

/* ----����Ҫ��----
   1���������������ͷ�ļ�
   2����������ȫ�ֱ�������̬�ֲ�����
   3������������������������ʼ/Ŀ�����ĺ���������������ʹ��ѭ�������������
   4����������ú������У���main�в���������κ���ʽ��ѭ��
	  ���������main�н��У���main���������ѭ��
   --------------------------------------------------------------------- */

   /***************************************************************************
	 �������ƣ�
	 ��    �ܣ���ӡn�㺺ŵ�����ƶ�˳��
	 ���������int n������
			   char src����ʼ��
			   char tmp���м���
			   char dst��Ŀ����
	 �� �� ֵ��
	 ˵    ����1�����������βΡ��������;���׼��
			   2������������������κ���ʽ��ѭ��
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
	cout << "�� " << x<< " �ƶ��� " << y << "���� " << n << " �㣬��ʱ����Ϊ " << sleep << "��" << (display == 0 ? "��" : "") << "��ʾ�ڲ�����ֵ\n";
	print();
	if (display == 1)
		cout << "��" << setw(4) << step << "��" << "(" << n << "#: " << x << "-->" << y << ") ";
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
  �������ƣ�
  ��    �ܣ���ӡn�㺺ŵ�����ƶ�˳��
  ���������int n������
			char src����ʼ��
			char tmp���м���
			char dst��Ŀ����
  �� �� ֵ��
  ˵    ����1�����������βΡ��������;���׼��
			2������������������κ���ʽ��ѭ��
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    �����������(��������뺯��)�����õݹ麯��
***************************************************************************/
int main()
{
	int x;
	char f, g, h;
	g = '0';

	while (1) {
		cout << "�����뺺ŵ���Ĳ���(1-10)��\n";
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
		cout << "��������ʼ��(A-C)��\n";
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
		cout << "������Ŀ����(A-C)��\n";
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
			cout << "Ŀ����(" << h << ")��������ʼ��(" << f << ")��ͬ\n";
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
		cout << "�������ƶ��ٶ�(0-5: 0-���س�������ʾ 1-��ʱ� 5-��ʱ���)\n";
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
		cout << "�������Ƿ���ʾ�ڲ�����ֵ(0-����ʾ 1-��ʾ)\n";
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
	cout << "�� " << f << " �ƶ��� " << h << "���� " << x<< " �㣬��ʱ����Ϊ " << sleep << "��" << (display == 0 ? "��" : "") << "��ʾ�ڲ�����ֵ\n";
	for (int i = 0; i <= 14; i++)
		cout << endl;
	cout << "��ʼ:                ";
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
