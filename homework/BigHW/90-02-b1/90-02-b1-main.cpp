/* 2152041 计科 王浩 */
#include <iostream>
#include <conio.h>
#include "../include/cmd_console_tools.h"
#include "../include/common_menu.h"
#include "../include/common_input.h"
#include "../include/common_output.h"
#include "../include/common_base.h"
using namespace std;

int main()
{
	while (1)
	{
		int line, row;
		int matrix_num[10][10] = { 0 };
		int mark_same[10][10] = { 0 };
		int goal_point =0;
		int location[2] = { 0 };
		int grade = 0;
		const char* sequence = "ABCDEFGQ";
		int choice = toupper(menu(sequence)) - 'A' + 1;
		int max_num = 3;
		int _9 = 1;
		srand((unsigned int)(time(NULL)));
		switch (choice)
		{
		case 17:
			break;
		case 1:
			cct_cls();
			input_ranks(&line, &row, 8, 10, 8, 10);
			for (int i = 0; i <= line - 1; i++)
				for (int j = 0; j <= row - 1; j++)
					matrix_num[i][j] = rand() % 5 + 1;
			output_matrix(line, row, matrix_num);
			while (1)
			{
				char line_location;
				int row_location;
				input_location(&line_location, &row_location, line, row);
				if (mark_same_recursion(matrix_num, mark_same, line_location - 'A', row_location, line, row) == 0)
					break;
			}
			is_end();
			break;
			case 2:
				cct_cls();
				input_ranks(&line, &row, 8, 10, 8, 10);
				for (int i = 0; i <= line - 1; i++)
					for (int j = 0; j <= row - 1; j++)
						matrix_num[i][j] = rand() % 5 + 1;
				output_matrix(line, row, matrix_num);
				char line_location;
				int row_location;
				while (1)
				{
					input_location(&line_location, &row_location, line, row);
					if (mark_same_recursion(matrix_num, mark_same, line_location - 'A', row_location, line, row) == 0)
						break;
				}
				merge_num(matrix_num, mark_same, line, row, line_location - 'A', row_location, max_num,0, &grade, 0);
				is_end();
				break;
			case 3:
				cct_cls();
				while (1)
				{
					input_ranks(&line, &row, 8, 10, 8, 10);
					for (int i = 0; i <= line - 1; i++)
						for (int j = 0; j <= row - 1; j++)
							matrix_num[i][j] = rand() % 5 + 1;
					int quit = 0;
					while (1)
					{
						output_matrix(line, row, matrix_num);
						char line_location;
						int row_location;
						while (1)
						{
							input_location(&line_location, &row_location, line, row);
							if (mark_same_recursion(matrix_num, mark_same, line_location - 'A', row_location, line, row) == 0)
								break;
						}
						int boring_play = merge_num(matrix_num, mark_same, line, row, line_location - 'A', row_location, max_num, 0, &grade, 0);
						quit = boring_play;
						for (int i = 0; i <= 7; i++)
							for (int j = 0; j <= 9; j++)
								mark_same[i][j] = 0;
						if (boring_play)
							break;
						if (judge_end(matrix_num, line, row) == 0)
						{
							cout << "没有可继续合成的相邻数字，按回车键游戏进入下一关\n";
							break;
						}
						int count = 0;
						for (int i = 0; i <= line - 1; i++)
							for (int j = 0; j <= row - 1; j++)
								if (matrix_num[i][j] != 0)
									count++;
						cout << "剩余" << count << "个星星\n";
						cout << "\n本次合成结束，按回车键继续新一次的合成...\n\n";
						while (_getch() != '\r');
					}
					if (quit)
						break;
					while (_getch() != '\r');
					cct_cls();
				}
				is_end();
				break;
			case 4:
				cct_cls();
				input_ranks(&line, &row,8, 10, 8, 10);
				for (int i = 0; i <= line - 1; i++)
					for (int j = 0; j <= row - 1; j++)
						matrix_num[i][j] = rand() % 5 + 1;
				cct_setconsoleborder(37 + (row - 5) * 6, 23 + (line - 5) * 3);
				cout << "屏幕当前设置为：" << 37 + (row - 5) * 6 << "行" << 23 + (line - 5) * 3 << "列" << endl;
				print_shell(matrix_num, line, row,0);
				cct_enable_mouse();
				choose_num_noline(matrix_num, line, row,location);
				is_end();
				break;
			case 5:
				cct_cls();
				input_ranks(&line, &row, 8, 10, 8, 10);
				for (int i = 0; i <= line - 1; i++)
					for (int j = 0; j <= row - 1; j++)
						matrix_num[i][j] = rand() % 5 + 1;
				cct_setconsoleborder(45 + (row - 5) * 8, 27 + (line - 5) * 4);
				cout << "屏幕当前设置为：" << 45 + (row - 5) * 8 << "行" << 27 + (line - 5) * 4 << "列" << endl;
				print_new_shell(matrix_num, line, row,0);
				cct_enable_mouse();
				choose_num(matrix_num, line, row, 0);
				is_end();
				break;
			case 6:
				cct_cls();
				input_ranks(&line, &row, 8, 10, 8, 10);
				for (int i = 0; i <= line - 1; i++)
					for (int j = 0; j <= row - 1; j++)
						matrix_num[i][j] = rand() % 5 + 1;
				cct_setconsoleborder(37 + (row - 5) * 6, 23 + (line - 5) * 3);
				cout << "屏幕当前设置为：" << 45 + (row - 5) * 8 << "行" << 27 + (line - 5) * 4 << "列" << endl;
				print_shell(matrix_num, line, row, 0);
				cct_enable_mouse();
				_9 = 0;
				plus_num(matrix_num, mark_same, line, row, max_num, goal_point, &grade, &_9, 0, 1);
				is_end();
				break;
			case 7:
				while (1)
				{
					cct_cls();
					input_ranks(&line, &row, 8, 10, 8, 10, 0, &goal_point);
					for (int i = 0; i <= line - 1; i++)
						for (int j = 0; j <= row - 1; j++)
							matrix_num[i][j] = rand() % 5 + 1;
					cct_setconsoleborder(45 + (row - 5) * 8, 27 + (line - 5) * 4);
					cout << "屏幕当前设置为：" << 45 + (row - 5) * 8 << "行" << 27 + (line - 5) * 4 << "列" << endl;
					print_new_shell(matrix_num, line, row, 0);
					while (1)
					{
						cct_enable_mouse();
						plus_num(matrix_num, mark_same, line, row, max_num, goal_point, &grade, &_9, 0);
						if (_9 == 81 || _9 == 113)
							break;
						if (judge_end(matrix_num, line, row) == 0)
						{
							cout << "没有可继续合成的相邻数字，回车进入下一关\n";
							break;
						}
					}
					if (judge_end(matrix_num, line, row) == 0)
					{
						int count = 0;
						for (int i = 0; i <= line - 1; i++)
							for (int j = 0; j <= row - 1; j++)
								if (matrix_num[i][j] != 0)
									count++;
						if (count < 10)
						{
							grade += 180 * (10 - count);
						}
						cct_gotoxy(0, line * 4 + 3);
						cout << "剩余" << count << "个星星\n";
						cout << "本次消除结束，按回车键继续下一关...\n\n";
						while (_getch() != '\r');
					}
					else
						break;
				}
				cct_gotoxy(0, line * 4 + 3);
				is_end();
				break;
		}
		if (choice == 17)
			break;
		cct_disable_mouse();
		cct_cls();
		grade = 0;
		for (int i = 0; i <= 9; i++)
			for (int j = 0; j <= 9; j++)
			{
				matrix_num[i][j] = 0;
				mark_same[i][j] = 0;
			}
		cct_setconsoleborder(121, 30, 121, 9002);
	}
	return 0;
}
