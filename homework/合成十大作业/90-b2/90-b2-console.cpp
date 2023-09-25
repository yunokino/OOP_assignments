/* 2152041 王浩 信07 */
#include<iostream>
#include"cmd_console_tools.h"
#include"90-b2.h"
#include<conio.h>
#include<Windows.h>
using namespace std;

void print_square(int matrix_num[][10], int line, int row, int x, int y)
{
	int old_x = x, old_y = y;
	int i = 0, j = 0;
	for (int m = 0; m <= line - 1; m++)
	{
		x = old_x;
		y = old_y;
		for (int n = 0; n <= row - 1; n++)
		{
			cct_gotoxy(x, y);
			cct_setcolor(matrix_num[i][j], 0);
			cout << "┏━┓";
			cct_gotoxy(x, y + 1);
			cout << "┃" << matrix_num[i][j] << " ┃";
			cct_gotoxy(x, y + 2);
			cout << "┗━┛";
			cct_setcolor();
			y = old_y;
			x += 6;
			j++;
		}
		old_y += 3;
		i++;
		j = 0;
	}
	cout << endl;
}

void print_new_square(int matrix_num[][10], int line, int row, int x, int y)
{
	int old_x = x, old_y = y;
	int i = 0, j = 0;
	for (int m = 0; m <= line - 1; m++)
	{
		x = old_x;
		y = old_y;
		for (int n = 0; n <= row - 1; n++)
		{
			cct_gotoxy(x, y);
			cct_setcolor(matrix_num[i][j], 0);
			cout << "┏━┓";
			cct_gotoxy(x, y + 1);
			cout << "┃" << matrix_num[i][j] << " ┃";
			cct_gotoxy(x, y + 2);
			cout << "┗━┛";
			cct_setcolor();
			y = old_y;
			x += 8;
			j++;
		}
		old_y += 4;
		i++;
		j = 0;
	}
	cout << endl;
}

void print_shell(int matrix_num[][10], int line, int row)
{
	int m = 0;
	int x_location, y_location;
	cout << "      ";
	for (int i = 0; i <= row - 1; i++)
		cout << i << "     ";
	cout << "\n  ";
	cct_setcolor(15, 0);
	cout << "┏━";
	for (int i = 0; i <= row - 2; i++)
		cout << "━━━";
	cout << "━━┓";
	cct_setcolor();
	cout << endl;
	cct_getxy(x_location, y_location);
	x_location += 4;
	for (int i = 1; i <= line * 3; i++)
	{
		if (i % 3 == 1 || i % 3 == 0)
		{
			cct_setcolor();
			cout << "  ";
			cct_setcolor(15, 0);
			cout << "┃";
			for (int j = 0; j <= row - 1; j++)
			{
				Sleep(10);
				cout << "      ";
			}
			cout << "┃";
			cct_setcolor();
			cout << " ";
		}
		else if (i % 3 == 2)
		{
			cct_setcolor();
			cout << char(m + 'A') << " ";
			m++;
			cct_setcolor(15, 0);
			cout << "┃";
			for (int j = 0; j <= row - 1; j++)
			{
				Sleep(10);
				cout << "      ";
			}
			cout << "┃";
			cct_setcolor();
			cout << " ";
		}
		else;
	}
	cout << "  ";
	cct_setcolor(15, 0);
	cout << "┗━";
	for (int i = 0; i <= row - 2; i++)
		cout << "━━━";
	cout << "━━┛";
	cct_setcolor();
	cout << endl;
	print_square(matrix_num, line, row, x_location, y_location);
}

void print_new_shell(int matrix_num[][10], int line, int row)
{
	int m = 0;
	int x_location, y_location;
	cout << "      ";
	for (int i = 0; i <= row - 1; i++)
		cout << i << "       ";
	cout << " ";
	cct_setcolor(15, 0);
	cout << "┏";
	for (int j = 1; j <= row * 4 - 1; j++)
	{
		if (j == row * 4 - 1)
			cout << "━┓";
		else if (j % 4 == 0)
			cout << "┳";
		else
			cout << "━";
	}
	cct_setcolor();
	cout << endl;
	cct_getxy(x_location, y_location);
	x_location += 4;
	for (int i = 1; i <= line * 4 - 1; i++)
	{
		if (i % 4 == 1 || i % 4 == 3)
		{
			cout << "  ";
			cct_setcolor(15, 0);
			cout << "┃";
			for (int j = 1; j <= row; j++)
			{
				Sleep(10);
				cout << "      ┃";
			}
			cct_setcolor();
			cout << endl;
		}
		else if (i % 4 == 2)
		{
			cout << char(m + 'A') << " ";
			m++;
			cct_setcolor(15, 0);
			cout << "┃";
			for (int j = 1; j <= row; j++)
			{
				Sleep(10);
				cout << "      ┃";
			}
			cct_setcolor();
			cout << endl;
		}
		else if (i % 4 == 0)
		{
			cout << "  ";
			cct_setcolor(15, 0);
			cout << "┣";
			for (int j = 1; j <= row * 4 - 1; j++)
			{
				if (j == row * 4 - 1)
					cout << "━┫";
				else if (j % 4 == 0)
					cout << "╋";
				else
					cout << "━";
			}
			cct_setcolor();
			cout << endl;
		}
		else;
	}
	cout << "  ";
	cct_setcolor(15, 0);
	cout << "┗";
	for (int j = 1; j <= row * 4 - 1; j++)
	{
		if (j == row * 4 - 1)
			cout << "━┛";
		else if (j % 4 == 0)
			cout << "┻";
		else
			cout << "━";
	}
	cct_setcolor();
	cout << endl;
	print_new_square(matrix_num, line, row, x_location, y_location);
}

