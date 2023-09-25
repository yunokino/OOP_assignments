/* 2152041 王浩 信07 */
#include <iostream>
#include<time.h>
using namespace std;
static const char other[21] = "~!@#$%^&*()-_=+[],.?";
int main()
{
	int password_length, daxie, xixie, number, others;
	srand((unsigned int)(time(NULL)));
	cout << "请输入密码长度(12-16)， 大写字母个数(≥2)， 小写字母个数(≥2)， 数字个数(≥2)， 其它符号个数(≥2)\n";
	cin >> password_length >> daxie >> xixie >> number >> others;
	if (cin.fail())
		cout << "输入非法" << endl;
	else if (password_length < 12 || password_length > 16)
		cout << "密码长度[" << password_length << "]不正确" << endl;
	else if (daxie<2 || daxie>password_length)
		cout << "大写字母个数[" << daxie << "]不正确" << endl;
	else if (xixie<2 || xixie>password_length)
		cout << "小写字母个数[" << xixie << "]不正确" << endl;
	else if (number<2 || number>password_length)
		cout << "数字个数[" << daxie << "]不正确" << endl;
	else if (others<2 || others>password_length)
		cout << "其它符号个数[" << others << "]不正确" << endl;
	else if (password_length < daxie + xixie + number + others)
		cout << "所有字符类型之和[" << daxie << "+" << xixie << "+" << number << "+" << others << "]大于总密码长度[12]" << endl;
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