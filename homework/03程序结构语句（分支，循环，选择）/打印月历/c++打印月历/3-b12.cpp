/*���� ��07 2152041*/
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main()
{
	int a, b, c, d;
	int i = 1;

	while (1)
	{
		cout << "���������(2000-2030)���·�(1-12) :";
		cin >> a >> b;
		if (cin.fail() || a < 2000 || a>2030 || b > 12 || b < 1)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "����Ƿ�������������" << endl;
			continue;
		}
		else
			break;
	}
	while (1)
	{
		cout << "������" << a << "��" << b << "��1�յ�����(0 - 6��ʾ������ - ������) :";
		cin >> c;
		if (cin.fail() || c < 0 || c>6)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "����Ƿ�������������" << endl;
			continue;
		}
		else
			break;
	}
	d = c - 1;
	cout << a << "��" << b << "�µ�����Ϊ:\n";
	cout << "������  ����һ  ���ڶ�  ������  ������  ������  ������\n";
	if (b == 1 || b == 3 || b == 5 || b == 7 || b == 8 || b == 10 || b == 12)
	{
		for (i = 1; i <= 31; i++)
		{
			if (c == 0 && i == 1)
				cout << resetiosflags(ios::right) << setw(4) << i;
			else if (c != 0 && i == 1)
			{
				cout << "    ";
				if (d >= 0)
				{
					int d = c - 2;
					for (d; d >= 0; d--)
						cout << "        ";
				}
				cout << resetiosflags(ios::right) << setw(8) << i;
				c = c + 1;
				continue;
			}
			else if (c == 0 && i != 1)
				cout << resetiosflags(ios::right) << setw(4) << i;
			else
				cout << resetiosflags(ios::right) << setw(8) << i;
			c++;
			if (c == 7)
			{
				cout << endl;
				c = 0;
			}
		}
	}
	if (b == 4 || b == 6 || b == 9 || b == 11)
	{
		for (i = 1; i <= 30; i++)
		{
			if (c == 0 && i == 1)
				cout << resetiosflags(ios::right) << setw(4) << i;
			else if (c != 0 && i == 1)
			{
				cout << "    ";
				if (d >= 0)
				{
					int d = c - 2;
					for (d; d >= 0; d--)
						cout << "        ";
				}
				cout << resetiosflags(ios::right) << setw(8) << i;
				c = c + 1;
				continue;
			}
			else if (c == 0 && i != 1)
				cout << resetiosflags(ios::right) << setw(4) << i;
			else
				cout << resetiosflags(ios::right) << setw(8) << i;
			c++;
			if (c == 7)
			{
				cout << endl;
				c = 0;
			}
		}
	}
	if (b == 2)
	{
		for (i = 1; i <= ((a % 4 == 0&&a%100!=0)||a%400==0) ? 29 : 28); i++)
		{
			if (c == 0 && i == 1)
				cout << resetiosflags(ios::right) << setw(4) << i;
			else if (c != 0 && i == 1)
			{
				cout << "    ";
				if (d >= 0)
				{
					int d = c - 2;
					for (d; d >= 0; d--)
						cout << "        ";
				}
				cout << resetiosflags(ios::right) << setw(8) << i;
				c = c + 1;
				continue;
			}
			else if (c == 0 && i != 1)
				cout << resetiosflags(ios::right) << setw(4) << i;
			else
				cout << resetiosflags(ios::right) << setw(8) << i;
			c++;
			if (c == 7)
			{
				cout << endl;
				c = 0;
			}
		}
	}

	return 0;
}
