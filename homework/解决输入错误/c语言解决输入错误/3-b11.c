/* 信07 2152041 王浩 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int ret, x;

	while (1) {
		printf("请输入x的值[0-100] : ");
		ret = scanf("%d", &x); //读入x的方式必须是scanf且格式符为%d，不准用非scanf
		while(ret!=1)
		{
			while (getchar() != '\n');
			break;
		}
		if (ret == 1 && (x >= 0 && x <= 100))
			break;
	}

	printf("x=%d\n", x);

	return 0;
}