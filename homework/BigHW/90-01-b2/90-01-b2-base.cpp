/* 2152041 王浩 计科 */
#include<iostream>
#include"90-01-b2.h"
#include<conio.h>
#include "../include/common_input.h"
#include "../include/common_output.h"
#include "../include/common_base.h"
#include "../include/cmd_console_tools.h"
using namespace std;

void mark_same_norecursion(int matrix_num[][10], int mark_same[][10], int output_line, int output_row)
{
	while (1)
	{
		char line = 'A';
		int row = 0;
		int store[80][2] = { 0 };//储存标记坐标
		int next[4][2] = { {0,1},{1,0},{0, -1},{ -1,0} };//标记移动方向
		input_location(&line, &row, output_line, output_row);
		mark_same[line - 'A'][row] = 1;
		store[0][0] = line - 'A';
		store[0][1] = row;
		int start = 0, end = 1;
		while (start < end)
		{
			for (int k = 0; k <= 3; k++)
			{
				int i = store[start][0], j = store[start][1];//记录起点
				while (1)
				{
					int old_i = i, old_j = j;
					i += next[k][0];
					j += next[k][1];
					if (i<0 || j<0 || i>output_line - 1 || j>output_row - 1)
						break;
					else
					{
						if (matrix_num[i][j] == matrix_num[old_i][old_j])
						{
							if (!mark_same[i][j])
							{
								store[end][0] = i;
								store[end][1] = j;
								end++;
							}
							mark_same[i][j] = 1;
						}
						else
							break;
					}
				}
			}
			start++;
		}
		if (end == 1)
		{
			for (int i = 0; i <= 7; i++)
				for (int j = 0; j <= 9; j++)
					mark_same[i][j] = 0;
			cout << "输入的矩阵坐标位置处无连续相同值，请重新输入";
		}
		else
		{
			output_mark_same(matrix_num, mark_same, output_line, output_row);
			break;
		}
	}
}


