/*2152041 ���� ��07*/
#include <iostream>
using namespace std;

int main()
{
	int a[1000] = {0}, b[1000] = {0}, t;
	cout << "������ɼ������1000��������-1����\n";
	for (int i = 0; i <= 999; i++)
	{
		cin >> a[i];
		if (a[i] < 0)
			break;
	}
	if (a[0] < 0)
		cout << "����Ч����" << endl;
	else
	{
		cout << "���������Ϊ:\n";
		for (int i = 0; i <= 999; i++)
		{
			if (a[i] < 0 && i % 10 == 0)
				break;
			else if (a[i] < 0 && i % 10 != 0)
			{
				cout << endl;
				break;
			}
			cout << a[i] << " ";
			if ((i + 1) % 10 == 0)
				cout << endl;
		}
		cout << "�����������Ķ�Ӧ��ϵΪ:\n";
		for (int i = 0; i < 999; i++)
		{
			if (a[i] < 0)
				break;
			for (int j = 0; j < 999 - (i + 1); j++)
			{
				if (a[i] < 0)
					break;
				if (a[j] < a[j + 1])
				{
					if (a[j] < 0)
						break;
					t = a[j];
					a[j] = a[j + 1];
					a[j + 1] = t;
				}
			}
		}
		for (int i = 0; i <= 999; i++)
		{
			if (a[i] < 0)
				break;
			for (int j = 0; j <= 999; j++)
			{
				if (a[j] < 0)
					break;
				if (a[i] == a[j])
					b[i]++;
			}
		}
		for (int i = 0; i <= 999; i++)
		{
			int _no1 = 0;
			if (a[i] < 0)
				break;
			for (int j = 0; j < i; j++)
			{
				if (a[j] < 0)
					break;
				if (a[j] == a[i])
				{
					_no1 = 1;
					break;
				}
			}
			if (_no1 == 0)
				cout << a[i] << " " << b[i] << endl;
		}
		return 0;
	}
}