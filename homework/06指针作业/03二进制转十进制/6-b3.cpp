/* 2152041 ���� ��07 */
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

	cout << "������һ��0/1��ɵ��ַ��������Ȳ�����32\n";
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
