/*���� ��07 2152041*/
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	double pi = 3.14159, a, b;
	cout << "������뾶�͸߶�\n";
	cin >> a >> b;
	cout << "Բ�ܳ�    :" << setiosflags(ios::fixed) << setprecision(2) << 2 * pi * a << endl;
	cout << "Բ���    :" << setiosflags(ios::fixed) << setprecision(2) << pi * a * a << endl;
	cout << "Բ������:" << setiosflags(ios::fixed) << setprecision(2) << 4 * pi * a * a << endl;
	cout << "Բ�����  :" << setiosflags(ios::fixed) << setprecision(2) << 4 * pi * a * a * a / 3 << endl;
	cout << "Բ�����  :" << setiosflags(ios::fixed) << setprecision(2) << pi * a * a * b << endl;

	 return 0;
}





















