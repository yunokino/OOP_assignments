/* 2152041 计科 王浩 */
#include <iostream>
#include <cmath>
using namespace std;

/* 从此处到标记替换行之间，给出各种类的定义及实现
	1、不允许全部变量（不含const和#define）
	2、不允许添加其它系统头文件
*/
class integral {
protected:
	double low = 0;
	double high = 0;
	int n = 0;
	int type = 0;//1为sin，2为cos，3为exp
public:
	friend istream& operator>>(istream& in, integral& value);
	virtual double value()const = 0;
};

istream& operator>>(istream& in, integral& value)
{
	int loop = 1;
	do
	{
		cout << "请输入";
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
		cout<<"的下限、上限及区间划分数量" << endl;
		in >> value.low >> value.high >> value.n;
		if (in.fail())
		{
			cout << "数据输入错误，请重新输入" << endl;
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
/* -- 替换标记行 -- 本行不要做任何改动 -- 本行不要删除 -- 在本行的下面不要加入任何自己的语句，作业提交后从本行开始会被替换 -- 替换标记行 -- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：fun_integral不准动，思考一下，integral应如何定义
***************************************************************************/
void fun_integral(integral& fRef)
{
	cin >> fRef;	//输入上下限、划分数
	cout << fRef.value() << endl;
	return;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数不准动
***************************************************************************/
int main()
{
	integral_sin s1;
	integral_cos s2;
	integral_exp s3;

	fun_integral(s1); //计算sinxdx的值
	fun_integral(s2); //计算cosxdx的值
	fun_integral(s3); //计算expxdx的值

	return 0;
}

//注：矩形计算取右值，输出为正常double格式

