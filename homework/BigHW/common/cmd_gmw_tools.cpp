/* 2152041 计科 王浩 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include<iomanip>
#include<Windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
using namespace std;

/* --------------------------------------------------
		此处可以给出需要的静态全局变量（尽可能少，最好没有）、静态全局只读变量/宏定义（个数不限）等
   -------------------------------------------------- */
/* 用来取行标 */
static const char row_character[53] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

/* --------------------------------------------------
		此处可以给出需要的内部辅助工具函数
		1、函数名不限，建议为 gmw_inner_* 
		2、个数不限
		3、必须是static函数，确保只在本源文件中使用
   -------------------------------------------------- */
static int gmw_inner_update_variable(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	//凡是与行列计算有关的都需要更新一遍
	/* 方块有关变量 */
	pCGI->CFI.block_width_ext = (pCGI->CFI.separator ? 2 : 0);
	pCGI->CFI.block_high_ext = (pCGI->CFI.separator ? 1 : 0);
	pCGI->CFI.bwidth = pCGI->CFI.block_width_ext + pCGI->CFI.block_width;
	pCGI->CFI.bhigh = pCGI->CFI.block_high_ext + pCGI->CFI.block_high;
	/* 起始坐标 */
	pCGI->start_x = pCGI->extern_left_cols;
	pCGI->start_y = pCGI->extern_up_lines;
	/* 窗口变量 */
	pCGI->cols = pCGI->extern_right_cols + pCGI->extern_left_cols
		+ (pCGI->draw_frame_with_row_no ? 2 : 0) +pCGI->col_num * (pCGI->CFI.block_width_ext + pCGI->CFI.block_width)
		- pCGI->CFI.block_width_ext + 5;
	pCGI->lines = (pCGI->top_status_line ? 1 : 0) + (pCGI->draw_frame_with_col_no ? 1 : 0)
		+ pCGI->extern_down_lines + pCGI->extern_up_lines +
		pCGI->row_num * (pCGI->CFI.block_high_ext + pCGI->CFI.block_high)
		- pCGI->CFI.block_high_ext + (pCGI->lower_status_line ? 1 : 0) +6;
	/* 框架有关坐标 */
	pCGI->SLI.top_start_x = pCGI->start_x;
	pCGI->SLI.top_start_y = pCGI->start_y;
	pCGI->SLI.lower_start_x = pCGI->start_x;
	pCGI->SLI.lower_start_y = pCGI->lines - pCGI->extern_down_lines - 5;
	pCGI->SLI.width = pCGI->cols - pCGI->extern_left_cols - pCGI->extern_right_cols - 1;
	return 0;

}

/* 处理中文字符的情况 */
static char* gmw_inner_chinese_character(const char* str)
{
	//1、超过2字节则只取前2字节
	//2、如果给NULL，用两个空格替代
	//3、如果给1字节，则补一个空格，如果因此而导致显示乱，不算错
	char* new_str = NULL;
	if (strlen(str) > 2)
	{
		strncpy(new_str, str, 2);
		new_str[2] = '\0';
	}
	else if (str == NULL)
	{
		strcpy(new_str,"  ");
	}
	else if (strlen(str) == 1)
	{
		strcpy(new_str, str);
		strcat(new_str, " ");
	}
	else
	{
		strcpy(new_str, str);
	}
	return new_str;
}

/* 将x,y坐标转换为对应的行列 */
static int gmw_inner_transform_location(const CONSOLE_GRAPHICS_INFO* const pCGI, const int x, const int y,int &MRow,int &MCol)
{
	bool in_block = 0;
	for (int i = 0; i < pCGI->row_num; i++)
	{
		for (int j = 0; j < pCGI->col_num; j++)
		{
			int lower_x = pCGI->start_x + (pCGI->draw_frame_with_row_no ? 2 : 0)
				+ j * (pCGI->CFI.block_width + 2 * (pCGI->CFI.separator ? 1 : 0)) + 2;
			int top_x = lower_x + pCGI->CFI.block_width;
			int lower_y = pCGI->start_y + 1 + i * (pCGI->CFI.block_high + (pCGI->CFI.separator ? 1 : 0))
				+ (pCGI->top_status_line ? 1 : 0) + (pCGI->draw_frame_with_col_no ? 1 : 0);
			int top_y = lower_y + pCGI->CFI.block_high;
			if (x >= lower_x && x < top_x && y >= lower_y && y < top_y)
			{
				in_block = 1;
				MRow = i;
				MCol = j;
				break;
			}
		}
		if (in_block)
			break;
	}
	if (in_block)
		return 1;
	else
		return 0;
}

/* 将行列转换为对应的xy坐标 */
static int gmw_inner_location_transform(const CONSOLE_GRAPHICS_INFO* const pCGI, int row,int col,int &x,int &y)
{
    x = pCGI->start_x + (pCGI->draw_frame_with_row_no ? 2 : 0) + pCGI->CFI.bwidth * col + 2;
    y = (pCGI->draw_frame_with_col_no ? 1 : 0) + (pCGI->top_status_line ? 1 : 0) + pCGI->start_y + pCGI->CFI.bhigh * row + 1;

	return 0;
}

/* 以x,y为起点画一个色块 */
static int gmw_inner_draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int x, const int y,const char*content, const int bdi_value, const int bgcolor,const int fgcolor)
{
	cct_setcolor(bgcolor, fgcolor);
	if (pCGI->CBI.block_border)
	{
		/* 输出色块首行 */
		cct_gotoxy(x, y);
		cout << pCGI->CBI.top_left;
		Sleep(pCGI->delay_of_draw_block);
		//while (1);
		for (int j = 0; j < pCGI->CFI.block_width / 2 - 2; j++)
		{
			cout << pCGI->CBI.h_normal;
			Sleep(pCGI->delay_of_draw_block);
		}
		cout << pCGI->CBI.top_right;
		Sleep(pCGI->delay_of_draw_block);
		/* 输出中间行 */
		for (int j = 1; j < pCGI->CFI.block_high - 1; j++) 
		{
			cct_gotoxy(x, y + j);
			cout<<pCGI->CBI.v_normal;
			Sleep(pCGI->delay_of_draw_block);
				if (j == pCGI->CFI.block_high / 2)
				{
					if (content[0] >= '0' && content[0] <= '9')
					{
						//if (strlen(content) == 1)
						//	cout << right << setw((pCGI->CFI.block_width - 2 * pCGI->CFI.block_width_ext)/2) << content;
						//else
						//	cout << setw((pCGI->CFI.block_width - 2 * pCGI->CFI.block_width_ext) / 2) << content;
						//if (((pCGI->CFI.block_width - 2 * pCGI->CFI.block_width_ext - strlen(content)) / 2) != 0)
						//	cout << setw((pCGI->CFI.block_width - 2 * pCGI->CFI.block_width_ext - strlen(content)) / 2) << " ";
						//cout << right << content;
						//if ((pCGI->CFI.block_width - 2 * pCGI->CFI.block_width_ext - strlen(content)) % 2 == 1)
						//	cout << setw((pCGI->CFI. block_width - 2 * pCGI->CFI.block_width_ext - strlen(content)) / 2 + 1) << " ";
						//else if ((pCGI->CFI.block_width - 2 * pCGI->CFI.block_width_ext - strlen(content)) != 0)
						//	cout << setw((pCGI->CFI.block_width - 2 * pCGI->CFI.block_width_ext - strlen(content)) / 2) << " ";
						//else;
						int length = pCGI->CFI.bwidth - (pCGI->CBI.block_border ? 4 : 0)
							- 2 * pCGI->CFI.separator - strlen(content);
						if (length / 2 != 0)
								cout << setw(length / 2) << " ";
						cout << content;
						if (length != 0)
						{
							if (length % 2 == 0)
								cout << setw(length / 2) << " ";
							else if (length % 2 == 1)
								cout << setw(length / 2 + 1) << " ";
							else;
						}
					}
					else
						cout << content;
				}
				else
					cout << setw(pCGI->CFI.bwidth - (pCGI->CBI.block_border ? 4 : 0)
						- 2 * pCGI->CFI.separator) << " ";
				Sleep(pCGI->delay_of_draw_block);
			cout << pCGI->CBI.v_normal;
			Sleep(pCGI->delay_of_draw_block);
		}
		/* 输出最后一行 */
		cct_gotoxy(x, y + pCGI->CFI.block_high - 1);
		cout << pCGI->CBI.lower_left;
		Sleep(pCGI->delay_of_draw_block);
		for (int j = 0; j < pCGI->CFI.block_width / 2 - 2; j++)
		{
			cout << pCGI->CBI.h_normal;
			Sleep(pCGI->delay_of_draw_block);

		}
		cout << pCGI->CBI.lower_right;
		Sleep(pCGI->delay_of_draw_block);
		//while (1);
	}
	else
	{
		for (int j = 0; j < pCGI->CFI.block_high; j++)
		{
			cct_gotoxy(x, y + j);
			for (int k = 0; k < pCGI->CFI.block_width / 2; k++)
			{
				if (j == pCGI->CFI.block_high / 2)
					cout << setw(2) << content;
				else
					cout << "  ";
				Sleep(pCGI->delay_of_draw_block);
			}
		}
	}

	return 0;
}

