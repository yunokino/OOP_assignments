/* 2152041 信07 王浩 */
#include <iostream>
using namespace std;

int replus(int a[],int base)
{
	int k = 0;
	int i = 0;
	while (a[i] != 0)
	{
		int x = a[i] % 9;
		if (x == 0)
			base == 9 ? k++:k;
		else
			base == x? k++ : k;
		i++;
	}
	return k;
}

int main()
{
	int num,base;
	int a[10000] = { 0 };
	int k = 0;
	cout << "请输入数据的个数[1..10000]\n";
	cin >> num;
	cout << "请输入" << num << "个正整数\n";
	for (int i = 0; i <= num - 1; i++)
		cin >> a[i];
	cout << "请输入要统计的基数[1..9]\n";
	cin >> base;
	cout << num << "个数中迭代累加后值为" << base << "的数字的个数 : "<< replus(a,base);
	cout << endl;
	return 0;
}
