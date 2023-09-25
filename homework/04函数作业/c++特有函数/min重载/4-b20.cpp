/*2152041 王浩 信07*/
#include<iostream>
using namespace std;

void min(int a=65536, int b=65536,int c=65536,int d=65536)
{
	cout << "min=";
	(a < b ? a : b) < (c < d ? c : d) ? cout << (a < b ? a : b) << endl : cout << (c < d ? c : d) << endl;
}

int main()
{
	int n, a, b, c, d;
	while (1) {
		cout << "请输入个数num及num个正整数：\n";
		cin >> n;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		else
			break;
	}
	if (n == 2)
	{
		while (1)
		{
			cin >> a >> b;
			if (cin.fail() || a <= 0 || b <= 0)
			{
				cin.clear();
				cin.ignore(65536, '\n');
				while (1) {
					cout << "请输入个数num及num个正整数：\n";
					cin >> n >> a >> b;
					if (cin.fail() || a <= 0 || b <= 0)
					{
						cin.clear();
						cin.ignore(65536, '\n');
						continue;
					}
					else
					{
						min(a, b);
						break;
					}
				}
				break;
			}
			else
			{
				min(a, b);
				break;
			}
		}
	}
	else if (n == 3)
	{
		while (1)
		{
			cin >> a >> b >> c;
			if (cin.fail() || a <= 0 || b <= 0 || c <= 0)
			{
				cin.clear();
				cin.ignore(65536, '\n');
				while (1) {
					cout << "请输入个数num及num个正整数：\n";
					cin >> n >> a >> b >> c;
					if (cin.fail() || a <= 0 || b <= 0 || c <= 0)
					{
						cin.clear();
						cin.ignore(65536, '\n');
						continue;
					}
					else
					{
						min(a, b, c);
						break;
					}
				}
				break;
			}
			else
			{
				min(a, b, c);
				break;
			}
		}
	}
	else if (n == 4)
	{
		while (1)
		{
			cin >> a >> b >> c >> d;
			if (cin.fail() || a <= 0 || b <= 0 || c <= 0 || d <= 0)
			{
				cin.clear();
				cin.ignore(65536, '\n');
				while (1) {
					cout << "请输入个数num及num个正整数：\n";
					cin >> n >> a >> b >> c >> d;
					if (cin.fail() || a <= 0 || b <= 0 || c <= 0 || d <= 0)
					{
						cin.clear();
						cin.ignore(65536, '\n');
						continue;
					}
					else
					{
						min(a, b, c, d);
						break;
					}
				}
				break;
			}
			else
			{
				min(a, b, c, d);
				break;
			}
		}
	}
	else
		cout << "个数输入错误" << endl;

	return 0;
}