/* ----------------------------------------------- 
		实现下面给出的函数（函数声明不准动）
   ----------------------------------------------- */
/***************************************************************************
  函数名称：
  功    能：设置游戏主框架的行列数
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int row						：行数(错误则为0，不设上限，人为保证正确性)
			const int col						：列数(错误则为0，不设上限，人为保证正确性)
  返 回 值：
  说    明：1、指消除类游戏的矩形区域的行列值
            2、行列的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_rowcol(CONSOLE_GRAPHICS_INFO *const pCGI, const int row, const int col)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->row_num = (row > 0 ? row : 0);	
	pCGI->col_num = (col > 0 ? col : 0);
	gmw_inner_update_variable(pCGI);
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置整个窗口（含游戏区、附加区在内的整个cmd窗口）的颜色
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int bg_color					：前景色（缺省COLOR_BLACK）
		   const int fg_color					：背景色（缺省COLOR_WHITE）
		   const bool cascade					：是否级联（缺省为true-级联）
  返 回 值：
  说    明：1、cascade = true时
				同步修改游戏主区域的颜色
				同步修改上下状态栏的正常文本的背景色和前景色，醒目文本的背景色（前景色不变）
			2、不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15
				    前景色背景色的值一致导致无法看到内容
					前景色正好是状态栏醒目前景色，导致无法看到醒目提示
					...
***************************************************************************/
int gmw_set_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int bgcolor, const int fgcolor, const bool cascade)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	/*修改窗口颜色*/
	pCGI->area_bgcolor = bgcolor;
	pCGI->area_fgcolor = fgcolor;
	cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
	if (cascade)
	{
		/* 游戏主区域颜色 */
		pCGI->CFI.bgcolor = bgcolor;
		pCGI->CFI.fgcolor = fgcolor;
		/* 上状态栏颜色 */
		pCGI->SLI.top_normal_bgcolor = bgcolor;
		pCGI->SLI.top_normal_fgcolor = fgcolor;
		pCGI->SLI.top_catchy_bgcolor = bgcolor;
		/* 下状态栏颜色 */
		pCGI->SLI.lower_normal_bgcolor = bgcolor;
		pCGI->SLI.lower_normal_fgcolor = fgcolor;
		pCGI->SLI.lower_catchy_bgcolor = bgcolor;
	}
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置窗口的字体
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const char *fontname					：字体名称（只能是"Terminal"和"新宋体"两种，错误则返回-1，不改变字体）
		   const int fs_high					：字体高度（缺省及错误为16，不设其它限制，人为保证）
		   const int fs_width					：字体高度（缺省及错误为8，不设其它限制，人为保证）
  返 回 值：
  说    明：1、与cmd_console_tools中的setfontsize相似，目前只支持“点阵字体”和“新宋体”
            2、若设置其它字体则直接返回，保持原字体设置不变
***************************************************************************/
int gmw_set_font(CONSOLE_GRAPHICS_INFO *const pCGI, const char *fontname, const int fs_high, const int fs_width)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (!strcmp(fontname, "Terminal") || !strcmp(fontname, "新宋体"))
	{
		pCGI->CFT.font_size_high = fs_high > 0 ? fs_high : 16;
		pCGI->CFT.font_size_width = fs_width > 0 ? fs_width : 8;
		strcpy(pCGI->CFT.font_type, fontname);
	}
	else
		return -1;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置延时
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int type						：延时的类型（目前为3种）
		   const int delay_ms					：以ms为单位的延时
			   画边框的延时：0 ~ 不设上限，人为保证正确（<0则置0）
			   画色块的延时：0 ~ 不设上限，人为保证正确（<0则置0）
			   色块移动的延时：BLOCK_MOVED_DELAY_MS ~ 不设上限，人为保证正确（ <BLOCK_MOVED_DELAY_MS 则置 BLOCK_MOVED_DELAY_MS）
  返 回 值：
  说    明：
***************************************************************************/
int gmw_set_delay(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const int delay_ms)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == DELAY_OF_DRAW_FRAME)
		pCGI->delay_of_draw_frame = (delay_ms > 0 ? delay_ms : 0);
	else if (type == DELAY_OF_DRAW_BLOCK)
		pCGI->delay_of_draw_block = (delay_ms > 0 ? delay_ms : 0);
	else if (type == DELAY_OF_BLOCK_MOVED)
		pCGI->delay_of_block_moved = (delay_ms > BLOCK_MOVED_DELAY_MS ? delay_ms : BLOCK_MOVED_DELAY_MS);
	else;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  输入参数：设置游戏主框架结构之外需要保留的额外区域
  功    能：CONSOLE_GRAPHICS_INFO *const pCGI	：
		   const int up_lines					：上部额外的行（缺省及错误为0，不设上限，人为保证）
		   const int down_lines				：下部额外的行（缺省及错误为0，不设上限，人为保证）
		   const int left_cols					：左边额外的列（缺省及错误为0，不设上限，人为保证）
		   const int right_cols				：右边额外的列（缺省及错误为0，不设上限，人为保证）
  返 回 值：
  说    明：额外行列的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_ext_rowcol(CONSOLE_GRAPHICS_INFO *const pCGI, const int up_lines, const int down_lines, const int left_cols, const int right_cols)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->extern_up_lines = (up_lines > 0) ? up_lines : 0;
	pCGI->extern_down_lines = (down_lines > 0) ? down_lines : 0;
	pCGI->extern_left_cols = (left_cols > 0) ? left_cols : 0;
	pCGI->extern_right_cols = (right_cols > 0) ? right_cols : 0;
	gmw_inner_update_variable(pCGI);
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_TYPE 结构中的11种线型（缺省4种）
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：1 - 全线 2 - 全单线 3 - 横双竖单 4 - 横单竖双
  返 回 值：
  说    明：
