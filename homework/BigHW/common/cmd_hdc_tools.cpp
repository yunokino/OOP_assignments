/* 2152041 王浩 计科 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "../include/cmd_hdc_tools.h"
using namespace std;

#if !HDC_SERIES_BY_TEACHER	//未定义的情况下才打开条件编译

/* 允许添加需要的头文件 */

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow(); //VS中此处会有波浪线，不影响正常使用

/* 已定义的静态全局变量 */
static HWND hWnd = GetConsoleWindow();
static HDC hdc = NULL;
static const double PI = 3.14159;
static int _BgColor_, _FgColor_, _Width_, _High;
static int _Delay_ms;

/* 允许适度使用静态全局变量，但仅限static，即外部不可见 */

/* 此处允许添加自定义函数，但仅限static，即外部不可见 */

/* 将一条直线的斜率转换成对应角度 */
static double location_to_angle(int x1, int y1, int x2, int y2)
{
	return atan(fabs(double(abs(y1 - y2)) / double(abs(x1 - x2))));
}
/* 下面给出了几个基本函数的完整实现，不要改动 */
/***************************************************************************
  函数名称：
  功    能：初始化
  输入参数：const int bgcolor：背景色
            const int fgcolor：前景色
			const int width  ：屏幕宽度（点阵）
			const int high   ：屏幕高度（点阵）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	/* 先释放，防止不release而再次init（hdc_release可重入） */
	hdc_release();

	/* 窗口init后，用一个静态全局量记录，后续hdc_cls()会用到 */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);

	cct_setcursor(CURSOR_INVISIBLE);
	cct_setcolor(bgcolor, fgcolor);
	cct_setfontsize("点阵字体", 16);
	cct_setconsoleborder(width / 8 + !!(width % 8), high / 16 + !!(high % 16)); //将点阵的宽度及高度转换为特定字体的行列数，!!的含义：如果不是8/16的倍数，行列多+1
	cct_cls();
}

