/* 2152041 ���� �ƿ� */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

#if !HDC_SERIES_BY_TEACHER	//δ���������²Ŵ���������

/* ���������Ҫ��ͷ�ļ� */

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow(); //VS�д˴����в����ߣ���Ӱ������ʹ��

/* �Ѷ���ľ�̬ȫ�ֱ��� */
static HWND hWnd = GetConsoleWindow();
static HDC hdc = NULL;
static const double PI = 3.14159;
static int _BgColor_, _FgColor_, _Width_, _High;
static int _Delay_ms;

/* �����ʶ�ʹ�þ�̬ȫ�ֱ�����������static�����ⲿ���ɼ� */

/* �˴���������Զ��庯����������static�����ⲿ���ɼ� */

/* ��һ��ֱ�ߵ�б��ת���ɶ�Ӧ�Ƕ� */
static double location_to_angle(int x1, int y1, int x2, int y2)
{
	return atan(fabs(double(abs(y1 - y2)) / double(abs(x1 - x2))));
}
/* ��������˼�����������������ʵ�֣���Ҫ�Ķ� */
/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʼ��
  ���������const int bgcolor������ɫ
            const int fgcolor��ǰ��ɫ
			const int width  ����Ļ��ȣ�����
			const int high   ����Ļ�߶ȣ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	/* ���ͷţ���ֹ��release���ٴ�init��hdc_release�����룩 */
	hdc_release();

	/* ����init����һ����̬ȫ������¼������hdc_cls()���õ� */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_setcolor(bgcolor, fgcolor);
	cct_setfontsize("��������", 16);
	cct_setconsoleborder(width / 8 + !!(width % 8), high / 16 + !!(high % 16)); //������Ŀ�ȼ��߶�ת��Ϊ�ض��������������!!�ĺ��壺�������8/16�ı��������ж�+1
	cct_cls();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ͷŻ�ͼ��Դ
  ���������
  �� �� ֵ��
  ˵    ����������
