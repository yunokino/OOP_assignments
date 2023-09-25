/* 2152041 王浩 计科 */
#include<iostream>
#include"../90-01-b2/90-01-b2.h"
#include<conio.h>
#include<windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/common_base.h"
#include "../include/common_input.h"
#include "../include/common_output.h"
using namespace std;

void panning_zero(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int line, int row,int command_line)
{
	int mark_zero_row[10] = { 0 };
	int exist_zero_row = 0;
	int count[10] = { 0 };
	for (int j = 0; j <= output_row - 1; j++)
		for (int i = 0; i <= output_line - 1; i++)
		{
			if (matrix_num[i][j] != 0)
			{
				mark_zero_row[j] = 1;
			}
		}
	for (int j = 0; j <= output_row - 1; j++)
	{
		for (int k = j; k > 0; k--)
		{
			if(!mark_zero_row[k])
				count[j]++;
		}
	}
	for (int j = 0; j <= output_row - 1; j++)
		for (int i = output_line - 1; i >= 0; i--)
		{
			if (count[j]&&mark_zero_row[j] && !command_line)
			{
				int k = j;
				while (!mark_zero_row[k])
					k++;
				int x_location = 4 + k * 8;
				if (matrix_num[i][k] != 0)
				{
					for (; x_location >= 5 + (k - count[k]) * 8; x_location--)
					{
						cct_gotoxy(x_location, 3 + i * 4);
						cct_setcolor(15, 15);
						cout << "      ";
						cct_gotoxy(x_location, 4 + i * 4);
						cout << "      ";
						cct_gotoxy(x_location, 5 + i * 4);
						cout << "      ";
						cct_setcolor();
						cct_setcolor(matrix_num[i][k], 0);
						cct_gotoxy(x_location - 1, 3 + i * 4);
						cout << "╔═╗";
						cct_gotoxy(x_location - 1, 4 + i * 4);
						cout << "║" << "★" << "║";
						cct_gotoxy(x_location - 1, 5 + i * 4);
						cout << "╚═╝";
						cct_setcolor();
						Sleep(5);
						if ((x_location - 5) % 8 == 0)
						{
							cct_setcolor(15, 0);
							cct_gotoxy(x_location + 5, 3 + i * 4);
							cout << "║";
							cct_gotoxy(x_location + 5, 4 + i * 4);
							cout << "║";
							cct_gotoxy(x_location + 5, 5 + i * 4);
							cout << "║";
						}
					}
				}
			}
		}
	for (int j = 0; j <= output_row - 1; j++)
	{
		if (!mark_zero_row[j] && j != output_row - 1)
		{
			exist_zero_row = 1;
			for (int i = 0; i <= output_line - 1; i++)
			{
				for (int k = j; k <= output_row - 2; k++)
				{
					matrix_num[i][k] = matrix_num[i][k + 1];
				}
			}
		}
	}
	if (exist_zero_row)
	{
		for (int i = 0; i <= output_line - 1; i++)
		{
			matrix_num[i][output_row - 1] = 0;
		}
	}
}

int mark_same_recursion(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row, int first,int make_to_ten,int command_line)
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
	if ((matrix_num[old_line][old_row] == 0 || k == 0) && first)
	{
		if (command_line)
		{
			if (k == 0)
				cout << "输入的矩阵坐标位置处无连续相同值，请重新输入";
			if (matrix_num[old_line][old_row] == 0)
				cout << "输入的矩阵坐标位置处矩阵值等于零，请重新输入";
		}
		if (make_to_ten)
		{
			for (int i = 0; i <= 7; i++)
				for (int j = 0; j <= 9; j++)
					mark_same[i][j] = 0;
		}
		else
		{
			for (int i = 0; i <= 9; i++)
				for (int j = 0; j <= 9; j++)
					mark_same[i][j] = 0;
		}
		return 1;
	}
	if (first&&command_line)
		output_mark_same(matrix_num, mark_same, output_line, output_row);
	if (command_line)
		return 0;
	else
		return k;
}

