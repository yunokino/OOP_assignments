/*2152041 �ƿ� ����*/
#include <iostream>
using namespace std;
int main()
{
	const char* month[] = { "January","February","March","April","May","June","July","August","September","October","November","December" };
	int input;
	cout << "�������·�(1-12)" << endl;
	cin >> input ? ((input >= 1 && input <= 12) ? cout << *(month + input - 1) : cout << "Invalid") : cout << "Invalid";
	cout << endl;
	return 0;
}