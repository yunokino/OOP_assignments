/* 2152041 ���� �ƿ� */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<conio.h>
#include<ctime>
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
using namespace std;

int main()
{
	int max_grade = 0;
	int loop = 1;
	char temp[256];
	CONSOLE_GRAPHICS_INFO pG2048_CGI;
	while (loop)
	{
		cct_cls();
		int row, col, goal_point, delay;
		int matrix_num[8][10] = { 0 };
		srand((unsigned int)(time(NULL)));
		int i, j;
		const char* gname = "2048";
		const BLOCK_DISPLAY_INFO bdi_normal[] = {
			{BDI_VALUE_BLANK, -1, -1, NULL},  //0����ʾ���ÿո���伴��
			{2, COLOR_HYELLOW, COLOR_BLACK, NULL},
			{4, COLOR_HRED, COLOR_BLACK, NULL},
			{8, COLOR_GREEN, COLOR_BLACK, NULL},
			{16, COLOR_RED, COLOR_BLACK, NULL},
			{32, COLOR_HGREEN, COLOR_BLACK, NULL},
			{64, COLOR_HYELLOW, COLOR_BLACK, NULL},
			{128, COLOR_HRED, COLOR_BLACK, NULL},
			{256, COLOR_HWHITE, COLOR_BLACK, NULL},
			{512, COLOR_HBLACK, COLOR_BLACK, NULL},
			{1024, COLOR_HPINK, COLOR_BLACK, NULL},
			{2048, COLOR_WHITE, COLOR_BLACK, NULL},
			{4096, COLOR_YELLOW, COLOR_BLACK, NULL},
			{8192, COLOR_PINK, COLOR_BLACK, NULL},
			{16384, COLOR_HBLUE, COLOR_BLACK, NULL},
			{32768, COLOR_HCYAN, COLOR_BLACK, NULL},
			{65536, COLOR_HGREEN, COLOR_BLACK, NULL},
			{131072, COLOR_HPINK, COLOR_BLACK, NULL},
			{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
		};

		int grade = 0;
		gmw_init(&pG2048_CGI);
		cout << "2048��������," << endl;
		cout << "����������[4-8]:";
		cin >> row;
		cout << "����������[4-10]:";
		cin >> col;
		if (row + col <= 14)
			cout << "������Ŀ�����(" << bdi_normal[row + col].value << "/" << bdi_normal[row + col + 1].value << "/" << bdi_normal[row + col + 2].value << "/" << bdi_normal[row + col + 3].value << ")"; \
		else
			cout << "������Ŀ�����(" << bdi_normal[14].value << "/" << bdi_normal[15].value << "/" << bdi_normal[16].value << "/" << bdi_normal[17].value << ")";
		cin >> goal_point;
		cout << "�����붯����ʱ(0-5):";
		cin >> delay;
		delay = 10 + delay * 20;
		cct_setcursor(CURSOR_INVISIBLE);
		gmw_set_color(&pG2048_CGI, COLOR_BLACK, COLOR_WHITE);
		gmw_set_font(&pG2048_CGI, "Terminal", 16, 8);
		gmw_set_frame_style(&pG2048_CGI, 10, 5, true);
		gmw_set_frame_color(&pG2048_CGI, COLOR_WHITE, COLOR_BLACK);
		gmw_set_block_border_switch(&pG2048_CGI, true);
		gmw_set_delay(&pG2048_CGI, BLOCK_MOVED_DELAY_MS, delay);
		gmw_set_rowno_switch(&pG2048_CGI, true);//��ʾ�к�
		gmw_set_colno_switch(&pG2048_CGI, true);//��ʾ�б�

		/* ��row/col��ֵ������Ϸ���������� */
		gmw_set_rowcol(&pG2048_CGI, row, col);
		/* ��ʾ��� */
		gmw_draw_frame(&pG2048_CGI);

		/* ��״̬����ʾ���� */
		sprintf(temp, "Ŀ��:%d ����:%d ���:%d (R:����,Q:�˳�)", goal_point, grade, max_grade);
		gmw_status_line(&pG2048_CGI, TOP_STATUS_LINE, temp);
		//while (1);
		/* ���ڲ�����չ�ֵ���Ļ�� */
		for (int k = 0; k < 2; k++)
		{
			int m = rand() % row;
			int n = rand() % col;
			matrix_num[m][n] = 2;
		}
		for (i = 0; i < row; i++)
			for (j = 0; j < col; j++) {
				if (matrix_num[i][j] != 0)
					gmw_draw_block(&pG2048_CGI, i, j, matrix_num[i][j], bdi_normal);
			}
		//while (1);
		int ret;
		int maction, old_mrow = 0, old_mcol = 0, mrow = 0, mcol = 0;
		int keycode1, keycode2;
		int quit = 0, reload = 0;
		cct_disable_mouse();
		while (1)
		{
			cct_setcursor(CURSOR_INVISIBLE);
			ret = gmw_read_keyboard_and_mouse(&pG2048_CGI, maction, mrow, mcol, keycode1, keycode2);
			sprintf(temp, "Ŀ��:%d ����:%d ���:%d (R:����,Q:�˳�)", goal_point, grade, max_grade);
			gmw_status_line(&pG2048_CGI, TOP_STATUS_LINE, temp);
			if (ret == CCT_KEYBOARD_EVENT)
			{ //CCT_KEYBOARD_EVENT - ������뺬��ȥ�� cmd_console_tools.cpp
				switch (keycode1) {
				case 0xE0: //224
					switch (keycode2) {
					case KB_ARROW_UP:
						for (int i = 0; i < row;i++)
							for (int j = 0; j < col; j++)
							{
								int count = 0;
								int same_count = 0;
								if (matrix_num[i][j] != 0)
								{
									int first = 0;
									for (int k = i - 1; k >= 0; k--)
									{
										if(matrix_num[k][j] == 0 )
											count++;
										if (matrix_num[k][j] != 0 && !first)
										{
											first = 1;
											if (matrix_num[k][j] == matrix_num[i][j])
											{
												first = 0;
												same_count++;
											}
										}
									}
									if (same_count % 2 == 1)
										count += 1;
									if (count != 0)
									{
										gmw_move_block(&pG2048_CGI, i, j, matrix_num[i][j], 0, bdi_normal, DOWN_TO_UP, count);
										if (same_count)
										{
											matrix_num[i - count][j] = 2 * matrix_num[i][j];
											grade += matrix_num[i - count][j];
											if (grade > max_grade)
												max_grade = grade;
											gmw_draw_block(&pG2048_CGI, i - count, j, matrix_num[i - count][j], bdi_normal);
											sprintf(temp, "Ŀ��:%d ����:%d ���:%d (R:����,Q:�˳�)", goal_point, grade, max_grade);
											gmw_status_line(&pG2048_CGI, TOP_STATUS_LINE, temp);
										}
										else
											matrix_num[i - count][j] = matrix_num[i][j];
										matrix_num[i][j] = 0;
									}
								}
							}
						//while (1);
						break;
					case KB_ARROW_DOWN:
						for (int i = row-1; i >= 0; i--)
							for (int j = col - 1; j >= 0; j--)
							{
								int count = 0;
								int same_count = 0;
								if (matrix_num[i][j] != 0)
								{
									int first = 0;
									for (int k = i + 1; k <= row - 1; k++)
									{
										if (matrix_num[k][j] == 0)
											count++;
										if (matrix_num[k][j] != 0 && !first)
										{
											first = 1;
											if (matrix_num[k][j] == matrix_num[i][j])
											{
												first = 0;
												same_count++;
											}
										}
									}
									if (same_count % 2 == 1)
										count += 1;
									if (count != 0)
									{
										gmw_move_block(&pG2048_CGI, i, j, matrix_num[i][j], 0, bdi_normal, UP_TO_DOWN, count);
										if (same_count)
										{
											matrix_num[i + count][j] = 2 * matrix_num[i][j];
											grade += matrix_num[i + count][j];
											if (grade > max_grade)
												max_grade = grade;
											gmw_draw_block(&pG2048_CGI, i + count, j, matrix_num[i + count][j], bdi_normal);
											sprintf(temp, "Ŀ��:%d ����:%d ���:%d (R:����,Q:�˳�)", goal_point, grade, max_grade);
											gmw_status_line(&pG2048_CGI, TOP_STATUS_LINE, temp);
										}
										else
											matrix_num[i + count][j] = matrix_num[i][j];
										matrix_num[i][j] = 0;
									}
								}
							}
						break;
					case KB_ARROW_LEFT:
						for (int i = 0; i < row; i++)
							for (int j = 0; j < col; j++)
							{
								int count = 0;
								int same_count = 0;
								if (matrix_num[i][j] != 0)
								{
									int first = 0;
									for (int k = j - 1; k >= 0; k--)
									{
										if (matrix_num[i][k] == 0)
											count++;
										if (matrix_num[i][k] != 0 && !first)
										{
											first = 1;
											if (matrix_num[i][k] == matrix_num[i][j])
											{
												first = 0;
												same_count++;
											}
										}
									}
									if (same_count % 2 == 1)
										count += 1;
									if (count != 0)
									{
										gmw_move_block(&pG2048_CGI, i, j, matrix_num[i][j], 0, bdi_normal, RIGHT_TO_LEFT, count);
										if (same_count)
										{
											matrix_num[i][j - count] = 2 * matrix_num[i][j];
											grade += matrix_num[i][j - count];
											if (grade > max_grade)
												max_grade = grade;
											gmw_draw_block(&pG2048_CGI, i, j - count, matrix_num[i][j - count], bdi_normal);
											sprintf(temp, "Ŀ��:%d ����:%d ���:%d (R:����,Q:�˳�)", goal_point, grade, max_grade);
											gmw_status_line(&pG2048_CGI, TOP_STATUS_LINE, temp);
										}
										else
											matrix_num[i][j - count] = matrix_num[i][j];
										matrix_num[i][j] = 0;
									}
								}
							}
						break;
					case KB_ARROW_RIGHT:
						for (int i = row - 1; i >= 0; i--)
							for (int j = col - 1; j >= 0; j--)
							{
								int count = 0;
								int same_count = 0;
								if (matrix_num[i][j] != 0)
								{
									int first = 0;
									for (int k = j + 1; k <= col - 1; k++)
									{
										if (matrix_num[i][k] == 0)
											count++;
										if (matrix_num[i][k] != 0 && !first)
										{
											first = 1;
											if (matrix_num[i][k] == matrix_num[i][j])
											{
												first = 0;
												same_count++;
											}
										}
									}
									if (same_count % 2 == 1)
										count += 1;
									if (count != 0)
									{
										gmw_move_block(&pG2048_CGI, i, j, matrix_num[i][j], 0, bdi_normal, LEFT_TO_RIGHT, count);
										if (same_count)
										{
											matrix_num[i][j + count] = 2 * matrix_num[i][j];
											grade += matrix_num[i][j + count];
											if (grade > max_grade)
												max_grade = grade;
											gmw_draw_block(&pG2048_CGI, i, j + count, matrix_num[i][j + count], bdi_normal);
											sprintf(temp, "Ŀ��:%d ����:%d ���:%d (R:����,Q:�˳�)", goal_point, grade, max_grade);
											gmw_status_line(&pG2048_CGI, TOP_STATUS_LINE, temp);
										}
										else
											matrix_num[i][j + count] = matrix_num[i][j];
										matrix_num[i][j] = 0;
									}
								}
							}
						break;
					}
					break;
				case 81:
				case 113:
					quit = 1;
					break;
				case 82:
				case 114:
					reload = 1;
					break;
				}//end of switch
			}
			else
				continue;
			if (quit || reload)
				break;
			while (1)
			{
				int m = rand() % row;
				int n = rand() % col;
				if (matrix_num[m][n] == 0)
				{
					matrix_num[m][n] = 2;
					gmw_draw_block(&pG2048_CGI, m, n, 2, bdi_normal);
					break;
				}
			}
			if (quit || reload)
				break;
		}

		for (i = 0; i < row; i++)
			for (j = 0; j < col; j++)
			{
				matrix_num[i][j] = 0;
			}
		if (quit)
			break;
	}
	sprintf(temp, "��Ϸ���˳�");
	gmw_status_line(&pG2048_CGI, LOWER_STATUS_LINE, temp,"ף��������죡");
	return 0;
}