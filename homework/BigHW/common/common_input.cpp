/* 2152041 王浩 计科 */
#include<iostream>
#include "../include/cmd_console_tools.h"
#include<time.h>
#include<conio.h>
#include"../90-01-b2/90-01-b2.h"
using namespace std;

void input_ranks(int* line, int* row, int min_line, int max_line, int min_row, int max_row, int _3 = 0, int* goal_point = 0)
{
	while (1)
	{
		(*line) = 0;
		cout << "请输入行数(" << min_line << "-" << max_line << ")：" << endl;
		cin >> (*line);
		if (*line >= min_line && *line <= max_line)
			break;
	}
	while (1)
	{
		(*row) = 0;
		cout << "请输入列数(" << min_row << "-" << max_row << ")：" << endl;
		cin >> (*row);
		if (*row >= min_row && *row <= max_row)
			break;
	}
	if (_3)
	{
		while (1)
		{
			cout << "请输入合成目标(5-20)：" << endl;
			cin >> (*goal_point);
			if (*goal_point >= 5 && *goal_point <= 20)
				break;
		}
	}
}

void input_location(char* line, int* row, int output_line, int output_row)
{
	char* old_line = line;
	char same_row, old_same_row = char(*row + '0');
	int* old_row = row;
	while (1)
	{
		line = old_line;
		same_row = old_same_row;
		cout << "\n请以字母+数字形式[例：c2]输入矩阵坐标：    \b\b\b\b";
		int x_location, y_location;
		cct_getxy(x_location, y_location);
		cin >> *line >> same_row;
		(*row) = same_row - '0';
		if ((*line) < 'A' || ((*line > output_line + 64) && (*line < 'a')) || *line > output_line + 96 || *row<0 || *row>output_row - 1)
		{
			cout << "\n输入错误，请重新输入.";
			cct_gotoxy(x_location, y_location - 1);
			continue;
		}
		else
		{
			cct_gotoxy(x_location, y_location);
			break;
		}
	}
	*line = toupper(*line);
	cout << "\n输入为" << *line << "行" << *row << "列\n\n";
}