/* 2152041 ��07 ���� */
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
	cout << "���������ݵĸ���[1..10000]\n";
	cin >> num;
	cout << "������" << num << "��������\n";
	for (int i = 0; i <= num - 1; i++)
		cin >> a[i];
	cout << "������Ҫͳ�ƵĻ���[1..9]\n";
	cin >> base;
	cout << num << "�����е����ۼӺ�ֵΪ" << base << "�����ֵĸ��� : "<< replus(a,base);
	cout << endl;
	return 0;
}
