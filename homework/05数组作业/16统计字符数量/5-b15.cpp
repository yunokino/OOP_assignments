/* 2152041 王浩 信07 */
#include <iostream>
using namespace std;

int main()
{
	char str[3][128] = { 0 };
	int daxie = 0, xixie = 0, number = 0, space = 0, others = 0;
	for (int i = 0; i <= 2; i++)
	{
		cout << "请输入第" << i + 1 << "行\n";
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
	cout << "大写 : " << daxie << endl;
	cout << "小写 : " << xixie << endl;
	cout << "数字 : " << number << endl;
	cout << "空格 : " << space << endl;
	cout << "其它 : " << others << endl;
	return 0;
}