/* 2152041 ���� ��07 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include"90-b2.h"
#include"cmd_console_tools.h"
#include "lib_mto10_net_tools.h"
#include<windows.h>
using namespace std;

#define		MAX_ROW_NUM		8
#define		MAX_COL_NUM		10
void best_solve(int matrix_num[][10], int output_line, int output_row, int* best_x, int* best_y);
void print_move(int matrix_num[][10], int line, int row);
void print_auto_square(int matrix_num[][10], int line, int row, int x, int y);
void except_auto_zero(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row, int x, int y);
void fall_auto_zero(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row, int y);


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ���������������ο������������������Ĳ�����Ҳ�����Լ�ȫ���Ʒ���д
***************************************************************************/
int game_progress(mto10_net_tools& client, int _b)
{
	char svrpack[RECVBUF_LEN];	//��Ŵ�Server���յ�������
	char row;
	int col;

	while (1) {
		/* -------------------
			Client=>Server
		   ------------------- */
		   /* ���ݷ���˷����ĵ�ͼ������һ�������꣨ĿǰΪ�ֹ�������ʽ����Ҫ��Ϊ�Զ�����ѽ����꣩
			  ��ʾ�����Խ�client.get_map()�ķ���ֵ���Ƶ��ַ������У��ٻ�ԭΪ���Լ��Ķ�ά��������
		   */
		if(!_b)
			client.print_map(); //��������Ϊʾ�⣬ͼ�ν����в��ܵ��ã�Ҫ�Լ�дת������
		/* ��Ϸ�ѽ������ٶ���*/
		if (client.is_gameover())
		{
			break;
		}
		int matrix_num[8][10] = { 0 };
		int mark_same[8][10] = { 0 };
		char map_num[81];
		int best_x = 0, best_y = 0;
		int output_line = client.get_row(), output_row = client.get_col();
		strcpy(map_num, client.get_map());
		cout << "��������(A-J)��(0-9)���� : ";
		int k = 0;
		for (int i = 0; i <= output_line - 1; i++)
			for (int j = 0; j <= output_row - 1; j++)
			{
				matrix_num[i][j] = ((map_num[k] >= '0' && map_num[k] <= '9') ? map_num[k] - '0' : map_num[k] - 'A' + 10);
				k++;
			}
		best_solve(matrix_num, output_line, output_row, &best_x, &best_y);
		row = char(best_x + 'A');
		col = best_y;
		if (_b)
		{
			cout << row << " " << col << endl;
			int x, y,old_x,old_y;
			int next[4][2] = { {0,1},{1,0},{0, -1},{ -1,0} };//����ƶ�����
			cct_getxy(x, y);
			old_x = x;
			old_y = y;
			x += 4;
			y += 2;
			print_move(matrix_num, output_line, output_row);
			print_auto_square(matrix_num, output_line, output_row, x, y);
			Sleep(700);
			for (int k = 0; k <= 3; k++)
			{
				int i = best_x, j = best_y;//��¼���
				mark_same[i][j] = 1;
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
							mark_same[i][j] = 1;
						else
							break;
					}
				}
			}
			cct_setcursor(CURSOR_INVISIBLE);
			except_auto_zero(matrix_num, mark_same, row - 'A', col, output_line, output_row,old_x,old_y);
			fall_auto_zero(matrix_num, mark_same, row - 'A', col, output_line, output_row, old_y);
			cout << "�ƶ����" << endl;;
			cct_setcursor(CURSOR_VISIBLE_NORMAL);
			cct_setcolor();
		}
		client.send_coordinate(row, col);

		/* -------------------
			Server=>Client
		   ------------------- */
		   /* �ȴ�Server�˵�gameprogress */
		if (client.get_gameprogress_string(svrpack) < 0) {
			return -1;
		}

		/* ��ӡ�� svrpack �����ݣ����д�������Server�˼�������
		   ���� Content �����ݣ��������£�
			"InvalidCoordinate" : �Ƿ�����
				GameID		��������ϷID
				Step		��Ŀǰ����
				Score		��Ŀǰ����
				MaxValue	��Ŀǰ�ϳɵ����ֵ
			"MergeFailed" : ѡ���������Χ�޿ɺϳ���
				GameID		��������ϷID
				Step		��Ŀǰ����
				Score		��Ŀǰ����
				MaxValue	��Ŀǰ�ϳɵ����ֵ
			"MergeSucceeded" : ���κϳɳɹ�
				GameID		��������ϷID
				Step		��Ŀǰ����
				Score		��Ŀǰ����
				MaxValue	��Ŀǰ�ϳɵ����ֵ
				OldMap		������ѡ�������ĵ�ͼ
				NewMap		������ѡ��������ٴ����ĵ�ͼ
			"GameOver" : ��ͼ�����������Ϸ����
				GameID			��������ϷID
				FinalStep		�����ղ���
				FinalScore		�����շ���
				FinalMaxValue	�����պϳɵ����ֵ
			"GameFinished" : �Ѻϳɵ��������ޣ�16������Ϸ���
				GameID			��������ϷID
				FinalStep		�����ղ���
				FinalScore		�����շ���
				FinalMaxValue	�����պϳɵ����ֵ */

				/* ��ӡ�յ���ԭʼ�ַ��� */
		cout << "ServerӦ�� : " << endl << svrpack << endl;
	}//end of while(1)
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int network(int _b)
{
	const char* my_no = "2152041";		//����ѧ��
	const char* my_pwd = "10yue26ri.";	//��������

	int wanted_row, wanted_col, wanted_id, wanted_delay;

#if 1 //�������룬�˴���Ϊ #if 0 ���ʾ�������� #else �е����
	wanted_row = 5;			//�˴������޸�Ϊ�����������ʽ
	wanted_col = 5;			//�˴������޸�Ϊ�����������ʽ
	wanted_id = -1;		//idΪ�����������Ϸ��ţ������-1����ʾ���������������[0..2^31-1]���ʾ��̶���ţ���Ź̶�����ÿ�θ����ĳ�ʼ���󼰺���������ͬ��������ԣ�
	wanted_delay = 60 * 1000;	//delayΪ�����ÿ��Ӧ����ʱ�ӣ���λms
#else
	wanted_row = -1;
	wanted_col = -1;
	wanted_id = -1;
	wanted_delay = -1;
#endif
	mto10_net_tools client;

	/* ��client������е�debug���أ�����ʱ�ɴ򿪣���ͼ�ν���ʱ��رգ� */
	if(!_b)
		client.set_debug_switch(true);
	else
		client.set_debug_switch(false);

	/* ���ӷ����� */
	if (client.connect() < 0) {
		/* ����ʧ����Ϣ����û��debug_switch����ӡ */
		cout << "���ӷ�����ʧ��!" << endl;
		return -1;
	}

	/* ��Server�˷�����֤��Ϣ������ */
	if (client.send_parameter(my_no, '*', my_pwd, wanted_row, wanted_col, wanted_id, wanted_delay) < 0) {
		cout << "������֤��������Ϣʧ��!" << endl;
		return -1;
	}

	/* �ȴ�Server���·���������Ϸ��ʼ��*/
	if (client.wait_for_game_start() < 0) {
		cout << "�ȴ�GameStartʧ��!" << endl;
		return -1;
	}

	/* ��ӡ�ӷ������յ��Ĳ�����������Ϸ�Դ˲���Ϊ׼����������6��6�У�����8��10�У��򱾴���Ϸ��8��10��Ϊ׼��
	   �����ӡ����Ϣ��ͼ�λ������������ȥ�� */
	cout << "������������Ϣ : " << endl;
	cout << "  ���� : " << client.get_row() << endl;
	cout << "  ���� : " << client.get_col() << endl;
	cout << "  ID�� : " << client.get_gameid() << endl;
	cout << "  ��ʱ : " << client.get_delay() / 1000.0 << "(��)" << endl;
	cout << "  ��ͼ : " << client.get_map() << endl;
	/* ��ͼ���е�ֵΪ1-9��A-F���ֱ��ʾ1-15��ֵ��
		   ���磺
			 ������������=3
			 ������������=4
			 ���������ص�ͼ=123A85CF2123
		   ���ʾ��ǰ��ͼΪ(����������ʾ��)
			 1 2 3  10
			 8 5 12 15
			 2 1 2  3
			��Ϸ����������Ϊ���ϳɵ�16�����κοɺϳ�Ԫ�� */

			/* ������Ϸ��������
			   1���յ�Server��GameOver�򷵻�0����Ϸ����
			   2���������������-1��������Ϣ����ȷ�ȴ��󣩣��������ٴ��ظ�	*/

	if (game_progress(client, _b) < 0) {
		client.close();
		return -1;
	}

	client.close();
	cout << "��Ϸ����" << endl;

	return 0;
}