***************************************************************************/
int gmw_set_frame_default_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const int type)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	/*═║╔ ╗╚ ╝╠ ╣╩ ╦ ╬
	  ─│┌ ┐└ ┘├ ┤┴ ┬ ┼
	  ═│╒ ╕╘ ╛╞ ╡╧ ╤ ╪
	  ─║╓ ╖╙ ╜╟ ╢╨ ╥ ╫*/
	switch (type)
	{
	case 1:
		strcpy(pCGI->CFI.top_left, "╔");
		strcpy(pCGI->CFI.h_normal, "═");
		strcpy(pCGI->CFI.h_top_separator, "╦");
		strcpy(pCGI->CFI.top_right, "╗");
		strcpy(pCGI->CFI.v_normal, "║");
		strcpy(pCGI->CFI.mid_separator, "╬");
		strcpy(pCGI->CFI.v_left_separator, "╠");
		strcpy(pCGI->CFI.v_right_separator, "╣");
		strcpy(pCGI->CFI.lower_left, "╚");
		strcpy(pCGI->CFI.h_lower_separator, "╩");
		strcpy(pCGI->CFI.lower_right, "╝");
		break;
	case 2:
		strcpy(pCGI->CFI.top_left, "┌");
		strcpy(pCGI->CFI.h_normal, "─");
		strcpy(pCGI->CFI.h_top_separator, "┬");
		strcpy(pCGI->CFI.top_right, "┐");
		strcpy(pCGI->CFI.v_normal, "│");
		strcpy(pCGI->CFI.mid_separator, "┼");
		strcpy(pCGI->CFI.v_left_separator, "├");
		strcpy(pCGI->CFI.v_right_separator, "┤");
		strcpy(pCGI->CFI.lower_left, "└");
		strcpy(pCGI->CFI.h_lower_separator, "┴");
		strcpy(pCGI->CFI.lower_right, "┘");
		break;
	case 3:
		//═│╒ ╕╘ ╛╞ ╡╧ ╤ ╪
		strcpy(pCGI->CFI.top_left, "╒");
		strcpy(pCGI->CFI.h_normal, "═");
		strcpy(pCGI->CFI.h_top_separator, "╤");
		strcpy(pCGI->CFI.top_right, "╕");
		strcpy(pCGI->CFI.v_normal, "│");
		strcpy(pCGI->CFI.mid_separator, "╪");
		strcpy(pCGI->CFI.v_left_separator, "╞");
		strcpy(pCGI->CFI.v_right_separator, "╡");
		strcpy(pCGI->CFI.lower_left, "╘");
		strcpy(pCGI->CFI.h_lower_separator, "╧");
		strcpy(pCGI->CFI.lower_right, "╛");
		break;
	case 4:
		// ─║╓ ╖╙ ╜╟ ╢╨ ╥ ╫
		strcpy(pCGI->CFI.top_left, "╓");
		strcpy(pCGI->CFI.h_normal, "─");
		strcpy(pCGI->CFI.h_top_separator, "╥");
		strcpy(pCGI->CFI.top_right, "╖");
		strcpy(pCGI->CFI.v_normal, "║");
		strcpy(pCGI->CFI.mid_separator, "╫");
		strcpy(pCGI->CFI.v_left_separator, "╟");
		strcpy(pCGI->CFI.v_right_separator, "╢");
		strcpy(pCGI->CFI.lower_left, "╙");
		strcpy(pCGI->CFI.h_lower_separator, "╨");
		strcpy(pCGI->CFI.lower_right, "╜");
		break;
	}
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_TYPE 结构中的11种线型
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const char *...						：共11种，具体见.h，此处略
  返 回 值：
  说    明：约定为一个中文制表符，可以使用其它内容，人为保证2字节
			1、超过2字节则只取前2字节
			2、如果给NULL，用两个空格替代
			3、如果给1字节，则补一个空格，如果因此而导致显示乱，不算错
***************************************************************************/
int gmw_set_frame_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const char *top_left, const char *lower_left, const char *top_right,
	const char *lower_right, const char *h_normal, const char *v_normal, const char *h_top_separator,
	const char *h_lower_separator, const char *v_left_separator, const char *v_right_separator, const char *mid_separator)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	strcpy(pCGI->CFI.top_left, top_left);
	strcpy(pCGI->CFI.lower_left, lower_left);
	strcpy(pCGI->CFI.top_right, top_right);
	strcpy(pCGI->CFI.lower_right, lower_right);
	strcpy(pCGI->CFI.h_normal, h_normal);
	strcpy(pCGI->CFI.v_normal, v_normal);
	strcpy(pCGI->CFI.h_top_separator, h_top_separator);
	strcpy(pCGI->CFI.h_lower_separator, h_lower_separator);
	strcpy(pCGI->CFI.v_left_separator, v_left_separator);
	strcpy(pCGI->CFI.v_right_separator, v_right_separator);
	strcpy(pCGI->CFI.mid_separator, mid_separator);
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_TYPE 结构中的色块数量大小、是否需要分隔线等
  输入参数：输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int block_width						：宽度（错误及缺省2，因为约定表格线为中文制表符，如果给出奇数，要+1）
			const int block_high						：高度（错误及缺省1）
			const bool separator						：是否需要分隔线（缺省为true，需要分隔线）
  返 回 值：
  说    明：框架大小/是否需要分隔线等的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_frame_style(CONSOLE_GRAPHICS_INFO *const pCGI, const int block_width, const int block_high, const bool separator)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (block_width > 0)
		pCGI->CFI.block_width = (block_width % 2 == 0 ? block_width : block_width + 1);
	else
		pCGI->CFI.block_width = 2;
	pCGI->CFI.block_high = (block_high > 0) ? block_high:1;
	pCGI->CFI.separator = separator;
	gmw_inner_update_variable(pCGI);
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BORDER_TYPE 结构中的颜色
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int bg_color					：背景色（缺省 -1表示用窗口背景色）
			const int fg_color					：前景色（缺省 -1表示用窗口前景色）
  返 回 值：
  说    明：不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15，前景色背景色的值一致导致无法看到内容等
***************************************************************************/
int gmw_set_frame_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int bgcolor, const int fgcolor)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->CFI.bgcolor = (bgcolor == -1 ? pCGI->area_bgcolor : bgcolor);
	pCGI->CFI.fgcolor = (fgcolor == -1 ? pCGI->area_fgcolor : fgcolor);

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BLOCK_INFO 结构中的6种线型（缺省4种）
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：1 - 全双线 2 - 全单线 3 - 横双竖单 4 - 横单竖双
  返 回 值：
  说    明：
