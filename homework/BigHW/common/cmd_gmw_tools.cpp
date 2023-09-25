/* 2152041 �ƿ� ���� */
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
		�˴����Ը�����Ҫ�ľ�̬ȫ�ֱ������������٣����û�У�����̬ȫ��ֻ������/�궨�壨�������ޣ���
   -------------------------------------------------- */
/* ����ȡ�б� */
static const char row_character[53] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

/* --------------------------------------------------
		�˴����Ը�����Ҫ���ڲ��������ߺ���
		1�����������ޣ�����Ϊ gmw_inner_* 
		2����������
		3��������static������ȷ��ֻ�ڱ�Դ�ļ���ʹ��
   -------------------------------------------------- */
static int gmw_inner_update_variable(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	//���������м����йصĶ���Ҫ����һ��
	/* �����йر��� */
	pCGI->CFI.block_width_ext = (pCGI->CFI.separator ? 2 : 0);
	pCGI->CFI.block_high_ext = (pCGI->CFI.separator ? 1 : 0);
	pCGI->CFI.bwidth = pCGI->CFI.block_width_ext + pCGI->CFI.block_width;
	pCGI->CFI.bhigh = pCGI->CFI.block_high_ext + pCGI->CFI.block_high;
	/* ��ʼ���� */
	pCGI->start_x = pCGI->extern_left_cols;
	pCGI->start_y = pCGI->extern_up_lines;
	/* ���ڱ��� */
	pCGI->cols = pCGI->extern_right_cols + pCGI->extern_left_cols
		+ (pCGI->draw_frame_with_row_no ? 2 : 0) +pCGI->col_num * (pCGI->CFI.block_width_ext + pCGI->CFI.block_width)
		- pCGI->CFI.block_width_ext + 5;
	pCGI->lines = (pCGI->top_status_line ? 1 : 0) + (pCGI->draw_frame_with_col_no ? 1 : 0)
		+ pCGI->extern_down_lines + pCGI->extern_up_lines +
		pCGI->row_num * (pCGI->CFI.block_high_ext + pCGI->CFI.block_high)
		- pCGI->CFI.block_high_ext + (pCGI->lower_status_line ? 1 : 0) +6;
	/* ����й����� */
	pCGI->SLI.top_start_x = pCGI->start_x;
	pCGI->SLI.top_start_y = pCGI->start_y;
	pCGI->SLI.lower_start_x = pCGI->start_x;
	pCGI->SLI.lower_start_y = pCGI->lines - pCGI->extern_down_lines - 5;
	pCGI->SLI.width = pCGI->cols - pCGI->extern_left_cols - pCGI->extern_right_cols - 1;
	return 0;

}

