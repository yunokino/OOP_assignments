/*2152041 ÍõºÆ ÐÅ07*/
#include <iostream>
using namespace std;

int main()
{
	int a[100] = {0};
	for (int i = 0; i <= 99; i++)
		for (int j = 0; j <= 99; j++)
		{
			if (i > j)
				continue;
			else
				(j + 1) % (i+1) == 0 ? a[j] = !a[j] : a[j] = a[j];
		}
	for (int m = 0; m <= 99; m++)
	{
		if (a[m] == 1 && m != 99)
			cout << m + 1 << " ";
		else if (a[m] == 1 && m == 99)
			cout << m + 1;
		else;
	}
	return 0;
}