void choose_num(int matrix_num[][10], int line, int row)
{
	cct_setcursor(CURSOR_INVISIBLE);
	int Mx = 0, My = 0, MAction, keycode1, keycode2;
	int i = 0, j = 0;
	int old_i = 0, old_j = 0;
	bool first_time = 1;
	cct_gotoxy(4, 3);
	cct_setcolor(matrix_num[0][0], 15);
	cout << "┏━┓";
	cct_gotoxy(4, 4);
	cout << "┃" << matrix_num[0][0] << " ┃";
	cct_gotoxy(4, 5);
	cout << "┗━┛";
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
		keycode1 == 224 ? cout << "键盘] " : cout << "鼠标] ";
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
			cout << "┏━┓";
			cct_gotoxy(4, 4);
			cout << "┃" << matrix_num[0][0] << " ┃";
			cct_gotoxy(4, 5);
			cout << "┗━┛";
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
			cout << "┏━┓";
			cct_gotoxy(4 + old_j * 8, 4 + old_i * 4);
			cout << "┃" << matrix_num[old_i][old_j] << " ┃";
			cct_gotoxy(4 + old_j * 8, 5 + old_i * 4);
			cout << "┗━┛";
			cct_gotoxy(4 + j * 8, 3 + i * 4);
			cct_setcolor(matrix_num[i][j], 15);
			cout << "┏━┓";
			cct_gotoxy(4 + j * 8, 4 + i * 4);
			cout << "┃" << matrix_num[i][j] << " ┃";
			cct_gotoxy(4 + j * 8, 5 + i * 4);
			cout << "┗━┛";
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
				cout << "┏━┓";
				cct_gotoxy(4 + old_j * 8, 4 + old_i * 4);
				cout << "┃" << matrix_num[old_i][old_j] << " ┃";
				cct_gotoxy(4 + old_j * 8, 5 + old_i * 4);
				cout << "┗━┛";
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

void print_merge(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int old)
{
	if (old)
	{
		for (int i = 0; i <= output_line - 1; i++)
			for (int j = 0; j <= output_row - 1; j++)
			{
				if (mark_same[i][j] == 1)
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
			}
	}
	else
	{
		for (int i = 0; i <= output_line - 1; i++)
			for (int j = 0; j <= output_row - 1; j++)
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

void fall_zero(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row)
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
					cout << "┏━┓";
					cct_gotoxy(4 + j * 8, y_location + 2);
					cout << "┃" << matrix_num[i][j] << " ┃";
					cct_gotoxy(4 + j * 8, y_location + 3);
					cout << "┗━┛";
					cct_setcolor();
					Sleep(5);
					if ((y_location + 2) % 4 == 0)
					{
						cct_gotoxy(4 + j * 8, y_location);
						cct_setcolor(15, 0);
						cout << "━━━";
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

void plus_num(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int &max_num, int goal_point, int* grade, int* _9)
{
	cct_setcursor(CURSOR_INVISIBLE);
	int Mx = 0, My = 0, MAction, keycode1, keycode2;
	int i = 0, j = 0;
	int old_i = 0, old_j = 0;
	bool first_time = 1;
	bool lonely = 0;
	bool click = 0;
	bool enter = 0;
	cct_gotoxy(4, 3);
	cct_setcolor(matrix_num[0][0], 15);
	cout << "┏━┓";
	cct_gotoxy(4, 4);
	cout << "┃" << matrix_num[0][0] << " ┃";
	cct_gotoxy(4, 5);
	cout << "┗━┛";
	cct_setcolor();
	cct_gotoxy(0, output_line * 4 + 3);
	cout << "鼠标/方向键移动，左击/回车选择";
	if (*_9)
		cout << "，q退出";
	while (1)
	{
		cct_read_keyboard_and_mouse(Mx, My, MAction, keycode1, keycode2);
		if ((*_9)&&(keycode1 == 81 || keycode1 == 113))
		{
			(*_9) = keycode1;
			break;
		}
		if (keycode1 != 13)
			enter = 0;
		cct_gotoxy(0, output_line * 4 + 3);
		if (!lonely)
		{
			cout << "[当前";
			(keycode1 == 224 || keycode1 == 13) ? cout << "键盘] " : cout << "鼠标] ";
		}
		if (keycode1 != 224 && keycode1 != 13)
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
			print_merge(matrix_num, mark_same, output_line, output_row, 0);
		}
		for (int m = 0; m <= 7; m++)
			for (int n = 0; n <= 9; n++)
				mark_same[m][n] = 0;
		bool in_square = (Mx >= 4 + j * 8 && Mx <= 10 + j * 8 && My >= 3 + i * 4 && My <= 5 + i * 4 && i <= output_line - 1 && j <= output_row - 1);
		if (first_time && in_square)
		{
			cct_gotoxy(4, 3);
			cct_setcolor(matrix_num[0][0], 0);
			cout << "┏━┓";
			cct_gotoxy(4, 4);
			cout << "┃" << matrix_num[0][0] << " ┃";
			cct_gotoxy(4, 5);
			cout << "┗━┛";
			cct_setcolor();
			old_i = i;
			old_j = j;
			first_time = 0;
		}
		if ((in_square) || (keycode1 == 224) || keycode1 == 13)
		{
			cct_gotoxy(11, output_line * 4 + 3);
			if (!lonely)
				cout << char(i + 'A') << "行" << j << "列                     \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
			cct_gotoxy(4 + old_j * 8, 3 + old_i * 4);
			cct_setcolor(matrix_num[old_i][old_j], 0);
			cout << "┏━┓";
			cct_gotoxy(4 + old_j * 8, 4 + old_i * 4);
			cout << "┃" << matrix_num[old_i][old_j] << " ┃";
			cct_gotoxy(4 + old_j * 8, 5 + old_i * 4);
			cout << "┗━┛";
			cct_gotoxy(4 + j * 8, 3 + i * 4);
			cct_setcolor(matrix_num[i][j], 15);
			cout << "┏━┓";
			cct_gotoxy(4 + j * 8, 4 + i * 4);
			cout << "┃" << matrix_num[i][j] << " ┃";
			cct_gotoxy(4 + j * 8, 5 + i * 4);
			cout << "┗━┛";
			cct_setcolor();
			old_i = i;
			old_j = j;
			if (MAction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13)
			{
				int store[80][2] = { 0 };//储存标记坐标
				int next[4][2] = { {0,1},{1,0},{0, -1},{ -1,0} };//标记移动方向
				mark_same[i][j] = 1;
				store[0][0] = i;
				store[0][1] = j;
				int start = 0, end = 1;
				while (start < end)
				{
					for (int k = 0; k <= 3; k++)
					{
						int m = store[start][0], n = store[start][1];//记录起点
						while (1)
						{
							int old_m = m, old_n = n;
							m += next[k][0];
							n += next[k][1];
							if (m<0 || n<0 || m>output_line - 1 || j>output_row - 1)
								break;
							else
							{
								if (matrix_num[m][n] == matrix_num[old_m][old_n])
								{
									if (!mark_same[m][n])
									{
										store[end][0] = m;
										store[end][1] = n;
										end++;
									}
									mark_same[m][n] = 1;
								}
								else
									break;
							}
						}
					}
					start++;
				}
				if (end == 1)
					lonely = 1;
				else
				{
					lonely = 0;
					print_merge(matrix_num, mark_same, output_line, output_row);
					cct_gotoxy(0, output_line * 4 + 3);
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
			print_merge(matrix_num, mark_same, output_line, output_row, 0);
			cct_gotoxy(0, output_line * 4 + 3);
			cout << "位置非法                             \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
		}
		if (lonely)
		{
			if(keycode1==224||keycode1==13)
				lonely = 0;
			cct_gotoxy(0, output_line * 4 + 3);
			cout << "坐标处无连续相同值";
		}
	}
	cct_gotoxy(0, output_line * 4 + 3);
	cout << "选中了" << char(i + 'A') << "行" << j << "列                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	int number = 0, is_central = 0, old_max_num = max_num;
	if (click || keycode1 == 13)
	{
		except_zero(matrix_num, mark_same, i, j, output_line, output_row, number, is_central, max_num);
		cct_gotoxy(0, output_line * 4 + 3);
		if (!(*_9))
		{
			cout << "合成完成，左击/回车下落0";
			while (1)
			{
				cct_read_keyboard_and_mouse(Mx, My, MAction, keycode1, keycode2);
				if (MAction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13)
					break;
			}
		}
		fall_zero(matrix_num, mark_same, i, j, output_line, output_row);
		if (!(*_9))
		{
			cct_setcolor();
			cct_gotoxy(0, output_line * 4 + 3);
			cout << "回车/左击进行新值填充...     \b\b\b\b\b";
			while (1)
			{
				cct_read_keyboard_and_mouse(Mx, My, MAction, keycode1, keycode2);
				if (MAction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13)
					break;
			}
		}
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
	}
	(*grade) += (number+1) * is_central * 3;
	cct_gotoxy(0, 0);
	cout << "本次得分: " << (number + 1) * is_central * 3 << " 总得分: " << *grade << " 合成目标:     \b\b\b" << goal_point;
	cct_gotoxy(0, output_line * 4 + 3);
	if (!(*_9))
	{
		cout << "合成完成,c/左击退出";
		while (1)
		{
			cct_read_keyboard_and_mouse(Mx, My, MAction, keycode1, keycode2);
			if (MAction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 67||keycode1==99)
				break;
		}
	}
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}