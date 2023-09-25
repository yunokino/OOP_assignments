/* 2152041 王浩 信07 */
#include <iostream>
using namespace std;
static const char other[21] = "~!@#$%^&*()-_=+[],.?";
int main()
{
	int password_length, daxie, xixie, number, others;
	char password[10][17];
	bool fit_require = 1;
	while(getchar()!='\n');
	cin >> password_length >> daxie >> xixie >> number >> others;
	if (cin.fail()|| daxie<2 || daxie>password_length|| xixie<2 || xixie>password_length|| number<2 || number>password_length|| others<2 || others>password_length)
	{
		fit_require = 0;
		cin.clear();
	}
	for (int i = 0; i <= 9; i++)
		cin >> password[i];
	for (int i = 0; i <= 9; i++)
	{
		int daxie_num = 0, xixie_num = 0, number_num = 0, others_num = 0;
		for (int j = 0; j <= password_length - 1; j++)
		{
			if (password[i][j] >= 65 && password[i][j] <= 90)
				daxie_num++;
			else if (password[i][j] >= 97 && password[i][j] <= 122)
				xixie_num++;
			else if (password[i][j] >= 48 && password[i][j] <= 57)
				number_num++;
			else
			{
				for (int k = 0; k <= 20; k++)
				{
					if (password[i][j] == other[k])
						others_num++;
				}
			}
		}
		if (fit_require)
		{
			if ((password_length >= 12 && password_length <= 16)  && (daxie_num + xixie_num + number_num + others_num == password_length) && (daxie_num >= daxie) && (xixie_num >= xixie) && (number_num >= number) && (others_num >= others))
				fit_require = 1;
			else
				fit_require = 0;
		}
	}
	if (fit_require)
		cout << "正确" << endl;
	else
		cout << "错误" << endl;
	return 0;
}