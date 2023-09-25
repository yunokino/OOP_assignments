/*2152041 计科 王浩*/
#include <iostream>
#include<cmath>
using namespace std;

double definite_integration(double fun(double), double low, double high, int n)
{
	double step = (high - low) / n;
	double total = 0;
	for (int i = 0; i < n; i++)
	{
		total += fun(low + (i+1) * step) * step;
	}
	return total;
}

int main()
{
	int n;
	double low, high, value;
	//sin
	cout << "请输入sinxdx的下限、上限及区间划分数量" << endl;
	cin >> low >> high >> n;

	value = definite_integration(sin, low, high, n);
	cout << "sinxdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;
	//cos
	cout << "请输入cosxdx的下限、上限及区间划分数量" << endl;
	cin >> low >> high >> n;
	value = definite_integration(cos, low, high, n);
	cout << "cosxdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;
	//e^x
	cout << "请输入e^xdx的下限、上限及区间划分数量" << endl;
	cin >> low >> high >> n;

	value = definite_integration(exp, low, high, n);
	cout << "e^xdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;

	return 0;
}