/* 2152041 ���� �ƿ� */
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<conio.h>
#include "../include/common_menu.h"
#include "../include/common_output.h"
#include "../include/common_base.h"
#include "../include/cmd_console_tools.h"
#include "../include/common_input.h"
#include "../include/cmd_gmw_tools.h"
using namespace std;

int mark_same_num(int matrix_num[][10], int mark_same[][10], int row, int col, int output_row, int output_col);

int main()
{
	const BLOCK_DISPLAY_INFO bdi_normal[] = {
		{BDI_VALUE_BLANK, -1, -1, NULL},  //0����ʾ���ÿո���伴��
		{1,  COLOR_BLUE,   COLOR_BLACK,  NULL},	//����1�ġ�������״̬
		{2,  COLOR_GREEN,  COLOR_BLACK,  NULL},
		{3,  COLOR_CYAN,   COLOR_BLACK,  NULL},
		{4,  COLOR_RED,    COLOR_BLACK,  NULL},
		{5,  COLOR_PINK,   COLOR_BLACK,  NULL},
		{6,  COLOR_HBLUE,  COLOR_BLACK,  NULL},
		{7,  COLOR_HGREEN, COLOR_BLACK,  NULL},
		{8,  COLOR_HCYAN,  COLOR_BLACK,  NULL},
		{9,  COLOR_HRED,   COLOR_BLACK,  NULL},
		{10, COLOR_HPINK,  COLOR_BLACK,  NULL},	//����10�ġ�������״̬�������Ҫ�������Լ�������11���Ժ������
		{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
	};
	const BLOCK_DISPLAY_INFO bdi_related[] = {
		{BDI_VALUE_BLANK, -1, -1, NULL},  //0����ʾ���ÿո���伴��
		{1,  COLOR_BLUE,   COLOR_WHITE,  NULL},	//����1�ġ���ѡ��+������״̬
		{2,  COLOR_GREEN,  COLOR_WHITE,  NULL},
		{3,  COLOR_CYAN,   COLOR_WHITE,  NULL},
		{4,  COLOR_RED,    COLOR_WHITE,  NULL},
		{5,  COLOR_PINK,   COLOR_WHITE,  NULL},
		{6,  COLOR_HBLUE,  COLOR_WHITE,  NULL},
		{7,  COLOR_HGREEN, COLOR_WHITE,  NULL},
		{8,  COLOR_HCYAN,  COLOR_WHITE,  NULL},
		{9,  COLOR_HRED,   COLOR_WHITE,  NULL},
		{10, COLOR_HPINK,  COLOR_WHITE,  NULL},	//����10�ġ���ѡ��+������״̬�������Ҫ�������Լ�������11���Ժ������
		{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
	};
	const BLOCK_DISPLAY_INFO bdi_selected[] = {
		{BDI_VALUE_BLANK, -1, -1, NULL},  //0����ʾ���ÿո���伴��
		{1, COLOR_BLUE,   COLOR_HWHITE, NULL},	//����1�ġ�ѡ�С�״̬
		{2, COLOR_GREEN,  COLOR_HWHITE, NULL},
		{3, COLOR_CYAN,   COLOR_HWHITE, NULL},
		{4, COLOR_RED,    COLOR_HWHITE, NULL},
		{5, COLOR_PINK,   COLOR_HWHITE, NULL},
		{6, COLOR_HBLUE,  COLOR_HWHITE, NULL},
		{7, COLOR_HGREEN, COLOR_HWHITE, NULL},
		{8, COLOR_HCYAN,  COLOR_HWHITE, NULL},
		{9, COLOR_HRED,   COLOR_HWHITE, NULL},
		{10,COLOR_HPINK,  COLOR_HWHITE, NULL},	//����10�ġ�ѡ�С�״̬�������Ҫ�������Լ�������11���Ժ������
		{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
	};
	int row, col;
	int matrix_num[10][10] = { 0 };
	int mark_same[10][10] = { 0 };
	int loop = 1;
	const char* gname = "�ϳ�ʮ";
	srand((unsigned int)(time(NULL)));
	cct_cls();
	input_ranks(&row, &col, 5, 10, 5, 10, 0);
	for (int i = 0; i <= row - 1; i++)
		for (int j = 0; j <= col - 1; j++)
			matrix_num[i][j] = rand() % 3 + 1;

	CONSOLE_GRAPHICS_INFO Mto10_CGI; //����һ��CGI����

	/*��ȱʡֵ��ʼ�������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ�ԣ�*/
	gmw_init(&Mto10_CGI);

	gmw_set_color(&Mto10_CGI, COLOR_BLACK, COLOR_WHITE);
	gmw_set_font(&Mto10_CGI, "Terminal", 16, 8);
	gmw_set_frame_style(&Mto10_CGI, 6, 3, false);	//���Ϊ6(�����2λ����)���߶�Ϊ3(����һ��)
	gmw_set_frame_color(&Mto10_CGI, COLOR_WHITE, COLOR_BLACK);
	gmw_set_block_border_switch(&Mto10_CGI, true);
	gmw_set_rowno_switch(&Mto10_CGI, true);//��ʾ�к�
	gmw_set_colno_switch(&Mto10_CGI, true);//��ʾ�б�

	char temp[256];
	int i, j;

	/* ��row/col��ֵ������Ϸ���������� */
	gmw_set_rowcol(&Mto10_CGI, row, col);

	/* ��ʾ��� */
	gmw_draw_frame(&Mto10_CGI);

	/* ��״̬����ʾ���� */
	sprintf(temp, "%s-���ڴ�С��%d�� %d��", gname, Mto10_CGI.lines, Mto10_CGI.cols);
	gmw_status_line(&Mto10_CGI, TOP_STATUS_LINE, temp);

	/* ��״̬����ʾ���� */
	gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, "��ʼ��Ϸ,q�˳���Ϸ", "������ɣ�");

	/* ���ڲ�����չ�ֵ���Ļ�� */
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++) {
			gmw_draw_block(&Mto10_CGI, i, j, matrix_num[i][j], bdi_normal);
		}
	cct_setcursor(CURSOR_INVISIBLE);
	int ret;
	int maction, old_mrow = 0, old_mcol = 0, mrow = 0, mcol = 0;
	int keycode1, keycode2;
	int choose = 0;
	gmw_draw_block(&Mto10_CGI, mrow, mcol, matrix_num[mrow][mcol], bdi_selected);
	while (loop)
	{
		old_mrow = mrow;
		old_mcol = mcol;
		ret = gmw_read_keyboard_and_mouse(&Mto10_CGI, maction, mrow, mcol, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT) {
			if (maction == MOUSE_ONLY_MOVED) {
				/* ��ʱ��mrow��mcol�϶����ղŲ�ͬ */

				/* ��һ��ɫ��仯��color_linez��������λ�ö���ɫ�飬�˴�ֱ����3���棩����ͬ��Ϸ�˴���ͬ�������Ǹ���ʾ */

				/* ԭɫ��������ʾ */
				if (old_mrow >= 0 && old_mcol >= 0)
					gmw_draw_block(&Mto10_CGI, old_mrow, old_mcol, matrix_num[old_mrow][old_mcol], bdi_normal);

				/* ��ɫ�����ԣ���Ϊ��������ɫ�鶼��ֵ���˴���3����� */
				gmw_draw_block(&Mto10_CGI, mrow, mcol, matrix_num[mrow][mcol], bdi_selected);
			}
			else if (maction == MOUSE_LEFT_BUTTON_CLICK) {
				/* ��״̬����ʾ���� */
				sprintf(temp, "[ѡ��] %c��%d��", char('A' + mrow), mcol); //δ����mrow����26��mcol����99�������������Ҫ�������д���
				gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp);
				choose = 1;
			}
			else;
		}
		else { //CCT_KEYBOARD_EVENT - ������뺬��ȥ�� cmd_console_tools.cpp
			switch (keycode1) {
			case 0x0D:
				/* ��״̬����ʾ���� */
				sprintf(temp, "[ѡ��] %c��%d��", char('A' + mrow), mcol); //δ����mrow����26��mcol����99�������������Ҫ�������д���
				gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp);
				choose = 1;
				break;
			case 0xE0: //224
				switch (keycode2) {
				case KB_ARROW_UP:
					/* ��״̬����ʾ���� */
					if (mrow >= 1)
					{
						mrow -= 1;
						gmw_draw_block(&Mto10_CGI, old_mrow, old_mcol, matrix_num[old_mrow][old_mcol], bdi_normal);
						gmw_draw_block(&Mto10_CGI, mrow, mcol, matrix_num[mrow][mcol], bdi_selected);
					}
					sprintf(temp, "[��ǰ����] %c��%d��", char('A' + mrow), mcol); //δ����mrow����26��mcol����99�������������Ҫ�������д���
					gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp);
					break;
				case KB_ARROW_DOWN:
					/* ��״̬����ʾ���� */
					if (mrow < row - 1)
					{
						mrow += 1;
						gmw_draw_block(&Mto10_CGI, old_mrow, old_mcol, matrix_num[old_mrow][old_mcol], bdi_normal);
						gmw_draw_block(&Mto10_CGI, mrow, mcol, matrix_num[mrow][mcol], bdi_selected);
					}
					sprintf(temp, "[��ǰ����] %c��%d��", char('A' + mrow), mcol); //δ����mrow����26��mcol����99�������������Ҫ�������д���
					gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp);
					break;
				case KB_ARROW_LEFT:
					/* ��״̬����ʾ���� */
					if (mcol >= 1)
					{
						mcol -= 1;
						gmw_draw_block(&Mto10_CGI, old_mrow, old_mcol, matrix_num[old_mrow][old_mcol], bdi_normal);
						gmw_draw_block(&Mto10_CGI, mrow, mcol, matrix_num[mrow][mcol], bdi_selected);
					}
					sprintf(temp, "[��ǰ����] %c��%d��", char('A' + mrow), mcol); //δ����mrow����26��mcol����99�������������Ҫ�������д���
					gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp);
					break;
				case KB_ARROW_RIGHT:
					/* ��״̬����ʾ���� */
					if (mcol <  col - 1)
					{
						mcol += 1;
						gmw_draw_block(&Mto10_CGI, old_mrow, old_mcol, matrix_num[old_mrow][old_mcol], bdi_normal);
						gmw_draw_block(&Mto10_CGI, mrow, mcol, matrix_num[mrow][mcol], bdi_selected);
					}
					sprintf(temp, "[��ǰ����] %c��%d��", char('A' + mrow), mcol); //δ����mrow����26��mcol����99�������������Ҫ�������д���
					gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp);
					break;
				}
				break;
			case 113:
			case 81:
				sprintf(temp, "��Ϸ");
				gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp,"���˳�");
				loop = 0;
				break;
			}//end of switch
		}//end of else
		if (choose)
		{			
			if (!mark_same_num(matrix_num, mark_same, mrow, mcol,row,col))
			{
				sprintf(temp, "��ǰλ����������ֵͬ"); //δ����mrow����26��mcol����99�������������Ҫ�������д���
				gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp);
				choose = 0;
			}
			else
			{
				matrix_num[mrow][mcol] += 1;
				for (int i = 0; i < row; i++)
					for (int j = 0; j < col; j++)
					{
						if (mark_same[i][j] == 1 && (i != mrow || j != mcol))
						{
							matrix_num[i][j] = 0;
						}
					}
				for (int i = 0; i < row; i++)
					for (int j = 0; j < col; j++)
					{
						if (mark_same[i][j] == 1)
						{
							gmw_draw_block(&Mto10_CGI, i, j, matrix_num[i][j], bdi_related);
						}
					}
			}
			for (int i = row - 1; i >= 0; i--)
				for (int j = col - 1; j >= 0; j--)
				{
					if (matrix_num[i][j] != 0)
					{
						int count = 0;
						for (int k = i + 1; k < row; k++)
						{
							if (matrix_num[k][j] == 0)
								count++;
						}
						if (count != 0)
						{
							gmw_move_block(&Mto10_CGI, i, j, matrix_num[i][j], 0, bdi_normal, UP_TO_DOWN, count);
						}
					}
				}
			for (int i = row - 1; i >= 0; i--)
				for (int j = col - 1; j >= 0; j--)
				{
					if (matrix_num[i][j] != 0)
					{
						int count = 0;
						for (int k = i + 1; k < row; k++)
						{
							if (matrix_num[k][j] == 0)
								count++;
						}
						if (count != 0)
						{
							matrix_num[i + count][j] = matrix_num[i][j];
							matrix_num[i][j] = 0;
						}
					}
				}
			//while (1);
			for (int i = 0; i < row; i++)
				for (int j = 0; j < col; j++)
				{
					if (matrix_num[i][j] == 0)
					{
						matrix_num[i][j] = rand() % 3 + 1;
						gmw_draw_block(&Mto10_CGI, i, j, matrix_num[i][j], bdi_normal);
					}
				}
