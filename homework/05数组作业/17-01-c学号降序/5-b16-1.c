/* 2152041 ���� ��07 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

void in_put(char sch_num[][8], char name[][9], int score[])
{
	for (int i = 0; i <= 9; i++)
	{
		printf("�������%d���˵�ѧ�š��������ɼ�\n", i + 1);
		scanf("%s %s %d", &sch_num[i], &name[i], &score[i]);
	}
}
void sort_order(char sch_num[][8], char name[][9], int score[])
{
	int t;
	char n;
	for (int i = 0; i <= 8; i++)
		for (int j = 0; j <= 8 - i; j++)
		{
			if (strncmp(sch_num[j], sch_num[j + 1], 7) < 0)
			{
				t = score[j];
				score[j] = score[j + 1];
				score[j + 1] = t;
				for (int m = 0; m <= 7; m++)
				{
					n = sch_num[j][m];
					sch_num[j][m] = sch_num[j + 1][m];
					sch_num[j + 1][m] = n;
				}
				for (int m = 0; m <= 8; m++)
				{
					n = name[j][m];
					name[j][m] = name[j + 1][m];
					name[j + 1][m] = n;
				}
			}
		}
}
void out_put(char sch_num[][8], char name[][9], int score[])
{
	printf("\n��������(ѧ�Ž���):\n");
	for (int i = 0; i <= 9; i++)
	{
		if (score[i] >= 60)
			printf("%s %s %d\n", name[i], sch_num[i], score[i]);
	}
}

int main()
{
	char school_num[10][8], name[10][9];
	int score[10];
	in_put(school_num, name, score);
	sort_order(school_num, name, score);
	out_put(school_num, name, score);

	return 0;
}
