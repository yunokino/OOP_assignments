/* 2152041 �ƿ� ���� */
#include <iostream>
/* --���ĳ����������Ҫ���˴�������������ĸ�ʽ����ͷ�ļ� --*/

using namespace std;


int main()
{
	char a[80];

#if (defined __WINNT)//||(defined __MINGW32__)  //DevC++
	gets(a);
#elif (defined _MSC_VER)       //VS2022
	gets_s(a);

#elif (defined __linux)       //Linux
	fgets(a, 80, stdin); //����Ҫ�������Ļس�
#endif

	cout << a << endl;
	return 0;
}
