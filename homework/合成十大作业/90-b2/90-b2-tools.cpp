/* 2152041 ���� ��07 */
#include<iostream>
#include"cmd_console_tools.h"
#include<time.h>
#include<conio.h>
#include"90-b2.h"
using namespace std;

void input_ranks(int* line, int* row, int _3, int* goal_point)
{
	while (1)
	{
		(*line) = 0;
		cout << "����������(5-8)��" << endl;
		cin >> (*line);
		if (*line >= 5 && *line <= 8)
			break;
	}
	while (1)
	{
		(*row) = 0;
		cout << "����������(5-10)��" << endl;
		cin >> (*row);
		if (*row >= 5 && *row <= 10)
			break;
	}
	if (_3)
	{
		while (1)
		{
			cout << "������ϳ�Ŀ��(5-20)��" << endl;
			cin >> (*goal_point);
			if (*goal_point >= 5 && *goal_point <= 20)
				break;
		}
	}
}

void output_matrix(int line, int row, int matrix_num[][10])
{
	int i = 0, j = 0;
	cout << "��ǰ���飺\n";
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
	cout << "\n���ҽ�����飺" << endl;
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
	cout << "\n��ǰ����(��ͬɫ��ʶ)��\n";
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

void input_location(char* line, int* row, int output_line, int output_row)
{
	char* old_line = line;
	char same_row, old_same_row = char(*row + '0');
	int* old_row = row;
	while (1)
	{
		line = old_line;
		same_row = old_same_row;
		cout << "\n������ĸ+������ʽ[����c2]����������꣺    \b\b\b\b";
		int x_location, y_location;
		cct_getxy(x_location, y_location);
		cin >> *line >> same_row;
		(*row) = same_row - '0';
		if ((*line) < 'A' || ((*line > output_line + 64) && (*line < 'a')) || *line > output_line + 96 || *row<0 || *row>output_row - 1)
		{
			cout << "\n�����������������.";
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
	cout << "\n����Ϊ" << *line << "��" << *row << "��\n\n";
}

void down_zero(int matrix_num[][10], int mark_same[][10], int output_line, int output_row, int line, int row)
{
	cout << "\n���س����������������0����...";
	while (_getch() != '\r');
	cout << "\n��0�������(��ͬɫ��ʶ)��\n";
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
	cout << "\n���س���������ֵ���...";
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
					/*�����������ʣ���Ϊ���ifִ�������Ĳ�ִ��,���Դ�ʱ����85%���������ܵ�10%���ʣ������������ʼ����*/
					else if (rand() % 17 == 0 || rand() % 17 == 1)
						matrix_num[i][j] = 5;
					else
						matrix_num[i][j] = rand() % 3 + 1;
				}
				else if (max_num == 6)
				{
					if (rand() % 20 == 0)
						matrix_num[i][j] = 6;
					/*������������*/
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

int judge_end(int matrix_num[][10], int line, int row)
{
	int exist_same = 0;
	int next[4][2] = { {0,1},{1,0},{0, -1},{ -1,0} };//����ƶ�����
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
					if (matrix_num[i][j] == matrix_num[old_i][old_j])
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
		cout << "\n\n��С�������������End����...        \b\b\b\b\b\b\b\b";
		int x_location, y_location;
		cct_getxy(x_location, y_location);
		char input_end[20] = { 0 };
		cin >> input_end;
		if (_stricmp(input_end, "end") != 0)
		{
			cout << "�����������������";
			cct_gotoxy(x_location, y_location - 2);
		}
		else
		{
			cout << endl;
			break;
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
					/*�����������ʣ���Ϊ���ifִ�������Ĳ�ִ��,���Դ�ʱ����85%���������ܵ�10%���ʣ������������ʼ����*/
					else if (rand() % 17 == 0 || rand() % 17 == 1)
						matrix_num[i][j] = 5;
					else
						matrix_num[i][j] = rand() % 3 + 1;
				}
				else if (max_num == 6)
				{
					if (rand() % 20 == 0)
						matrix_num[i][j] = 6;
					/*������������*/
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
