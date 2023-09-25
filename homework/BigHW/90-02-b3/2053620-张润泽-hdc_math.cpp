/* 2053620 �ƿ� ������ */
#include <conio.h>  
#include <math.h>
using namespace std;

#include "../include/cmd_hdc_tools.h"

//�ο������꣨����·��ߵ����ģ�
const int reference_center_x = 150;
const int reference_center_y = 650;
//�ο��߰볤
const double radius = sqrt(5) * 50;
// 2\1\����5-�����ε���С�� - ƫ��ǣ��ײ��ο�ֱ������ֱ�ļн�.
const double reference_angle = 26.565-0.05*13;
// ���ο��ߵ�x��ƫ��������Ҳ�
const int reference_cross_x = 500; 
// ���ο��ߵ�y��ƫ��������²�
const int reference_cross_y = -50;
// ���������������ο��ߵĸ߲��Ϊ��
const int reference_height_above = 400; 
// �ߵĵȷ���
const int N = 15;

#define ANGLE_RESTRICT  1  // ת������

/*
	��ѧ�������ƣ�ֱ���� - ˫�������� - ���� ���ο��ߣ���ͶӰ�ߣ�.
	������ʽ����Ť�� �� a , ��ƽ���� d , �������� c , �˳�.������ת�����Ƹ�Ϊ0�����ɷſ������鳤��������.
	ע���ܵ������ܵ��µĻ����ٶȵ�Ӱ�죬�ڵ��������³������ܵ����ڲ��ߵ���ʱ��������Ҫ���鼫�µ�˿�������Ʋ������壡
 */
void hdc_draw_Mathematical_curve_2053620()
{
	hdc_cls();

	// �˸���׼�������
	double left_lower_x1, left_lower_y1, left_lower_x2, left_lower_y2;
	double right_lower_x1, right_lower_y1, right_lower_x2, right_lower_y2;
	double left_high_x1, left_high_y1, left_high_x2, left_high_y2;
	double right_high_x1, right_high_y1, right_high_x2, right_high_y2;

	// ����ʱ��Ҫ�õ��ı���
	double x1, x2, y1, y2;
	double my_angle = 0;
	char ch;
	
	while (1)
	{
		hdc_cls();
		cct_showstr(2, 1, "<��Ť��������>", 7, 0);
		cct_showstr(2, 2, "[�� a ��ƽ���� d �������� c �˳�] ", 7, 0);

		// �ײ�ͶӰ
		left_lower_x1 = reference_center_x - radius * sin(reference_angle + my_angle);
		left_lower_y1 = reference_center_y - radius * cos(reference_angle + my_angle);
		left_lower_x2 = reference_center_x + radius * sin(reference_angle + my_angle);
		left_lower_y2 = reference_center_y + radius * cos(reference_angle + my_angle);
		right_lower_x1 = left_lower_x1 + reference_cross_x;
		right_lower_y1 = left_lower_y1 + reference_cross_y;
		right_lower_x2 = left_lower_x2 + reference_cross_x;
		right_lower_y2 = left_lower_y2 + reference_cross_y;
		
		hdc_line((int)left_lower_x1, (int)left_lower_y1, (int)left_lower_x2, (int)left_lower_y2, 1);
		hdc_line((int)right_lower_x1, (int)right_lower_y1, (int)right_lower_x2, (int)right_lower_y2, 1);
		hdc_line((int)left_lower_x1, (int)left_lower_y1, (int)right_lower_x1, (int)right_lower_y1, 1);
		hdc_line((int)left_lower_x2, (int)left_lower_y2, (int)right_lower_x2, (int)right_lower_y2, 1);

		// ��������
		left_high_x1 = left_lower_x1;
		left_high_y1 = left_lower_y1 - reference_height_above;
		left_high_x2 = left_lower_x2;
		left_high_y2 = left_lower_y2 - reference_height_above;
		right_high_x1 = right_lower_x1;
		right_high_y1 = right_lower_y2 - reference_height_above;
		right_high_x2 = right_lower_x2;
		right_high_y2 = right_lower_y1 - reference_height_above;

		// �ɼ�����
		hdc_line((int)left_high_x1, (int)left_high_y1, (int)left_high_x2, (int)left_high_y2, 3);
		hdc_line((int)right_high_x1, (int)right_high_y1, (int)right_high_x2, (int)right_high_y2, 3 - ANGLE_RESTRICT);
		hdc_line((int)left_high_x2, (int)left_high_y2, (int)right_high_x2, (int)right_high_y2, 3);
		// Զ��ϸ��
		hdc_line((int)left_high_x1, (int)left_high_y1, (int)right_high_x1, (int)right_high_y1, 1);

		// �ڲ�ϸ��
		for (int i = 1; i < N; ++i)
		{
			x1 = left_high_x1 + i * (left_high_x2 - left_high_x1) / N;
			y1 = left_high_y1 + i * (left_high_y2 - left_high_y1) / N;
			x2 = right_high_x1 + i * (right_high_x2 - right_high_x1) / N;
			y2 = right_high_y1 + i * (right_high_y2 - right_high_y1) / N;
			hdc_line((int)x1, (int)y1, (int)x2, (int)y2, 1);

			x1 = left_high_x2 + i * (right_high_x2 - left_high_x2) / N;
			y1 = left_high_y2 + i * (right_high_y2 - left_high_y2) / N;
			x2 = left_high_x1 + i * (right_high_x1 - left_high_x1) / N;
			y2 = left_high_y1 + i * (right_high_y1 - left_high_y1) / N;
			hdc_line((int)x1, (int)y1, (int)x2, (int)y2, 1);
		}

		// Ť������
		int loop = 1;
		while (loop)
		{
			ch = _getch();
			switch (ch)
			{
				case 'a':
					#if ANGLE_RESTRICT
					if (my_angle >= 0.05 * 6) // �������ת�ǣ�ת�����Ƹ�Ϊ0�ɷſ����ƣ����鳤������
						continue;
					#endif
					my_angle += 0.05;
					loop = 0;
					break;
				case 'd':
					#if ANGLE_RESTRICT
					if (my_angle <= -0.05 * 9) // �������ת�ǣ�ת�����Ƹ�Ϊ0�ɷſ����ƣ����鳤������
						continue;
					#endif
					my_angle -= 0.05;
					loop = 0;
					break;
				case 'c':  //��C�˳�
					return;
				default:
					continue;
					break;
			}
		}
	}
}
	