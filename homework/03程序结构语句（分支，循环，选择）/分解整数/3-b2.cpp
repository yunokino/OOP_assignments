/*���� ��07 2152041*/
#include <iostream>
using namespace std;

int main()
{
	int i;
	cout << "������һ��[1..30000]�������\n";
	cin >> i;
	cout << "��λ : " << i/10000 << endl;
	cout << "ǧλ : " << i/10/10/10%10 << endl;
	cout << "��λ : " << i/10/10%10<< endl;
	cout << "ʮλ : " << i/10%10 << endl;
	cout << "��λ : " << i%10 << endl;

	 return 0;
}
