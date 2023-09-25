/*���� ��07 2152041*/
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int zeller(int y, int m, int d)
{
	int w;
	if (m == 1 || m == 2)
	{
		y -= 1;
		m += 12;
	}
	int a = int(y / 100);//���ǰ��λ
	int b = y - int(y / 100) * 100;//��ݺ���λ
	w = b + int(b / 4) + int(a / 4) - 2 * a + int(13 * (m + 1) / 5) + d - 1;
	while (w < 0)
	{
		w += 7;
	}
	return w % 7;
}
int calendar(int y, int m, int d)
{
	int i = 1;
	cout << y << "��" << m << "��\n";
	cout << "======================================================\n";
	cout << "������  ����һ  ���ڶ�  ������  ������  ������  ������\n";
	cout << "======================================================\n";
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
	{
		for (i = 1; i <= 31; i++)
		{
			if (d == 0 && i == 1)
				cout << resetiosflags(ios::right) << setw(4) << i;
			else if (d != 0 && i == 1)
			{
				cout << "    ";
				if (d >= 0)
				{
					int e = d - 2;
					for (e; e >= 0; e--)
						cout << "        ";
				}
				cout << resetiosflags(ios::right) << setw(8) << i;
				d = d + 1;
				if (d >= 7)
				{
					cout << endl;
					d = 0;
				}
				continue;
			}
			else if (d == 0 && i != 1)
				cout << resetiosflags(ios::right) << setw(4) << i;
			else
				cout << resetiosflags(ios::right) << setw(8) << i;
			d++;
			if (d >= 7)
			{
				cout << endl;
				d = 0;
			}
		}
	}
	if (m == 4 || m == 6 || m == 9 || m == 11)
	{
		for (i = 1; i <= 30; i++)
		{
			if (d == 0 && i == 1)
				cout << resetiosflags(ios::right) << setw(4) << i;
			else if (d != 0 && i == 1)
			{
				cout << "    ";
				if (d >= 0)
				{
					int e = d - 2;
					for (e; e >= 0; e--)
						cout << "        ";
				}
				cout << resetiosflags(ios::right) << setw(8) << i;
				d = d + 1;
				if (d >= 7)
				{
					cout << endl;
					d = 0;
				}
				continue;
			}
			else if (d == 0 && i != 1)
				cout << resetiosflags(ios::right) << setw(4) << i;
			else
				cout << resetiosflags(ios::right) << setw(8) << i;
			d++;
			if (d == 7)
			{
				cout << endl;
				d = 0;
			}
		}
	}
	if (m == 2)
	{
		for (i = 1; i <= ((a % 4 == 0&&a%100!=0)||a%400==0) ? 29 : 28); i++)
		{
			if (d == 0 && i == 1)
				cout << resetiosflags(ios::right) << setw(4) << i;
			else if (d != 0 && i == 1)
			{
				cout << "    ";
				if (d >= 0)
				{
					int e = d - 2;
					for (e; e >= 0; e--)
						cout << "        ";
				}
				cout << resetiosflags(ios::right) << setw(8) << i;
				d = d + 1;
				if (d >= 7)
				{
					cout << endl;
					d = 0;
				}
				continue;
			}
			else if (d == 0 && i != 1)
				cout << resetiosflags(ios::right) << setw(4) << i;
			else
				cout << resetiosflags(ios::right) << setw(8) << i;
			d++;
			if (d == 7)
			{
				cout << endl;
				d = 0;
			}
		}
	}
	return 0;
}
int main()
{
	int year, m;
	while (1)
	{
		cout << "��������[1900-2100]����\n";
		cin >> year >> m;
		cout << endl;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "�����������������\n";
			continue;
		}
		else
		{
			if (year < 1900 || year > 2100)
			{
				cout << "��ݲ���ȷ������������\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			else if (m < 0 || m > 12)
			{
				cout << "�·ݲ���ȷ������������\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			else
				break;
		}
	}
	zeller(year, m, 1);
	calendar(year, m, (zeller(year, m, 1)));
	cout << endl;
	cout << endl;
	return 0;
}
