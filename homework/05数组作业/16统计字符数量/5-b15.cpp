/* 2152041 ���� ��07 */
#include <iostream>
using namespace std;

int main()
{
	char str[3][128] = { 0 };
	int daxie = 0, xixie = 0, number = 0, space = 0, others = 0;
	for (int i = 0; i <= 2; i++)
	{
		cout << "�������" << i + 1 << "��\n";
		for (int j = 0; j <= 127; j++)
		{
			str[i][j] = getchar();
			if (str[i][j] == '\n')
				break;
		}
	}
	for (int i = 0; i <= 2; i++)
	{
		int j = 0;
		while (str[i][j] != '\n')
		{
			if (str[i][j] >= 65 && str[i][j] <= 90)
				daxie++;
			else if (str[i][j] >= 97 && str[i][j] <= 122)
				xixie++;
			else if (str[i][j] >= 48 && str[i][j] <= 57)
				number++;
			else if (str[i][j] == 32)
				space++;
			else
				others++;
			j++;
		}
	}
	cout << "��д : " << daxie << endl;
	cout << "Сд : " << xixie << endl;
	cout << "���� : " << number << endl;
	cout << "�ո� : " << space << endl;
	cout << "���� : " << others << endl;
	return 0;
}