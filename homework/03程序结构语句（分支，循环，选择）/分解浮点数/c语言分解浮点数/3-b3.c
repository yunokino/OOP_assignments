/*���� ��07 2152041*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main()
{
	double a, b;
	unsigned int i;
	printf("������[0-100�ڣ�֮�������\n");
	scanf(" % f", &a);
	i = (int)a / 10;
	b = a / 10 - i + 0.0001;
	printf("ʮ��λ : %d\n", i / 100000000 %10);
	printf("��λ   : %d\n", i / 10000000 %10);
	printf("ǧ��λ : %d\n", i / 1000000 %10);
	printf("����λ : %d\n", i / 100000 %10);
	printf("ʮ��λ : %d\n", i / 10000 %10);
	printf("��λ   : %d\n", i / 1000 %10);
	printf("ǧλ   : %d\n", i / 100 % 10);
	printf("��λ   : %d\n", i / 10 % 10);
	printf("ʮλ   : %d\n", i % 10);
	printf("Ԫ     : %d\n", (int)(10 * b) % 10);
	printf("��     : %d\n", (int)(100 * b) % 10);
	printf("��     : %d\n", (int)(1000 * b) % 10);

	return 0;
}