void best_solve(int matrix_num[][10], int output_line, int output_row, int* best_x, int* best_y)
{
	int grade = 0, old_grade = grade;
	int mark_same[8][10];
	for (int p = 0; p <= output_line - 1; p++)
		for (int q = 0; q <= output_row - 1; q++)
		{
			int store[80][2] = { 0 };//����������
			int next[4][2] = { {0,1},{1,0},{0, -1},{ -1,0} };//����ƶ�����
			mark_same[p][1] = 1;
			store[0][0] = p;
			store[0][1] = q;
			int start = 0, end = 1;
			while (start < end)
			{
				for (int k = 0; k <= 3; k++)
				{
					int i = store[start][0], j = store[start][1];//��¼���
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
			if (end != 1)
			{
				int k = 0;
				for (int i = 0; i <= 7; i++)
					for (int j = 0; j <= 9; j++)
						if (mark_same[i][j] == 1)
							k++;
				grade = k * matrix_num[p][q] * 3;
				if (grade > old_grade)
				{
					old_grade = grade;
					(*best_x) = p;
					(*best_y) = q;
				}
			}
			for (int i = 0; i <= output_line - 1; i++)
				for (int j = 0; j <= output_row - 1; j++)
					mark_same[i][j] = 0;
			start = 0;
			end = 1;
		}
}

void print_auto_square(int matrix_num[][10], int line, int row, int x, int y)
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
			cout << "������";
			cct_gotoxy(x, y + 1);
			cout << "��" << matrix_num[i][j] << " ��";
			cct_gotoxy(x, y + 2);
			cout << "������";
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

void fall_auto_zero(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row,int y)
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
	{
		for (int i = output_line - 2; i >= 0; i--)
		{
			int y_location = 2 + i * 4 + y;
			if (count[i][j] != 0)
			{
				for (; y_location <= 1 + y + (i + count[i][j]) * 4; y_location++)
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
					cout << "������";
					cct_gotoxy(4 + j * 8, y_location + 2);
					cout << "��" << matrix_num[i][j] << " ��";
					cct_gotoxy(4 + j * 8, y_location + 3);
					cout << "������";
					cct_setcolor();
					Sleep(5);
					if ((y_location - y - 2) % 4 == 0)
					{
						cct_setcolor(15, 0);
						cct_gotoxy(4 + j * 8, y_location - 1);
						cout << "������";
						cct_setcolor();
					}
				}
			}
			if ((y_location - y - 2) % 4 == 0)
			{
				cct_setcolor(15, 0);
				cct_gotoxy(4 + j * 8, y_location - 1);
				cout << "������";
				cct_setcolor();
			}
		}
	}
	cct_gotoxy(0, y + 2+output_line * 4);
}

