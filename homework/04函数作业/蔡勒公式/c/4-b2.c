/* ��07 2152041 ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int zeller(int y, int m, int d)
{
	int w;
	if (m == 1 || m == 2)
	{
		y -= 1;
		m += 12;
	}
	int a = (int)(y / 100);//���ǰ��λ
	int b = y - (int)(y / 100) * 100;//��ݺ���λ
	w = b + (int)(b / 4) + (int)(a / 4) - 2 * a + (int)(13 * (m + 1) / 5) + d - 1;
	while (w < 0)
	{
		w += 7;
	}
	return w%7;
}

int main()
{
	int ret,year,m,d;
	while (1) {
		printf("��������[1900-2100]���¡��գ�\n");
		ret = scanf("%d %d %d", &year,&m,&d);
		if(ret != 3 )
		{
			printf("�����������������\n");
			while (getchar() != '\n');
			continue;
		}
		if (year < 1900 || year > 2100)
		{
			printf( "��ݲ���ȷ������������\n");
			while (getchar() != '\n');
			continue;
		}
		else if (m < 0 || m > 12)
		{
			printf( "�·ݲ���ȷ������������\n");
			while (getchar() != '\n');
			continue;
		}
		else if ((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && (d < 0 || d>31))
		{
			printf( "�ղ���ȷ������������\n");
			while (getchar() != '\n');
			continue;
		}
		else if ((m == 4 || m == 6 || m == 9 || m == 11) && (d < 0 || d>30))
		{
			printf( "�ղ���ȷ������������\n");
			while (getchar() != '\n');
			continue;
		}
		else if ((m == 2) && (year % 4 == 0 ? (d < 0 || d>29) : (d < 0 || d>28)))
		{
			printf( "�ղ���ȷ������������\n");
			while (getchar() != '\n');
			continue;
		}
		else
			break;
	}
		switch (zeller(year, m, d))
	{
		case 0:
			printf( "������");
			break;
		case 1:
			printf( "����һ");
			break;
		case 2:
			printf( "���ڶ�");
			break;
		case 3:
			printf( "������");
			break;
		case 4:
			printf( "������");
			break;
		case 5:
			printf( "������");
			break;
		case 6:
			printf( "������");
			break;
	}
	printf("\n");
	return 0;
}
