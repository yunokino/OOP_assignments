/*���� ��07 2152041*/
#include <iostream>
using namespace std;

int year(int a)
{
	return (a % 4 == 0 ? 1 : 0);
}

int day(int a, int b, int c,int leap)
{
	if (a == 1)
	{
		if (b > 12 || b < 1)
		{
			cout << "�������-�·ݲ���ȷ\n";
			leap = 0;
		}
		else
		{
			if (b == 1 || b == 3 || b == 5 || b == 7 || b == 8 || b == 10 || b == 12)
			{
				if (c > 31 || c < 1)
				{
					cout << "�������-�����µĹ�ϵ�Ƿ�\n";
					leap = 0;
				}
			}
			else if (b == 2)
			{
				if (c > 29 || c < 10)
				{
					cout << "�������-�����µĹ�ϵ�Ƿ�\n";
					leap = 0;
				}
			}
			else
			{
				if (c > 30 || c < 1)
				{
					cout << "�������-�����µĹ�ϵ�Ƿ�\n";
					leap = 0;
				}
			}
			if (leap)
			{
				int d[13] = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };
				for (int i = 0; i + 1 <= b; i++)
					c += d[i];
			}
		}
	}
	else
	{
		if (b > 12 || b < 1)
		{
			cout << "�������-�·ݲ���ȷ\n";
			leap = 0;
		}
		else
		{
			if (b == 1 || b == 3 || b == 5 || b == 7 || b == 8 || b == 10 || b == 12)
			{
				if (c > 31 || c < 1)
				{
					cout << "�������-�����µĹ�ϵ�Ƿ�\n";
					leap = 0;
				}
			}
			else if (b == 2)
			{
				if (c > 28 || c < 10)
				{
					cout << "�������-�����µĹ�ϵ�Ƿ�\n";
					leap = 0;
				}
			}
			else
			{
				if (c > 30 || c < 1)
				{
					cout << "�������-�����µĹ�ϵ�Ƿ�\n";
					leap = 0;
				}
			}
			if (leap)
			{
				int d[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
				for (int i = 0; i + 1 <= b; i++)
					c += d[i];
			}
		}
	}
	return (leap==1?c: 0);
}
int main()
{
	int a, b, c;
	cout << "�������꣬�£���" << endl;
	cin >> a >> b >> c;
	year(a);
	if(day(year(a), b, c, 1))
		cout << a << "-" << b << "-" << c << "��" << a << "��ĵ�" << day(year(a), b, c,1) << "��" << endl;
	return 0;
}