/***************************************************************************
  函数名称：
  功    能：释放画图资源
  输入参数：
  返 回 值：
  说    明：可重入
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_delay(int ms)
{
	if (ms > 0)
		_Delay_ms = ms;
	else
		_Delay_ms = 0;
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB值
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_pencolor(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB三色，值0-255
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor(RGB(red, green, blue));
}

/***************************************************************************
  函数名称：
  功    能：清除屏幕上现有的图形
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_cls()
{
    /* 发现一定要换一种颜色初始化才能清除像素点，找到更简便方法的同学可以通知我 */
	hdc_init(_BgColor_, (_FgColor_  + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* 部分机器上运行demo时，会出现hdc_cls()后第一根线有缺线的情况，加延时即可
	   如果部分机器运行还有问题，调高此延时值 */
	Sleep(30);
}

/***************************************************************************
  函数名称：
  功    能：在(x,y)位置处用指定颜色画出一个像素点
  输入参数：const int x：x坐标，左上角为(0,0)
            const int y：y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定，可以在调用处指定
***************************************************************************/
static inline void hdc_base_point(const int x, const int y)
{
	MoveToEx(hdc, x - 1, y - 1, NULL);
	LineTo(hdc, x, y);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  函数名称：
  功    能：在(x1,y1)-(x2,y2)之间画出一个像素点的连线
  输入参数：const int x1：起点x坐标，左上角为(0,0)
			const int y1：起点y坐标，左上角为(0,0)
			const int x2：终点y坐标，左上角为(0,0)
			const int y2：终点y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定
***************************************************************************/
static inline void hdc_base_line(const int x1, const int y1, const int x2, const int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	if (_Delay_ms > 0)
		Sleep(_Delay_ms);
}

/***************************************************************************
  函数名称：
  功    能：在(x,y)位置处用指定颜色画一个指定粗细的点(用画实心圆来模拟)
  输入参数：const int x			：x坐标，左上角为(0,0)
            const int y			：y坐标，左上角为(0,0)
			const int thickness	：点的粗细，下限位1，上限不限(如过大会导致不完全填充)（有缺省值）
			const int RGB_value	：点的颜色（有缺省值）
  返 回 值：
  说    明：改进运行效率
***************************************************************************/
void hdc_point(const int x, const int y, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限
	/* 不卡点直径的上限，但是单上限超过一定大小是，画出的圆部分位置未实心 */

	const int tn_end = (tn <= 1) ? 1 : tn/2;

	int angle, level;
	int old_x1 = INT_MAX, old_y1 = INT_MAX, x1, y1;
	int count = 0;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);

	/* 用画圆的方式模拟粗点 */
	for (level = 1; level <= tn_end; level++) {
		for (angle = 0; angle <= 360; angle ++) {
			/* 注意，系统的坐标轴，0°在圆的最下方 */
			x1 = x + (int)(level * sin(angle * PI / 180));
			y1 = y - (int)(level * cos(angle * PI / 180));

			/* 当半径很小时，角度变化不会引起int型的x1/y1变化，因此加判断语句，避免重复画同一像素点 */
			if (x1 != old_x1 || y1 != old_y1) {
				old_x1 = x1;
				old_y1 = y1;
				hdc_base_point(x1, y1);
				++count;
			}
		}
	}
#if 0
	/* 放开此注释，可以看到一个粗点用了几个像素点组成 */
	cct_gotoxy(0, 41);
	printf("count=%d           ", count);
	getchar();
#endif
}

/* -------------------------------------------------------------------------
	给出下列函数的实现，函数名及参数表不准改动
	1、不需要调用系统的其他有关图形操作的函数
	2、下列函数的实现都基于hdc_base_point/hdc_base_line函数的组合
	3、想一想，是不是所有函数都需要给出独立的实现过程？应该先实现哪些函数？
	4、填充是实现中最复杂的部分
	5、系统的角度与函数参数中的角度含义相差180°
   ------------------------------------------------------------------------- */

/***************************************************************************
  函数名称：
  功    能：画线段
  输入参数：const int x1		：起点的x
            const int y1		：起点的y
			const int x2		：终点的x
			const int y2		：终点的y
			const int thickness	：线段的粗细（有缺省值）
			const int RGB_value	：线段的颜色（有缺省值）
  返 回 值：
  说    明：本函数可以用基于hdc_point的组合（速度慢）
                  也可以用hdc_base_point/hdc_base_line的组合（速度快）
***************************************************************************/
void hdc_line(const int x1, const int y1, const int x2, const int y2, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限
	const int tn_end = (tn <= 1) ? 1 : tn / 2;

	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);//设置颜色

	//double angle = location_to_angle(x1, y1, x2, y2);
	/* 接下来求起始坐标和终止坐标 */
	/*这种情况下有了45度的突出部分，原本是打算计算连线斜率后
	  进行修正，修正凸出部分调试过后反而不如这样美观，且于人
	  眼几乎无影响，遂作罢*/
	for(int i =0; i < tn; i++)
		for (int j = 0; j < tn; j++)
		{
			hdc_base_line(x1 + i - tn_end, y1 + j - tn_end, x2 + i - tn_end, y2 + j - tn_end);
		}
}

