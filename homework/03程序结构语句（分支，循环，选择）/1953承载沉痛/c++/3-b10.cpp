/*���� ��07 2152041*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <windows.h> //ȡϵͳʱ��
using namespace std;

int main()
{
	LARGE_INTEGER tick, begin, end;

	QueryPerformanceFrequency(&tick);	//��ü�����Ƶ��
	QueryPerformanceCounter(&begin);	//��ó�ʼӲ������������

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

	QueryPerformanceCounter(&end);		//�����ֹӲ������������

	cout << "������Ƶ�� : " << tick.QuadPart << "Hz" << endl;
	cout << "���������� : " << end.QuadPart - begin.QuadPart << endl;
	cout << setiosflags(ios::fixed) << setprecision(6) << double(end.QuadPart - begin.QuadPart) / tick.QuadPart << "��" << endl;

	return 0;
}
