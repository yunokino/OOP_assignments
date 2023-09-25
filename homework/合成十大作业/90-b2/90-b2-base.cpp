/* 2152041 王浩 信07 */
#include<iostream>
#include"90-b2.h"
#include<conio.h>
#include"cmd_console_tools.h"
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

int mark_same_recursion(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row, int first)
{
	int k = 0;
	int next[4][2] = { {0,1},{1,0},{0, -1},{ -1,0} };//标记移动方向
	mark_same[line][row] = 1;
	int old_line = line, old_row = row;
	for (int i = 0; i <= 3; i++)
	{
		line = old_line;
		row = old_row;
		line += next[i][0];
		row += next[i][1];
		if (line<0 || row<0 || line>output_line - 1 || row>output_row - 1)
			continue;
		if (matrix_num[line][row] == matrix_num[old_line][old_row])
		{
			if (!mark_same[line][row])
			{
				k++;
				mark_same[line][row] = 1;
				mark_same_recursion(matrix_num, mark_same, line, row, output_line, output_row, 0);
			}
		}
	}
	if (k == 0 && first)
	{
		cout << "输入的矩阵坐标位置处无连续相同值，请重新输入";
		for (int i = 0; i <= 7; i++)
			for (int j = 0; j <= 7; j++)
				mark_same[i][j] = 0;
		return 1;
	}
	if (first)
		output_mark_same(matrix_num, mark_same, output_line, output_row);
	return 0;
}

int merge_num(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int line, int row, int &max_num, int goal_point,int *grade)
{
	static int first_time = 1;
	cout << "\n请确认是否把相邻的相同值合并到" << char(line + 65) << row << "中(Y / N / Q)：";
	while (1)
	{
		char choice = _getche();
		if (choice == 'Y' || choice == 'y')
		{
			if (matrix_num[line][row] == max_num)
			{
				max_num++;
				if (max_num >= goal_point)
					first_time = 1;
			}
			cout << "\n\n相同值归并后的数组(不同色标识)：\n";
			int k = 0;
			for (int i = 0; i <= 7; i++)
				for (int j = 0; j <= 9; j++)
				{
					if (mark_same[i][j] == 1)
					{
						k++;
						if (i != line || j != row)
							matrix_num[i][j] = 0;
						else
							matrix_num[i][j]++;
					}
				}
			(*grade) += 3 * k * (matrix_num[line][row] - 1);
			output_newnum(matrix_num, mark_same, output_line, output_row, line, row,goal_point,1);
			cout << "本次得分：" << 3 * k * (matrix_num[line][row] - 1) << " 总得分：" << *grade<< " 合成目标：" << goal_point << endl;
			down_zero(matrix_num, mark_same, output_line, output_row, line, row);
			make_new_num(matrix_num, max_num,output_line,output_row);
			output_newnum(matrix_num, mark_same, output_line, output_row, line, row, goal_point);
			if (max_num >= goal_point&& first_time)
			{
				first_time = 0;
				cct_setcolor(14,4);
				cout << "\n已经合成到"<<max_num<<",按回车键继续向更高目标进发...";
				cct_setcolor();
				while (_getch() != '\r');
			}
			return 0;
			break;
		}
		else if (choice == 'N' || choice == 'n')
		{
			return 0;
			break;
		}
		else if (choice == 'Q' || choice == 'q')
		{
			return 1;
			break;
		}
		else;
	}
}