/***************************************************************************
  函数名称：
  功    能：给出三点的坐标，画一个三角形
  输入参数：const int x1		：第1个点的x
            const int y1		：第1个点的y
			const int x2		：第2个点的x
			const int y2		：第2个点的y
			const int x3		：第3个点的x
			const int y3		：第3个点的y
			bool filled			：是否需要填充（有缺省值）
			const int thickness	：边的粗细（有缺省值）
			const int RGB_value	：颜色（有缺省值）
  返 回 值：
  说    明：不判断三点是否共线，如果共线，划出一条直线即可
***************************************************************************/
void hdc_triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, bool filled, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限
	const int tn_end = (tn <= 1) ? 1 : tn / 2;
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);//设置颜色

	hdc_line(x1, y1, x2, y2, tn, RGB_value);
	hdc_line(x1, y1, x3, y3, tn, RGB_value);
	hdc_line(x2, y2, x3, y3, tn, RGB_value);
	if (filled)//填充三角形内部
	{
		/* 考察包含此三角形的中最大矩形 */
		for(int i = min(x1, min(x2, x3)); i < max(x1, max(x2, x3)); i++)
			for (int j = min(y1, min(y2, y3)); j < max(y1, max(y2, y3)); j++)
			{
				/* 若点在三角形内 */
				/* 重心法判断点的位置 */
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
  函数名称：
  功    能：给出左上角坐标及宽度、高度，画出一个长方形
  输入参数：const int left_up_x			：左上角x
            const int left_up_y			：左上角y
			const int width				：宽度
			const int high				：高度
			const int rotation_angles	：以左上角为支点，与x轴的旋转倾角（向下转为正）
			bool filled					：是否需要填充（有缺省值）
			const int thickness			：边的粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_rectangle(const int left_up_x, const int left_up_y, const int width, const int high, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限
	const int tn_end = (tn <= 1) ? 1 : tn / 2;
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);//设置颜色

	int right_up_x, right_up_y;//右上角坐标
	int left_down_x, left_down_y;//左下角坐标
	int right_down_x, right_down_y;//右下角坐标
	/* 计算即给坐标赋初值 */
	right_up_x = left_up_x + (int)(width * cos(rotation_angles * PI / 180));
	right_up_y = left_up_y + (int)(width * sin(rotation_angles * PI / 180));
	left_down_x = left_up_x - (int)(high * sin(rotation_angles * PI / 180));
	left_down_y = left_up_y + (int)(high * cos(rotation_angles * PI / 180));
	right_down_x = left_down_x + (int)(width * cos(rotation_angles * PI / 180));
	right_down_y = left_down_y + (int)(width * sin(rotation_angles * PI / 180));
	/* 绘画边框 */
	hdc_line(left_up_x, left_up_y, left_down_x, left_down_y, tn, RGB_value);
	hdc_line(left_up_x, left_up_y, right_up_x, right_up_y, tn, RGB_value);
	hdc_line(left_down_x, left_down_y, right_down_x, right_down_y, tn, RGB_value);
	hdc_line(right_up_x, right_up_y, right_down_x, right_down_y, tn, RGB_value);
	/* 填充内部 */
	if (filled)
	{
		/* 一个矩形有两个三角形 */
		hdc_triangle(left_up_x, left_up_y, left_down_x, left_down_y, right_up_x, right_up_y, true, tn, RGB_value);
		hdc_triangle(right_down_x, right_down_y, left_down_x, left_down_y, right_up_x, right_up_y, true, tn, RGB_value);
	}
}

/***************************************************************************
  函数名称：
  功    能：给出左上角坐标及边长，画出一个长方形
  输入参数：const int left_up_x			：左上角x
			const int left_up_y			：左上角y
			const int length			：边长
			const int rotation_angles	：以左上角为支点，与x轴的旋转倾角（向下转为正）（有缺省值）
			const bool filled			：是否需要填充（有缺省值）
			const int thickness			：边的粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	/* 正方形是特殊的矩形 */
	hdc_rectangle(left_up_x, left_up_y, length, length, rotation_angles, filled, thickness, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一段圆弧
  输入参数：const int point_x		：圆心的x
            const int point_y		：圆心的y
			const int radius		：半径
			const int angle_begin	：起始角度（以圆的最上方为0°，顺时针为正，注意：与系统坐标差了180°!!!）（有缺省值）
			const int angle_end		：结束角度（同上）（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);//设置颜色
	double  angle = (int)angle_begin;
	int old_x1 = INT_MAX, old_y1 = INT_MAX, x1, y1;	
	/* 模仿画线的函数中模仿画圆的方式画圆 */
	while (angle > angle_end)
	{
		angle -= 360;
	}
	for (; angle < angle_end; angle+=0.5)//angle++得到的点不够密集，故缩短其步长
	{
		/* 注意，系统的坐标轴，0°在圆的最下方 */
		x1 = point_x + (int)(radius * sin(angle * PI / 180));
		y1 = point_y - (int)(radius * cos(angle * PI / 180));

		/* 当半径很小时，角度变化不会引起int型的x1/y1变化，因此加判断语句，避免重复画同一像素点 */
		if (x1 != old_x1 || y1 != old_y1) 
		{
			old_x1 = x1;
			old_y1 = y1;
			hdc_point(x1, y1, tn+1, RGB_value);
		}
	}
	
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个扇形
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const int angle_begin	：起始角度（以圆的最上方为0°，顺时针为正，注意：与系统坐标差了180°!!!）（有缺省值）
			const int angle_end		：结束角度（同上）（有缺省值）
			const bool filled		：是否需要填充（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  输入参数：
  返 回 值：
  说    明：当起始/结束角度差值为360的倍数时，不画两条边
***************************************************************************/
void hdc_sector(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const bool filled, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);//设置颜色
	int angle = angle_begin;
	while (angle > angle_end)
	{
		angle -= 360;
	}
	/* 首先画个圆弧 */
	hdc_arc(point_x, point_y, radius, angle, angle_end, tn, RGB_value);
	/* 再画两条半径线 */
	if ((angle_end - angle_begin) % 360 != 0)
	{
		int end_x1 = point_x + (int)(radius * sin(angle_begin * PI / 180));
		int end_y1 = point_y - (int)(radius * cos(angle_begin * PI / 180));
		int end_x2 = point_x + (int)(radius * sin(angle_end * PI / 180));
		int end_y2 = point_y - (int)(radius * cos(angle_end * PI / 180));
		hdc_line(point_x, point_y, end_x1, end_y1, tn, RGB_value);
		hdc_line(point_x, point_y, end_x2, end_y2, tn, RGB_value);
	}
	if (filled)//填充扇形
	{
		double tmp_angle = (double)angle_begin;
		while (tmp_angle > angle_end)
		{
			tmp_angle -= 360;
		}
		for (;tmp_angle < angle_end; tmp_angle += 0.5)//angle++得到的点不够密集，故缩短其步长
		{
			/* 注意，系统的坐标轴，0°在圆的最下方 */
			int x1 = point_x + (int)(radius * sin(tmp_angle * PI / 180));
			int y1 = point_y - (int)(radius * cos(tmp_angle * PI / 180));
			//hdc_base_line(x1, y1, point_x, point_y);
			hdc_line(x1, y1, point_x, point_y, 3 , RGB_value);//填充部分宽度自定
		}
		
	}
}

