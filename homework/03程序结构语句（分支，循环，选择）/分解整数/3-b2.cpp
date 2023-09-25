/*王浩 信07 2152041*/
#include <iostream>
using namespace std;

int main()
{
	int i;
	cout << "请输入一个[1..30000]间的整数\n";
	cin >> i;
	cout << "万位 : " << i/10000 << endl;
	cout << "千位 : " << i/10/10/10%10 << endl;
	cout << "百位 : " << i/10/10%10<< endl;
	cout << "十位 : " << i/10%10 << endl;
	cout << "个位 : " << i%10 << endl;

	 return 0;
}
