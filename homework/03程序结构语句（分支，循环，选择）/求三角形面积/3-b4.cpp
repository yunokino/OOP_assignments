/*���� ��07 2152041*/
#include<iostream>
#include<iomanip>
#include<cmath>

using namespace std;

int main()
{
    int a, b,c;
    float d,pi=3.14159f;
    cout << "�����������ε����߼���н�(�Ƕ�)\n";
    cin >> a >> b >> c;
    d =   a * b * sin(c*pi/180)/2;
    cout << "���������Ϊ : " << fixed<<setprecision(3)<<d << endl;

    return 0;
} 