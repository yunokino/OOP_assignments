/*ÍõºÆ ÐÅ07 2152041*/
#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	int m, n;
	for(m=1;m<=9;m++)
	{
		for (n = 1;n<=m;n++)
		{
			cout << setiosflags(ios::left)<< n << "¡Á" << m<< "=" << setw(3)<<m * n ;
		}
		cout << endl;
	}
	return 0;
}