/***************************************************************************
  函数名称：
  功    能：按照给出的参数画一个圆
  输入参数：const int point_x		：圆心的x
			const int point_y		：圆心的y
			const int radius		：半径
			const bool filled		：是否需要填充（有缺省值）
			const int thickness		：粗细（有缺省值）
			const int RGB_value		：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_circle(const int point_x, const int point_y, const int radius, const bool filled, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);//设置颜色
	hdc_arc(point_x, point_y, radius, 0, 360, tn, RGB_value);
	if (filled)
	{
		/* 考察包含这个圆形的最小矩形 */
		/* 若点在圆内(用距离公式即可) */
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
  函数名称：
  功    能：按照给出的参数画一个椭圆
  输入参数：const int point_x			：圆心的x
			const int point_y			：圆心的y
			const int radius_a			：平行于X轴的半径
			const int radius_b			：平行于Y轴的半，径
			const int rotation_angles	：以圆心为支点，与x轴的旋转倾角（向下转为正）（有缺省值）
			const bool filled			：是否需要填充（有缺省值）
			const int thickness			：粗细（有缺省值）
			const int RGB_value			：颜色（有缺省值）
  返 回 值：
  说    明：
***************************************************************************/
void hdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//处理下限
	if (RGB_value != INVALID_RGB)
		hdc_set_pencolor(RGB_value);//设置颜色
	/* 采用类似填充的方法，考察包含椭圆的最小矩形，若点在椭圆上，采用对称画法调用hdc_point绘制 */
	/* 使用椭圆的标准方程判断 */
	int max_square = max(radius_a, radius_b);
	for(int i = point_x - max_square; i <= point_x + max_square;i++)
		for (int j = (point_y - max_square); j <= point_y + max_square; j++)
		{
			/* 旋转转换成正交坐标系上的点 */

			double location_x = (i - point_x) * cos(rotation_angles * PI / 180) + (j - point_y) * sin(rotation_angles * PI / 180);
			double location_y = (j - point_y) * cos(rotation_angles * PI / 180) - (i - point_x) * sin(rotation_angles * PI / 180);
			double tmp1 = (double)radius_b * (double)radius_b * location_x * location_x;
			double tmp2 = (double)radius_a * (double)radius_a * location_y * location_y;
			double tmp3 = (double)radius_a * (double)radius_a * (double)radius_b * (double)radius_b;
			/*因为x, y在 + 1的过程中会存在一定误差，就是因为步长是一而椭圆上的点的坐标不一定就是正好全
			正在整数上，所以进行了一定修正 */
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