/* ���������ַ������ */
static char* gmw_inner_chinese_character(const char* str)
{
	//1������2�ֽ���ֻȡǰ2�ֽ�
	//2�������NULL���������ո����
	//3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
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

/* ��x,y����ת��Ϊ��Ӧ������ */
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

/* ������ת��Ϊ��Ӧ��xy���� */
static int gmw_inner_location_transform(const CONSOLE_GRAPHICS_INFO* const pCGI, int row,int col,int &x,int &y)
{
    x = pCGI->start_x + (pCGI->draw_frame_with_row_no ? 2 : 0) + pCGI->CFI.bwidth * col + 2;
    y = (pCGI->draw_frame_with_col_no ? 1 : 0) + (pCGI->top_status_line ? 1 : 0) + pCGI->start_y + pCGI->CFI.bhigh * row + 1;

	return 0;
}

/* ��x,yΪ��㻭һ��ɫ�� */
static int gmw_inner_draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int x, const int y,const char*content, const int bdi_value, const int bgcolor,const int fgcolor)
{
	cct_setcolor(bgcolor, fgcolor);
	if (pCGI->CBI.block_border)
	{
		/* ���ɫ������ */
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
		/* ����м��� */
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
		/* ������һ�� */
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
		ʵ����������ĺ���������������׼����
   ----------------------------------------------- */
/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ϸ����ܵ�������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int row						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
			const int col						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
  �� �� ֵ��
  ˵    ����1��ָ��������Ϸ�ľ������������ֵ
            2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_rowcol(CONSOLE_GRAPHICS_INFO *const pCGI, const int row, const int col)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->row_num = (row > 0 ? row : 0);	
	pCGI->col_num = (col > 0 ? col : 0);
	gmw_inner_update_variable(pCGI);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������������ڣ�����Ϸ�������������ڵ�����cmd���ڣ�����ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int bg_color					��ǰ��ɫ��ȱʡCOLOR_BLACK��
		   const int fg_color					������ɫ��ȱʡCOLOR_WHITE��
		   const bool cascade					���Ƿ�����ȱʡΪtrue-������
  �� �� ֵ��
  ˵    ����1��cascade = trueʱ
				ͬ���޸���Ϸ���������ɫ
				ͬ���޸�����״̬���������ı��ı���ɫ��ǰ��ɫ����Ŀ�ı��ı���ɫ��ǰ��ɫ���䣩
			2���������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15
				    ǰ��ɫ����ɫ��ֵһ�µ����޷���������
					ǰ��ɫ������״̬����Ŀǰ��ɫ�������޷�������Ŀ��ʾ
					...
***************************************************************************/
int gmw_set_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int bgcolor, const int fgcolor, const bool cascade)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	/*�޸Ĵ�����ɫ*/
	pCGI->area_bgcolor = bgcolor;
	pCGI->area_fgcolor = fgcolor;
	cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
	if (cascade)
	{
		/* ��Ϸ��������ɫ */
		pCGI->CFI.bgcolor = bgcolor;
		pCGI->CFI.fgcolor = fgcolor;
		/* ��״̬����ɫ */
		pCGI->SLI.top_normal_bgcolor = bgcolor;
		pCGI->SLI.top_normal_fgcolor = fgcolor;
		pCGI->SLI.top_catchy_bgcolor = bgcolor;
		/* ��״̬����ɫ */
		pCGI->SLI.lower_normal_bgcolor = bgcolor;
		pCGI->SLI.lower_normal_fgcolor = fgcolor;
		pCGI->SLI.lower_catchy_bgcolor = bgcolor;
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ô��ڵ�����
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *fontname					���������ƣ�ֻ����"Terminal"��"������"���֣������򷵻�-1�����ı����壩
		   const int fs_high					������߶ȣ�ȱʡ������Ϊ16�������������ƣ���Ϊ��֤��
		   const int fs_width					������߶ȣ�ȱʡ������Ϊ8�������������ƣ���Ϊ��֤��
  �� �� ֵ��
  ˵    ����1����cmd_console_tools�е�setfontsize���ƣ�Ŀǰֻ֧�֡��������塱�͡������塱
            2������������������ֱ�ӷ��أ�����ԭ�������ò���
***************************************************************************/
int gmw_set_font(CONSOLE_GRAPHICS_INFO *const pCGI, const char *fontname, const int fs_high, const int fs_width)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (!strcmp(fontname, "Terminal") || !strcmp(fontname, "������"))
	{
		pCGI->CFT.font_size_high = fs_high > 0 ? fs_high : 16;
		pCGI->CFT.font_size_width = fs_width > 0 ? fs_width : 8;
		strcpy(pCGI->CFT.font_type, fontname);
	}
	else
		return -1;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������ʱ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type						����ʱ�����ͣ�ĿǰΪ3�֣�
		   const int delay_ms					����msΪ��λ����ʱ
			   ���߿����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ��ɫ�����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ɫ���ƶ�����ʱ��BLOCK_MOVED_DELAY_MS ~ �������ޣ���Ϊ��֤��ȷ�� <BLOCK_MOVED_DELAY_MS ���� BLOCK_MOVED_DELAY_MS��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_delay(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const int delay_ms)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == DELAY_OF_DRAW_FRAME)
		pCGI->delay_of_draw_frame = (delay_ms > 0 ? delay_ms : 0);
	else if (type == DELAY_OF_DRAW_BLOCK)
		pCGI->delay_of_draw_block = (delay_ms > 0 ? delay_ms : 0);
	else if (type == DELAY_OF_BLOCK_MOVED)
		pCGI->delay_of_block_moved = (delay_ms > BLOCK_MOVED_DELAY_MS ? delay_ms : BLOCK_MOVED_DELAY_MS);
	else;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ���������������Ϸ����ܽṹ֮����Ҫ�����Ķ�������
  ��    �ܣ�CONSOLE_GRAPHICS_INFO *const pCGI	��
		   const int up_lines					���ϲ�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int down_lines				���²�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int left_cols					����߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int right_cols				���ұ߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
  �� �� ֵ��
  ˵    �����������еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_ext_rowcol(CONSOLE_GRAPHICS_INFO *const pCGI, const int up_lines, const int down_lines, const int left_cols, const int right_cols)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->extern_up_lines = (up_lines > 0) ? up_lines : 0;
	pCGI->extern_down_lines = (down_lines > 0) ? down_lines : 0;
	pCGI->extern_left_cols = (left_cols > 0) ? left_cols : 0;
	pCGI->extern_right_cols = (right_cols > 0) ? right_cols : 0;
	gmw_inner_update_variable(pCGI);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_frame_default_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	/*�T�U�X �[�^ �a�d �g�m �j �p
	  ������ ���� ���� �ȩ� �� ��
	  �T���V �Y�\ �_�b �e�k �h �n
	  ���U�W �Z�] �`�c �f�l �i �o*/
	switch (type)
	{
	case 1:
		strcpy(pCGI->CFI.top_left, "�X");
		strcpy(pCGI->CFI.h_normal, "�T");
		strcpy(pCGI->CFI.h_top_separator, "�j");
		strcpy(pCGI->CFI.top_right, "�[");
		strcpy(pCGI->CFI.v_normal, "�U");
		strcpy(pCGI->CFI.mid_separator, "�p");
		strcpy(pCGI->CFI.v_left_separator, "�d");
		strcpy(pCGI->CFI.v_right_separator, "�g");
		strcpy(pCGI->CFI.lower_left, "�^");
		strcpy(pCGI->CFI.h_lower_separator, "�m");
		strcpy(pCGI->CFI.lower_right, "�a");
		break;
	case 2:
		strcpy(pCGI->CFI.top_left, "��");
		strcpy(pCGI->CFI.h_normal, "��");
		strcpy(pCGI->CFI.h_top_separator, "��");
		strcpy(pCGI->CFI.top_right, "��");
		strcpy(pCGI->CFI.v_normal, "��");
		strcpy(pCGI->CFI.mid_separator, "��");
		strcpy(pCGI->CFI.v_left_separator, "��");
		strcpy(pCGI->CFI.v_right_separator, "��");
		strcpy(pCGI->CFI.lower_left, "��");
		strcpy(pCGI->CFI.h_lower_separator, "��");
		strcpy(pCGI->CFI.lower_right, "��");
		break;
	case 3:
		//�T���V �Y�\ �_�b �e�k �h �n
		strcpy(pCGI->CFI.top_left, "�V");
		strcpy(pCGI->CFI.h_normal, "�T");
		strcpy(pCGI->CFI.h_top_separator, "�h");
		strcpy(pCGI->CFI.top_right, "�Y");
		strcpy(pCGI->CFI.v_normal, "��");
		strcpy(pCGI->CFI.mid_separator, "�n");
		strcpy(pCGI->CFI.v_left_separator, "�b");
		strcpy(pCGI->CFI.v_right_separator, "�e");
		strcpy(pCGI->CFI.lower_left, "�\");
		strcpy(pCGI->CFI.h_lower_separator, "�k");
		strcpy(pCGI->CFI.lower_right, "�_");
		break;
	case 4:
		// ���U�W �Z�] �`�c �f�l �i �o
		strcpy(pCGI->CFI.top_left, "�W");
		strcpy(pCGI->CFI.h_normal, "��");
		strcpy(pCGI->CFI.h_top_separator, "�i");
		strcpy(pCGI->CFI.top_right, "�Z");
		strcpy(pCGI->CFI.v_normal, "�U");
		strcpy(pCGI->CFI.mid_separator, "�o");
		strcpy(pCGI->CFI.v_left_separator, "�c");
		strcpy(pCGI->CFI.v_right_separator, "�f");
		strcpy(pCGI->CFI.lower_left, "�]");
		strcpy(pCGI->CFI.h_lower_separator, "�l");
		strcpy(pCGI->CFI.lower_right, "�`");
		break;
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const char *...						����11�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_frame_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const char *top_left, const char *lower_left, const char *top_right,
	const char *lower_right, const char *h_normal, const char *v_normal, const char *h_top_separator,
	const char *h_lower_separator, const char *v_left_separator, const char *v_right_separator, const char *mid_separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�ɫ��������С���Ƿ���Ҫ�ָ��ߵ�
  ������������������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int block_width						����ȣ�����ȱʡ2����ΪԼ�������Ϊ�����Ʊ�����������������Ҫ+1��
			const int block_high						���߶ȣ�����ȱʡ1��
			const bool separator						���Ƿ���Ҫ�ָ��ߣ�ȱʡΪtrue����Ҫ�ָ��ߣ�
  �� �� ֵ��
  ˵    ������ܴ�С/�Ƿ���Ҫ�ָ��ߵȵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_frame_style(CONSOLE_GRAPHICS_INFO *const pCGI, const int block_width, const int block_high, const bool separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (block_width > 0)
		pCGI->CFI.block_width = (block_width % 2 == 0 ? block_width : block_width + 1);
	else
		pCGI->CFI.block_width = 2;
	pCGI->CFI.block_high = (block_high > 0) ? block_high:1;
	pCGI->CFI.separator = separator;
	gmw_inner_update_variable(pCGI);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BORDER_TYPE �ṹ�е���ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int bg_color					������ɫ��ȱʡ -1��ʾ�ô��ڱ���ɫ��
			const int fg_color					��ǰ��ɫ��ȱʡ -1��ʾ�ô���ǰ��ɫ��
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_frame_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int bgcolor, const int fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->CFI.bgcolor = (bgcolor == -1 ? pCGI->area_bgcolor : bgcolor);
	pCGI->CFI.fgcolor = (fgcolor == -1 ? pCGI->area_fgcolor : fgcolor);

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ˫�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_block_default_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	switch (type) 
	{
	case 1:
		strcpy(pCGI->CBI.top_left, "�X");
		strcpy(pCGI->CBI.lower_left, "�^");
		strcpy(pCGI->CBI.top_right, "�[");
		strcpy(pCGI->CBI.lower_right, "�a");
		strcpy(pCGI->CBI.h_normal, "�T");
		strcpy(pCGI->CBI.v_normal, "�U");
		break;
	case 2:
		strcpy(pCGI->CBI.top_left, "��");
		strcpy(pCGI->CBI.lower_left, "��");
		strcpy(pCGI->CBI.top_right, "��");
		strcpy(pCGI->CBI.lower_right, "��");
		strcpy(pCGI->CBI.h_normal, "��");
		strcpy(pCGI->CBI.v_normal, "��");
		break;
	case 3:
		strcpy(pCGI->CBI.top_left, "�V");
		strcpy(pCGI->CBI.lower_left, "�\");
		strcpy(pCGI->CBI.top_right, "�Y");
		strcpy(pCGI->CBI.lower_right, "�_");
		strcpy(pCGI->CBI.h_normal, "�T");
		strcpy(pCGI->CBI.v_normal, "��");
		break;
	case 4:
		strcpy(pCGI->CBI.top_left, "�W");
		strcpy(pCGI->CBI.lower_left, "�]");
		strcpy(pCGI->CBI.top_right, "�Z");
		strcpy(pCGI->CBI.lower_right, "�`");
		strcpy(pCGI->CBI.h_normal, "��");
		strcpy(pCGI->CBI.v_normal, "�U");
		break;
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *...					����6�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_block_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const char *top_left, const char *lower_left, const char *top_right, const char *lower_right, const char *h_normal, const char *v_normal)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ÿ����Ϸɫ��(����)�Ƿ���ҪС�߿�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡfalse��
  �� �� ֵ��
  ˵    �����߿�Լ��Ϊ�����Ʊ����˫��
***************************************************************************/
int gmw_set_block_border_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->CBI.block_border = on_off;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ����״̬��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡtrue��
  �� �� ֵ��
  ˵    ����1��״̬�������Լ�����£�
			   1.1����״̬��ֻ��һ�У������������Ϸ�����/�б�����棬Ϊ��������ʼһ�У�����������Ͻ����������״̬�������꣩
			   1.2����״̬��ֻ��һ�У������������·����ߵ�����
			   1.3��״̬���Ŀ��Ϊ�������ȣ������Ϣ������ض�
		   2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_status_line_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���������״̬������ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const int normal_bgcolor			�������ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int normal_fgcolor			�������ı�ǰ��ɫ��ȱʡ -1��ʾʹ�ô���ǰ��ɫ��
			const int catchy_bgcolor			����Ŀ�ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int catchy_fgcolor			����Ŀ�ı�ǰ��ɫ��ȱʡ -1��ʾʹ������ɫ��
  ���������
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_status_line_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const int normal_bgcolor, const int normal_fgcolor, const int catchy_bgcolor, const int catchy_fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�к�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���к�Լ��Ϊ��ĸA��ʼ�������У��������26�����a��ʼ������52��ͳһΪ*��ʵ��Ӧ�ò����ܣ�
            2���Ƿ���ʾ�кŵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_rowno_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_row_no = on_off;
	gmw_inner_update_variable(pCGI);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�б�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���б�Լ��Ϊ����0��ʼ�������У�����0-99������99ͳһΪ**��ʵ��Ӧ�ò����ܣ�
            2���Ƿ���ʾ�б�ı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_colno_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_col_no = on_off;
	gmw_inner_update_variable(pCGI);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ CONSOLE_GRAPHICS_INFO �ṹ���еĸ���Աֵ
  ���������
  �� �� ֵ��
  ˵    ����1�����������ã���ӡ��ʽ�Զ���
            2������������������δ���ù������Բ�ʵ��
***************************************************************************/
int gmw_print(const CONSOLE_GRAPHICS_INFO *const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��� CONSOLE_GRAPHICS_INFO �ṹ����ȱʡֵ���г�ʼ��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
		   const int row					����Ϸ����ɫ��������ȱʡ10��
		   const int col					����Ϸ����ɫ��������ȱʡ10��
		   const int bgcolor				���������ڱ���ɫ��ȱʡ COLOR_BLACK��
		   const int fgcolor				���������ڱ���ɫ��ȱʡ COLOR_WHITE��
  �� �� ֵ��
  ˵    �������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ��
***************************************************************************/
int gmw_init(CONSOLE_GRAPHICS_INFO *const pCGI, const int row, const int col, const int bgcolor, const int fgcolor)
{
///* ����й����� */
	/* �����ñ�� */
	pCGI->inited = CGI_INITED;
	/* ��ʼ������ṹ */
	/* ���������޶������� */
	pCGI->extern_down_lines = 0;
	pCGI->extern_up_lines = 0;
	pCGI->extern_left_cols = 0;
	pCGI->extern_right_cols = 0;
	/* ��Ϸ�����ɫ�������� */
	pCGI->row_num = row;
	pCGI->col_num = col;
	/* ����ͼ�ν��汳����/ǰ���� */
	pCGI->area_bgcolor = bgcolor;
	pCGI->area_fgcolor = fgcolor;
	/* ����״̬������ */
	pCGI->top_status_line = true;
	pCGI->lower_status_line = true;
	/* ���кš��б� */
	pCGI->draw_frame_with_col_no = false;
	pCGI->draw_frame_with_row_no = false;
	/* ��ʱʱ������ */
	pCGI->delay_of_draw_frame = 0;//�����ܵ���ʱ
	pCGI->delay_of_draw_block = 0;//����Ϸ�����ʱ
	pCGI->delay_of_block_moved = BLOCK_MOVED_DELAY_MS;//��Ϸ���ƶ�����ʱ
	/* ������ʼ���� */
    pCGI->start_x = pCGI->extern_left_cols;
    pCGI->start_y = pCGI->extern_up_lines;
	/* �����������Ϣ */
	//��ʼ����ඣ�
	//*******************************************************
	/* �������Ϊ˫�� */
	strcpy(pCGI->CFI.top_left, "�X");
	strcpy(pCGI->CFI.lower_left, "�^");
	strcpy(pCGI->CFI.top_right, "�[");
	strcpy(pCGI->CFI.lower_right, "�a");
	strcpy(pCGI->CFI.h_normal, "�T");///Horizontal
	strcpy(pCGI->CFI.v_normal, "�U");//Vertical
	strcpy(pCGI->CFI.h_top_separator, "�j");
	strcpy(pCGI->CFI.h_lower_separator, "�m");
	strcpy(pCGI->CFI.v_left_separator, "�d");
	strcpy(pCGI->CFI.v_right_separator, "�g");
	strcpy(pCGI->CFI.mid_separator, "�p");
	/* ��������򱳾�ɫ��ǰ��ɫ */
	pCGI->CFI.bgcolor = COLOR_BLACK;
	pCGI->CFI.fgcolor = COLOR_WHITE;
	/* ɫ����2/�߶�1/��С�߿� */
	pCGI->CFI.block_high = 1;
	pCGI->CFI.block_width = 2;
	/* ɫ���ָ��� */
	pCGI->CFI.separator = 1;
	/* ɫ�鸽�ӿ�Ⱥ͸߶� */
	pCGI->CFI.block_width_ext = (pCGI->CFI.separator ? 2 : 0);
	pCGI->CFI.block_high_ext  = (pCGI->CFI.separator ? 1 : 0);
	/* ÿ��ÿ�к��ָ����ܿ�� */
	pCGI->CFI.bwidth = pCGI->CFI.block_width_ext + pCGI->CFI.block_width;
	pCGI->CFI.bhigh = pCGI->CFI.block_high_ext + pCGI->CFI.block_high;
	//*******************************************************
	/* ����ɫ����Ϣ */
	/* ����С�߿�������״ */
	strcpy(pCGI->CBI.top_left,   "�X");
	strcpy(pCGI->CBI.lower_left, "�^");
	strcpy(pCGI->CBI.top_right,	 "�[");
	strcpy(pCGI->CBI.lower_right,"�a");
	strcpy(pCGI->CBI.h_normal,	 "�T");	//Horizontal
	strcpy(pCGI->CBI.v_normal,	 "�U");	//Vertical
	/* ����ҪС�߿� */
	pCGI->CBI.block_border = 0;
	//*******************************************************
	/* ��ʼ��״̬����Ϣ */
	/* ����״̬������ʾ */
	pCGI->SLI.is_top_status_line = 1;
	pCGI->SLI.is_lower_status_line = 1;
	/* ��Ϸ����Ŀ�� */
	pCGI->SLI.width = pCGI->cols - pCGI->extern_left_cols - pCGI->extern_right_cols - 1;
	/* ��״̬����λ�� */
	pCGI->SLI.top_start_x = pCGI->extern_left_cols;
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;;
	/* ��״̬��������Ϣ��ɫ */
	pCGI->SLI.top_normal_bgcolor = COLOR_BLACK;
	pCGI->SLI.top_normal_fgcolor = COLOR_WHITE;
	/* ��״̬����Ŀ��Ϣ��ɫ */
	pCGI->SLI.top_catchy_bgcolor = COLOR_BLACK;
	pCGI->SLI.top_catchy_fgcolor = COLOR_HYELLOW;
	/* ��״̬��������Ϣ��ɫ */
	pCGI->SLI.lower_normal_bgcolor = COLOR_BLACK;
	pCGI->SLI.lower_normal_fgcolor = COLOR_WHITE;
	/* ��״̬����Ŀ��Ϣ��ɫ */
	pCGI->SLI.lower_catchy_bgcolor = COLOR_BLACK;
	pCGI->SLI.lower_catchy_fgcolor = COLOR_HYELLOW;
	//*******************************************************
	/* ����������Ϣ */
	/* Ĭ�ϵ���16*8 */
	strcpy(pCGI->CFT.font_type, "Terminal");
	pCGI->CFT.font_size_high = 16;
	pCGI->CFT.font_size_width = 8;
	//*******************************************************
	/* ����cmd���ڴ�С */
	//�����ɹ�
	pCGI->cols = pCGI->extern_right_cols + pCGI->extern_left_cols
		+ (pCGI->draw_frame_with_row_no ? 2 : 0) + pCGI->col_num * (pCGI->CFI.block_width_ext + pCGI->CFI.block_width)
		- pCGI->CFI.block_width_ext + 5;
	pCGI->lines = (pCGI->top_status_line ? 1 : 0) + (pCGI->draw_frame_with_col_no ? 1 : 0)
		+ pCGI->extern_down_lines + pCGI->extern_up_lines +
		pCGI->row_num * (pCGI->CFI.block_high_ext + pCGI->CFI.block_high)
		- pCGI->CFI.block_high_ext + (pCGI->lower_status_line ? 1 : 0) + 6;
	/* ��״̬����λ�� */
	pCGI->SLI.lower_start_x = pCGI->start_x;
	pCGI->SLI.lower_start_y = pCGI->lines - pCGI->extern_down_lines - 5;


	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ϸ���
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
  �� �� ֵ��
  ˵    ��������ɲο�demo��Ч��
***************************************************************************/
int gmw_draw_frame(const CONSOLE_GRAPHICS_INFO *const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	/* ��ʼ�� */
	cct_setfontsize(pCGI->CFT.font_type, pCGI->CFT.font_size_high, pCGI->CFT.font_size_width);
	cct_setconsoleborder(pCGI->cols, pCGI->lines, -1, -1);
	cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
	cct_cls();
	int start_frame_x, start_frame_y;
	char row_no, col_no[10] = { 0 };
	start_frame_x = pCGI->start_x + (pCGI->draw_frame_with_row_no ? 2 : 0);
	start_frame_y = pCGI->start_y + (pCGI->draw_frame_with_col_no ? 1 : 0) + (pCGI->top_status_line ? 1 : 0);
	/* ����к� */
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
	/* �����һ�� */
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
	/* ����м��� */
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
	/* ������һ�� */
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���״̬������ʾ��Ϣ
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type							��ָ������/��״̬��
		   const char *msg						��������Ϣ
		   const char *catchy_msg					����Ҫ�ر��ע����Ϣ����������Ϣǰ��ʾ��
  �� �� ֵ��
  ˵    ����1���������޶�Ϊ����ܵĿ�ȣ����к��б�λ�ã����������ȥ
            2��������һ���ַ���ĳ���ֵ�ǰ������ᵼ�º������룬Ҫ����
***************************************************************************/
int gmw_status_line(const CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const char *msg, const char *catchy_msg)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	char str_comb[256] = "";
	if(catchy_msg!=NULL)
		strcpy(str_comb, catchy_msg);

	if (!type && pCGI->top_status_line)
	{
		/* ��״̬�� */
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
		/* ��״̬�� */
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

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾĳһ��ɫ��(����Ϊ�ַ���������Ϊrow/col)
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const BLOCK_DISPLAY_INFO *const bdi		����Ÿ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
  �� �� ֵ��
  ˵    ����1��BLOCK_DISPLAY_INFO �ĺ����ͷ�ļ����÷��ο���������
            2��bdi_valueΪ BDI_VALUE_BLANK ��ʾ�հ׿飬Ҫ���⴦��
***************************************************************************/
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO *const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO *const bdi)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	/* ���ȼ����ɫ�����Ͻ����꣬���뻭ɫ��ĺ����� */
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ƶ�ĳһ��ɫ��
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const int blank_bdi_value				���ƶ����������ڶ���Ч����ʾʱ���ڱ�ʾ�հ׵�ֵ��һ��Ϊ0���˴���Ϊ�������룬�ǿ��ǵ����ܳ��ֵ����������
		   const BLOCK_DISPLAY_INFO *const bdi		�������ʾֵ/�հ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
		   const int direction						���ƶ�����һ�����֣������cmd_gmw_tools.h
		   const int distance						���ƶ����루��1��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_move_block(const CONSOLE_GRAPHICS_INFO *const pCGI, const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO *const bdi, const int direction, const int distance)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
					  //��ӡ��ʧ�ĺ��� pCGI->CFI.block_high
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
					  //��ӡ��ʧ�ĺ��� pCGI->CFI.block_high
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
					  //��ӡ��ʧ������
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
					  //��ӡ��ʧ������
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
	  
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������̻����
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   int &MAction							��������� CCT_MOUSE_EVENT�����ֵ��Ч��Ϊ MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK/MOUSE_RIGHT_BUTTON_CLICK ����֮һ
		                                               ������� CCT_KEYBOARD_EVENT�����ֵ��Ч
		   int &MRow								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &MCol								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode1							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ��һ����
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode2							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ�ڶ���������ǵ����룬��Ϊ0��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   const bool update_lower_status_line		������ƶ�ʱ���Ƿ�Ҫ�ڱ���������ʾ"[��ǰ���] *��*��/λ�÷Ƿ�"����Ϣ��true=��ʾ��false=����ʾ��ȱʡΪtrue��
  �� �� ֵ����������Լ��
		   1�����������ƶ����õ���MRow/MCol�봫�����ͬ(���ָ��΢С���ƶ�)���򲻷��أ�������
							  �õ����зǷ�λ�ã��򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
							  �õ���MRow/MCol�봫��Ĳ�ͬ(��������һ���仯)������ update_lower_status_line ����������״̬����ʾ"[��ǰ���] *��*��"���ٷ���MOUSE_ONLY_MOVED����Щ��Ϸ���غ�Ҫ����ɫ��Ĳ�ͬ��ɫ��ʾ��
		   2������ǰ������������ҵ�ǰ���ָ��ͣ��������Ϸ�����*��*���ϣ��򷵻� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_LEFT_BUTTON_CLICK, MRow Ϊ�кţ�MCol Ϊ�б�
		                          �ҵ�ǰ���ָ��ͣ���ڷǷ����򣨷���Ϸ������Ϸ�����еķָ��ߣ����򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
		   3������ǰ�������Ҽ������ж����ָ��ͣ�������Ƿ�Ϸ���ֱ�ӷ��� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_RIGHT_BUTTON_CLICK, MRow��MColȡ��ǰֵ����Ϊ�������ǵ��Ҽ������Ҫ���꣩
		   4��������¼����ϵ�ĳ������˫���밴��������ֱ�ӷ��� CCT_KEYBOARD_EVENT��KeyCode1/KeyCode2��Ϊ��Ӧ�ļ���ֵ
 ˵    ����ͨ������ cmd_console_tools.cpp �е� read_read ����ʵ��
***************************************************************************/
int gmw_read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO *const pCGI, int &MAction, int &MRow, int &MCol, int &KeyCode1, int &KeyCode2, const bool update_lower_status_line)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
						sprintf(buffer, "[��ǰ���] %c��%d��", MRow + 'A', MCol);
						gmw_status_line(pCGI, LOWER_STATUS_LINE, buffer);
					}
					if (old_row!=MRow || old_col!=MCol)//����䶯
					{
						if (update_lower_status_line)
						{
							sprintf(buffer, "[��ǰ���] %c��%d��", MRow + 'A', MCol);
							gmw_status_line(pCGI, LOWER_STATUS_LINE, buffer);
						}
						loop = 0;
					}
				}
				else if (update_lower_status_line)
				{
					sprintf(buffer, "[��ǰ���] λ�÷Ƿ�");
					gmw_status_line(pCGI, LOWER_STATUS_LINE, buffer);
				}
				break;
			case MOUSE_LEFT_BUTTON_CLICK:
				if (gmw_inner_transform_location(pCGI, mouse_x, mouse_y, MRow, MCol))
				{
					sprintf(buffer, "[��ǰ���] %c��%d��", MRow + 'A', MCol);
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

