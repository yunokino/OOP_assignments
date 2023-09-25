/* 2152041 王浩 信07 */
#include<iostream>
#include<conio.h>
#include "cmd_console_tools.h"
#include"90-b2.h"
#include "lib_mto10_net_tools.h"
using namespace std;

int game_progress(mto10_net_tools& client);
int network(int _b);

char menu()
{
	char pick_choice;
	cout << "---------------------------------------" << endl;
	cout << "1.命令行找出可合成项并标识（非递归）" << endl;
	cout << "2.命令行找出可合成项并标识（递归）" << endl;
	cout << "3.命令行完成一次合成（分步骤显示）" << endl;
	cout << "4.命令行完整版（分步骤显示）" << endl;
	cout << "5.伪图形界面显示初始数组（无分隔线）" << endl;
	cout << "6.伪图形界面显示初始数组（有分隔线）" << endl;
	cout << "7.伪图形界面下用箭头键/鼠标选择当前色块" << endl;
	cout << "8.伪图形界面完成一次合成（分步骤）" << endl;
	cout << "9.伪图形界面完整版(支持鼠标)" << endl;
	cout << "--------------------------------------- " << endl;
	cout << "A.命令行界面（网络自动解 - 基本版）" << endl;
	cout << "B.伪图形界面（网络自动解 - 基本版）" << endl;
	cout << "---------------------------------------" << endl;
	cout << "0.退出" << endl;
	cout << "---------------------------------------" << endl;
	cout << "[请选择:]";
	cin >> pick_choice;
	return pick_choice;
}

