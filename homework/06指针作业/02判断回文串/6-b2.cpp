/* 2152041 ���� ��07 */
#include <iostream>
using namespace std;

void judge_circle(char* x)
{
	bool is_circle = 1;
	char* y = x;
	char* t = x;
	for (; *x != '\n'; x++)
		y++;	
	//��Ϊfgets����뻻�з�������y�Լ�һ
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
	cout << "������һ������С��80���ַ��������Ĵ���\n";
	fgets(p1, 81, stdin);
	judge_circle(p1);
	return 0;
}