/*���� ��07 2152041*/
#include <iostream>
using namespace std;

int main()
{
	double a,b;
	 int i;
	cout << "������[0-100�ڣ�֮�������\n";
	cin >> a; 
	i =  int(a/10);
	b = a / 10 - i + 0.0001;

   	cout<<"ʮ��λ : "<<i / 100000000 %10<<endl;
	cout<<"��λ   : "<<i / 10000000 %10<<endl;    
	cout<<"ǧ��λ : "<<i / 1000000 %10<<endl;     
	cout<<"����λ : "<<i / 100000 %10<<endl;      
	cout<<"ʮ��λ : "<<i / 10000 %10<<endl;       
	cout<<"��λ   : "<<i / 1000 %10<<endl;        
	cout<<"ǧλ   : "<<i / 100 % 10<<endl;         
	cout<<"��λ   : "<<i / 10 % 10<<endl;         
	cout<<"ʮλ   : "<<i % 10<<endl;              
	cout<<"Ԫ     : "<<(int)(10 * b) % 10<<endl;  
	cout<<"��     : "<<(int)(100 * b) % 10<<endl; 
	cout<<"��     : "<<(int)(1000 * b) % 10<<endl;
	
	return 0;
}
