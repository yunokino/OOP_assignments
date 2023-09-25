/* 计科 2152041 王浩 */
#include<iostream>
#include <conio.h>  
#include <math.h>
#include"../include/cmd_hdc_tools.h"
using namespace std;

#define PI 3.14159
const int start_x = 300;
const int start_y = 200;
/* 心脏线:据说是来自于笛卡尔的一个爱情故事，真伪不知，
   不过确实有种美感, 当然把它看成桃子或者其他的不好说的也很像... */
void hdc_draw_Mathematical_curve_2152041()
{
	hdc_cls();
	int radius, angle;
	int color;
	int count = 0;
	cct_showstr(0, 2, "请选择心脏颜色:1、热情红色 2、冷酷绿色 3、深邃蓝色 4、质朴黑色 5、五颜六色", 7, 0);
	cout << endl;
	cin >> color;

	while (cin.fail() || color < 1 || color > 5)
	{
		count++;
		cin.clear();
		cin.ignore(65536, '\n');
		cct_showstr(0, 2 + count, "呐呐，用户君，我说啊，你刚才有在故意输错吧", 7, 0);
		count++;
		cct_showstr(0, 2 + count, "请选择心脏颜色:1、热情红色 2、冷酷绿色 3、深邃蓝色 4、质朴黑色 5、五颜六色", 7, 0);
		cout << endl;
		count++;
		cin >> color;
		count++;
	}
	hdc_cls();
	switch (color)
	{
	case 1:
		hdc_set_pencolor(255, 0, 0);
		break;
	case 2:
		hdc_set_pencolor(0, 255, 0);
		break;
	case 3:
		hdc_set_pencolor(0, 0, 255);
		break;
	case 4:
		hdc_set_pencolor(0, 0, 0);
		break;
	default:
		break;
	}
	for (angle = 0; angle <= 360; angle++)
	{
		radius = (int)(200 * (1 + sin(angle * PI / 180)));
		int location_x = (int)(start_x + radius * cos(angle * PI / 180));
		int location_y = (int)(start_y + radius * sin(angle * PI / 180));
		if (color == 5)
		{
			hdc_set_pencolor(rand() % 255, rand() % 255, rand() % 255);
		}
		hdc_point(location_x, location_y, 10);
	}
}