/*王浩 信07 2152041*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <windows.h> //取系统时间
using namespace std;

int main()
{
	LARGE_INTEGER tick, begin, end;

	QueryPerformanceFrequency(&tick);	//获得计数器频率
	QueryPerformanceCounter(&begin);	//获得初始硬件计数器计数

	int a, b, c;
	int n = 0;
	for (a = 111; a <= 651; a++)
	{
		for (b = a + 1; b < 1000; b++)
		{
			if (a / 10 % 10 != 0 && a % 10 != 0 && b / 10 % 10 != 0 && b % 10 != 0 && a / 100 % 10 != a / 10 % 10 && a / 100 % 10 != a % 10 && a / 100 % 10 != b / 100 % 10 && a / 100 % 10 != b / 10 % 10 && a / 100 % 10 != b % 10 && a / 10 % 10 != a % 10 && a / 10 % 10 != b / 100 % 10 && a / 10 % 10 != b / 10 % 10 && a / 10 % 10 != b % 10)
			{
				c = 1953 - a - b;
				if (c > b && c / 10 % 10 != 0 && c % 10 != 0 && c < 1000 && a / 100 % 10 != a / 10 % 10 && a / 100 % 10 != a % 10 && a / 100 % 10 != b / 100 % 10 && a / 100 % 10 != b / 10 % 10 && a / 100 % 10 != b % 10 && a / 10 % 10 != a % 10 && a / 10 % 10 != b / 100 % 10 && a / 10 % 10 != b / 10 % 10 && a / 10 % 10 != b % 10 && a / 100 % 10 != a / 10 % 10 && a / 100 % 10 != a % 10 && a / 100 % 10 != b / 100 % 10 && a / 100 % 10 != b / 10 % 10 && a / 100 % 10 != b % 10 && a / 100 % 10 != c / 100 % 10 && a / 100 % 10 != c / 10 % 10 && a / 100 % 10 != c % 10 && a / 10 % 10 != a % 10 && a / 10 % 10 != b / 100 % 10 && a / 10 % 10 != b / 10 % 10 && a / 10 % 10 != b % 10 && a / 10 % 10 != c / 100 % 10 && a / 10 % 10 != c / 10 % 10 && a / 10 % 10 != c % 10 && b / 100 % 10 != b / 10 % 10 && b / 100 % 10 != b % 10 && b / 100 % 10 != c / 100 % 10 && b / 100 % 10 != c / 10 % 10 && b / 100 % 10 != c % 10 && b / 10 % 10 != b % 10 && b / 10 % 10 != c / 100 % 10 && b / 10 % 10 != c / 10 % 10 && b / 10 % 10 != c % 10 && b % 10 != c / 100 % 10 && b % 10 != c / 10 % 10 && b % 10 != c % 10 && c / 100 % 10 != c / 10 % 10 && c / 100 % 10 != c % 10 && c / 10 % 10 != c % 10)
				{
					++n;
					cout<<"No."<<setiosflags(ios::right)<<setw(3)<<n<<" : "<<a<<" + "<<b<<" + "<<c<<" = 1953\n" ;
				}
			}
		}
	}

	QueryPerformanceCounter(&end);		//获得终止硬件计数器计数

	cout << "计数器频率 : " << tick.QuadPart << "Hz" << endl;
	cout << "计数器计数 : " << end.QuadPart - begin.QuadPart << endl;
	cout << setiosflags(ios::fixed) << setprecision(6) << double(end.QuadPart - begin.QuadPart) / tick.QuadPart << "秒" << endl;

	return 0;
}
