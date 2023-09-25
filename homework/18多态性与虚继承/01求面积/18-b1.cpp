/* 2152041 �ƿ� ���� */
#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.14159

class Shape {
protected:
    //������Ҫ������Ӧ�ĳ�Ա��Ҳ����Ϊ��
public:
    virtual void ShapeName() = 0; //�˾䲻׼��
    //������Ҫ������Ӧ�ĳ�Ա��Ҳ����Ϊ��
    virtual double area() const;
};
double Shape::area()const
{
    return 0;
}
//�˴����������Ķ��弰ʵ��
class Circle :virtual public Shape {
protected:
    double radius = 0;
public:
    Circle(double rad);
    virtual void ShapeName();
    virtual double area() const;
};

void Circle::ShapeName()
{
    cout << "Circle" << endl;
}

Circle::Circle(double rad)
{
    if (rad > 0)
        radius = rad;
}

double Circle::area() const
{
    return PI * radius * radius;
}

class Square :virtual public Shape {
protected:
    double edge = 0;
public:
    Square(double ed);
    virtual void ShapeName();
    virtual double area() const;
};

void Square::ShapeName()
{
    cout << "Square" << endl;
}

Square::Square(double ed)
{
    if (ed > 0)
        edge = ed;
}

double Square::area() const
{
    return edge * edge;
}

class Rectangle :virtual public Shape {
protected:
    double length = 0;
    double width  = 0;
public:
    Rectangle(double length, double width);
    virtual void ShapeName();
    virtual double area() const;
};

Rectangle::Rectangle(double len, double wid)
{
    if (len > 0 && wid > 0)
    {
        length = len;
        width = wid;
    }
}

void Rectangle::ShapeName()
{
    cout << "Rectangle" << endl;
}

double Rectangle::area()const
{
    return length * width;
}

class Trapezoid :virtual public Shape {
protected:
    double topline = 0;
    double baseline = 0;
    double height = 0;
public:
    Trapezoid(double, double ,double);
    virtual void ShapeName();
    virtual double area() const;
};

Trapezoid::Trapezoid(double top, double base,double hei)
{
    if (hei > 0 && top > 0 && base > 0)
    {
        topline = top;
        baseline = base;
        height = hei;
    }
}

void Trapezoid::ShapeName()
{
    cout << "Trapezoid" << endl;
}

double Trapezoid::area()const
{
    return (topline + baseline) * height * 0.5;
}

class Triangle :virtual public Shape {
protected:
    double a = 0;
    double b = 0;
    double c = 0;
public:
    Triangle(double, double, double);
    virtual void ShapeName();
    virtual double area() const;
};

Triangle::Triangle(double a1, double b1, double c1)
{
    int is_Triangle = (a1 + b1 > c1) && (a1 + c1 > b1) && (b1 + c1 > a1);
    if (a1 > 0 && b1 > 0 && c1 > 0 && is_Triangle)
    {
        a = a1;
        b = b1;
        c = c1;
    }
}

void Triangle::ShapeName()
{
    cout << "Triangle" << endl;
}

double Triangle::area()const
{
    double p = (a + b + c) * 0.5;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

/* -- �滻����� -- ���в�Ҫ���κθĶ� -- ���в�Ҫɾ�� -- �ڱ��е����治Ҫ�����κ��Լ�����䣬��ҵ�ύ��ӱ��п�ʼ�ᱻ�滻 -- �滻����� -- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
    if (1) {
        Circle    c1(5.2);           //�뾶5.2�����<=0�����Ϊ0��
        Square    s1(5.2);           //�߳�5.2�����<=0�����Ϊ0��
        Rectangle r1(5.2, 3.7);      //�����������һ<=0�����Ϊ0��
        Trapezoid t1(2.3, 4.4, 3.8); //�ϵס��µס��ߣ������һ<=0�����Ϊ0��
        Triangle  t2(3, 4, 5);       //���߳��ȣ������һ<=0�򲻹��������Σ����Ϊ0��
        Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };

        int   i;
        for (i = 0; i < 5; i++) {
            s[i]->ShapeName(); //�ֱ��ӡ��ͬ��״ͼ�ε����ƣ���Ӣ�ľ��ɣ�
            cout << s[i]->area() << endl; //�ֱ��ӡ��ͬ��״ͼ�ε����
            cout << endl;
        }
    }

    if (1) {
        Circle    c1(-1);           //�뾶5.2�����<=0�����Ϊ0��
        Square    s1(-1);           //�߳�5.2�����<=0�����Ϊ0��
        Rectangle r1(5.2, -1);      //�����������һ<=0�����Ϊ0��
        Trapezoid t1(2.3, -1, 3.8); //�ϵס��µס��ߣ������һ<=0�����Ϊ0��
        Triangle  t2(3, 4, -1);       //���߳��ȣ������һ<=0�򲻹��������Σ����Ϊ0��
        Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };

        cout << "============" << endl;
        int   i;
        for (i = 0; i < 5; i++) {
            s[i]->ShapeName(); //�ֱ��ӡ��ͬ��״ͼ�ε����ƣ���Ӣ�ľ��ɣ�
            cout << s[i]->area() << endl; //�ֱ��ӡ��ͬ��״ͼ�ε����
            cout << endl;
        }
    }

    return 0;
}
