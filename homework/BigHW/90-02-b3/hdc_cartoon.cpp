/* 计科 2152041 王浩 */
#include<iostream>
#include <conio.h>  
#include <math.h>
#include <Windows.h>
#include"../include/cmd_hdc_tools.h"
using namespace std;

#define Pi 3.14159

static const int color_pink =  RGB(253, 237, 240);
static const int color_brown = RGB(165, 160, 162);

static void hand(const int base_x, const int base_y)
{
	hdc_arc(base_x - 80, base_y + 20, 20, 90, 270, 5, color_brown);
	hdc_arc(base_x + 80, base_y + 20, 20, 90, 270, 5, color_brown);
}

static void heart(const int base_x, const int base_y)
{
	/* 大的心把小兔子包裹 */
	for (int angle = 0; angle <= 360; angle++)
	{
		int radius = (int)(200 * (1 + sin(angle * Pi / 180)));
		int location_x = (int)(base_x + radius * cos(angle * Pi / 180));
		int location_y = (int)(base_y - 185 + radius * sin(angle * Pi / 180));
		hdc_point(location_x, location_y, 10, color_brown);
	}
	/* 中间有小兔子的小心 */
	for (int angle = 0; angle <= 360; angle++)
	{
		int radius = (int)(30 * (1 + sin(angle * Pi / 180)));
		int location_x = (int)(base_x + radius * cos(angle * Pi / 180));
		int location_y = (int)(base_y + 30 + radius * sin(angle * Pi / 180));
		hdc_point(location_x, location_y, 10, color_brown);
	}
	/* 填充小心 */
	hdc_circle(base_x, base_y + 60, 25, true, 3, color_pink);
	hdc_circle(base_x - 16, base_y + 38, 10, true, 3, color_pink);
	hdc_circle(base_x - 20, base_y + 40, 10, true, 3, color_pink);
	hdc_circle(base_x - 23, base_y + 45, 10, true, 3, color_pink);
	hdc_circle(base_x - 25, base_y + 50, 10, true, 3, color_pink);
	hdc_circle(base_x - 22, base_y + 59, 10, true, 3, color_pink);
	hdc_circle(base_x + 16, base_y + 38, 10, true, 3, color_pink);
	hdc_circle(base_x + 20, base_y + 40, 10, true, 3, color_pink);
	hdc_circle(base_x + 23, base_y + 45, 10, true, 3, color_pink);
	hdc_circle(base_x + 25, base_y + 50, 10, true, 3, color_pink);
	hdc_circle(base_x + 22, base_y + 59, 10, true, 3, color_pink);
}

static void eyes(const int base_x, const int base_y)
{
	hdc_ellipse(base_x - 40, base_y - 100, 7, 10, 0, true, 4, color_brown);
	hdc_ellipse(base_x + 40, base_y - 100, 7, 10, 0, true, 4, color_brown);
}

static void cheek(const int base_x, const int base_y)
{
	hdc_circle(base_x - 60, base_y - 60, 5, true, 3, color_pink);
	hdc_circle(base_x + 60, base_y - 60, 5, true, 3, color_pink);
}

static void head(const int base_x, const int base_y)
{
	hdc_arc(base_x, base_y - 30, 150, -55, 55, 6, color_brown);
}

static void body(const int base_x, const int base_y)
{
	hdc_arc(base_x + 165, base_y + 40, 300, 245, 285, 6, color_brown);
	hdc_arc(base_x - 150, base_y + 90, 300, 65, 105, 6, color_brown);
}

static void ear(const int base_x, const int base_y)
{
	hdc_arc(base_x - (int)(150 * cos(55 * Pi / 180)), base_y - 50, 75, -90, -30, 6, color_brown);
	hdc_arc(base_x + (int)(150 * cos(55 * Pi / 180)), base_y - 50, 75, 30, 90, 6, color_brown);
	hdc_arc(base_x - 140, base_y - 45, 20, 120, 270, 5, color_brown);
	hdc_arc(base_x + 140, base_y - 45, 20, 90, 240, 5, color_brown);
}

static void mouth(const int base_x, const int base_y)
{
	hdc_arc(base_x , base_y - 40, 20, 115, 245, 4, color_pink);
}
/* 大一上高程的时候从刘孔阳助教姐姐那里收的表情包，但是做了对称处理，
   可爱滴捏 */
void hdc_draw_cartoon_2152041(const int base_x, const int base_y)
{
	hdc_cls();
	mouth(base_x, base_y);
	eyes(base_x, base_y);
	cheek(base_x, base_y);
	head(base_x, base_y);
	hand(base_x, base_y);
	ear(base_x, base_y);
	body(base_x, base_y);
	heart(base_x, base_y);

}