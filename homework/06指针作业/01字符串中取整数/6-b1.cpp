/* 2152041 ���� ��07 */
#include <iostream>
using namespace std;

#define  N  10	/* �������ת��10������ */

/* �������ٶ�������������ȫ�ֱ��� */

int main()
{
	/* ����в���Ҫ�ı���������ɾ��������������ӻ��滻Ϊ�������͵ı��� */
	char str[256], * p;
	int  a[N] = { 0 }, * pnum, * pa;
	bool is_num;

	/* ����Ķ��岻׼��(ɾ������Ҫ�ı�������)������Ϊ����ľ���ʵ�֣�Ҫ�󲻵��ٶ����κα����������������� */
	cout << "�����������������������ֵ��ַ���\n";
	p = str;
	pa = a;                                                                                                                                                                                                                                                                                                      
	is_num = 0;
	pnum =a;
	gets_s(p, 256);
	for(;*p != '\0';p++)
	{
		if (*p >= 48 && *p <= 57)
		{
			if (is_num)
			{
				*pa = (int)(*p - 48) + ((*pa)*10);
				continue;
			}
			else
			{
				pnum++;
				is_num = 1;
				*pa = (int)(*p-48);
				continue;
			}
		}
		else
		{
			if (pnum - a == N)
				break;
			if (is_num)
			{
				pa++;
				is_num = 0;
			}
			continue;
		}
	}
	cout << "����" << pnum - a << "������"<<endl;
	pa = a;
	for(; (pnum - a)!=0;pa++,pnum--)
		cout << *pa<<" ";
	cout << endl;
	return 0;
}