int merge_num(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int line, int row, int& max_num, int goal_point, int* grade, int make_to_ten)
{
	static int first_time = 1;
	if (make_to_ten)
		cout << "\n请确认是否把相邻的相同值合并到" << char(line + 65) << row << "中(Y / N / Q)：";
	else
		cout << "\n请确认是否要把相邻的相同值消除" << char(line + 65) << row << "中(Y / N / Q)：";
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
						{
							if (make_to_ten)
								matrix_num[i][j]++;
							else
								matrix_num[i][j] = 0;
						}
					}
				}
			if (make_to_ten)
				(*grade) += 3 * k * (matrix_num[line][row] - 1);
			else
				(*grade) += 5 * k * k;
			output_newnum(matrix_num, mark_same, output_line, output_row, line, row, goal_point, 1);
			if(make_to_ten)
				cout << "本次得分：" << 3 * k * (matrix_num[line][row] - 1) << " 总得分：" << *grade;
			else
				cout << "本次得分：" << 5 * k * k << " 总得分：" << *grade;
			if (make_to_ten)
				cout << " 合成目标：" << goal_point << endl;
			else
				cout << endl;
			down_zero(matrix_num, mark_same, output_line, output_row, line, row);
			if (make_to_ten)
			{
				make_new_num(matrix_num, max_num, output_line, output_row);
				output_newnum(matrix_num, mark_same, output_line, output_row, line, row, goal_point);
				if (max_num >= goal_point && first_time)
				{
					first_time = 0;
					cct_setcolor(14, 4);
					cout << "\n已经合成到" << max_num << ",按回车键继续向更高目标进发...";
					cct_setcolor();
					while (_getch() != '\r');
				}
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

void down_zero(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int line, int row)
{
	cout << "\n按回车键进行数组下落除0操作...";
	while (_getch() != '\r');
	cout << "\n除0后的数组(不同色标识)：\n";
	cout << "\n  |  ";
	for (int j = 0; j <= output_row - 1; j++)
	{
		int t = 0;
		for (int i = 0; i < output_line - 1; i++)
			for (int m = 0; m < output_line - (i + 1); m++)
			{
				if (matrix_num[m][j] > matrix_num[m + 1][j] && matrix_num[m + 1][j] == 0)
				{
					t = matrix_num[m][j];
					matrix_num[m][j] = matrix_num[m + 1][j];
					matrix_num[m + 1][j] = t;
					mark_same[m][j] = 1;
					mark_same[m + 1][j] = 0;
				}
			}
	}
	for (int i = 0; i <= output_line - 1; i++)
		for (int j = 0; j <= output_row - 1; j++)
		{
			mark_same[i][j] = 0;
			if (matrix_num[i][j] == 0)
				mark_same[i][j] = 1;
		}
	for (int j = 0; j <= output_row - 1; j++)
		cout << j << "  ";
	cout << "\n--+--";
	for (int j = 0; j <= output_row - 1; j++)
	{
		if (j == output_row - 1)
			cout << "--";
		else
			cout << "---";
	}
	cout << endl;
	for (int i = 0; i <= output_line - 1; i++)
	{
		cout << char(i + 65) << " |  ";
		for (int j = 0; j <= output_row - 1; j++)
		{
			if (mark_same[i][j] == 1)
				cct_setcolor(14, 0);
			cout << matrix_num[i][j];
			cct_setcolor();
			cout << "  ";
		}
		cout << endl;
	}
}

void make_new_num(int matrix_num[][10], int max_num, int output_line, int output_row)
{
	srand((unsigned int)(time(NULL)));
	cout << "\n按回车键进行新值填充...";
	while (_getch() != '\r');
	for (int i = 0; i <= output_row - 1; i++)
		for (int j = 0; j <= output_line - 1; j++)
			if (matrix_num[i][j] == 0)
			{
				if (max_num == 3)
					matrix_num[i][j] = rand() % 3 + 1;
				else if (max_num == 4)
				{
					if (rand() % 10 == 0)
						matrix_num[i][j] = 4;
					else
						matrix_num[i][j] = rand() % 3 + 1;
				}
				else if (max_num == 5)
				{
					if (rand() % 15 == 0)
						matrix_num[i][j] = 4;
					/*考虑条件概率，因为如果if执行则后面的不执行,所以此时是在85%概率里算总的10%概率，根据条件概率计算得*/
					else if (rand() % 17 == 0 || rand() % 17 == 1)
						matrix_num[i][j] = 5;
					else
						matrix_num[i][j] = rand() % 3 + 1;
				}
				else if (max_num == 6)
				{
					if (rand() % 20 == 0)
						matrix_num[i][j] = 6;
					/*考虑条件概率*/
					else if (rand() % 19 == 0 || rand() % 19 == 1 || rand() % 19 == 2)
						matrix_num[i][j] = 5;
					else
						matrix_num[i][j] = rand() % 4 + 1;
				}
				else
				{
					if (rand() % 20 == 0)
						matrix_num[i][j] = max_num;
					else if (rand() % 19 == 0)
						matrix_num[i][j] = max_num - 1;
					else if (rand() % 9 == 0)
						matrix_num[i][j] = max_num - 2;
					else
						matrix_num[i][j] = rand() % (max_num - 3) + 1;
				}
			}
}

void choose_num_noline(int matrix_num[][10], int line, int row,int location[])
{
	cct_setcursor(CURSOR_INVISIBLE);
	int Mx = 0, My = 0, MAction, keycode1, keycode2;
	int i = location[0], j = location[1];
	int old_i = location[0], old_j = location[1];
	bool first_time = 1;
	cct_gotoxy(4 + location[1] * 6, 3 + location[0] * 3);
	cct_setcolor(matrix_num[location[0]][location[1]], 15);

	cout << "╔═╗";
	cct_gotoxy(4 + location[1] * 6, 4 + location[0] * 3);
	cout << "║" << "★" << "║";
	cct_gotoxy(4 + location[1] * 6, 5 + location[0] * 3);
	cout << "╚═╝";
	cct_setcolor();
	cct_gotoxy(0, line * 3 + 4);
	cout << "鼠标/方向键移动,左击/回车选方块,q退出";
	while (1)
	{
		cct_read_keyboard_and_mouse(Mx, My, MAction, keycode1, keycode2);
		if (keycode1 == 13 && keycode2 == 0)
			break;
		if (keycode1 != 224)
		{
			i = (My - 3) / 3;
			if (i < 0)
				i = 0;
			j = (Mx - 3) / 6;
		}
		else
		{
			if (keycode2 == 72)
			{
				i--;
				if (i < 0)
					i = line - 1;
			}
			else if (keycode2 == 80)
			{
				i++;
				if (i > line - 1)
					i = 0;
			}
			else if (keycode2 == 77)
			{
				j++;
				if (j > row - 1)
					j = 0;
			}
			else if (keycode2 == 75)
			{
				j--;
				if (j < 0)
					j = row - 1;
			}
			else;
		}
		bool in_square = (Mx >= 4 + j * 6 && Mx <= 9 + j * 6 && My >= 3 + i * 3 && My <= 5 + i * 3 && i <= line - 1 && j <= row - 1);
		cct_gotoxy(0, line * 3 + 4);
		cout << "[当前";
		keycode1 == 224 ? cout << "键盘] " : cout << "鼠标]";
		cout << "                                     \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		if (first_time && in_square)
		{
			cct_gotoxy(4 + j * 6, 3 + i * 3);
			cct_setcolor(matrix_num[i][j], 15);
			cout << "╔═╗";
			cct_gotoxy(4 + j * 6, 4 + i * 3);
			cout << "║" << "★" << "║";
			cct_gotoxy(4 + j * 6, 5 + i * 3);
			cout << "╚═╝";
			cct_setcolor();
			old_i = i;
			old_j = j;
			first_time = 0;
		}
		if ((in_square) || (keycode1 == 224))
		{
			cct_gotoxy(11, line * 3 + 4);
			cout << char(i + 'A') << "行" << j << "列                \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
			cct_gotoxy(4 + old_j * 6, 3 + old_i * 3);
			cct_setcolor(matrix_num[old_i][old_j], 0);
			cout << "╔═╗";
			cct_gotoxy(4 + old_j * 6, 4 + old_i * 3);
			cout << "║" << "★" << "║";
			cct_gotoxy(4 + old_j * 6, 5 + old_i * 3);
			cout << "╚═╝";
			cct_gotoxy(4 + j * 6, 3 + i * 3);
			cct_setcolor(matrix_num[i][j], 15);
			cout << "╔═╗";
			cct_gotoxy(4 + j * 6, 4 + i * 3);
			cout << "║" << "★" << "║";
			cct_gotoxy(4 + j * 6, 5 + i * 3);
			cout << "╚═╝";
			cct_setcolor();
			old_i = i;
			old_j = j;
			if ((MAction == MOUSE_LEFT_BUTTON_CLICK))
				break;
		}
		else
		{
			if (!first_time || !in_square)
			{
				cct_gotoxy(4 + old_j * 6, 3 + old_i * 3);
				cct_setcolor(matrix_num[old_i][old_j], 0);
				cout << "╔═╗";
				cct_gotoxy(4 + old_j * 6, 4 + old_i * 3);
				cout << "║" << "★" << "║";
				cct_gotoxy(4 + old_j * 6, 5 + old_i * 3);
				cout << "╚═╝";
				cct_gotoxy(11, line * 3 + 4);
				cct_setcolor();
			}
			cout << "位置非法                \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		}
	}
	cct_gotoxy(0, line * 3 + 4);
	cout << "选中了" << char(i + 'A') << "行" << j << "列                           \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	location[0] = i;
	location[1] = j;
	cct_setcursor(CURSOR_INVISIBLE);
}

void choose_num(int matrix_num[][10], int line, int row, int make_to_ten)
{
	cct_setcursor(CURSOR_INVISIBLE);
	int Mx = 0, My = 0, MAction, keycode1, keycode2;
	int i = 0, j = 0;
	int old_i = 0, old_j = 0;
	bool first_time = 1;
	cct_gotoxy(4, 3);
	cct_setcolor(matrix_num[0][0], 15);
	if(make_to_ten)
		cout << "┏━┓";
	else
		cout << "╔═╗";
	cct_gotoxy(4, 4);
	if (make_to_ten)
		cout << "┃" << matrix_num[0][0] << " ┃";
	else
		cout << "║" << "★" << "║";
	cct_gotoxy(4, 5);
	if(make_to_ten)
		cout << "┗━┛"; 
	else
		cout << "╚═╝";
	cct_setcolor();
	cct_gotoxy(0, line * 4 + 3);
	cout << "鼠标/方向键移动，左击/回车选方块";
	while (1)
	{
		cct_read_keyboard_and_mouse(Mx, My, MAction, keycode1, keycode2);
		if (keycode1 == 13 && keycode2 == 0)
			break;
		cct_gotoxy(0, line * 4 + 3);
		cout << "[当前";
		keycode1 == 224 ? cout << "键盘] " : cout << "鼠标]        \b\b\b\b\b\b\b\b";
		if (keycode1 != 224)
		{
			i = (My - 3) / 4;
			j = (Mx - 3) / 8;
		}
		else
		{
			if (keycode2 == 72)
			{
				i--;
				if (i < 0)
					i = line - 1;
			}
			else if (keycode2 == 80)
			{
				i++;
				if (i > line - 1)
					i = 0;
			}
			else if (keycode2 == 77)
			{
				j++;
				if (j > row - 1)
					j = 0;
			}
			else if (keycode2 == 75)
			{
				j--;
				if (j < 0)
					j = row - 1;
			}
			else;
		}
		bool in_square = (Mx >= 4 + j * 8 && Mx <= 10 + j * 8 && My >= 3 + i * 4 && My <= 5 + i * 4 && i <= line - 1 && j <= row - 1);
		if (first_time && in_square)
		{
			cct_gotoxy(4, 3);
			cct_setcolor(matrix_num[0][0], 0);
			if(make_to_ten)
				cout << "┏━┓";
			else
				cout << "╔═╗";
			cct_gotoxy(4, 4);
			if (make_to_ten)
				cout << "┃" << matrix_num[0][0] << " ┃";
			else
				cout << "║" << "★" << "║";
			cct_gotoxy(4, 5);
			if(make_to_ten)
				cout << "┗━┛";
			else
				cout << "╚═╝";
			cct_setcolor();
			old_i = i;
			old_j = j;
			first_time = 0;
		}
		if ((in_square) || (keycode1 == 224))
		{
			cct_gotoxy(11, line * 4 + 3);
			cout << char(i + 'A') << "行" << j << "列                \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
			cct_gotoxy(4 + old_j * 8, 3 + old_i * 4);
			cct_setcolor(matrix_num[old_i][old_j], 0);
			if (make_to_ten)
				cout << "┏━┓";
			else
				cout << "╔═╗";
			cct_gotoxy(4 + old_j * 8, 4 + old_i * 4);
			if (make_to_ten)
				cout << "┃" << matrix_num[old_i][old_j] << " ┃";
			else
				cout << "║" << "★" << "║";
			cct_gotoxy(4 + old_j * 8, 5 + old_i * 4);
			if (make_to_ten)
				cout << "┗━┛";
			else
				cout << "╚═╝";
			cct_gotoxy(4 + j * 8, 3 + i * 4);
			cct_setcolor(matrix_num[i][j], 15);
			if (make_to_ten)
				cout << "┏━┓";
			else
				cout << "╔═╗";
			cct_gotoxy(4 + j * 8, 4 + i * 4);
			if (make_to_ten)
				cout << "┃" << matrix_num[i][j] << " ┃";
			else
				cout << "║" << "★" << "║";
			cct_gotoxy(4 + j * 8, 5 + i * 4);
			if (make_to_ten)
				cout << "┗━┛";
			else
				cout << "╚═╝";
			cct_setcolor();
			old_i = i;
			old_j = j;
			if ((MAction == MOUSE_LEFT_BUTTON_CLICK))
				break;
		}
		else
		{
			if (!first_time || !in_square)
			{
				cct_gotoxy(4 + old_j * 8, 3 + old_i * 4);
				cct_setcolor(matrix_num[old_i][old_j], 0);
				if (make_to_ten)
					cout << "┏━┓";
				else
					cout << "╔═╗";
				cct_gotoxy(4 + old_j * 8, 4 + old_i * 4);
				if (make_to_ten)
					cout << "┃" << matrix_num[old_i][old_j] << " ┃";
				else
					cout << "║" << "★" << "║";
				cct_gotoxy(4 + old_j * 8, 5 + old_i * 4);
				if (make_to_ten)
					cout << "┗━┛";
				else
					cout << "╚═╝";
				cct_gotoxy(11, line * 4 + 3);
				cct_setcolor();
			}
			cout << "位置非法                \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		}
	}
	cct_gotoxy(0, line * 4 + 3);
	cout << "选中了" << char(i + 'A') << "行" << j << "列                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}

void print_merge(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int old, int make_to_ten, int no_line)
{
	cct_setcursor(CURSOR_INVISIBLE);
	if (old)
	{
		for (int i = 0; i <= output_line - 1; i++)
			for (int j = 0; j <= output_row - 1; j++)
			{
				if (mark_same[i][j] == 1)
				{
					if (make_to_ten)
					{
						cct_gotoxy(4 + j * 8, 3 + i * 4);
						cct_setcolor(matrix_num[i][j], 15);
						cout << "┏━┓";
						cct_gotoxy(4 + j * 8, 4 + i * 4);
						cout << "┃" << matrix_num[i][j] << " ┃";
						cct_gotoxy(4 + j * 8, 5 + i * 4);
						cout << "┗━┛";
						cct_setcolor();
					}
					else
					{
						if (no_line)
						{
							cct_gotoxy(4 + j * 6, 3 + i * 3);
							cct_setcolor(matrix_num[i][j], 15);
							cout << "╔═╗";
							cct_gotoxy(4 + j * 6, 4 + i * 3);
							cout << "║" << "★" << "║";
							cct_gotoxy(4 + j * 6, 5 + i * 3);
							cout << "╚═╝";
							cct_setcolor();
						}
						else
						{
							if (matrix_num[i][j] != 0)
							{
								cct_gotoxy(4 + j * 8, 3 + i * 4);
								cct_setcolor(matrix_num[i][j], 15);
								cout << "╔═╗";
								cct_gotoxy(4 + j * 8, 4 + i * 4);
								cout << "║" << "★" << "║";
								cct_gotoxy(4 + j * 8, 5 + i * 4);
								cout << "╚═╝";
								cct_setcolor();
							}
						}
					}
				}
			}
	}
	else
	{
		for (int i = 0; i <= output_line - 1; i++)
			for (int j = 0; j <= output_row - 1; j++)
			{
				if (make_to_ten)
				{
					cct_gotoxy(4 + j * 8, 3 + i * 4);
					cct_setcolor(matrix_num[i][j], 0);
					cout << "┏━┓";
					cct_gotoxy(4 + j * 8, 4 + i * 4);
					cout << "┃" << matrix_num[i][j] << " ┃";
					cct_gotoxy(4 + j * 8, 5 + i * 4);
					cout << "┗━┛";
					cct_setcolor();
				}
				else
				{
					if (no_line)
					{
						cct_gotoxy(4 + j * 6, 3 + i * 3);
						cct_setcolor(matrix_num[i][j], 0);
						cout << "╔═╗";
						cct_gotoxy(4 + j * 6, 4 + i * 3);
						cout << "║" << "★" << "║";
						cct_gotoxy(4 + j * 6, 5 + i * 3);
						cout << "╚═╝";
						cct_setcolor();
					}
					else
					{
						if (matrix_num[i][j] != 0)
						{
							cct_gotoxy(4 + j * 8, 3 + i * 4);
							cct_setcolor(matrix_num[i][j], 0);
							cout << "╔═╗";
							cct_gotoxy(4 + j * 8, 4 + i * 4);
							cout << "║" << "★" << "║";
							cct_gotoxy(4 + j * 8, 5 + i * 4);
							cout << "╚═╝";
							cct_setcolor();
						}
					}
				}
			}
	}
}

void except_zero(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row, int& k, int& is_central, int& max_num)
{
	k = 0;
	is_central = matrix_num[line][row];
	for (int i = 0; i <= output_line - 1; i++)
		for (int j = 0; j <= output_row - 1; j++)
		{
			if (mark_same[i][j] == 1 && (i != line || j != row))
			{
				k++;
				cct_setcolor(15, 15);
				cct_gotoxy(4 + j * 8, 3 + i * 4);
				cout << "      ";
				cct_gotoxy(4 + j * 8, 4 + i * 4);
				cout << "      ";
				cct_gotoxy(4 + j * 8, 5 + i * 4);
				cout << "      ";
				cct_setcolor();
				matrix_num[i][j] = 0;
			}
		}
	if (matrix_num[line][row] == max_num)
		max_num++;
	matrix_num[line][row]++;
	for (int i = 0; i <= 3; i++)
	{
		Sleep(50);
		cct_setcolor(matrix_num[line][row], 3);
		cct_gotoxy(4 + row * 8, 3 + line * 4);
		cout << "┏━┓";
		cct_gotoxy(4 + row * 8, 4 + line * 4);
		cout << "┃" << matrix_num[line][row] << " ┃";
		cct_gotoxy(4 + row * 8, 5 + line * 4);
		cout << "┗━┛";
		Sleep(50);
		cct_setcolor(matrix_num[line][row], 0);
		cct_gotoxy(4 + row * 8, 3 + line * 4);
		cout << "┏━┓";
		cct_gotoxy(4 + row * 8, 4 + line * 4);
		cout << "┃" << matrix_num[line][row] << " ┃";
		cct_gotoxy(4 + row * 8, 5 + line * 4);
		cout << "┗━┛";
		cct_setcolor();
	}
	cct_setcolor(matrix_num[line][row], 0);
	cct_gotoxy(4 + row * 8, 3 + line * 4);
	cout << "┏━┓";
	cct_gotoxy(4 + row * 8, 4 + line * 4);
	cout << "┃" << matrix_num[line][row] << " ┃";
	cct_gotoxy(4 + row * 8, 5 + line * 4);
	cout << "┗━┛";
	cct_setcolor();
}

void destory_zero(int matrix_num[][10], int mark_same[][10], int output_line, int output_row,int no_line)
{
	for (int i = 0; i <= output_line - 1; i++)
		for (int j = 0; j <= output_row - 1; j++)
		{
			if (mark_same[i][j] == 1)
			{
				cct_setcolor(15, 15);
				if (no_line)
				{
					cct_gotoxy(4 + j * 6, 3 + i * 3);
					cout << "      ";
					cct_gotoxy(4 + j * 6, 4 + i * 3);
					cout << "      ";
					cct_gotoxy(4 + j * 6, 5 + i * 3);
					cout << "      ";
				}
				else
				{
					cct_gotoxy(4 + j * 8, 3 + i * 4);
					cout << "      ";
					cct_gotoxy(4 + j * 8, 4 + i * 4);
					cout << "      ";
					cct_gotoxy(4 + j * 8, 5 + i * 4);
					cout << "      ";
				}
				cct_setcolor();
				matrix_num[i][j] = 0;
			}
		}
}

void fall_zero(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row,int make_to_ten, int no_line)
{
	int count[8][10] = { 0 };
	for (int j = 0; j <= output_row - 1; j++)
		for (int i = 0; i <= output_line - 1; i++)
		{
			if (matrix_num[i][j] != 0)
			{
				for (int m = i; m <= output_line - 1; m++)
				{
					if (matrix_num[m][j] == 0)
						count[i][j]++;
				}
			}
		}
	for (int j = 0; j <= output_row - 1; j++)
		for (int i = output_line - 2; i >= 0; i--)
		{
			if (count[i][j] != 0)
			{
				if (no_line)
				{
					int y_location = 3 + i * 3;
					for (; y_location <= 2 + (i + count[i][j]) * 3; y_location++)
					{
						cct_gotoxy(4 + j * 6, y_location);
						cct_setcolor(15, 15);
						cout << "      ";
						cct_gotoxy(4 + j * 6, y_location + 1);
						cout << "      ";
						cct_gotoxy(4 + j * 6, y_location + 2);
						cout << "      ";
						cct_setcolor();
						cct_setcolor(matrix_num[i][j], 0);
						cct_gotoxy(4 + j * 6, y_location + 1);
						cout << "╔═╗";
						cct_gotoxy(4 + j * 6, y_location + 2);
						cout << "║" << "★" << "║";
						cct_gotoxy(4 + j * 6, y_location + 3);
						cout << "╚═╝";
						cct_setcolor();
						Sleep(10);
					}
				}
				else
				{
					int y_location = 3 + i * 4;
					for (; y_location <= 2 + (i + count[i][j]) * 4; y_location++)
					{
						cct_gotoxy(4 + j * 8, y_location);
						cct_setcolor(15, 15);
						cout << "      ";
						cct_gotoxy(4 + j * 8, y_location + 1);
						cout << "      ";
						cct_gotoxy(4 + j * 8, y_location + 2);
						cout << "      ";
						cct_setcolor();
						cct_setcolor(matrix_num[i][j], 0);
						cct_gotoxy(4 + j * 8, y_location + 1);
						if (make_to_ten)
							cout << "┏━┓";
						else
							cout << "╔═╗";
						cct_gotoxy(4 + j * 8, y_location + 2);
						if(make_to_ten)
							cout << "┃" << matrix_num[i][j] << " ┃";
						else
							cout << "║" << "★" << "║";
						cct_gotoxy(4 + j * 8, y_location + 3);
						if (make_to_ten)
							cout << "┗━┛";
						else
							cout << "╚═╝";
						cct_setcolor();
						Sleep(5);
						if ((y_location + 2) % 4 == 0)
						{
							cct_gotoxy(4 + j * 8, y_location);
							cct_setcolor(15, 0);
							if(make_to_ten)
								cout << "━━━";
							else
								cout << "═══";
						}
					}
				}
			}
		}
	for (int j = 0; j <= output_row - 1; j++)
	{
		int t = 0;
		for (int i = 0; i < output_line - 1; i++)
			for (int m = 0; m < output_line - (i + 1); m++)
			{
				if (matrix_num[m][j] > matrix_num[m + 1][j] && matrix_num[m + 1][j] == 0)
				{
					t = matrix_num[m][j];
					matrix_num[m][j] = matrix_num[m + 1][j];
					matrix_num[m + 1][j] = t;
					mark_same[m][j] = 1;
					mark_same[m + 1][j] = 0;
				}
			}
	}
}

void make_new_num_tuxing(int matrix_num[][10], int max_num, int output_line, int output_row)
{
	srand((unsigned int)(time(NULL)));
	cct_setcolor();
	cct_setcolor();
	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 9; j++)
			if (matrix_num[i][j] == 0)
			{
				if (max_num == 3)
					matrix_num[i][j] = rand() % 3 + 1;
				else if (max_num == 4)
				{
					if (rand() % 10 == 0)
						matrix_num[i][j] = 4;
					else
						matrix_num[i][j] = rand() % 3 + 1;
				}
				else if (max_num == 5)
				{
					if (rand() % 15 == 0)
						matrix_num[i][j] = 4;
					/*考虑条件概率，因为如果if执行则后面的不执行,所以此时是在85%概率里算总的10%概率，根据条件概率计算得*/
					else if (rand() % 17 == 0 || rand() % 17 == 1)
						matrix_num[i][j] = 5;
					else
						matrix_num[i][j] = rand() % 3 + 1;
				}
				else if (max_num == 6)
				{
					if (rand() % 20 == 0)
						matrix_num[i][j] = 6;
					/*考虑条件概率*/
					else if (rand() % 19 == 0 || rand() % 19 == 1 || rand() % 19 == 2)
						matrix_num[i][j] = 5;
					else
						matrix_num[i][j] = rand() % 4 + 1;
				}
				else
				{
					if (rand() % 20 == 0)
						matrix_num[i][j] = max_num;
					else if (rand() % 19 == 0)
						matrix_num[i][j] = max_num - 1;
					else if (rand() % 9 == 0)
						matrix_num[i][j] = max_num - 2;
					else
						matrix_num[i][j] = rand() % (max_num - 3) + 1;
				}
			}
}

void print_cube(int matrix_num[][10], int i, int j,int color,int make_to_ten,int no_line)
{
	if (make_to_ten)
	{
		cct_gotoxy(4 + j * 8, 3 + i * 4);
		cct_setcolor(matrix_num[i][j], color);
		cout << "┏━┓";
		cct_gotoxy(4 + j * 8, 4 + i * 4);
		cout << "┃" << matrix_num[i][j] << " ┃";
		cct_gotoxy(4 + j * 8, 5 + i * 4);
		cout << "┗━┛";
	}
	else
	{
		if (no_line)
		{
			cct_gotoxy(4 + j * 6, 3 + i * 3);
			cct_setcolor(matrix_num[i][j], color);
			cout << "╔═╗";
			cct_gotoxy(4 + j * 6, 4 + i * 3);
			cout << "║" << "★" << "║";
			cct_gotoxy(4 + j * 6, 5 + i * 3);
			cout << "╚═╝";
		}
		else
		{
			cct_gotoxy(4 + j * 8, 3 + i * 4);
			cct_setcolor(matrix_num[i][j], color);
			cout << "╔═╗";
			cct_gotoxy(4 + j * 8, 4 + i * 4);
			cout << "║" << "★" << "║";
			cct_gotoxy(4 + j * 8, 5 + i * 4);
			cout << "╚═╝";
		}
	}
	cct_setcolor();
}

void plus_num(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int& max_num, int goal_point, int* grade, int* _9, int make_to_ten, int no_line)
{
		cct_setcursor(CURSOR_INVISIBLE);
		int Mx = 0, My = 0, MAction, keycode1, keycode2;
		int i = 0, j = 0;
		int old_i = 0, old_j = 0;
		static bool first_time = 1;
		bool in_square;
		bool lonely = 0;
		bool click = 0;
		bool enter = 0;
		if (matrix_num[0][0] != 0)
			print_cube(matrix_num, 0, 0, 15, make_to_ten, no_line);
		output_info(output_line, 0, "鼠标/方向键移动，左击/回车选择", no_line);
		if (*_9)
			cout << "q退出";
		for (int i = 0; i <= output_line - 1; i++)
			for (int j = 0; j <= output_row - 1; j++)
			{
				if (matrix_num[i][j] == 0 && !make_to_ten && !no_line)
				{
					cct_gotoxy(4 + j * 8, 3 + i * 4);
					cct_setcolor(15, 15);
					cout << "      ";
					cct_gotoxy(4 + j * 8, 4 + i * 4);
					cout << "      ";
					cct_gotoxy(4 + j * 8, 5 + i * 4);
					cout << "      ";
					cct_setcolor();
				}
			}
		while (1)
		{
			cct_read_keyboard_and_mouse(Mx, My, MAction, keycode1, keycode2);
			if ((*_9) && (keycode1 == 81 || keycode1 == 113))
			{
				(*_9) = keycode1;
				break;
			}
			if (keycode1 != 13)
				enter = 0;
			if(!no_line)
				cct_gotoxy(0, output_line * 4 + 3);
			else
				cct_gotoxy(0, output_line * 3 + 4);
			if (!lonely)
			{
				cout << "[当前";
				(keycode1 == 224 || keycode1 == 13) ? cout << "键盘] " : cout << "鼠标] ";
				cout << "                      \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
			}
			if (keycode1 != 224 && keycode1 != 13)
			{
				if (!no_line)
				{
					i = (My - 3) / 4;
					j = (Mx - 3) / 8;
				}
				else
				{
					i = (My - 3) / 3;
					if (i < 0)
						i = 0;
					j = (Mx - 3) / 6;
				}
			}
			else
			{
				if (keycode2 == 72)
				{
					i--;
					if (i < 0)
						i = output_line - 1;
				}
				else if (keycode2 == 80)
				{
					i++;
					if (i > output_line - 1)
						i = 0;
				}
				else if (keycode2 == 77)
				{
					j++;
					if (j > output_row - 1)
						j = 0;
				}
				else if (keycode2 == 75)
				{
					j--;
					if (j < 0)
						j = output_row - 1;
				}
				else;
				print_merge(matrix_num, mark_same, output_line, output_row, 1, make_to_ten, no_line);
			}
			if (make_to_ten)
			{
				for (int m = 0; m <= 7; m++)
					for (int n = 0; n <= 9; n++)
						mark_same[m][n] = 0;
			}
			else
			{
				for (int m = 0; m <= 9; m++)
					for (int n = 0; n <= 9; n++)
						mark_same[m][n] = 0;
			}
			if(!no_line)
				in_square = (Mx >= 4 + j * 8 && Mx <= 10 + j * 8 && My >= 3 + i * 4 && My <= 5 + i * 4 && i <= output_line - 1 && j <= output_row - 1);
			else
				in_square = (Mx >= 4 + j * 6 && Mx <= 10 + j * 6 && My >= 3 + i * 3 && My <= 5 + i * 3 && i <= output_line - 1 && j <= output_row - 1);
			if (first_time && in_square)
			{
				if (matrix_num[old_i][old_j] != 0)
					print_cube(matrix_num, old_i, old_j, 0, make_to_ten, no_line);
				print_cube(matrix_num, i, j, 15, make_to_ten, no_line);
				old_i = i;
				old_j = j;
				first_time = 0;
			}
			if ((in_square) || (keycode1 == 224) || keycode1 == 13)
			{
				if(!no_line)
					cct_gotoxy(11, output_line * 4 + 3);
				else
					cct_gotoxy(11, output_line * 3 + 4);
				if (!lonely)
					cout << char(i + 'A') << "行" << j << "列                     \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";			
				if (matrix_num[old_i][old_j] != 0)
					print_cube(matrix_num, old_i, old_j, 0, make_to_ten, no_line);
				if(matrix_num[i][j] != 0)
					print_cube(matrix_num, i, j, 15, make_to_ten, no_line);
				old_i = i;
				old_j = j;
				if (MAction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13)
				{
					int count = 0;
					if (make_to_ten)
						count = mark_same_recursion(matrix_num, mark_same, i, j, output_line, output_row, 0, 1, 0);
					else
						count = mark_same_recursion(matrix_num, mark_same, i, j, output_line, output_row, 0, 0, 0);
					if (count == 0)
						lonely = 1;
					else
					{
						lonely = 0;
						print_merge(matrix_num, mark_same, output_line, output_row, 1, make_to_ten, no_line);
						if(!no_line)
							cct_gotoxy(0, output_line * 4 + 3);
						else
							cct_gotoxy(0, output_line * 3 + 4);
						if (click || enter)
							break;
						if (MAction == MOUSE_LEFT_BUTTON_CLICK)
							click = 1;
						if (keycode1 == 13)
							enter = 1;
					}
				}
			}
			else
			{
				lonely = 0;
				click = 0;
				enter = 0;
				lonely = 0;
				print_merge(matrix_num, mark_same, output_line, output_row, 0, make_to_ten, no_line);
				output_info(output_line, 0, "位置非法", no_line);
			}
			if (lonely)
			{
				if (keycode1 == 224 || keycode1 == 13)
					lonely = 0;
				output_info(output_line, 0, "坐标处无连续相同值", no_line);
			}
		}
		if(!no_line)
			cct_gotoxy(0, output_line * 4 + 3);
		else
			cct_gotoxy(0, output_line * 3 + 4);
		cout << "选中了" << char(i + 'A') << "行" << j << "列                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		int number = 0, is_central = 0, old_max_num = max_num;
		if (click || keycode1 == 13)
		{
			if (make_to_ten)
				except_zero(matrix_num, mark_same, i, j, output_line, output_row, number, is_central, max_num);
			else
				destory_zero(matrix_num, mark_same, output_line, output_row,no_line);
			if (!(*_9))
			{
				output_info(output_line, 0, "合成完成，左击/回车下落0", no_line);
				while (1)
				{
					cct_read_keyboard_and_mouse(Mx, My, MAction, keycode1, keycode2);
					if (MAction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13)
						break;
				}
			}
			fall_zero(matrix_num, mark_same, i, j, output_line, output_row,make_to_ten, no_line);
			if(!make_to_ten)
				panning_zero(matrix_num, mark_same, output_line, output_row, i, j, 0);
			if (!(*_9) && make_to_ten)
			{
				cct_setcolor();
				output_info(output_line, 0, "回车/左击进行新值填充..", no_line);
				while (1)
				{
					cct_read_keyboard_and_mouse(Mx, My, MAction, keycode1, keycode2);
					if (MAction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13)
						break;
				}
			}
			if (make_to_ten)
			{
				make_new_num_tuxing(matrix_num, max_num, output_line, output_row);
				print_merge(matrix_num, mark_same, output_line, output_row, 0);
				if ((max_num >= goal_point) && max_num > old_max_num)
				{
					cct_gotoxy(0, output_line * 4 + 3);
					cct_setcolor(0, 4);
					cout << "已经合成到" << max_num << "，回车/左击继续";
					cct_setcolor();
					old_max_num = max_num;
					while (1)
					{
						cct_read_keyboard_and_mouse(Mx, My, MAction, keycode1, keycode2);
						if (MAction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13)
							break;
					}
				}
				(*grade) += (number + 1) * is_central * 3;
				cct_setcolor();
				cct_gotoxy(0, 0);
				cout << "本次得分: " << (number + 1) * is_central * 3 << " 总得分: " << *grade << " 合成目标:     \b\b\b" << goal_point;
			}
			else
			{
				int count = 0;
				for(int i = 0;i <= output_line - 1;i++)
					for (int j = 0; j <= output_row - 1; j++)
					{
						if (mark_same[i][j] != 0)
							count++;
					}
				(*grade) += 5 * count * count;
				cct_setcolor();
				cct_gotoxy(0, 0);
				cout << "本次得分: " << 5 * count * count << " 总得分: " << *grade << "     \b\b\b";
			}
		}
		if (!(*_9))
		{
			output_info(output_line, 0, "合成完成,c/左击退出", no_line);
			while (1)
			{
				cct_read_keyboard_and_mouse(Mx, My, MAction, keycode1, keycode2);
				if (MAction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 67 || keycode1 == 99)
					break;
			}
		}
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
}

int judge_end(int matrix_num[][10], int line, int row)
{
	int exist_same = 0;
	int next[4][2] = { {0,1},{1,0},{0, -1},{ -1,0} };//标记移动方向
	for (int i = 0; i <= line - 1; i++)
		for (int j = 0; j <= row - 1; j++)
		{
			for (int k = 0; k <= 3; k++)
			{
				int old_i = i, old_j = j;
				i += next[k][0];
				j += next[k][1];
				if (i<0 || j<0 || i>line - 1 || j>row - 1)
					continue;
				else
				{
					if ((matrix_num[i][j] == matrix_num[old_i][old_j]) && matrix_num[i][j] != 0)
						exist_same = 1;
				}
			}
		}
	return exist_same;
}

void is_end()
{
	while (1)
	{
		cout << "\n\n本小题结束，请输入End继续...        \b\b\b\b\b\b\b\b";
		int x_location, y_location;
		cct_getxy(x_location, y_location);
		char input_end[20] = { 0 };
		cin >> input_end;
		if (_stricmp(input_end, "end") != 0)
		{
			cout << "输入错误，请重新输入";
			cct_gotoxy(x_location, y_location - 2);
		}
		else
		{
			cout << endl;
			break;
		}
	}
}