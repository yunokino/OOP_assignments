/*���� ��07 2152041*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	double a,b,x;
	bool Y = true;
	cout<<"������aֵ" << endl;
	cin >> a;
	b = a / 2;
	while(Y)
	{
		x = (b + a / b) / 2;
		if (fabs(x-b) < 0.00001)
			break;
		b = x;
	}
	cout<< a << "��ƽ����="<<setiosflags(ios::fixed) << setprecision(3) <<x<<endl;
	return 0;
}