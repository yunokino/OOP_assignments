/* 2152041 ���� ��07 */
#include <iostream>
#include <cmath>
using namespace std;

class triangle;  //�����ǰ������˼��һ�£����������Ŀ����Ϊʲô
class point {
private:
	int x;
	int y;
public:
	/* �������ڴ����һ����Ա����������1����,Ҫ������ʵ�� */
	int set(int p_x, int p_y,int x_location = 0,int value=1)
	{
		if (value)
		{
			x = p_x;
			y = p_y;
			return 0;
		}
		else
		{
			if (x_location)
				return x;
			else
				return y;
		}
	}
	/* ������������Ǹ���Ա�����⣬������������κε����ݳ�Ա�ͳ�Ա�����������Ը�����Ҫ����������� */
};

class triangle {
private:
	point p1;
	point p2;
	point p3;
public:
	/* ������Ҫ������Ӧ���������area����(�β�Ϊ�գ���׼��)��Ҫ����������ܹ��������Σ��򷵻���������򷵻� -1 */
	double area()
	{
		int x1, x2, x3, y1, y2, y3, x = 0, y = 0;//x��y������������βΣ�ʵ��û���κ�����
		x1 = p1.set(x, y, 1, 0);
		y1 = p1.set(x, y, 0, 0);
		x2 = p2.set(x, y, 1, 0);
		y2 = p2.set(x, y, 0, 0);
		x3 = p3.set(x, y, 1, 0);
		y3 = p3.set(x, y, 0, 0);
		
		double size = fabs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2;
		if (size != 0)
			return size;
		else
			return -1;
	}
	/* ���캯�� */
	triangle(int p1_x, int p1_y, int p2_x, int p2_y, int p3_x, int p3_y)
	{
		/* ��p1/p2/p3������ֱ�x,y����ֵ */
		p1.set(p1_x, p1_y);
		p2.set(p2_x, p2_y);
		p3.set(p3_x, p3_y);
	}
	/* ���Զ�����Ҫ�ĳ�Ա�������������ޣ��������ڷ�ʽʵ�֣�������������ݳ�Ա */

};

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������׼��
***************************************************************************/
int main()
{
	if (1) {
		triangle tr(0, 0, 0, 1, 1, 0);  //������Ϊ(0,0) (0,1) (1,0)�������
		cout << "���������Ӧ���ǣ�0.5��ʵ���ǣ�" << tr.area() << endl;
	}

	if (1) {
		triangle tr(0, 2, -1, -1, 1, -1);  //������Ϊ(0,2) (-1,-1) (1,-1)�������
		cout << "���������Ӧ���ǣ�3��  ʵ���ǣ�" << tr.area() << endl;
	}

	if (1) {
		triangle tr(5, 5, -3, 1, 9, -2);  //������Ϊ(5,5) (-3,1) (9,-2)�������
		cout << "���������Ӧ���ǣ�36�� ʵ���ǣ�" << tr.area() << endl;
	}

	if (1) {
		triangle tr(0, 0, 1, 1, 2, 2);  //���㹲��
		cout << "���������Ӧ���ǣ�-1�� ʵ���ǣ�" << tr.area() << endl;
	}

	return 0;
}
