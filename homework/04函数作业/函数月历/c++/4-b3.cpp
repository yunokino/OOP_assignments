/*王浩 信07 2152041*/
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
	int a = int(y / 100);//年份前两位
	int b = y - int(y / 100) * 100;//年份后两位
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
	cout << y << "年" << m << "月\n";
	cout << "======================================================\n";
	cout << "星期日  星期一  星期二  星期三  星期四  星期五  星期六\n";
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
		cout << "请输入年[1900-2100]、月\n";
		cin >> year >> m;
		cout << endl;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "输入错误，请重新输入\n";
			continue;
		}
		else
		{
			if (year < 1900 || year > 2100)
			{
				cout << "年份不正确，请重新输入\n";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			else if (m < 0 || m > 12)
			{
				cout << "月份不正确，请重新输入\n";
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
