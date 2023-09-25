/*王浩 信07 2152041*/
#include<iostream>
#include<iomanip>
#include<cmath>

using namespace std;

int main()
{
    int a, b,c;
    float d,pi=3.14159f;
    cout << "请输入三角形的两边及其夹角(角度)\n";
    cin >> a >> b >> c;
    d =   a * b * sin(c*pi/180)/2;
    cout << "三角形面积为 : " << fixed<<setprecision(3)<<d << endl;

    return 0;
} 