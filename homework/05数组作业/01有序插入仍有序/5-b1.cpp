/*2152041 王浩 信07*/
#include <iostream>
using namespace std;

int main()
{
	cout << "请输入任意个正整数（升序，最多20个），以-1结束\n";
	int a[20] = {0}, b, c[21] = {0}, t;
	for (int i = 0; i <= 19; i++)
	{
		cin >> a[i];
		if (a[i] < 0)
			break;
	}
	if (a[0] < 0)
		cout << "无有效输入" << endl;
	else
	{
		cin.ignore(65536, '\n');
		cout << "原数组为：\n";
		for (int i = 0; i <= 19; i++)
		{
			if (a[i] <= 0)
				break;
			cout << a[i] << " ";
		}
		cout << endl;
		for (int i = 0; i <= 19; i++)
			c[i] = a[i];
		cout << "请输入要插入的正整数\n";
		cin >> b;
		cout << "插入后的数组为：\n";
		c[20] = b;
		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 20 - i; j++)
			{
				if (c[j] > c[j + 1])
				{
					t = c[j];
					c[j] = c[j + 1];
					c[j + 1] = t;
				}
			}
		for (int i = 0; i <= 20; i++)
		{
			if (c[i] > 0)
				cout << c[i] << " ";
		}
	}
	cout << endl;
	return 0;
}