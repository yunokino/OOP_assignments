/* 2152041 ÍõºÆ ÐÅ07 */
#include <iostream>
#include <stdlib.h>
#include<time.h>
using namespace std;

int main()
{
	char mine_sweep[10][26] = { 0 };
	srand((unsigned int)(time(NULL)));
	while (1)
	{
		for (int i = 0; i <= 49; i++)
		{
			int num1 = rand() % 9;
			int num2 = rand() % 25;
			mine_sweep[num1][num2] = '*';
		}
		int k = 0;
		for (int i = 0; i <= 9; i++)
			for (int j = 0; j <= 25; j++)
				if (mine_sweep[i][j] == '*')
					k++;
		if (k == 50)
			break;
		else
		{
			for (int i = 0; i <= 9; i++)
			{
				for (int j = 0; j <= 25; j++)
					mine_sweep[i][j] = '\0';
			}
			continue;
		}
	}
	for (int i = 0; i <= 9; i++)
		for (int j = 0; j <= 25; j++)
			if (mine_sweep[i][j] != '*')
			{
				if (i == 0)
				{
					if (j == 0)
					{
						mine_sweep[i][j] = mine_sweep[1][0] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[1][1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[0][1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					}
					else if (j == 25)
					{
						mine_sweep[i][j] = mine_sweep[1][25] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[1][24] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[0][24] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					}
					else
					{
						mine_sweep[i][j] = mine_sweep[i][j - 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[i][j + 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[i + 1][j - 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[i + 1][j + 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[i + 1][j] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					}
				}
				else if (i == 9)
				{
					if (j == 0)
					{
						mine_sweep[i][j] = mine_sweep[8][0] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[8][1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[9][1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					}
					else if (j == 25)
					{
						mine_sweep[i][j] = mine_sweep[8][25] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[8][24] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[9][24] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					}
					else
					{
						mine_sweep[i][j] = mine_sweep[i][j - 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[i][j + 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[i - 1][j - 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[i - 1][j + 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
						mine_sweep[i][j] = mine_sweep[i - 1][j] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					}
				}
				else if (j == 0)
				{
					mine_sweep[i][j] = mine_sweep[i - 1][j] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i + 1][j] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i - 1][j + 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i][j + 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i + 1][j + 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
				}
				else if (j == 25)
				{
					mine_sweep[i][j] = mine_sweep[i - 1][j] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i + 1][j] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i - 1][j - 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i][j - 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i + 1][j - 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
				}
				else
				{
					mine_sweep[i][j] = mine_sweep[i - 1][j - 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i - 1][j] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i - 1][j + 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i][j - 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i][j + 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i + 1][j - 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i + 1][j] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
					mine_sweep[i][j] = mine_sweep[i + 1][j + 1] == '*' ? mine_sweep[i][j] + 1 : mine_sweep[i][j];
				}
			}
	for (int i = 0; i <= 9; i++)
		for (int j = 0; j <= 25; j++)
			if (mine_sweep[i][j] != '*')
			{
				mine_sweep[i][j] += 48;
			}
	for (int i = 0; i <= 9; i++)
	{
		for (int j = 0; j <= 25; j++)
		{
			if (mine_sweep[i][j] == 0)
				cout << "0" << " ";
			else
				cout << mine_sweep[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