***************************************************************************/
int gmw_set_block_default_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const int type)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	switch (type) 
	{
	case 1:
		strcpy(pCGI->CBI.top_left, "╔");
		strcpy(pCGI->CBI.lower_left, "╚");
		strcpy(pCGI->CBI.top_right, "╗");
		strcpy(pCGI->CBI.lower_right, "╝");
		strcpy(pCGI->CBI.h_normal, "═");
		strcpy(pCGI->CBI.v_normal, "║");
		break;
	case 2:
		strcpy(pCGI->CBI.top_left, "┌");
		strcpy(pCGI->CBI.lower_left, "└");
		strcpy(pCGI->CBI.top_right, "┐");
		strcpy(pCGI->CBI.lower_right, "┘");
		strcpy(pCGI->CBI.h_normal, "─");
		strcpy(pCGI->CBI.v_normal, "│");
		break;
	case 3:
		strcpy(pCGI->CBI.top_left, "╒");
		strcpy(pCGI->CBI.lower_left, "╘");
		strcpy(pCGI->CBI.top_right, "╕");
		strcpy(pCGI->CBI.lower_right, "╛");
		strcpy(pCGI->CBI.h_normal, "═");
		strcpy(pCGI->CBI.v_normal, "│");
		break;
	case 4:
		strcpy(pCGI->CBI.top_left, "╓");
		strcpy(pCGI->CBI.lower_left, "╙");
		strcpy(pCGI->CBI.top_right, "╖");
		strcpy(pCGI->CBI.lower_right, "╜");
		strcpy(pCGI->CBI.h_normal, "─");
		strcpy(pCGI->CBI.v_normal, "║");
		break;
	}
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BLOCK_INFO 结构中的6种线型
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const char *...					：共6种，具体见.h，此处略
  返 回 值：
  说    明：约定为一个中文制表符，可以使用其它内容，人为保证2字节
			1、超过2字节则只取前2字节
			2、如果给NULL，用两个空格替代
			3、如果给1字节，则补一个空格，如果因此而导致显示乱，不算错
***************************************************************************/
int gmw_set_block_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const char *top_left, const char *lower_left, const char *top_right, const char *lower_right, const char *h_normal, const char *v_normal)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	top_left    = gmw_inner_chinese_character(top_left);
	lower_left  = gmw_inner_chinese_character(lower_left);
	top_right   = gmw_inner_chinese_character(top_right);
	lower_right = gmw_inner_chinese_character(lower_right);
	h_normal    = gmw_inner_chinese_character(h_normal);
	v_normal    = gmw_inner_chinese_character(v_normal);
	strcpy(pCGI->CBI.top_left,   top_left   );
	strcpy(pCGI->CBI.lower_left, lower_left );
	strcpy(pCGI->CBI.top_right,  top_right  );
	strcpy(pCGI->CBI.lower_right,lower_right);
	strcpy(pCGI->CBI.h_normal,   h_normal   );
	strcpy(pCGI->CBI.v_normal,   v_normal   );
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置每个游戏色块(彩球)是否需要小边框
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const bool on_off					：true - 需要 flase - 不需要（缺省false）
  返 回 值：
  说    明：边框约定为中文制表符，双线
***************************************************************************/
int gmw_set_block_border_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->CBI.block_border = on_off;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示上下状态栏
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：状态栏类型（上/下）
			const bool on_off					：true - 需要 flase - 不需要（缺省true）
  返 回 值：
  说    明：1、状态栏的相关约定如下：
			   1.1、上状态栏只能一行，在主区域最上方框线/列标的上面，为主区域的最开始一行（主区域的左上角坐标就是上状态栏的坐标）
			   1.2、下状态栏只能一行，在主区域最下方框线的下面
			   1.3、状态栏的宽度为主区域宽度，如果信息过长则截断
		   2、行列的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_status_line_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type)
	{
		if (type != 1)
			return -1;
		pCGI->lower_status_line = on_off;
		pCGI->SLI.is_lower_status_line = pCGI->lower_status_line;
	}
	else
	{
		pCGI->top_status_line = on_off;
		pCGI->SLI.is_top_status_line = pCGI->top_status_line;
	}
	gmw_inner_update_variable(pCGI);
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置上下状态栏的颜色
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：状态栏类型（上/下）
			const int normal_bgcolor			：正常文本背景色（缺省 -1表示使用窗口背景色）
			const int normal_fgcolor			：正常文本前景色（缺省 -1表示使用窗口前景色）
			const int catchy_bgcolor			：醒目文本背景色（缺省 -1表示使用窗口背景色）
			const int catchy_fgcolor			：醒目文本前景色（缺省 -1表示使用亮黄色）
  输入参数：
  返 回 值：
  说    明：不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15，前景色背景色的值一致导致无法看到内容等
***************************************************************************/
int gmw_set_status_line_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const int normal_bgcolor, const int normal_fgcolor, const int catchy_bgcolor, const int catchy_fgcolor)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type)
	{
		if (type != 1)
			return -1;
		if (normal_bgcolor == -1)
			pCGI->SLI.lower_normal_bgcolor = pCGI->area_bgcolor;
		else
			pCGI->SLI.lower_normal_bgcolor = normal_bgcolor;
		if (normal_fgcolor == -1)
			pCGI->SLI.lower_normal_fgcolor = pCGI->area_fgcolor;
		else
			pCGI->SLI.lower_normal_fgcolor = normal_fgcolor;
		if (catchy_bgcolor == -1)
			pCGI->SLI.lower_catchy_bgcolor = pCGI->area_bgcolor;
		else
			pCGI->SLI.lower_catchy_bgcolor = catchy_bgcolor;
		if (catchy_fgcolor == -1)
			pCGI->SLI.lower_catchy_fgcolor = 14;
		else
			pCGI->SLI.lower_catchy_fgcolor = catchy_fgcolor;
	}
	else
	{
		if (normal_bgcolor == -1)
			pCGI->SLI.top_normal_bgcolor = pCGI->area_bgcolor;
		else
			pCGI->SLI.top_normal_bgcolor = normal_bgcolor;
		if (normal_fgcolor == -1)
			pCGI->SLI.top_normal_fgcolor = pCGI->area_fgcolor;
		else
			pCGI->SLI.top_normal_fgcolor = normal_fgcolor;
		if (catchy_bgcolor == -1)
			pCGI->SLI.top_catchy_bgcolor = pCGI->area_bgcolor;
		else
			pCGI->SLI.top_catchy_bgcolor = catchy_bgcolor;
		if (catchy_fgcolor == -1)
			pCGI->SLI.top_catchy_fgcolor = 14;
		else
			pCGI->SLI.top_catchy_fgcolor = catchy_fgcolor;
	}
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示行号
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const bool on_off					：true - 显示 flase - 不显示（缺省false）
  返 回 值：
  说    明：1、行号约定为字母A开始连续排列（如果超过26，则从a开始，超过52的统一为*，实际应用不可能）
            2、是否显示行号的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_rowno_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_row_no = on_off;
	gmw_inner_update_variable(pCGI);
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示列标
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const bool on_off					：true - 显示 flase - 不显示（缺省false）
  返 回 值：
  说    明：1、列标约定为数字0开始连续排列（数字0-99，超过99统一为**，实际应用不可能）
            2、是否显示列标的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_colno_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_col_no = on_off;
	gmw_inner_update_variable(pCGI);
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：打印 CONSOLE_GRAPHICS_INFO 结构体中的各成员值
  输入参数：
  返 回 值：
  说    明：1、仅供调试用，打印格式自定义
            2、本函数测试用例中未调用过，可以不实现
