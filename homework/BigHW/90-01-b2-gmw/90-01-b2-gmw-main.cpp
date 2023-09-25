/* 2152041 王浩 计科 */
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
		{BDI_VALUE_BLANK, -1, -1, NULL},  //0不显示，用空格填充即可
		{1,  COLOR_BLUE,   COLOR_BLACK,  NULL},	//数字1的“正常”状态
		{2,  COLOR_GREEN,  COLOR_BLACK,  NULL},
		{3,  COLOR_CYAN,   COLOR_BLACK,  NULL},
		{4,  COLOR_RED,    COLOR_BLACK,  NULL},
		{5,  COLOR_PINK,   COLOR_BLACK,  NULL},
		{6,  COLOR_HBLUE,  COLOR_BLACK,  NULL},
		{7,  COLOR_HGREEN, COLOR_BLACK,  NULL},
		{8,  COLOR_HCYAN,  COLOR_BLACK,  NULL},
		{9,  COLOR_HRED,   COLOR_BLACK,  NULL},
		{10, COLOR_HPINK,  COLOR_BLACK,  NULL},	//数字10的“正常”状态，如果需要，还可以继续增加11及以后的数字
		{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
	};
	const BLOCK_DISPLAY_INFO bdi_related[] = {
		{BDI_VALUE_BLANK, -1, -1, NULL},  //0不显示，用空格填充即可
		{1,  COLOR_BLUE,   COLOR_WHITE,  NULL},	//数字1的“可选择+关联”状态
		{2,  COLOR_GREEN,  COLOR_WHITE,  NULL},
		{3,  COLOR_CYAN,   COLOR_WHITE,  NULL},
		{4,  COLOR_RED,    COLOR_WHITE,  NULL},
		{5,  COLOR_PINK,   COLOR_WHITE,  NULL},
		{6,  COLOR_HBLUE,  COLOR_WHITE,  NULL},
		{7,  COLOR_HGREEN, COLOR_WHITE,  NULL},
		{8,  COLOR_HCYAN,  COLOR_WHITE,  NULL},
		{9,  COLOR_HRED,   COLOR_WHITE,  NULL},
		{10, COLOR_HPINK,  COLOR_WHITE,  NULL},	//数字10的“可选择+关联”状态，如果需要，还可以继续增加11及以后的数字
		{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
	};
	const BLOCK_DISPLAY_INFO bdi_selected[] = {
		{BDI_VALUE_BLANK, -1, -1, NULL},  //0不显示，用空格填充即可
		{1, COLOR_BLUE,   COLOR_HWHITE, NULL},	//数字1的“选中”状态
		{2, COLOR_GREEN,  COLOR_HWHITE, NULL},
		{3, COLOR_CYAN,   COLOR_HWHITE, NULL},
		{4, COLOR_RED,    COLOR_HWHITE, NULL},
		{5, COLOR_PINK,   COLOR_HWHITE, NULL},
		{6, COLOR_HBLUE,  COLOR_HWHITE, NULL},
		{7, COLOR_HGREEN, COLOR_HWHITE, NULL},
		{8, COLOR_HCYAN,  COLOR_HWHITE, NULL},
		{9, COLOR_HRED,   COLOR_HWHITE, NULL},
		{10,COLOR_HPINK,  COLOR_HWHITE, NULL},	//数字10的“选中”状态，如果需要，还可以继续增加11及以后的数字
		{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
	};
	int row, col;
	int matrix_num[10][10] = { 0 };
	int mark_same[10][10] = { 0 };
	int loop = 1;
	const char* gname = "合成十";
	srand((unsigned int)(time(NULL)));
	cct_cls();
	input_ranks(&row, &col, 5, 10, 5, 10, 0);
	for (int i = 0; i <= row - 1; i++)
		for (int j = 0; j <= col - 1; j++)
			matrix_num[i][j] = rand() % 3 + 1;

	CONSOLE_GRAPHICS_INFO Mto10_CGI; //声明一个CGI变量

	/*用缺省值初始化（窗口背景黑/前景白，点阵16*8，上下左右无额外行列，上下状态栏均有，无行号/列标，框架线型为双线，色块宽度2/高度1/无小边框，颜色略）*/
	gmw_init(&Mto10_CGI);

	gmw_set_color(&Mto10_CGI, COLOR_BLACK, COLOR_WHITE);
	gmw_set_font(&Mto10_CGI, "Terminal", 16, 8);
	gmw_set_frame_style(&Mto10_CGI, 6, 3, false);	//宽度为6(放最多2位数字)，高度为3(最多放一行)
	gmw_set_frame_color(&Mto10_CGI, COLOR_WHITE, COLOR_BLACK);
	gmw_set_block_border_switch(&Mto10_CGI, true);
	gmw_set_rowno_switch(&Mto10_CGI, true);//显示行号
	gmw_set_colno_switch(&Mto10_CGI, true);//显示列标

	char temp[256];
	int i, j;

	/* 按row/col的值重设游戏主区域行列 */
	gmw_set_rowcol(&Mto10_CGI, row, col);

	/* 显示框架 */
	gmw_draw_frame(&Mto10_CGI);

	/* 上状态栏显示内容 */
	sprintf(temp, "%s-窗口大小：%d行 %d列", gname, Mto10_CGI.lines, Mto10_CGI.cols);
	gmw_status_line(&Mto10_CGI, TOP_STATUS_LINE, temp);

	/* 下状态栏显示内容 */
	gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, "开始游戏,q退出游戏", "加载完成，");

	/* 将内部数组展现到屏幕上 */
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
				/* 这时，mrow、mcol肯定跟刚才不同 */

				/* 做一个色块变化（color_linez不是所有位置都有色块，此处直接用3代替），不同游戏此处不同，仅仅是个演示 */

				/* 原色块正常显示 */
				if (old_mrow >= 0 && old_mcol >= 0)
					gmw_draw_block(&Mto10_CGI, old_mrow, old_mcol, matrix_num[old_mrow][old_mcol], bdi_normal);

				/* 新色块亮显（因为不是所有色块都有值，此处用3替代） */
				gmw_draw_block(&Mto10_CGI, mrow, mcol, matrix_num[mrow][mcol], bdi_selected);
			}
			else if (maction == MOUSE_LEFT_BUTTON_CLICK) {
				/* 下状态栏显示内容 */
				sprintf(temp, "[选中] %c行%d列", char('A' + mrow), mcol); //未考虑mrow超过26，mcol超过99的情况，如有需要，请自行处理
				gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp);
				choose = 1;
			}
			else;
		}
		else { //CCT_KEYBOARD_EVENT - 具体键码含义去读 cmd_console_tools.cpp
			switch (keycode1) {
			case 0x0D:
				/* 下状态栏显示内容 */
				sprintf(temp, "[选中] %c行%d列", char('A' + mrow), mcol); //未考虑mrow超过26，mcol超过99的情况，如有需要，请自行处理
				gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp);
				choose = 1;
				break;
			case 0xE0: //224
				switch (keycode2) {
				case KB_ARROW_UP:
					/* 下状态栏显示内容 */
					if (mrow >= 1)
					{
						mrow -= 1;
						gmw_draw_block(&Mto10_CGI, old_mrow, old_mcol, matrix_num[old_mrow][old_mcol], bdi_normal);
						gmw_draw_block(&Mto10_CGI, mrow, mcol, matrix_num[mrow][mcol], bdi_selected);
					}
					sprintf(temp, "[当前键盘] %c行%d列", char('A' + mrow), mcol); //未考虑mrow超过26，mcol超过99的情况，如有需要，请自行处理
					gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp);
					break;
				case KB_ARROW_DOWN:
					/* 下状态栏显示内容 */
					if (mrow < row - 1)
					{
						mrow += 1;
						gmw_draw_block(&Mto10_CGI, old_mrow, old_mcol, matrix_num[old_mrow][old_mcol], bdi_normal);
						gmw_draw_block(&Mto10_CGI, mrow, mcol, matrix_num[mrow][mcol], bdi_selected);
					}
					sprintf(temp, "[当前键盘] %c行%d列", char('A' + mrow), mcol); //未考虑mrow超过26，mcol超过99的情况，如有需要，请自行处理
					gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp);
					break;
				case KB_ARROW_LEFT:
					/* 下状态栏显示内容 */
					if (mcol >= 1)
					{
						mcol -= 1;
						gmw_draw_block(&Mto10_CGI, old_mrow, old_mcol, matrix_num[old_mrow][old_mcol], bdi_normal);
						gmw_draw_block(&Mto10_CGI, mrow, mcol, matrix_num[mrow][mcol], bdi_selected);
					}
					sprintf(temp, "[当前键盘] %c行%d列", char('A' + mrow), mcol); //未考虑mrow超过26，mcol超过99的情况，如有需要，请自行处理
					gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp);
					break;
				case KB_ARROW_RIGHT:
					/* 下状态栏显示内容 */
					if (mcol <  col - 1)
					{
						mcol += 1;
						gmw_draw_block(&Mto10_CGI, old_mrow, old_mcol, matrix_num[old_mrow][old_mcol], bdi_normal);
						gmw_draw_block(&Mto10_CGI, mrow, mcol, matrix_num[mrow][mcol], bdi_selected);
					}
					sprintf(temp, "[当前键盘] %c行%d列", char('A' + mrow), mcol); //未考虑mrow超过26，mcol超过99的情况，如有需要，请自行处理
					gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp);
					break;
				}
				break;
			case 113:
			case 81:
				sprintf(temp, "游戏");
				gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp,"已退出");
				loop = 0;
				break;
			}//end of switch
		}//end of else
		if (choose)
		{			
			if (!mark_same_num(matrix_num, mark_same, mrow, mcol,row,col))
			{
				sprintf(temp, "当前位置无连续相同值"); //未考虑mrow超过26，mcol超过99的情况，如有需要，请自行处理
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
			sprintf(temp, "没有可合成项");
			gmw_status_line(&Mto10_CGI, LOWER_STATUS_LINE, temp, "游戏已退出");
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
	int next[4][2] = { {0,1},{1,0},{0, -1},{ -1,0} };//标记移动方向
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