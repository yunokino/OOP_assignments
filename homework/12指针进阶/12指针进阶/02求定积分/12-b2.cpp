/*2152041 �ƿ� ����*/
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
	cout << "������sinxdx�����ޡ����޼����仮������" << endl;
	cin >> low >> high >> n;

	value = definite_integration(sin, low, high, n);
	cout << "sinxdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;
	//cos
	cout << "������cosxdx�����ޡ����޼����仮������" << endl;
	cin >> low >> high >> n;
	value = definite_integration(cos, low, high, n);
	cout << "cosxdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;
	//e^x
	cout << "������e^xdx�����ޡ����޼����仮������" << endl;
	cin >> low >> high >> n;

	value = definite_integration(exp, low, high, n);
	cout << "e^xdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;

	return 0;
}