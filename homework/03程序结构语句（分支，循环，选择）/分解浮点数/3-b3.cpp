/*王浩 信07 2152041*/
#include <iostream>
using namespace std;

int main()
{
	double a,b;
	 int i;
	cout << "请输入[0-100亿）之间的数字\n";
	cin >> a; 
	i =  int(a/10);
	b = a / 10 - i + 0.0001;

   	cout<<"十亿位 : "<<i / 100000000 %10<<endl;
	cout<<"亿位   : "<<i / 10000000 %10<<endl;    
	cout<<"千万位 : "<<i / 1000000 %10<<endl;     
	cout<<"百万位 : "<<i / 100000 %10<<endl;      
	cout<<"十万位 : "<<i / 10000 %10<<endl;       
	cout<<"万位   : "<<i / 1000 %10<<endl;        
	cout<<"千位   : "<<i / 100 % 10<<endl;         
	cout<<"百位   : "<<i / 10 % 10<<endl;         
	cout<<"十位   : "<<i % 10<<endl;              
	cout<<"元     : "<<(int)(10 * b) % 10<<endl;  
	cout<<"角     : "<<(int)(100 * b) % 10<<endl; 
	cout<<"分     : "<<(int)(1000 * b) % 10<<endl;
	
	return 0;
}
