/* 2152041 王浩 信07 */
/* 2152359 陈芝杨 2151412 杨智皓 2153048 周振堂 2152586 赵新浩 2150258 金屹峰 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int error1 = 0, error2 = 0;
	char mine_sweep[10][52];
	for (int i = 0; i <= 9; i++)
		for (int j = 0; j <= 25; j++)
			scanf(" %c", &mine_sweep[i][j]);
	for (int i = 0; i <= 9; i++)
		for (int j = 0; j <= 25; j++)
			if (mine_sweep[i][j] != '*')
			{
				mine_sweep[i][j] -= 48;
			}
	int k = 0;
	for (int i = 0; i <= 9; i++)
		for (int j = 0; j <= 25; j++)
			if (mine_sweep[i][j] == '*')
				k++;
	if (k != 50)
		error1 = 1;
	for (int i = 0; i <= 9; i++)
		for (int j = 0; j <= 25; j++)
			if (mine_sweep[i][j] != '*')
			{
				if (i == 0)
				{
					if (j == 0)
					{
						mine_sweep[i][j] = mine_sweep[1][0] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[1][1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[0][1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					}
					else if (j == 25)
					{
						mine_sweep[i][j] = mine_sweep[1][25] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[1][24] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[0][24] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					}
					else
					{
						mine_sweep[i][j] = mine_sweep[i][j - 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[i][j + 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[i + 1][j - 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[i + 1][j + 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[i + 1][j] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					}
				}
				else if (i == 9)
				{
					if (j == 0)
					{
						mine_sweep[i][j] = mine_sweep[8][0] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[8][1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[9][1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					}
					else if (j == 25)
					{
						mine_sweep[i][j] = mine_sweep[8][25] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[8][24] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[9][24] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					}
					else
					{
						mine_sweep[i][j] = mine_sweep[i][j - 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[i][j + 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[i - 1][j - 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[i - 1][j + 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[i - 1][j] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					}
				}
				else if (j == 0)
				{
					mine_sweep[i][j] = mine_sweep[i - 1][j] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i + 1][j] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i - 1][j + 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i][j + 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i + 1][j + 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
				}
				else if (j == 25)
				{
					mine_sweep[i][j] = mine_sweep[i - 1][j] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i + 1][j] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i - 1][j - 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i][j - 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i + 1][j - 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
				}
				else
				{
					mine_sweep[i][j] = mine_sweep[i - 1][j - 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i - 1][j] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i - 1][j + 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i][j - 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i][j + 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i + 1][j - 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i + 1][j] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i + 1][j + 1] == '*' ? mine_sweep[i][j] - 1 : mine_sweep[i][j];
				}
			}
	for (int i = 0; i <= 9; i++)
		for (int j = 0; j <= 25; j++)
			if (mine_sweep[i][j] != 0&& mine_sweep[i][j] != '*')
			{
				error2 = 1;
			}
	if (error1)
		printf("错误1");
	else if (error2)
		printf("错误2");
	else
		printf("正确");
	printf("\n"); 
	return 0;
}
