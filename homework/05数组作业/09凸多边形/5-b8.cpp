/* 2152041 ���� ��07 */
#include <iostream>
#include<cmath>
using namespace std;

int main()
{
	int point;
	int i = 0;
	double a[7] = { 0 };
	double b[7] = { 0 };
	while (1)
	{
		cout << "���������εĶ�������(4-7)\n";
		cin >> point;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if (point >= 4 && point <= 7)
		{
			cin.ignore(65536, '\n');
			break;
		}
	}
	cout << "�밴˳ʱ��/��ʱ�뷽������" << point << "�������x,y���꣺\n";
	while (i <= point - 1)
	{
		while (1)
		{
			cout << "�������" << i + 1 << "����������꣺\n";
			cin >> a[i] >> b[i];
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(65536, '\n');
				continue;
			}
			else
				break;
		}
		i++;
	}
	double mianji = 0;
	bool yice = 1;
	double A, B, C;
	for (int i = 0; i <= point - 3; i++)
	{
		A = b[i + 1] - b[i];
		B = a[i] - a[i + 1];
		C = a[i + 1] * b[i] - a[i] * b[i + 1];
		if (A * a[i + 2] + B * b[i + 2] + C >= 0)
		{
			for (int j = 0; j <= point-1; j++)
			{
				if (j != i && j != i + 1 && j != i + 2)
				{
					if (A * a[j] + B * b[j] + C <= 0)
						yice = 0;
					break;
				}
			}
		}
		else
		{
			for (int j = 0; j <= point-1; j++)
			{
				if (j != i && j != i + 1 && j != i + 2)
				{
					if (A * a[j] + B * b[j] + C >= 0)
						yice = 0;
					break;
				}
			}
		}
	}
	for (int j = 1; j <= point - 2; j++)
		mianji += ((a[j] - a[0]) * (b[j + 1] - b[0]) - (b[j] - b[0]) * (a[j + 1] - a[0])) / 2.0;
	if (yice)
		cout << "͹" << point << "���ε����=" << fabs(mianji);
	else
		cout << "����͹" << point << "����";
	cout << endl;
	return 0;
}
