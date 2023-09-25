/* 2152041 �ƿ� ���� */
#include <iostream>
#include <cmath>
using namespace std;

/* �Ӵ˴�������滻��֮�䣬����������Ķ��弰ʵ��
	1��������ȫ������������const��#define��
	2���������������ϵͳͷ�ļ�
*/
class integral {
protected:
	double low = 0;
	double high = 0;
	int n = 0;
	int type = 0;//1Ϊsin��2Ϊcos��3Ϊexp
public:
	friend istream& operator>>(istream& in, integral& value);
	virtual double value()const = 0;
};

istream& operator>>(istream& in, integral& value)
{
	int loop = 1;
	do
	{
		cout << "������";
		switch (value.type)
		{
		case 1:
			cout << "sinxdx";
			break;
		case 2:
			cout << "cosxdx";
			break;
		case 3:
			cout << "e^xdx";
			break;
		default:
			break;
		}
		cout<<"�����ޡ����޼����仮������" << endl;
		in >> value.low >> value.high >> value.n;
		if (in.fail())
		{
			cout << "���������������������" << endl;
			in.clear();
			in.ignore(65536, '\n');
			continue;
		}
		loop = 0;
	} while (loop);
	return in;
}

double integral::value()const
{
	return 0;
}

class integral_sin:public integral {
public:
	integral_sin();
	virtual double value()const;
};

integral_sin::integral_sin()
{
	type = 1;
}

double integral_sin::value()const
{
	double step = (high - low) / n;
	double total = 0;
	for (int i = 0; i < n; i++)
	{
		total += sin(low + (i + 1) * step) * step;
	}
	cout << "sinxdx[" << low << "~" << high << "/n=" << n << "] : " << total << endl;
	return total;
}

class integral_cos :public integral {
public:
	integral_cos();
	virtual double value()const;
};

integral_cos::integral_cos()
{
	type = 2;
}

double integral_cos::value()const
{
	double step = (high - low) / n;
	double total = 0;
	for (int i = 0; i < n; i++)
	{
		total += cos(low + (i + 1) * step) * step;
	}
	cout << "cosxdx[" << low << "~" << high << "/n=" << n << "] : " << total << endl;
	return total;
}

class integral_exp :public integral {
public:
	integral_exp();
	virtual double value()const;
};

integral_exp::integral_exp()
{
	type = 3;
}

double integral_exp::value()const
{
	double step = (high - low) / n;
	double total = 0;
	for (int i = 0; i < n; i++)
	{
		total += exp(low + (i + 1) * step) * step;
	}
	cout << "e^xdx[" << low << "~" << high << "/n=" << n << "] : " << total << endl;
	return total;
}
/* -- �滻����� -- ���в�Ҫ���κθĶ� -- ���в�Ҫɾ�� -- �ڱ��е����治Ҫ�����κ��Լ�����䣬��ҵ�ύ��ӱ��п�ʼ�ᱻ�滻 -- �滻����� -- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����fun_integral��׼����˼��һ�£�integralӦ��ζ���
***************************************************************************/
void fun_integral(integral& fRef)
{
	cin >> fRef;	//���������ޡ�������
	cout << fRef.value() << endl;
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������׼��
***************************************************************************/
int main()
{
	integral_sin s1;
	integral_cos s2;
	integral_exp s3;

	fun_integral(s1); //����sinxdx��ֵ
	fun_integral(s2); //����cosxdx��ֵ
	fun_integral(s3); //����expxdx��ֵ

	return 0;
}

//ע�����μ���ȡ��ֵ�����Ϊ����double��ʽ

