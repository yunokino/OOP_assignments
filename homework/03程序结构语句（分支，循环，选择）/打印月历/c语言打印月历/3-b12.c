/* ��07 2152041 ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int ret1,ret2, a,b,c,d;
	int i = 1;

	while (1) {
		printf("���������(2000-2030)���·�(1-12) :");
		ret1 = scanf("%d %d", &a,&b);
		while (ret1 != 2 || a < 2000 || a>2030 || b > 12 || b < 1)
		{
			printf("����Ƿ�������������\n");
			while (getchar() != '\n');
			break;
		}
		if (ret1 == 2 )
			break;
	}
	printf("������%d��%d��1�յ�����(0 - 6��ʾ������ - ������) :", a, b);
	while (1) {
		ret2 = scanf("%d", &c);
		while (ret2 != 1 ||c<0||c>6)
		{
			printf("����Ƿ�������������\n");
			while (getchar() != '\n');
			break;
		}
		if (ret2 == 1 && (c>=0 && c<=6))
			break;
	}
	d = c - 1;
	printf("%d��%d�µ�����Ϊ:\n" ,a,b);
	printf( "������  ����һ  ���ڶ�  ������  ������  ������  ������\n");
	if (b == 1 || b == 3 || b == 5 || b == 7 || b == 8 || b == 10 || b == 12)
	{
		for (i = 1; i <= 31; i++)
		{
			if (c == 0 && i == 1)
				printf("%4d",i);
			else if (c != 0 && i == 1)
			{
				printf("    ");
				if (d >= 0)
				{
					int d = c - 2;
					for (d; d >= 0; d--)
						printf( "        ");
				}
				printf("%8d", i);
				c = c + 1;
				continue;
			}
			else if (c == 0 && i != 1)
				printf("%4d", i);
			else
				printf("%8d",i);
			c++;
			if (c == 7)
			{
				printf("\n");
				c = 0;
			}
		}
	}
	if (b == 4 || b == 6 || b == 9 || b == 11)
	{
		for (i = 1; i <= 30; i++)
		{
			if (c == 0 && i == 1)
				printf("%4d", i);
			else if (c != 0 && i == 1)
			{
				printf( "    ");
				if (d >= 0)
				{
					int d = c - 2;
					for (d; d >= 0; d--)
						printf("        ");
				}
				printf("%8d", i);
				c = c + 1;
				continue;
			}
			else if (c == 0 && i != 1)
				printf("%4d", i);
			else
				printf("%8d", i);
			c++;
			if (c == 7)
			{
				printf("\n");
				c = 0;
			}
		}
	}
	if (b == 2)
	{
		for (i = 1; i <= ((a % 4 == 0&&a%100!=0)||a%400==0) ? 29 : 28); i++)
		{
			if (c == 0 && i == 1)
				printf("%4d", i);
			else if (c != 0 && i == 1)
			{
				printf("    ");
				if (d >= 0)
				{
					int d = c - 2;
					for (d; d >= 0; d--)
						printf("        ");
				}
				printf("%8d", i);
				c = c + 1;
				continue;
			}
			else if (c == 0 && i != 1)
				printf("%4d", i);
			else
				printf("%8d", i);
			c++;
			if (c == 7)
			{
				printf("\n");
				c = 0;
			}
		}
	}
	return 0;
}
