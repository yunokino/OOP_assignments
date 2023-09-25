/* 2152041 王浩 信07 */
#include <iostream>
using namespace std;

#define  N  10	/* 假设最多转换10个数字 */

/* 不允许再定义其它函数、全局变量 */

int main()
{
	/* 如果有不需要的变量，允许删除，但不允许添加或替换为其它类型的变量 */
	char str[256], * p;
	int  a[N] = { 0 }, * pnum, * pa;
	bool is_num;

	/* 上面的定义不准动(删除不需要的变量除外)，下面为程序的具体实现，要求不得再定义任何变量、常量、常变量 */
	cout << "请输入间隔含有若干正负数字的字符串\n";
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
	cout << "共有" << pnum - a << "个整数"<<endl;
	pa = a;
	for(; (pnum - a)!=0;pa++,pnum--)
		cout << *pa<<" ";
	cout << endl;
	return 0;
}