void except_auto_zero(int matrix_num[][10], int mark_same[][10],int line, int row, int output_line, int output_row,int x,int y)
{

	for (int i = 0; i <= output_line - 1; i++)
		for (int j = 0; j <= output_row - 1; j++)
		{
			if (mark_same[i][j] == 1 && (i != line || j != row))
			{
				cct_setcolor(15, 15);
				cct_gotoxy(4 + x + j * 8, 2 + y + i * 4);
				cout << "      ";
				cct_gotoxy(4 + x + j * 8, 3 + y + i * 4);
				cout << "      ";
				cct_gotoxy(4 + x + j * 8, 4 + y + i * 4);
				cout << "      ";
				cct_setcolor();
				matrix_num[i][j] = 0;
			}
			if (i == line && j == row)
			{
				matrix_num[i][j]++;
				cct_setcolor(matrix_num[i][j], 0);
				cct_gotoxy(4 + x + j * 8, 2 + y + i * 4);
				cout << "������";
				cct_gotoxy(4 + x + j * 8, 3 + y + i * 4);
				cout << "��" << matrix_num[i][j]<<setw(3)<< "��";
				cct_gotoxy(4 + x + j * 8, 4 + y + i * 4);
				cout << "������";
				cct_setcolor();
			}
		}
}

void print_move(int matrix_num[][10], int line, int row)
{
	int m = 0;
	int x_location, y_location;
	cout << "      ";
	for (int i = 0; i <= row - 1; i++)
		cout << i << "       ";
	cout << " " << endl << "  ";
	cct_setcolor(15, 0);
	cout << "��";
	for (int j = 1; j <= row * 4 - 1; j++)
	{
		if (j == row * 4 - 1)
			cout << "����";
		else if (j % 4 == 0)
			cout << "��";
		else
			cout << "��";
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
			cout << "��";
			for (int j = 1; j <= row; j++)
				cout << "      ��";
			cct_setcolor();
			cout << endl;
		}
		else if (i % 4 == 2)
		{
			cout << char(m + 'A') << " ";
			m++;
			cct_setcolor(15, 0);
			cout << "��";
			for (int j = 1; j <= row; j++)
				cout << "      ��";
			cct_setcolor();
			cout << endl;
		}
		else if (i % 4 == 0)
		{
			cout << "  ";
			cct_setcolor(15, 0);
			cout << "��";
			for (int j = 1; j <= row * 4 - 1; j++)
			{
				if (j == row * 4 - 1)
					cout << "����";
				else if (j % 4 == 0)
					cout << "��";
				else
					cout << "��";
			}
			cct_setcolor();
			cout << endl;
		}
		else;
	}
	cout << "  ";
	cct_setcolor(15, 0);
	cout << "��";
	for (int j = 1; j <= row * 4 - 1; j++)
	{
		if (j == row * 4 - 1)
			cout << "����";
		else if (j % 4 == 0)
			cout << "��";
		else
			cout << "��";
	}
	cct_setcolor();
	cout << endl;
}

