/* 2152041 ���� ��07 */
#include<iostream>
using namespace std;

int main()
{
	int a[5] = { 0 };
	int* b = a;
	(*(b - 1))++;
	return 0;
}