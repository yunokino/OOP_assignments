/* 2152041 ���� ��07 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/* ----����Ҫ��----
   1���������������ͷ�ļ�
   2��������һ��ȫ�ֱ������������徲̬�ֲ�����
   3������������������������ʼ/Ŀ�����ĺ���������������ʹ��ѭ�������������
   4����������ú������У���main�в���������κ���ʽ��ѭ��
	  ���������main�н��У���main���������ѭ��
   --------------------------------------------------------------------- */


   /***************************************************************************
	 �������ƣ�
	 ��    �ܣ���ӡn�㺺ŵ�����ƶ�˳��
	 ���������int n������
			   char src����ʼ��
			   char tmp���м���
			   char dst��Ŀ����
	 �� �� ֵ��
	 ˵    ����1�����������βΡ��������;���׼��
			   2������������������κ���ʽ��ѭ��
   ***************************************************************************/
int step = 1;
int a[3];
int zhu[3][10];
void move(int n, char x, char y)
{
	printf("��%4d ��(%2d): %c-->%c ", step, n, x, y);
	step++;
	if (x == 'A' && y == 'B')
	{
		zhu[1][a[1]++] = zhu[0][--a[0]];
		zhu[0][a[0]] = 0;
	}
	else if (x == 'A' && y == 'C')
	{
		zhu[2][a[2]++] = zhu[0][--a[0]];
		zhu[0][a[0]] = 0;
	}
	else if (x == 'B' && y == 'A')
	{
		zhu[0][a[0]++] = zhu[1][--a[1]];
		zhu[1][a[1]] = 0;
	}
	else if (x == 'B' && y == 'C')
	{
		zhu[2][a[2]++] = zhu[1][--a[1]];
		zhu[1][a[1]] = 0;
	}
	else if (x == 'C' && y == 'A')
	{
		zhu[0][a[0]++] = zhu[2][--a[2]];
		zhu[2][a[2]] = 0;
	}
	else
	{
		zhu[1][a[1]++] = zhu[2][--a[2]];
		zhu[2][a[2]] = 0;
	}
	printf("A:");
	for (int i = 0; i <= 9; i++)
	{
		if (zhu[0][i] == 0)
		{
			if (i == 0)
				printf("   ");
			else
				printf("  ");
		}
		else
		{
			if (i == 0)
				printf("%2d ", zhu[0][i]);
			else
				printf("%d ", zhu[0][i]);
		}
	}
	printf("B:");
	for (int i = 0; i <= 9; i++)
	{
		if (zhu[1][i] == 0)
		{
			if (i == 0)
				printf("   ");
			else
				printf("  ");
		}
		else
		{
			if (i == 0)
				printf("%2d ", zhu[1][i]);
			else
				printf("%d ", zhu[1][i]);
		}
	}
	printf( "C:");
	for (int i = 0; i <= 9; i++)
	{
		if (zhu[2][i] == 0)
		{
			if (i == 0)
				printf( "   ");
			else
				printf( "  ");
		}
		else
		{
			if (i == 0)
				printf("%2d ",zhu[2][i]);
			else
				printf("%d ", zhu[2][i]);
		}
	}
	printf("\n");
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡn�㺺ŵ�����ƶ�˳��
  ���������int n������
			char src����ʼ��
			char tmp���м���
			char dst��Ŀ����
  �� �� ֵ��
  ˵    ����1�����������βΡ��������;���׼��
			2������������������κ���ʽ��ѭ��
***************************************************************************/
void hanoi(int n, char src, char tmp, char dst)
{
	if (n == 1)
	{
		move(1, src, dst);
	}
	else
	{
		hanoi(n - 1, src, dst, tmp);
		move(n, src, dst);
		hanoi(n - 1, tmp, src, dst);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    �����������(��������뺯��)�����õݹ麯��
***************************************************************************/
int main()
{
	int x, ret;
	char f, g, h;
	g = '0';

	while (1) {
		printf("�����뺺ŵ���Ĳ���(1-10)��\n");
		ret = scanf("%d", &x);
		if (ret != 1)
		{
			while (getchar() != '\n')
				continue;
		}
		if (x >= 1 && x <= 10)
		{
			while (getchar() != '\n');
			break;
		}
	}
	while (1) {
		printf("��������ʼ��(A-C)��\n");
		ret = scanf("%c", &f);
		if (ret != 1)
		{
			while (getchar() != '\n');
			continue;
		}
		if (f == 'a' || f == 'b' || f == 'c' || f == 'A' || f == 'B' || f == 'C')
		{
			while (getchar() != '\n');
			break;
		}
	}
	while (1) {
		printf("������Ŀ����(A-C)��\n");
		ret = scanf("%c", &h);
		if (ret != 1)
		{
			while (getchar() != '\n');
			continue;
		}
		if ((int)f == (int)h || (int)f == (int)h - 32 || (int)f == (int)h + 32)
		{
			h = ((int)(h) > 90) ? (char)((int)(h)-32) : h;
			f = ((int)(f) > 90) ? (char)((int)(f)-32) : f;
			printf("Ŀ����(%c)��������ʼ��(%c)��ͬ\n", h, f);
			while (getchar() != '\n');
			continue;
		}
		else if ((h == 'a' || h == 'b' || h == 'c' || h == 'A' || h == 'B' || h == 'C'))
		{
			while (getchar() != '\n');
			break;
		}
	}
	int _1, _2, _3;
	_1 = _2 = _3 = 1;
	switch ((int)(f))
	{
		case 65:
		case 97:
			_1 = 0;
			f = 'A';
			break;
		case 66:
		case 98:
			_2 = 0;
			f = 'B';
			break;
		case 67:
		case 99:
			_3 = 0;
			f = 'C';
			break;
	}
	switch ((int)(h))
	{
		case 65:
		case 97:
			_1 = 0;
			h = 'A';
			break;
		case 66:
		case 98:
			_2 = 0;
			h = 'B';
			break;
		case 67:
		case 99:
			_3 = 0;
			h = 'C';
			break;
	}
	if (_1)
		g = 'A';
	if (_2)
		g = 'B';
	if (_3)
		g = 'C';
	a[0] = (f == 'A' ? x : 0);
	a[1] = (f == 'B' ? x : 0);
	a[2] = (f == 'C' ? x : 0);
	printf("��ʼ:                ");
	(x == 10 && f == 'A') ? printf(" A:") : printf(" A: ");
	int j = x;
	if (f == 'A')
	{
		for (int i = 0; i <= x - 1; i++)
		{
			zhu[0][i] = j;
			j--;
			printf("%d " ,zhu[0][i]);
		}
		for (int i = 20 - 2 * x; i >= 1; i--)
			printf( " ");
	}
	else
	{
		for (int i = 0; i <= 19; i++)
			printf( " ");
	}
	(x == 10 && f == 'B') ? printf("B:") : printf("B: ");
	if (f == 'B')
	{
		for (int i = 0; i <= x - 1; i++)
		{
			zhu[1][i] = j;
			j--;
			printf("%d ", zhu[1][i]);
		}
		for (int i = 20 - 2 * x; i >= 1; i--)
			printf(" ");
	}
	else
	{
		for (int i = 0; i <= 19; i++)
			printf(" ");
	}
	(x == 10 && f == 'C') ? printf("C:") : printf("C: ");
	if (f == 'C')
	{
		for (int i = 0; i <= x - 1; i++)
		{
			zhu[2][i] = j;
			j--;
			printf("%d ", zhu[2][i]);
		}
		for (int i = 20 - 2 * x; i >= 1; i--)
			printf(" ");
	}
	else
	{
		for (int i = 0; i <= 19; i++)
			printf(" ");
	}
	printf("\n");
	hanoi(x, f, g, h);
	return 0;
}