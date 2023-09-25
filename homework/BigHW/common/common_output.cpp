/* 计科 2152041 王浩 */
#include<iostream>
#include "../include/cmd_console_tools.h"
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include"../90-01-b2/90-01-b2.h"
using namespace std;

void output_matrix(int line, int row, int matrix_num[][10])
{
	int i = 0, j = 0;
	cout << "当前数组：\n";
	cout << "\n  |  ";
	for (; i <= row - 1; i++)
		cout << i << "  ";
	cout << "\n--+--";
	for (i = 0; i <= row - 1; i++)
	{
		if (i == row - 1)
			cout << "--";
		else
			cout << "---";
	}
	cout << endl;
	i = 0;
	j = 0;
	for (; j <= line - 1; j++)
	{
		cout << char(j + 65) << " |  ";
		for (i = 0; i <= row - 1; i++)
			cout << matrix_num[j][i] << "  ";
		cout << endl;
	}
}

void output_mark_same(int matrix_num[][10], int mark_same[][10], int output_line, int output_row)
{
	cout << "\n查找结果数组：" << endl;
	cout << "\n  |  ";
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
			cout << mark_same[i][j] << "  ";
		cout << endl;
	}
	cout << "\n当前数组(不同色标识)：\n";
	cout << "\n  |  ";
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

void output_newnum(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int line, int row, int goal_point, int display)
{
	cout << "\n  |  ";
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
			if (mark_same[i][j] == 1 && (display == 1 ? 1 : (i != line || j != row)))
				cct_setcolor(14, 0);
			cout << matrix_num[i][j];
			cct_setcolor();
			cout << "  ";
		}
		cout << endl;
	}
}

void print_square(int matrix_num[][10], int line, int row, int x, int y, int make_to_ten = 1)
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
			if (make_to_ten)
				cout << "┏━┓";
			else
				cout << "╔═╗";
			cct_gotoxy(x, y + 1);
			if(make_to_ten)
				cout << "┃" << matrix_num[i][j] << " ┃";
			else
				cout << "║" << "★" << "║";
			cct_gotoxy(x, y + 2);
			if (make_to_ten)
				cout << "┗━┛";
			else
				cout << "╚═╝";
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

void print_shell(int matrix_num[][10], int line, int row, int make_to_ten = 1) {
	int m = 0;
	int x_location, y_location;
	cout << "      ";
	for (int i = 0; i <= row - 1; i++)
		cout << i << "     ";
	cout << "\n  ";
	cct_setcolor(15, 0);
	if (make_to_ten)
	{
		cout << "┏━";
		for (int i = 0; i <= row - 2; i++)
			cout << "━━━";
		cout << "━━┓";
	}
	else
	{
		cout << "╔═";
		for (int i = 0; i <= row - 2; i++)
			cout << "═══";
		cout << "══╗";
	}
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
			if(make_to_ten)
				cout << "┃";
			else
				cout << "║";
			for (int j = 0; j <= row - 1; j++)
			{
				Sleep(10);
				cout << "      ";
			}
			if (make_to_ten)
				cout << "┃";
			else
				cout << "║";
			cct_setcolor();
			cout << " ";
		}
		else if (i % 3 == 2)
		{
			cct_setcolor();
			cout << char(m + 'A') << " ";
			m++;
			cct_setcolor(15, 0);
			if (make_to_ten)
				cout << "┃";
			else
				cout << "║";
			for (int j = 0; j <= row - 1; j++)
			{
				Sleep(10);
				cout << "      ";
			}
			if (make_to_ten)
				cout << "┃";
			else
				cout << "║";
			cct_setcolor();
			cout << " ";
		}
		else;
	}
	cout << "  ";
	cct_setcolor(15, 0);
	if (make_to_ten)
	{
		cout << "┗━";
		for (int i = 0; i <= row - 2; i++)
			cout << "━━━";
		cout << "━━┛";
	}
	else
	{
		cout << "╚═";
		for (int i = 0; i <= row - 2; i++)
			cout << "═══";
		cout << "══╝";
	}
	cct_setcolor();
	cout << endl;
	print_square(matrix_num, line, row, x_location, y_location,make_to_ten);
};

void print_new_square(int matrix_num[][10], int line, int row, int x, int y,int make_to_ten=1)
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
			if (make_to_ten)
				cout << "┏━┓";
			else
				cout << "╔═╗";
			cct_gotoxy(x, y + 1);
			if(make_to_ten)
				cout << "┃" << matrix_num[i][j] << " ┃";
			else
				cout << "║" << "★" << "║";
			cct_gotoxy(x, y + 2);
			if (make_to_ten)
				cout << "┗━┛";
			else
				cout << "╚═╝";
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

void print_new_shell(int matrix_num[][10], int line, int row,int make_to_ten = 1)
{
	int m = 0;
	int x_location, y_location;
	cout << "      ";
	for (int i = 0; i <= row - 1; i++)
		cout << i << "       ";
	cout << " ";
	cct_setcolor(15, 0);
	if(make_to_ten)
		cout << "┏";
	else
		cout << "╔";
	for (int j = 1; j <= row * 4 - 1; j++)
	{
		if (make_to_ten)
		{
			if (j == row * 4 - 1)
				cout << "━┓";
			else if (j % 4 == 0)
				cout << "┳";
			else
				cout << "━";
		}
		else
		{
			if (j == row * 4 - 1)
				cout << "═╗";
			else if (j % 4 == 0)
				cout << "╦";		
			else
				cout << "═";
		}
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
			if(make_to_ten)
				cout << "┃";
			else
				cout << "║";
			for (int j = 1; j <= row; j++)
			{
				Sleep(10);
				if(make_to_ten)
					cout << "      ┃";
				else
					cout << "      ║";
			}
			cct_setcolor();
			cout << endl;
		}
		else if (i % 4 == 2)
		{
			cout << char(m + 'A') << " ";
			m++;
			cct_setcolor(15, 0);
			if (make_to_ten)
				cout << "┃";
			else
				cout << "║";
			for (int j = 1; j <= row; j++)
			{
				Sleep(10);
				if (make_to_ten)
					cout << "      ┃";
				else
					cout << "      ║";
			}
			cct_setcolor();
			cout << endl;
		}
		else if (i % 4 == 0)
		{
			cout << "  ";
			cct_setcolor(15, 0);
			if (make_to_ten)
			{
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
			}
			else
			{
				cout << "╠";
				for (int j = 1; j <= row * 4 - 1; j++)
				{
					
					if (j == row * 4 - 1)
						cout << "═╣";
					else if (j % 4 == 0)
						cout << "╬";
					else
						cout << "═";
				}
			}
			cct_setcolor();
			cout << endl;
		}
		else;
	}
	cout << "  ";
	cct_setcolor(15, 0);
	if (make_to_ten)
	{
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
	}
	else
	{
		cout << "╚";
		for (int j = 1; j <= row * 4 - 1; j++)
		{
			if (j == row * 4 - 1)
				cout << "═╝";
			else if (j % 4 == 0)
				cout << "╩";
			else
				cout << "═";
		}
	}
	cct_setcolor();
	cout << endl;
	print_new_square(matrix_num, line, row, x_location, y_location,make_to_ten);
}

void output_info(int line,int direction,const char* str,int no_line)
{
	if (direction == 1)
		cct_gotoxy(0, 0);
	else
	{
		if(no_line)
			cct_gotoxy(0, line * 3 + 4);
		else
			cct_gotoxy(0, line * 4 + 3);
	}
	cct_setcursor(CURSOR_INVISIBLE);
	cout << str<<"                       \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
}