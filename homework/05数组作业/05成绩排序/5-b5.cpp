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
		cout << "���������εĶ�Ӧ��ϵΪ:\n";
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
		for (int j = 0; j <= 999; j++)
		{
			if (a[j] < 0)
				break;
			b[j] = 1;
		}
		for (int i = 1; i <= 999; i++)
		{
			static int num = 1;
			if (a[i] < 0)
				break;
			if (a[i] == a[i - 1])
			{
				num++;
				continue;
			}
			else
			{
				b[i] += num;
				num = 1;
				for (int j = i; j <= 999; j++)
				{
					if (a[j] < 0)
						break;
					b[j] = b[i];
				}
			}
		}
		for (int i = 0; i <= 999; i++)
		{
			if (a[i] < 0)
				break;
			cout << a[i] << " " << b[i] << endl;
		}
		return 0;
	}
}