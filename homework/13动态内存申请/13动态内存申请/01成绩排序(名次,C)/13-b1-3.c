/* 2152041 计科 王浩 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>

struct student
{
	int no;
	char name[9];
	int score;
	int rank;
};

int main()
{
	FILE* infile;
	int num;
	infile = fopen("student.txt", "r");
	if (infile == NULL)
	{
		printf("打开文件失败\n");
		return -1;
	}
	fscanf(infile, "%d", &num);
	struct student* pointer = malloc(num * sizeof(struct student));
	if (pointer == NULL)
		return -1;
	for (int i = 0; i < num; i++)
	{
		fscanf(infile, "%d %s %d", &(pointer + i)->no, &(pointer + i)->name, &(pointer + i)->score);
	}
	for (int i = 0; i < num - 1; i++)
		for (int j = 0; j < num - 1 - i; j++)
		{
			if ((pointer + j)->score < (pointer + j + 1)->score)
			{
				int tmp_no, tmp_score;
				char tmp_name[9];
				tmp_no = (pointer + j)->no;
				(pointer + j)->no = (pointer + j + 1)->no;
				(pointer + j + 1)->no = tmp_no;
				for (int k = 0; k < 8; k++)
				{
					tmp_name[k] = (pointer + j)->name[k];
					(pointer + j)->name[k] = (pointer + j + 1)->name[k];
					(pointer + j + 1)->name[k] = tmp_name[k];
				}
				tmp_score = (pointer + j)->score;
				(pointer + j)->score = (pointer + j + 1)->score;
				(pointer + j + 1)->score = tmp_score;
			}
		}
	int old_rank = 0;
	for (int i = 0; i < num; i++)
	{
		if (i == 0)
		{
			old_rank = 1;
			(pointer + i)->rank = 1;
		}
		else
		{
			if ((pointer + i)->score == (pointer + i - 1)->score)
				(pointer + i)->rank = old_rank;
			else
			{
				(pointer + i)->rank = i + 1;
				old_rank = i + 1;
			}
		}
	}
	int count = 0;
	for (int m = 0; m < num; m++)
	{
		for (int n = m; n < num - 1; n++)
		{

			if ((pointer + n)->rank == (pointer + n + 1)->rank)
			{
				count++;
			}
			else
			{
				if (count != 0)
				{
					for (int i = m; i < m + count; i++)
					{
						int min = i;
						for (int j = i + 1; j < m + count + 1; j++)
						{
							if ((pointer + j)->no < (pointer + min)->no)
							{
								min = j;
							}
						}
						int tmp_no, tmp_score;
						char tmp_name[9];
						tmp_no = (pointer + i)->no;
						(pointer + i)->no = (pointer + min)->no;
						(pointer + min)->no = tmp_no;
						for (int k = 0; k < 8; k++)
						{
							tmp_name[k] = (pointer + i)->name[k];
							(pointer + i)->name[k] = (pointer + min)->name[k];
							(pointer +min)->name[k] = tmp_name[k];
						}
						tmp_score = (pointer + i)->score;
						(pointer + i)->score = (pointer + min)->score;
						(pointer + min)->score = tmp_score;
					}
					count = 0;
					break;
				}
				else
					break;
			}
		}
	}
	for (int i = 0; i < num; i++)
	{
		printf("%d %s %d %d\n", (pointer + i)->no, (pointer + i)->name, (pointer + i)->score, (pointer + i)->rank);
	}
	fclose(infile);
	free(pointer);
	return 0;
}