***************************************************************************/
int gmw_print(const CONSOLE_GRAPHICS_INFO *const pCGI)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：将 CONSOLE_GRAPHICS_INFO 结构体用缺省值进行初始化
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI：整体结构指针
		   const int row					：游戏区域色块行数（缺省10）
		   const int col					：游戏区域色块列数（缺省10）
		   const int bgcolor				：整个窗口背景色（缺省 COLOR_BLACK）
		   const int fgcolor				：整个窗口背景色（缺省 COLOR_WHITE）
  返 回 值：
  说    明：窗口背景黑/前景白，点阵16*8，上下左右无额外行列，上下状态栏均有，无行号/列标，框架线型为双线，色块宽度2/高度1/无小边框，颜色略
***************************************************************************/
int gmw_init(CONSOLE_GRAPHICS_INFO *const pCGI, const int row, const int col, const int bgcolor, const int fgcolor)
{
///* 框架有关坐标 */
	/* 首先置标记 */
	pCGI->inited = CGI_INITED;
	/* 初始化整体结构 */
	/* 上下左右无额外行列 */
	pCGI->extern_down_lines = 0;
	pCGI->extern_up_lines = 0;
	pCGI->extern_left_cols = 0;
	pCGI->extern_right_cols = 0;
	/* 游戏主框架色块行列数 */
	pCGI->row_num = row;
	pCGI->col_num = col;
	/* 整个图形界面背景黑/前景白 */
	pCGI->area_bgcolor = bgcolor;
	pCGI->area_fgcolor = fgcolor;
	/* 上下状态栏均有 */
	pCGI->top_status_line = true;
	pCGI->lower_status_line = true;
	/* 无行号、列标 */
	pCGI->draw_frame_with_col_no = false;
	pCGI->draw_frame_with_row_no = false;
	/* 延时时间设置 */
	pCGI->delay_of_draw_frame = 0;//画外框架的延时
	pCGI->delay_of_draw_block = 0;//画游戏块的延时
	pCGI->delay_of_block_moved = BLOCK_MOVED_DELAY_MS;//游戏块移动的延时
	/* 设置起始坐标 */
    pCGI->start_x = pCGI->extern_left_cols;
    pCGI->start_y = pCGI->extern_up_lines;
	/* 设置主框架信息 */
	//开始加速喽！
	//*******************************************************
	/* 框架线型为双线 */
	strcpy(pCGI->CFI.top_left, "╔");
	strcpy(pCGI->CFI.lower_left, "╚");
	strcpy(pCGI->CFI.top_right, "╗");
	strcpy(pCGI->CFI.lower_right, "╝");
	strcpy(pCGI->CFI.h_normal, "═");///Horizontal
	strcpy(pCGI->CFI.v_normal, "║");//Vertical
	strcpy(pCGI->CFI.h_top_separator, "╦");
	strcpy(pCGI->CFI.h_lower_separator, "╩");
	strcpy(pCGI->CFI.v_left_separator, "╠");
	strcpy(pCGI->CFI.v_right_separator, "╣");
	strcpy(pCGI->CFI.mid_separator, "╬");
	/* 主框架区域背景色和前景色 */
	pCGI->CFI.bgcolor = COLOR_BLACK;
	pCGI->CFI.fgcolor = COLOR_WHITE;
	/* 色块宽度2/高度1/无小边框 */
	pCGI->CFI.block_high = 1;
	pCGI->CFI.block_width = 2;
	/* 色块间分割线 */
	pCGI->CFI.separator = 1;
	/* 色块附加宽度和高度 */
	pCGI->CFI.block_width_ext = (pCGI->CFI.separator ? 2 : 0);
	pCGI->CFI.block_high_ext  = (pCGI->CFI.separator ? 1 : 0);
	/* 每行每列含分割线总宽度 */
	pCGI->CFI.bwidth = pCGI->CFI.block_width_ext + pCGI->CFI.block_width;
	pCGI->CFI.bhigh = pCGI->CFI.block_high_ext + pCGI->CFI.block_high;
	//*******************************************************
	/* 设置色块信息 */
	/* 设置小边框的组成形状 */
	strcpy(pCGI->CBI.top_left,   "╔");
	strcpy(pCGI->CBI.lower_left, "╚");
	strcpy(pCGI->CBI.top_right,	 "╗");
	strcpy(pCGI->CBI.lower_right,"╝");
	strcpy(pCGI->CBI.h_normal,	 "═");	//Horizontal
	strcpy(pCGI->CBI.v_normal,	 "║");	//Vertical
	/* 不需要小边框 */
	pCGI->CBI.block_border = 0;
	//*******************************************************
	/* 初始化状态栏信息 */
	/* 上下状态栏的显示 */
	pCGI->SLI.is_top_status_line = 1;
	pCGI->SLI.is_lower_status_line = 1;
	/* 游戏区域的宽度 */
	pCGI->SLI.width = pCGI->cols - pCGI->extern_left_cols - pCGI->extern_right_cols - 1;
	/* 上状态栏的位置 */
	pCGI->SLI.top_start_x = pCGI->extern_left_cols;
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;;
	/* 上状态栏正常信息配色 */
	pCGI->SLI.top_normal_bgcolor = COLOR_BLACK;
	pCGI->SLI.top_normal_fgcolor = COLOR_WHITE;
	/* 上状态栏醒目信息配色 */
	pCGI->SLI.top_catchy_bgcolor = COLOR_BLACK;
	pCGI->SLI.top_catchy_fgcolor = COLOR_HYELLOW;
	/* 下状态栏正常信息配色 */
	pCGI->SLI.lower_normal_bgcolor = COLOR_BLACK;
	pCGI->SLI.lower_normal_fgcolor = COLOR_WHITE;
	/* 下状态栏醒目信息配色 */
	pCGI->SLI.lower_catchy_bgcolor = COLOR_BLACK;
	pCGI->SLI.lower_catchy_fgcolor = COLOR_HYELLOW;
	//*******************************************************
	/* 设置字体信息 */
	/* 默认点阵16*8 */
	strcpy(pCGI->CFT.font_type, "Terminal");
	pCGI->CFT.font_size_high = 16;
	pCGI->CFT.font_size_width = 8;
	//*******************************************************
	/* 设置cmd窗口大小 */
	//暂且蒙古
	pCGI->cols = pCGI->extern_right_cols + pCGI->extern_left_cols
		+ (pCGI->draw_frame_with_row_no ? 2 : 0) + pCGI->col_num * (pCGI->CFI.block_width_ext + pCGI->CFI.block_width)
		- pCGI->CFI.block_width_ext + 5;
	pCGI->lines = (pCGI->top_status_line ? 1 : 0) + (pCGI->draw_frame_with_col_no ? 1 : 0)
		+ pCGI->extern_down_lines + pCGI->extern_up_lines +
		pCGI->row_num * (pCGI->CFI.block_high_ext + pCGI->CFI.block_high)
		- pCGI->CFI.block_high_ext + (pCGI->lower_status_line ? 1 : 0) + 6;
	/* 下状态栏的位置 */
	pCGI->SLI.lower_start_x = pCGI->start_x;
	pCGI->SLI.lower_start_y = pCGI->lines - pCGI->extern_down_lines - 5;


	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：画主游戏框架
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
  返 回 值：
  说    明：具体可参考demo的效果
***************************************************************************/
int gmw_draw_frame(const CONSOLE_GRAPHICS_INFO *const pCGI)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	/* 初始化 */
	cct_setfontsize(pCGI->CFT.font_type, pCGI->CFT.font_size_high, pCGI->CFT.font_size_width);
	cct_setconsoleborder(pCGI->cols, pCGI->lines, -1, -1);
	cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
	cct_cls();
	int start_frame_x, start_frame_y;
	char row_no, col_no[10] = { 0 };
	start_frame_x = pCGI->start_x + (pCGI->draw_frame_with_row_no ? 2 : 0);
	start_frame_y = pCGI->start_y + (pCGI->draw_frame_with_col_no ? 1 : 0) + (pCGI->top_status_line ? 1 : 0);
	/* 输出列号 */
	if (pCGI->draw_frame_with_col_no)
	{
		int start_colno = start_frame_x + pCGI->CFI.block_width / 2 + 1;
		for (int i = 0; i < pCGI->col_num; ++i)
		{
			if (i > 99)
				sprintf(col_no, "**");
			else
				sprintf(col_no, "%d", i);
			cct_showstr(start_colno + pCGI->CFI.bwidth * i, start_frame_y - 1, col_no, pCGI->area_bgcolor, pCGI->area_fgcolor, 1, -1);
		}
	}
	cct_showstr(start_frame_x, start_frame_y, pCGI->CFI.top_left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1, -1);
	Sleep(pCGI->delay_of_draw_frame);
	/* 输出第一行 */
	for (int j = 0; j < pCGI->col_num; ++j)
	{
		int initial_x = start_frame_x + pCGI->CFI.bwidth * j + 2;
		cct_showstr(initial_x, start_frame_y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width / 2, -1);
		if (pCGI->CFI.block_width_ext > 0 && j < pCGI->col_num - 1)
			cct_showstr(pCGI->CFI.block_width + initial_x, start_frame_y, pCGI->CFI.h_top_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1, -1);
		Sleep(pCGI->delay_of_draw_frame);
	}
	cct_showstr(start_frame_x + pCGI->CFI.bwidth * pCGI->col_num + 2 - pCGI->CFI.block_width_ext, start_frame_y, pCGI->CFI.top_right, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1, -1);
	Sleep(pCGI->delay_of_draw_frame);
	/* 输出中间行 */
	for (int k = 0; k < pCGI->row_num; ++k)
	{
		for (int m = 0; m < pCGI->CFI.bhigh; ++m)
		{
			int initial_y = start_frame_y + pCGI->CFI.bhigh * k + 1;
			if (pCGI->draw_frame_with_row_no && m == (pCGI->CFI.block_high - 1) / 2)
			{
				row_no = (k < 26 ? k + 65 : (k >= 52 ? 42 : k + 71));
				cct_showch(start_frame_x - 2, m + initial_y, row_no, pCGI->area_bgcolor, pCGI->area_fgcolor, 1);
			}
			if (pCGI->CFI.block_high_ext > 0 && m == pCGI->CFI.bhigh - 1)
			{
				if (k < pCGI->row_num - 1)
					cct_showstr(start_frame_x, m + initial_y, pCGI->CFI.v_left_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1, -1);
			}
			else
				cct_showstr(start_frame_x, m + initial_y, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1, -1);
			Sleep(pCGI->delay_of_draw_frame);
			for (int n = 0; n < pCGI->col_num; ++n)
			{
				int initial_x = start_frame_x + pCGI->CFI.bwidth * n + 2;
				if (pCGI->CFI.block_high_ext > 0 && m == pCGI->CFI.bhigh - 1)
				{
					if (k < pCGI->row_num - 1)
						cct_showstr(initial_x, m + initial_y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width / 2, -1);
				}
				else
				{
					cct_showstr(initial_x, m + initial_y, " ", pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width, -1);
				}
				if (pCGI->CFI.block_width_ext > 0 && n < pCGI->col_num - 1)
				{
					if (m == pCGI->CFI.bhigh - 1)
					{
						if (k < pCGI->row_num - 1)
							cct_showstr(pCGI->CFI.block_width + initial_x, m + initial_y, pCGI->CFI.mid_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1, -1);
					}
					else
					{
						cct_showstr(pCGI->CFI.block_width + initial_x, m + initial_y, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1, -1);
					}
				}
				Sleep(pCGI->delay_of_draw_frame);
			}
			int x_location = pCGI->start_x + (pCGI->draw_frame_with_row_no ? 2 : 0) +pCGI->CFI.bwidth * pCGI->col_num + 2 - pCGI->CFI.block_width_ext;
			int y_location = start_frame_y + pCGI->CFI.bhigh * k + 1;
			if (pCGI->CFI.block_high_ext > 0 && m == pCGI->CFI.bhigh - 1)
			{
				if (k < pCGI->row_num - 1)
					cct_showstr(x_location, m + y_location, pCGI->CFI.v_right_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1, -1);
			}
			else
			{
				cct_showstr(x_location, m + y_location, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1, -1);
			}
			Sleep(pCGI->delay_of_draw_frame);
		}
	}
	int last_y = start_frame_y + pCGI->CFI.bhigh * pCGI->row_num + 1 - pCGI->CFI.block_high_ext;
	cct_showstr(start_frame_x, last_y, pCGI->CFI.lower_left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1, -1);
	Sleep(pCGI->delay_of_draw_frame);
	/* 输出最后一行 */
	for (int j = 0; j < pCGI->col_num; ++j)
	{
		int last_x = start_frame_x + pCGI->CFI.bwidth * j + 2;
		cct_showstr(last_x, last_y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width / 2, -1);
		if (pCGI->CFI.block_width_ext > 0 && j < pCGI->col_num - 1)
			cct_showstr(pCGI->CFI.block_width + last_x, last_y, pCGI->CFI.h_lower_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1, -1);
		Sleep(pCGI->delay_of_draw_frame);
	}
	cct_showstr(start_frame_x + pCGI->CFI.bwidth * pCGI->col_num + 2 - pCGI->CFI.block_width_ext, last_y, pCGI->CFI.lower_right, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1, -1);
	Sleep(pCGI->delay_of_draw_frame);
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：在状态栏上显示信息
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int type							：指定是上/下状态栏
		   const char *msg						：正常信息
		   const char *catchy_msg					：需要特别标注的信息（在正常信息前显示）
  返 回 值：
  说    明：1、输出宽度限定为主框架的宽度（含行号列标位置），超出则截去
            2、如果最后一个字符是某汉字的前半个，会导致后面乱码，要处理
***************************************************************************/
int gmw_status_line(const CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const char *msg, const char *catchy_msg)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	char str_comb[256] = "";
	if(catchy_msg!=NULL)
		strcpy(str_comb, catchy_msg);

	if (!type && pCGI->top_status_line)
	{
		/* 上状态栏 */
		if (catchy_msg != NULL)
		{
			//strcat(str_comb, msg);
			cct_showstr(pCGI->SLI.top_start_x, pCGI->SLI.top_start_y, catchy_msg, pCGI->SLI.top_catchy_bgcolor, pCGI->SLI.top_catchy_fgcolor, 1, pCGI->cols);
			cct_showstr(pCGI->SLI.top_start_x + strlen(catchy_msg), pCGI->SLI.top_start_y, msg, pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor, 1, pCGI->cols - strlen(catchy_msg));
		}
		else
		{
			cct_showstr(pCGI->SLI.top_start_x, pCGI->SLI.top_start_y, msg, pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor, 1, pCGI->cols);
		}
	}
	else if(type && pCGI->lower_status_line)
	{
		/* 下状态栏 */
		if (catchy_msg != NULL)
		{
			//strcat(str_comb, msg);
			cct_showstr(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y, catchy_msg, pCGI->SLI.lower_catchy_bgcolor, pCGI->SLI.lower_catchy_fgcolor, 1, pCGI->cols);
			cct_showstr(pCGI->SLI.lower_start_x + strlen(catchy_msg), pCGI->SLI.lower_start_y, msg, pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor, 1, pCGI->cols - strlen(catchy_msg));
		}
		else
		{
			cct_showstr(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y, msg, pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor ,1, pCGI->cols);
		}
	}

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：显示某一个色块(内容为字符串，坐标为row/col)
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int row_no						：行号（从0开始，人为保证正确性，程序不检查）
		   const int col_no						：列号（从0开始，人为保证正确性，程序不检查）
		   const int bdi_value						：需要显示的值
		   const BLOCK_DISPLAY_INFO *const bdi		：存放该值对应的显示信息的结构体数组
  返 回 值：
  说    明：1、BLOCK_DISPLAY_INFO 的含义见头文件，用法参考测试样例
            2、bdi_value为 BDI_VALUE_BLANK 表示空白块，要特殊处理
***************************************************************************/
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO *const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO *const bdi)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	/* 首先计算出色块左上角坐标，传入画色块的函数中 */
	int i = 0;
	char* content;
	char buffer[100];
	int x = pCGI->start_x + (pCGI->draw_frame_with_row_no ? 2 : 0) +pCGI->CFI.bwidth * col_no + 2;
	int y = (pCGI->draw_frame_with_col_no ? 1 : 0) + (pCGI->top_status_line ? 1 : 0) +pCGI->start_y + pCGI->CFI.bhigh * row_no + 1;
	cct_gotoxy(x, y);
	for (i = 0; bdi[i].value != BDI_VALUE_END && bdi[i].value != bdi_value; ++i);
	if (bdi[i].value == BDI_VALUE_END)
		return -1;
	int bgcolor = ((bdi[i].bgcolor < 0) ? pCGI->CFI.bgcolor : bdi[i].bgcolor);
	int fgcolor = 0;
	if (bdi[i].value)
		fgcolor = ((bdi[i].fgcolor < 0) ? pCGI->CFI.fgcolor : bdi[i].fgcolor);
	else
		fgcolor = bgcolor;
	sprintf(buffer, "%d", bdi[i].value);
	if (bdi[i].content)
		content = (char*)bdi[i].content;
	else
		content = buffer;
	gmw_inner_draw_block(pCGI, x, y, content, bdi_value,bgcolor,fgcolor);
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：移动某一个色块
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int row_no						：行号（从0开始，人为保证正确性，程序不检查）
		   const int col_no						：列号（从0开始，人为保证正确性，程序不检查）
		   const int bdi_value						：需要显示的值
		   const int blank_bdi_value				：移动过程中用于动画效果显示时用于表示空白的值（一般为0，此处做为参数代入，是考虑到可能出现的特殊情况）
		   const BLOCK_DISPLAY_INFO *const bdi		：存放显示值/空白值对应的显示信息的结构体数组
		   const int direction						：移动方向，一共四种，具体见cmd_gmw_tools.h
		   const int distance						：移动距离（从1开始，人为保证正确性，程序不检查）
  返 回 值：
  说    明：