int main()
{
	while (1)
	{
		int line, row;
		int matrix_num[8][10] = { 0 };
		int mark_same[8][10] = { 0 };
		int grade = 0;
		int goal_point;
		int choice = menu() - '0';
		int max_num = 3;
		int _9 = 1;
		srand((unsigned int)(time(NULL)));
		switch (choice)
		{
			case 0:
				break;
			case 1:
				cct_cls();
				input_ranks(&line, &row);
				for (int i = 0; i <= line - 1; i++)
					for (int j = 0; j <= row - 1; j++)
						matrix_num[i][j] = rand() % 3 + 1;
				output_matrix(line, row, matrix_num);
				mark_same_norecursion(matrix_num, mark_same, line, row);
				is_end();
				break;
			case 2:
				cct_cls();
				input_ranks(&line, &row);
				for (int i = 0; i <= line - 1; i++)
					for (int j = 0; j <= row - 1; j++)
						matrix_num[i][j] = rand() % 3 + 1;
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
			case 3:
				cct_cls();
				input_ranks(&line, &row, 1, &goal_point);
				for (int i = 0; i <= line - 1; i++)
					for (int j = 0; j <= row - 1; j++)
						matrix_num[i][j] = rand() % 3 + 1;
				output_matrix(line, row, matrix_num);
				char line_location;
				int row_location;
				while (1)
				{
					input_location(&line_location, &row_location, line, row);
					if (mark_same_recursion(matrix_num, mark_same, line_location - 'A', row_location, line, row) == 0)
						break;
				}
				merge_num(matrix_num, mark_same, line, row, line_location - 'A', row_location, max_num, goal_point, &grade);
				is_end();
				break;
			case 4:
				cct_cls();
				input_ranks(&line, &row, 1, &goal_point);
				for (int i = 0; i <= line - 1; i++)
					for (int j = 0; j <= row - 1; j++)
						matrix_num[i][j] = rand() % 3 + 1;
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
					int boring_play = merge_num(matrix_num, mark_same, line, row, line_location - 'A', row_location, max_num, goal_point, &grade);
					for (int i = 0; i <= 7; i++)
						for (int j = 0; j <= 9; j++)
							mark_same[i][j] = 0;
					if (boring_play)
						break;
					if (judge_end(matrix_num, line, row) == 0)
					{
						cout << "没有可继续合成的相邻数字，游戏结束\n";
						break;
					}
					cout << "\n本次合成结束，按回车键继续新一次的合成...\n\n";
					while (_getch() != '\r');
				}
				is_end();
				break;
			case 5:
				cct_cls();
				input_ranks(&line, &row);
				for (int i = 0; i <= line - 1; i++)
					for (int j = 0; j <= row - 1; j++)
						matrix_num[i][j] = rand() % 3 + 1;
				cct_setconsoleborder(37 + (row - 5) * 6, 23 + (line - 5) * 3);
				cout << "屏幕当前设置为：" << 37 + (row - 5) * 6 << "行" << 23 + (line - 5) * 3 << "列" << endl;
				print_shell(matrix_num, line, row);
				is_end();
				break;
			case 6:
				cct_cls();
				input_ranks(&line, &row);
				for (int i = 0; i <= line - 1; i++)
					for (int j = 0; j <= row - 1; j++)
						matrix_num[i][j] = rand() % 3 + 1;
				cct_setconsoleborder(45 + (row - 5) * 8, 27 + (line - 5) * 4);
				cout << "屏幕当前设置为：" << 45+(row-5)*8 << "行" << 27+(line-5)*4 << "列" << endl;
				print_new_shell(matrix_num, line, row);
				is_end();
				break;
			case 7:
				cct_cls();
				input_ranks(&line, &row);
				for (int i = 0; i <= line - 1; i++)
					for (int j = 0; j <= row - 1; j++)
						matrix_num[i][j] = rand() % 3 + 1;
				cct_setconsoleborder(45 + (row - 5) * 8, 27 + (line - 5) * 4);
				cout << "屏幕当前设置为：" << 45 + (row - 5) * 8 << "行" << 27 + (line - 5) * 4 << "列" << endl;
				print_new_shell(matrix_num, line, row);
				cct_enable_mouse();
				choose_num(matrix_num,line,row);
				is_end();
				break;
			case 8:
				cct_cls();
				input_ranks(&line, &row, 1, &goal_point);
				for (int i = 0; i <= line - 1; i++)
					for (int j = 0; j <= row - 1; j++)
						matrix_num[i][j] = rand() % 3 + 1;
				cct_setconsoleborder(45 + (row - 5) * 8, 27 + (line - 5) * 4);
				cout << "屏幕当前设置为：" << 45 + (row - 5) * 8 << "行" << 27 + (line - 5) * 4 << "列" << endl;
				print_new_shell(matrix_num, line, row);
				cct_enable_mouse();
				_9 = 0;
				plus_num(matrix_num,mark_same, line, row, max_num,goal_point,&grade,&_9);
				is_end();
				break;
			case 9:
				cct_cls();
				input_ranks(&line, &row, 1, &goal_point);
				for (int i = 0; i <= line - 1; i++)
					for (int j = 0; j <= row - 1; j++)
						matrix_num[i][j] = rand() % 3 + 1;
				cct_setconsoleborder(45 + (row - 5) * 8, 27 + (line - 5) * 4);
				cout << "屏幕当前设置为：" << 45 + (row - 5) * 8 << "行" << 27 + (line - 5) * 4 << "列" << endl;
				print_new_shell(matrix_num, line, row);
				while (1)
				{
					cct_enable_mouse();
					plus_num(matrix_num, mark_same, line, row,max_num, goal_point, &grade,&_9);
					if (_9 == 81 || _9 == 113)
						break;
					if (judge_end(matrix_num, line, row) == 0)
					{
						cout << "没有可继续合成的相邻数字，游戏结束\n";
						break;
					}
				}
				is_end();
				break;
			case 17:
			case 49:
				cct_cls();
				cout << "按回车键开始" << endl;
				while (_getch() != '\r');
				network(0);
				is_end();
				break;
			case 18:
			case 50:
				cct_cls();
				cout << "按回车键开始" << endl;
				while (_getch() != '\r');
				network(1);
				is_end();
				break;
		}
		if (choice == 0)
			break;
		cct_disable_mouse();
		cct_cls();
		grade = 0;
		for (int i = 0; i <= 7; i++)
			for (int j = 0; j <= 9; j++)
			{
				matrix_num[i][j] = 0;
				mark_same[i][j] = 0;
			}
		cct_setconsoleborder(121, 30, 121, 9002);
	}

	return 0;
}