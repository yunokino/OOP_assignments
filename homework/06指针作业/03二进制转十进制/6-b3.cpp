/* 2152041 王浩 信07 */
#include <iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

unsigned int transform_num(char* x)
{
	unsigned int sum = 0;
	for (; *x != '\n'; x++)
	{
		if (sum != 0)
			sum = (unsigned int)(*x - 48) + (sum * 2);
		else
			sum = (unsigned int)(*x - 48);
	}
	return sum;
}

int main()
{
	char* p1;
	char str[33];
	p1 = str;

	cout << "请输入一个0/1组成的字符串，长度不超过32\n";
	for (; p1 - str <= 32; p1++)
	{
		*p1 = getchar();
		if (*p1 == '\n')
			break;
	}
	p1 = str;
	cout << transform_num(p1) << endl;

	return 0;
}
