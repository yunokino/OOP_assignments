/* 2152041 ���� ��07 */
#include <iostream>
#include<time.h>
using namespace std;
static const char other[21] = "~!@#$%^&*()-_=+[],.?";
int main()
{
	int password_length, daxie, xixie, number, others;
	srand((unsigned int)(time(NULL)));
	cout << "���������볤��(12-16)�� ��д��ĸ����(��2)�� Сд��ĸ����(��2)�� ���ָ���(��2)�� �������Ÿ���(��2)\n";
	cin >> password_length >> daxie >> xixie >> number >> others;
	if (cin.fail())
		cout << "����Ƿ�" << endl;
	else if (password_length < 12 || password_length > 16)
		cout << "���볤��[" << password_length << "]����ȷ" << endl;
	else if (daxie<2 || daxie>password_length)
		cout << "��д��ĸ����[" << daxie << "]����ȷ" << endl;
	else if (xixie<2 || xixie>password_length)
		cout << "Сд��ĸ����[" << xixie << "]����ȷ" << endl;
	else if (number<2 || number>password_length)
		cout << "���ָ���[" << daxie << "]����ȷ" << endl;
	else if (others<2 || others>password_length)
		cout << "�������Ÿ���[" << others << "]����ȷ" << endl;
	else if (password_length < daxie + xixie + number + others)
		cout << "�����ַ�����֮��[" << daxie << "+" << xixie << "+" << number << "+" << others << "]���������볤��[12]" << endl;
	else
	{
		cout << password_length << " " << daxie << " " << xixie << " " << number << " " << others << endl;
		char password[10][17];
		for (int i = 0; i <= 9; i++)
		{
			while (1)
			{
				int daxie_num = 0, xixie_num = 0, number_num = 0, others_num = 0;
				for (int j = 0; j <= password_length - 1; j++)
				{
					password[i][j] = char(rand() % 93 + 33);
					if (password[i][j] >= 65 && password[i][j] <= 90)
						daxie_num++;
					else if (password[i][j] >= 97 && password[i][j] <= 122)
						xixie_num++;
					else if (password[i][j] >= 48 && password[i][j] <= 57)
						number_num++;
					else
					{
						password[i][j] = other[(rand() % 20)];
						others_num++;
					}
				}
				if ((daxie_num >= daxie) && (xixie_num >= xixie) && (number_num >= number) && (others_num >= others))
					break;
			}
		}
		for (int i = 0; i <= 9; i++)
		{
			for (int j = 0; j <= password_length - 1; j++)
			{
				cout << password[i][j];
			}
			cout << endl;
		}
		return 0;
	}
}