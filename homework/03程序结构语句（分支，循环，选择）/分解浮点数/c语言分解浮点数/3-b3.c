/*王浩 信07 2152041*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main()
{
	double a, b;
	unsigned int i;
	printf("请输入[0-100亿）之间的数字\n");
	scanf(" % f", &a);
	i = (int)a / 10;
	b = a / 10 - i + 0.0001;
	printf("十亿位 : %d\n", i / 100000000 %10);
	printf("亿位   : %d\n", i / 10000000 %10);
	printf("千万位 : %d\n", i / 1000000 %10);
	printf("百万位 : %d\n", i / 100000 %10);
	printf("十万位 : %d\n", i / 10000 %10);
	printf("万位   : %d\n", i / 1000 %10);
	printf("千位   : %d\n", i / 100 % 10);
	printf("百位   : %d\n", i / 10 % 10);
	printf("十位   : %d\n", i % 10);
	printf("元     : %d\n", (int)(10 * b) % 10);
	printf("角     : %d\n", (int)(100 * b) % 10);
	printf("分     : %d\n", (int)(1000 * b) % 10);

	return 0;
}
