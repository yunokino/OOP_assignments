/* 2152041 王浩 信07 */
#include <iostream>
#include<iomanip>
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
		w += 7;
	return w % 7;
}

int main()
{
	int year;
	int month[24][21];
	int day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	while (1)
	{
		cout << "请输入年份[1900-2100]\n";
		cin >> year;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		else
		{
			if (year < 1900 || year > 2100)
			{
				cin.ignore(65536, '\n');
				continue;
			}
			else
				break;
		}
	}
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		day[1] = 29;
	cout << year << "年的日历:\n" << endl;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 7; j++)
		{
			month[i][j] = j + 1 + i * 7 - zeller(year, 1, 1);
			if (month[i][j] <= 0 || month[i][j] > day[0])
				month[i][j] = 0;
		}
	for (int i = 0; i < 6; i++)
		for (int j = 7; j < 14; j++)
		{
			month[i][j] = j - 6 + i * 7 - zeller(year, 2, 1);
			if (month[i][j] <= 0 || month[i][j] > day[1])
				month[i][j] = 0;
		}
	for (int i = 0; i < 6; i++)
		for (int j = 14; j < 21; j++)
		{
			month[i][j] = j - 13 + i * 7 - zeller(year, 3, 1);
			if (month[i][j] <= 0 || month[i][j] > day[2])
				month[i][j] = 0;
		}
	for (int i = 6; i < 12; i++)
		for (int j = 0; j < 7; j++)
		{
			month[i][j] = j + 1 + (i - 6) * 7 - zeller(year, 4, 1);
			if (month[i][j] <= 0 || month[i][j] > day[3])
				month[i][j] = 0;
		}
	for (int i = 6; i < 12; i++)
		for (int j = 7; j < 14; j++)
		{
			month[i][j] = j - 6 + (i - 6) * 7 - zeller(year, 5, 1);
			if (month[i][j] <= 0 || month[i][j] > day[4])
				month[i][j] = 0;
		}
	for (int i = 6; i < 12; i++)
		for (int j = 14; j < 21; j++)
		{
			month[i][j] = j - 13 + (i - 6) * 7 - zeller(year, 6, 1);
			if (month[i][j] <= 0 || month[i][j] > day[5])
				month[i][j] = 0;
		}
	for (int i = 12; i < 18; i++)
		for (int j = 0; j < 7; j++)
		{
			month[i][j] = j + 1 + (i - 12) * 7 - zeller(year, 7, 1);
			if (month[i][j] <= 0 || month[i][j] > day[6])
				month[i][j] = 0;
		}
	for (int i = 12; i < 18; i++)
		for (int j = 7; j < 14; j++)
		{
			month[i][j] = j - 6 + (i - 12) * 7 - zeller(year, 8, 1);
			if (month[i][j] <= 0 || month[i][j] > day[7])
				month[i][j] = 0;
		}
	for (int i = 12; i < 18; i++)
		for (int j = 14; j < 21; j++)
		{
			month[i][j] = j - 13 + (i - 12) * 7 - zeller(year, 9, 1);
			if (month[i][j] <= 0 || month[i][j] > day[8])
				month[i][j] = 0;
		}
	for (int i = 18; i < 24; i++)
		for (int j = 0; j < 7; j++)
		{
			month[i][j] = j + 1 + (i - 18) * 7 - zeller(year, 10, 1);
			if (month[i][j] <= 0 || month[i][j] > day[9])
				month[i][j] = 0;
		}
	for (int i = 18; i < 24; i++)
		for (int j = 7; j < 14; j++)
		{
			month[i][j] = j - 6 + (i - 18) * 7 - zeller(year, 11, 1);
			if (month[i][j] <= 0 || month[i][j] > day[10])
				month[i][j] = 0;
		}
	for (int i = 18; i < 24; i++)
		for (int j = 14; j < 21; j++)
		{
			month[i][j] = j - 13 + (i - 18) * 7 - zeller(year, 12, 1);
			if (month[i][j] <= 0 || month[i][j] > day[11])
				month[i][j] = 0;
		}
	bool re1 = 0, re2 = 0, re3 = 0, re4 = 0;
	for (int i = 0; i < 24; i++)
	{
		if (i == 0)
		{
			cout << "            1月                             2月                             3月\n";
			cout << "Sun Mon Tue Wed Thu Fri Sat     Sun Mon Tue Wed Thu Fri Sat     Sun Mon Tue Wed Thu Fri Sat\n";
		}
		if (i == 6)
		{
			cout << "            4月                             5月                             6月\n";
			cout << "Sun Mon Tue Wed Thu Fri Sat     Sun Mon Tue Wed Thu Fri Sat     Sun Mon Tue Wed Thu Fri Sat\n";
		}
		if (i == 12)
		{
			cout << "            7月                             8月                             9月\n";
			cout << "Sun Mon Tue Wed Thu Fri Sat     Sun Mon Tue Wed Thu Fri Sat     Sun Mon Tue Wed Thu Fri Sat\n";
		}
		if (i == 18)
		{
			cout << "           10月                            11月                            12月\n";
			cout << "Sun Mon Tue Wed Thu Fri Sat     Sun Mon Tue Wed Thu Fri Sat     Sun Mon Tue Wed Thu Fri Sat\n";
		}
		for (int j = 0; j < 21; j++)
		{
			if (month[5][j] != 0)
			{
				re1 = 1;
				break;
			}
		}
		for (int j = 0; j < 21; j++)
		{
			if (month[11][j] != 0)
			{
				re2 = 1;
				break;
			}
		}
		for (int j = 0; j < 21; j++)
		{
			if (month[17][j] != 0)
			{
				re3 = 1;
				break;
			}
		}
		for (int j = 0; j < 21; j++)
		{
			if (month[23][j] != 0)
			{
				re4 = 1;
				break;
			}
		}
		for (int j = 0; j < 21; j++)
		{
			if (month[i][j] > 0)
				cout << left << setw(2) << month[i][j] << "  ";
			else if (i != 5 && i != 11 && i != 17 && i != 23 && month[i][j] == 0)
				cout << "    ";
			else if ((((!re1) && i == 5) || ((!re2) && i == 11) || ((!re3) && i == 17) || ((!re4) && i == 23)))
			{
				cout << endl;
				break;
			}
			else
				cout << "    ";
			if (j == 6 || j == 13)
				cout << "    ";
			if (j == 20)
				cout << endl;
		}
		if (re1 && i == 5)
			cout << endl;
		if (re2 && i == 11)
			cout << endl;
		if (re3 && i == 17)
			cout << endl;
		if (re4 && i == 23)
			cout << endl;
	}
	cout << endl;
	return 0;
}






