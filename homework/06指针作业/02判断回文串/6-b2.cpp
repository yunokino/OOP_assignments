/* 2152041 王浩 信07 */
#include <iostream>
using namespace std;

void judge_circle(char* x)
{
	bool is_circle = 1;
	char* y = x;
	char* t = x;
	for (; *x != '\n'; x++)
		y++;	
	//因为fgets会读入换行符，所以y自减一
	y -= 1;
	x = t;
	while (x <= y)
	{
		if (*x != *y)
			is_circle = 0;
		x++;
		y--;
	}
	if (is_circle)
		cout << "yes\n";
	else
		cout << "no\n";
}

int main()
{
	char str[81], * p1;
	p1 = str;
	cout << "请输入一个长度小于80的字符串（回文串）\n";
	fgets(p1, 81, stdin);
	judge_circle(p1);
	return 0;
}