***************************************************************************/
int gmw_move_block(const CONSOLE_GRAPHICS_INFO *const pCGI, const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO *const bdi, const int direction, const int distance)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	  ////////////////////////////////////////////
	  cct_setcursor(CURSOR_INVISIBLE);
	  int i = 0;
	  char* content;
	  char buffer[100];
	  for (i = 0; bdi[i].value != BDI_VALUE_END && bdi[i].value != bdi_value; ++i);
	  if (bdi[i].value == BDI_VALUE_END)
	  	return -1;
	  int bgcolor = ((bdi[i].bgcolor < 0) ? pCGI->CFI.bgcolor : bdi[i].bgcolor);
	  int fgcolor = 0;
	  if (bdi[i].value)
	  	fgcolor = ((bdi[i].fgcolor < 0) ? pCGI->CFI.fgcolor : bdi[i].fgcolor);
	  else
	  	fgcolor = bgcolor;
	  sprintf(buffer, "%d", bdi[i].value);
	  if (bdi[i].content)
	  	content = (char*)bdi[i].content;
	  else
	  	content = buffer;
	  ////////////////////////////////////////////
	  int x = 0, y = 0;
	  gmw_inner_location_transform(pCGI, row_no, col_no, x, y);

		  switch (direction)
		  {
		  case DOWN_TO_UP:
			  for (int k = 1; k <= pCGI->CFI.bhigh * distance; k++)
			  {
				  for (int m = 0; m < pCGI->CFI.bhigh - pCGI->CFI.block_high_ext; m++)
				  {
					  cct_showstr(x, y - k + m + 1 , " ", pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width);
				  }
				  gmw_inner_draw_block(pCGI, x, y - k, content, bdi_value, bgcolor, fgcolor);
				  if (pCGI->CFI.separator && (((y - k) + pCGI->CFI.block_high - (pCGI->start_y + pCGI->draw_frame_with_col_no + pCGI->top_status_line)) % (pCGI->CFI.bhigh) == 0))
				  {
					  //打印消失的横线 pCGI->CFI.block_high
					  cct_setcursor(CURSOR_VISIBLE_NORMAL);
					  int tmp_x, tmp_y;
					  cct_getxy(tmp_x, tmp_y);
					  cct_gotoxy(tmp_x - pCGI->CFI.block_width, tmp_y + pCGI->CFI.block_high_ext);
					  cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
					  for (int m = 0; m < pCGI->CFI.block_width / 2; m++)
						  cout << pCGI->CFI.h_normal;
				  }
				  Sleep(pCGI->delay_of_block_moved);
			  }
			  break;
		  case UP_TO_DOWN:
			  for (int k = 1; k <= pCGI->CFI.bhigh * distance; k++)
			  {
				  for (int m = 0; m < pCGI->CFI.bhigh - pCGI->CFI.block_high_ext; m++)
				  {
					  cct_showstr(x, y + k + m - 1, " ", pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width);
				  }
				  gmw_inner_draw_block(pCGI, x, y + k, content, bdi_value, bgcolor, fgcolor);
				  if (pCGI->CFI.separator && (((y + k) + pCGI->CFI.block_high - (pCGI->start_y + pCGI->draw_frame_with_col_no + pCGI->top_status_line)) % (pCGI->CFI.bhigh) == 0))
				  {
					  //打印消失的横线 pCGI->CFI.block_high
					  int tmp_x, tmp_y;
					  cct_getxy(tmp_x, tmp_y);
					  cct_gotoxy(tmp_x - pCGI->CFI.block_width, tmp_y - pCGI->CFI.block_high);
					  cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
					  for (int m = 0; m < pCGI->CFI.block_width / 2; m++)
						  cout << pCGI->CFI.h_normal;
				  }
				  Sleep(pCGI->delay_of_block_moved);
			  }
			  break;
		  case RIGHT_TO_LEFT:
			  for (int k = 1; k <= pCGI->CFI.bwidth * distance; k++)
			  {
				  for (int m = 0; m < pCGI->CFI.bhigh - pCGI->CFI.block_high_ext; m++)
				  {
					  cct_showstr(x - k + 1, y + m, " ", pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width);
					  //cct_showstr(x, y + k + m - 1, " ", pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width);
				  }
				  gmw_inner_draw_block(pCGI, x - k, y, content, bdi_value, bgcolor, fgcolor);
				  if (pCGI->CFI.separator && (((x - k) + pCGI->CFI.block_width - (pCGI->start_x + (pCGI->draw_frame_with_row_no?2:0))) % (pCGI->CFI.bwidth) == 0))
				  {
					  //打印消失的竖线
					  int tmp_x, tmp_y;
					  cct_getxy(tmp_x, tmp_y);
					  for (int m = 0; m < pCGI->CFI.block_high; m++)
					  {
						  cct_showstr(tmp_x, tmp_y - pCGI->CFI.block_high + m + 1, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
					  }
				  }
				  Sleep(pCGI->delay_of_block_moved);
			  }
			  break;
		  case LEFT_TO_RIGHT:
			  for (int k = 1; k <= pCGI->CFI.bwidth * distance; k++)
			  {
				  for (int m = 0; m < pCGI->CFI.bhigh - pCGI->CFI.block_high_ext; m++)
				  {
					  cct_showstr(x + k - 1, y + m, " ", pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width);
					  //cct_showstr(x, y + k + m - 1, " ", pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width);
				  }
				  gmw_inner_draw_block(pCGI, x + k, y, content, bdi_value, bgcolor, fgcolor);
				  if (pCGI->CFI.separator && (((x + k) - pCGI->CFI.block_width_ext - (pCGI->start_x + (pCGI->draw_frame_with_row_no ? 2 : 0))) % (pCGI->CFI.bwidth) == 0))
				  {
					  //打印消失的竖线
					  int tmp_x, tmp_y;
					  cct_getxy(tmp_x, tmp_y);
					  for (int m = 0; m < pCGI->CFI.block_high; m++)
					  {
						  cct_showstr(tmp_x - pCGI->CFI.bwidth, tmp_y - pCGI->CFI.block_high + m + 1, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
					  }
				  }
				  Sleep(pCGI->delay_of_block_moved);
			  }
			  break;
		  }
	  
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：读键盘或鼠标
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   int &MAction							：如果返回 CCT_MOUSE_EVENT，则此值有效，为 MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK/MOUSE_RIGHT_BUTTON_CLICK 三者之一
		                                               如果返回 CCT_KEYBOARD_EVENT，则此值无效
		   int &MRow								：如果返回 CCT_MOUSE_EVENT 且 MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK，则此值有效，表示左键选择的游戏区域的行号（从0开始）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &MCol								：如果返回 CCT_MOUSE_EVENT 且 MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK，则此值有效，表示左键选择的游戏区域的列号（从0开始）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &KeyCode1							：如果返回 CCT_KEYBOARD_EVENT，则此值有效，为读到的键码（如果双键码，则为第一个）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &KeyCode2							：如果返回 CCT_KEYBOARD_EVENT，则此值有效，为读到的键码（如果双键码，则为第二个，如果是单键码，则为0）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   const bool update_lower_status_line		：鼠标移动时，是否要在本函数中显示"[当前光标] *行*列/位置非法"的信息（true=显示，false=不显示，缺省为true）
  返 回 值：函数返回约定
		   1、如果是鼠标移动，得到的MRow/MCol与传入的相同(鼠标指针微小的移动)，则不返回，继续读
							  得到行列非法位置，则不返回，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] 位置非法"
							  得到的MRow/MCol与传入的不同(行列至少一个变化)，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] *行*列"，再返回MOUSE_ONLY_MOVED（有些游戏返回后要处理色块的不同颜色显示）
		   2、如果是按下鼠标左键，且当前鼠标指针停留在主游戏区域的*行*列上，则返回 CCT_MOUSE_EVENT ，MAction 为 MOUSE_LEFT_BUTTON_CLICK, MRow 为行号，MCol 为列标
		                          且当前鼠标指针停留在非法区域（非游戏区域，游戏区域中的分隔线），则不返回，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] 位置非法"
		   3、如果是按下鼠标右键，则不判断鼠标指针停留区域是否合法，直接返回 CCT_MOUSE_EVENT ，MAction 为 MOUSE_RIGHT_BUTTON_CLICK, MRow、MCol取当前值（因为消灭星星的右键标记需要坐标）
		   4、如果按下键盘上的某键（含双键码按键），则直接返回 CCT_KEYBOARD_EVENT，KeyCode1/KeyCode2中为对应的键码值
 说    明：通过调用 cmd_console_tools.cpp 中的 read_read 函数实现
