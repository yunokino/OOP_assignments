/*2152041 ���� ��07*/
#include <iostream>
using namespace std;

int main()
{
	cout << "��������������������������20��������-1����\n";
	int a[20] = {0}, b, c[21] = {0}, t;
	for (int i = 0; i <= 19; i++)
	{
		cin >> a[i];
		if (a[i] < 0)
			break;
	}
	if (a[0] < 0)
		cout << "����Ч����" << endl;
	else
	{
		cin.ignore(65536, '\n');
		cout << "ԭ����Ϊ��\n";
		for (int i = 0; i <= 19; i++)
		{
			if (a[i] <= 0)
				break;
			cout << a[i] << " ";
		}
		cout << endl;
		for (int i = 0; i <= 19; i++)
			c[i] = a[i];
		cout << "������Ҫ�����������\n";
		cin >> b;
		cout << "����������Ϊ��\n";
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