***************************************************************************/
void hdc_release()
{
	if (hdc) {
		ReleaseDC(hWnd, hdc);
		hdc = NULL;
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_delay(int ms)
{
	if (ms > 0)
		_Delay_ms = ms;
	else
		_Delay_ms = 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����û�����ɫ������RGBֵ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_pencolor(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����û�����ɫ������RGB��ɫ��ֵ0-255
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor(RGB(red, green, blue));
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ļ�����е�ͼ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_cls()
{
    /* ����һ��Ҫ��һ����ɫ��ʼ������������ص㣬�ҵ�����㷽����ͬѧ����֪ͨ�� */
	hdc_init(_BgColor_, (_FgColor_  + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* ���ֻ���������demoʱ�������hdc_cls()���һ������ȱ�ߵ����������ʱ����
	   ������ֻ������л������⣬���ߴ���ʱֵ */
	Sleep(30);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x,y)λ�ô���ָ����ɫ����һ�����ص�
  ���������const int x��x���꣬���Ͻ�Ϊ(0,0)
            const int y��y���꣬���Ͻ�Ϊ(0,0)
  �� �� ֵ��
  ˵    ������ɫֱ���õ�ǰ�趨�������ڵ��ô�ָ��
***************************************************************************/
static inline void hdc_base_point(const int x, const int y)
{
	MoveToEx(hdc, x - 1, y - 1, NULL);
	LineTo(hdc, x, y);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x1,y1)-(x2,y2)֮�仭��һ�����ص������
  ���������const int x1�����x���꣬���Ͻ�Ϊ(0,0)
			const int y1�����y���꣬���Ͻ�Ϊ(0,0)
			const int x2���յ�y���꣬���Ͻ�Ϊ(0,0)
			const int y2���յ�y���꣬���Ͻ�Ϊ(0,0)
  �� �� ֵ��
  ˵    ������ɫֱ���õ�ǰ�趨
***************************************************************************/
static inline void hdc_base_line(const int x1, const int y1, const int x2, const int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x,y)λ�ô���ָ����ɫ��һ��ָ����ϸ�ĵ�(�û�ʵ��Բ��ģ��)
  ���������const int x			��x���꣬���Ͻ�Ϊ(0,0)
            const int y			��y���꣬���Ͻ�Ϊ(0,0)
			const int thickness	����Ĵ�ϸ������λ1�����޲���(�����ᵼ�²���ȫ���)����ȱʡֵ��
			const int RGB_value	�������ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    �����Ľ�����Ч��
***************************************************************************/
void hdc_point(const int x, const int y, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//��������
	/* ������ֱ�������ޣ����ǵ����޳���һ����С�ǣ�������Բ����λ��δʵ�� */

	const int tn_end = (tn <= 1) ? 1 : tn/2;

	int angle, level;
	int old_x1 = INT_MAX, old_y1 = INT_MAX, x1, y1;
	int count = 0;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	/* �û�Բ�ķ�ʽģ��ֵ� */
	for (level = 1; level <= tn_end; level++) {
		for (angle = 0; angle <= 360; angle ++) {
			/* ע�⣬ϵͳ�������ᣬ0����Բ�����·� */
			x1 = x + (int)(level * sin(angle * PI / 180));
			y1 = y - (int)(level * cos(angle * PI / 180));

			/* ���뾶��Сʱ���Ƕȱ仯��������int�͵�x1/y1�仯����˼��ж���䣬�����ظ���ͬһ���ص� */
			if (x1 != old_x1 || y1 != old_y1) {
				old_x1 = x1;
				old_y1 = y1;
				hdc_base_point(x1, y1);
				++count;
			}
		}
	}
#if 0
	/* �ſ���ע�ͣ����Կ���һ���ֵ����˼������ص���� */
	cct_gotoxy(0, 41);
	printf("count=%d           ", count);
	getchar();
#endif
}

/* -------------------------------------------------------------------------
	�������к�����ʵ�֣���������������׼�Ķ�
	1������Ҫ����ϵͳ�������й�ͼ�β����ĺ���
	2�����к�����ʵ�ֶ�����hdc_base_point/hdc_base_line���������
	3����һ�룬�ǲ������к�������Ҫ����������ʵ�ֹ��̣�Ӧ����ʵ����Щ������
	4�������ʵ������ӵĲ���
	5��ϵͳ�ĽǶ��뺯�������еĽǶȺ������180��
   ------------------------------------------------------------------------- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ����߶�
  ���������const int x1		������x
            const int y1		������y
			const int x2		���յ��x
			const int y2		���յ��y
			const int thickness	���߶εĴ�ϸ����ȱʡֵ��
			const int RGB_value	���߶ε���ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ���������������û���hdc_point����ϣ��ٶ�����
                  Ҳ������hdc_base_point/hdc_base_line����ϣ��ٶȿ죩
***************************************************************************/
void hdc_line(const int x1, const int y1, const int x2, const int y2, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//��������
	const int tn_end = (tn <= 1) ? 1 : tn / 2;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);//������ɫ

	//double angle = location_to_angle(x1, y1, x2, y2);
	/* ����������ʼ�������ֹ���� */
	/*�������������45�ȵ�ͻ�����֣�ԭ���Ǵ����������б�ʺ�
	  ��������������͹�����ֵ��Թ��󷴶������������ۣ�������
	  �ۼ�����Ӱ�죬������*/
	for(int i =0; i < tn; i++)
		for (int j = 0; j < tn; j++)
		{
			hdc_base_line(x1 + i - tn_end, y1 + j - tn_end, x2 + i - tn_end, y2 + j - tn_end);
		}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������������꣬��һ��������
  ���������const int x1		����1�����x
            const int y1		����1�����y
			const int x2		����2�����x
			const int y2		����2�����y
			const int x3		����3�����x
			const int y3		����3�����y
			bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness	���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value	����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    �������ж������Ƿ��ߣ�������ߣ�����һ��ֱ�߼���
***************************************************************************/
void hdc_triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, bool filled, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//��������
	const int tn_end = (tn <= 1) ? 1 : tn / 2;
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);//������ɫ

	hdc_line(x1, y1, x2, y2, tn, RGB_value);
	hdc_line(x1, y1, x3, y3, tn, RGB_value);
	hdc_line(x2, y2, x3, y3, tn, RGB_value);
	if (filled)//����������ڲ�
	{
		/* ��������������ε��������� */
		for(int i = min(x1, min(x2, x3)); i < max(x1, max(x2, x3)); i++)
			for (int j = min(y1, min(y2, y3)); j < max(y1, max(y2, y3)); j++)
			{
				/* �������������� */
				/* ���ķ��жϵ��λ�� */
				bool in_triangle = 0;
				double dx1 = i - x1;
				double dy1 = j - y1;
				double dx2 = x3 - x1;
				double dy2 = y3 - y1;
				double dx3 = x2 - x1;
				double dy3 = y2 - y1;
				double u = (double)(dx1 * dy3 - dx3 * dy1) / (double)(dx2 * dy3 - dx3 * dy2);
				double v = (double)(dx1 * dy2 - dx2 * dy1) / (double)(dx3 * dy2 - dx2 * dy3);
				if (u > 0 && v > 0 && u + v < 1)
					in_triangle = 1;
				if (in_triangle)
					hdc_base_point(i, j);
			}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��������Ͻ����꼰��ȡ��߶ȣ�����һ��������
  ���������const int left_up_x			�����Ͻ�x
            const int left_up_y			�����Ͻ�y
			const int width				�����
			const int high				���߶�
			const int rotation_angles	�������Ͻ�Ϊ֧�㣬��x�����ת��ǣ�����תΪ����
			bool filled					���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_rectangle(const int left_up_x, const int left_up_y, const int width, const int high, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//��������
	const int tn_end = (tn <= 1) ? 1 : tn / 2;
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);//������ɫ

	int right_up_x, right_up_y;//���Ͻ�����
	int left_down_x, left_down_y;//���½�����
	int right_down_x, right_down_y;//���½�����
	/* ���㼴�����긳��ֵ */
	right_up_x = left_up_x + (int)(width * cos(rotation_angles * PI / 180));
	right_up_y = left_up_y + (int)(width * sin(rotation_angles * PI / 180));
	left_down_x = left_up_x - (int)(high * sin(rotation_angles * PI / 180));
	left_down_y = left_up_y + (int)(high * cos(rotation_angles * PI / 180));
	right_down_x = left_down_x + (int)(width * cos(rotation_angles * PI / 180));
	right_down_y = left_down_y + (int)(width * sin(rotation_angles * PI / 180));
	/* �滭�߿� */
	hdc_line(left_up_x, left_up_y, left_down_x, left_down_y, tn, RGB_value);
	hdc_line(left_up_x, left_up_y, right_up_x, right_up_y, tn, RGB_value);
	hdc_line(left_down_x, left_down_y, right_down_x, right_down_y, tn, RGB_value);
	hdc_line(right_up_x, right_up_y, right_down_x, right_down_y, tn, RGB_value);
	/* ����ڲ� */
	if (filled)
	{
		/* һ������������������ */
		hdc_triangle(left_up_x, left_up_y, left_down_x, left_down_y, right_up_x, right_up_y, true, tn, RGB_value);
		hdc_triangle(right_down_x, right_down_y, left_down_x, left_down_y, right_up_x, right_up_y, true, tn, RGB_value);
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��������Ͻ����꼰�߳�������һ��������
  ���������const int left_up_x			�����Ͻ�x
			const int left_up_y			�����Ͻ�y
			const int length			���߳�
			const int rotation_angles	�������Ͻ�Ϊ֧�㣬��x�����ת��ǣ�����תΪ��������ȱʡֵ��
			const bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			���ߵĴ�ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	/* ������������ľ��� */
	hdc_rectangle(left_up_x, left_up_y, length, length, rotation_angles, filled, thickness, RGB_value);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ��Բ��
  ���������const int point_x		��Բ�ĵ�x
            const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const int angle_begin	����ʼ�Ƕȣ���Բ�����Ϸ�Ϊ0�㣬˳ʱ��Ϊ����ע�⣺��ϵͳ�������180��!!!������ȱʡֵ��
			const int angle_end		�������Ƕȣ�ͬ�ϣ�����ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//��������
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);//������ɫ
	double  angle = (int)angle_begin;
	int old_x1 = INT_MAX, old_y1 = INT_MAX, x1, y1;	
	/* ģ�»��ߵĺ�����ģ�»�Բ�ķ�ʽ��Բ */
	while (angle > angle_end)
	{
		angle -= 360;
	}
	for (; angle < angle_end; angle+=0.5)//angle++�õ��ĵ㲻���ܼ����������䲽��
	{
		/* ע�⣬ϵͳ�������ᣬ0����Բ�����·� */
		x1 = point_x + (int)(radius * sin(angle * PI / 180));
		y1 = point_y - (int)(radius * cos(angle * PI / 180));

		/* ���뾶��Сʱ���Ƕȱ仯��������int�͵�x1/y1�仯����˼��ж���䣬�����ظ���ͬһ���ص� */
		if (x1 != old_x1 || y1 != old_y1) 
		{
			old_x1 = x1;
			old_y1 = y1;
			hdc_point(x1, y1, tn+1, RGB_value);
		}
	}
	
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ������
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const int angle_begin	����ʼ�Ƕȣ���Բ�����Ϸ�Ϊ0�㣬˳ʱ��Ϊ����ע�⣺��ϵͳ�������180��!!!������ȱʡֵ��
			const int angle_end		�������Ƕȣ�ͬ�ϣ�����ȱʡֵ��
			const bool filled		���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  ���������
  �� �� ֵ��
  ˵    ��������ʼ/�����ǶȲ�ֵΪ360�ı���ʱ������������
***************************************************************************/
void hdc_sector(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const bool filled, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//��������
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);//������ɫ
	int angle = angle_begin;
	while (angle > angle_end)
	{
		angle -= 360;
	}
	/* ���Ȼ���Բ�� */
	hdc_arc(point_x, point_y, radius, angle, angle_end, tn, RGB_value);
	/* �ٻ������뾶�� */
	if ((angle_end - angle_begin) % 360 != 0)
	{
		int end_x1 = point_x + (int)(radius * sin(angle_begin * PI / 180));
		int end_y1 = point_y - (int)(radius * cos(angle_begin * PI / 180));
		int end_x2 = point_x + (int)(radius * sin(angle_end * PI / 180));
		int end_y2 = point_y - (int)(radius * cos(angle_end * PI / 180));
		hdc_line(point_x, point_y, end_x1, end_y1, tn, RGB_value);
		hdc_line(point_x, point_y, end_x2, end_y2, tn, RGB_value);
	}
	if (filled)//�������
	{
		double tmp_angle = (double)angle_begin;
		while (tmp_angle > angle_end)
		{
			tmp_angle -= 360;
		}
		for (;tmp_angle < angle_end; tmp_angle += 0.5)//angle++�õ��ĵ㲻���ܼ����������䲽��
		{
			/* ע�⣬ϵͳ�������ᣬ0����Բ�����·� */
			int x1 = point_x + (int)(radius * sin(tmp_angle * PI / 180));
			int y1 = point_y - (int)(radius * cos(tmp_angle * PI / 180));
			//hdc_base_line(x1, y1, point_x, point_y);
			hdc_line(x1, y1, point_x, point_y, 3 , RGB_value);//��䲿�ֿ���Զ�
		}
		
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ��Բ
  ���������const int point_x		��Բ�ĵ�x
			const int point_y		��Բ�ĵ�y
			const int radius		���뾶
			const bool filled		���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness		����ϸ����ȱʡֵ��
			const int RGB_value		����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_circle(const int point_x, const int point_y, const int radius, const bool filled, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//��������
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);//������ɫ
	hdc_arc(point_x, point_y, radius, 0, 360, tn, RGB_value);
	if (filled)
	{
		/* ����������Բ�ε���С���� */
		/* ������Բ��(�þ��빫ʽ����) */
		for(int i = point_x - radius;i <= point_x + radius; i++)
			for (int j = point_y - radius; j <= point_y + radius; j++)
			{
				if (pow(i - point_x, 2) + pow(j - point_y, 2) < radius * radius)
				{
					hdc_base_point(i, j);
				}
			}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ո����Ĳ�����һ����Բ
  ���������const int point_x			��Բ�ĵ�x
			const int point_y			��Բ�ĵ�y
			const int radius_a			��ƽ����X��İ뾶
			const int radius_b			��ƽ����Y��İ룬��
			const int rotation_angles	����Բ��Ϊ֧�㣬��x�����ת��ǣ�����תΪ��������ȱʡֵ��
			const bool filled			���Ƿ���Ҫ��䣨��ȱʡֵ��
			const int thickness			����ϸ����ȱʡֵ��
			const int RGB_value			����ɫ����ȱʡֵ��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void hdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//��������
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);//������ɫ
	/* �����������ķ��������������Բ����С���Σ���������Բ�ϣ����öԳƻ�������hdc_point���� */
	/* ʹ����Բ�ı�׼�����ж� */
	int max_square = max(radius_a, radius_b);
	for(int i = point_x - max_square; i <= point_x + max_square;i++)
		for (int j = (point_y - max_square); j <= point_y + max_square; j++)
		{
			/* ��תת������������ϵ�ϵĵ� */

			double location_x = (i - point_x) * cos(rotation_angles * PI / 180) + (j - point_y) * sin(rotation_angles * PI / 180);
			double location_y = (j - point_y) * cos(rotation_angles * PI / 180) - (i - point_x) * sin(rotation_angles * PI / 180);
			double tmp1 = (double)radius_b * (double)radius_b * location_x * location_x;
			double tmp2 = (double)radius_a * (double)radius_a * location_y * location_y;
			double tmp3 = (double)radius_a * (double)radius_a * (double)radius_b * (double)radius_b;
			/*��Ϊx, y�� + 1�Ĺ����л����һ����������Ϊ������һ����Բ�ϵĵ�����겻һ����������ȫ
			���������ϣ����Խ�����һ������ */
			double patch = double(tmp3 / 30);
			if (tmp1 + tmp2 - tmp3 <= 0 && tmp1 + tmp2 - tmp3>= -patch)
			{
				hdc_base_point(i, j);
			}
			if (filled)
			{
				if (tmp1 + tmp2 - tmp3 <= 0)
				{
					hdc_base_point(i, j);
				}
			}
		}
	
}

#endif !HDC_SERIES_BY_TEACHER