//			while (1);
			//for (int i = 0; i < row; i++)
			//	for (int j = 0; j < col; j++)
			//	{
			//		if (mark_same[i][j] == 1 && (i != mrow || j != mcol))
			//		{
			//			gmw_draw_block(&Mto10_CGI, i, j, matrix_num[i][j], bdi_normal);
			//		}
			//	}
			for (int i = 0; i < row; i++)
				for (int j = 0; j < col; j++)
				{
					mark_same[i][j] = 0;
				}
			choose = 0;
		}
		if (judge_end(matrix_num, row, col) == 0)
		{
			loop = 0;
			sprintf(temp, "û�пɺϳ���");
			gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp, "��Ϸ���˳�");
		}
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
			{
				mark_same[i][j] = 0;
			}
	}//end of while
	return 0;
}

int mark_same_num(int matrix_num[][10], int mark_same[][10], int row, int col,int output_row,int output_col)
{
	int k = 0;
	int next[4][2] = { {0,1},{1,0},{0, -1},{ -1,0} };//����ƶ�����
	mark_same[row][col] = 1;
	int old_row = row, old_col = col;
	for (int i = 0; i <= 3; i++)
	{
		row = old_row;
		col = old_col;
		row += next[i][0];
		col += next[i][1];
		if (row < 0 || col < 0 || row > output_row - 1 || col > output_col - 1)
			continue;
		if (matrix_num[row][col] == matrix_num[old_row][old_col])
		{
			if (!mark_same[row][col])
			{
				k++;
				mark_same[row][col] = 1;
				mark_same_recursion(matrix_num, mark_same, row, col, output_row, output_col, 0);
			}
		}
	}
	return k;
}