***************************************************************************/
int gmw_read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO *const pCGI, int &MAction, int &MRow, int &MCol, int &KeyCode1, int &KeyCode2, const bool update_lower_status_line)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	char buffer[400];
	bool loop = 1;
	int mouse_x = 0, mouse_y = 0;
	int old_row, old_col;
	int ret = 0;
	cct_enable_mouse();
	while (loop)
	{
		old_row = MRow;
		old_col = MCol;
		ret = cct_read_keyboard_and_mouse(mouse_x, mouse_y, MAction, KeyCode1, KeyCode2);
		if (ret == CCT_KEYBOARD_EVENT)
		{
			loop = 0;
		}
		else if (ret == CCT_MOUSE_EVENT)
		{
			switch (MAction)
			{
			case MOUSE_ONLY_MOVED:
				if (gmw_inner_transform_location(pCGI,mouse_x,mouse_y,MRow,MCol))
				{
					if (update_lower_status_line)
					{
						sprintf(buffer, "[当前光标] %c行%d列", MRow + 'A', MCol);
						gmw_status_line(pCGI, LOWER_STATUS_LINE, buffer);
					}
					if (old_row!=MRow || old_col!=MCol)//坐标变动
					{
						if (update_lower_status_line)
						{
							sprintf(buffer, "[当前光标] %c行%d列", MRow + 'A', MCol);
							gmw_status_line(pCGI, LOWER_STATUS_LINE, buffer);
						}
						loop = 0;
					}
				}
				else if (update_lower_status_line)
				{
					sprintf(buffer, "[当前光标] 位置非法");
					gmw_status_line(pCGI, LOWER_STATUS_LINE, buffer);
				}
				break;
			case MOUSE_LEFT_BUTTON_CLICK:
				if (gmw_inner_transform_location(pCGI, mouse_x, mouse_y, MRow, MCol))
				{
					sprintf(buffer, "[当前光标] %c行%d列", MRow + 'A', MCol);
					gmw_status_line(pCGI, LOWER_STATUS_LINE, buffer);
					loop = 0;
				}
				break;
			case MOUSE_RIGHT_BUTTON_CLICK:
				loop = 0;
				break;
			}
		}
		else;
	}
	cct_disable_mouse();
	return ret;
}

