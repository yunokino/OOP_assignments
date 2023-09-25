/*王浩 信07 2152041*/
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	double pi = 3.14159, a, b;
	cout << "请输入半径和高度\n";
	cin >> a >> b;
	cout << "圆周长    :" << setiosflags(ios::fixed) << setprecision(2) << 2 * pi * a << endl;
	cout << "圆面积    :" << setiosflags(ios::fixed) << setprecision(2) << pi * a * a << endl;
	cout << "圆球表面积:" << setiosflags(ios::fixed) << setprecision(2) << 4 * pi * a * a << endl;
	cout << "圆球体积  :" << setiosflags(ios::fixed) << setprecision(2) << 4 * pi * a * a * a / 3 << endl;
	cout << "圆柱体积  :" << setiosflags(ios::fixed) << setprecision(2) << pi * a * a * b << endl;

	 return 0;
}





















