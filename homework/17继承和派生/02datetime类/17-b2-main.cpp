/* 2152041 计科 王浩 */
/* 2154301 黄昱翔 2153812 彭兆祥  2151613 毛宇录 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "17-b2-date.h"
#include "17-b2-datetime.h"
#include "17-b2-time.h"
using namespace std;

#if defined(__linux) || defined(__linux__) //Linux
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (getchar() != '\n')
		;
	cout << endl << endl;
}

#else //VS+Dev
#include <Windows.h>
#include <conio.h>
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}
#endif

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数不准动，也不需要提交，检查时会替换（细节可能有错，如果发现请及时提出）
***************************************************************************/
int main()
{
	if (1)  {
		DateTime d1;
		DateTime d2(2022, 11, 10, 11, 22, 3);

		cout << "测试初始化，完全正确的赋值" << endl;

		cout << "d1应该是1900.01.01.00.00.00，实际为：";
		d1.show();
		cout << "d2应该是2022.11.10.11.22.03，实际为：";
		d2.show();

		wait_for_enter();
	}

	if (1)  {
		DateTime d1(1870, 3, 15);  
		DateTime d2(2002, 3, 4, 5, 6, 7);   

		cout << "测试初始化" << endl;

		cout << "d1应该是1900.01.01.00.00.00，实际为：";
		d1.show();
		cout << "d2应该是2002.03.04.05.06.07，实际为：";
		d2.show();

		wait_for_enter();
	}

	if (1)  {
		DateTime d1, d2, d3, d4, d5, d6;

		cout << "测试set，带缺省值" << endl;
		d1.set(2022, 11, 10, 11, 20, 30);
		d2.set(2022, 11, 10, 11, 20);
		d3.set(2022, 11, 10, 11);
		d4.set(2022, 11, 10);
		d5.set(2022, 11);

		cout << "d1应该是2022.11.10.11.20.30，实际为：";
		d1.show();
		cout << "d2应该是2022.11,10.11.20.0， 实际为：";
		d2.show();
		cout << "d3应该是2022.11.10.11.00.00，实际为：";
		d3.show();
		cout << "d4应该是2022.11.10.00.00.00，实际为：";
		d4.show();
		cout << "d5应该是2022.11.01.00.00.00，实际为：";
		d5.show();

		wait_for_enter();
	}

	if (1)  {
		DateTime d1;

		cout << "测试set" << endl;

		d1.set(2112, 2, 29, 00, 00, 00);
		cout << "d1应该是1900.01.01.00.00.00， 实际为：";
		d1.show();

		wait_for_enter();
	}

	if (1)  {
		DateTime d1(2022, 11, 10, 11, 20, 30);

		cout << "测试cout" << endl;
		cout << "d1应该是2022.11.10.11.20.30，实际为：" << d1 << endl;

		wait_for_enter();
	}

	if (1)  {
		DateTime d1;

		cout << "测试cin/cout" << endl;

		cout << "请输入2022 11 10 11 20 30" << endl;
		cin >> d1;
		cout << "d1应该是2022.11.10.11.20.30，实际为：" << d1 << endl;

		cout << "请输入2112 15 34 25 67 66" << endl;
		cin >> d1;
		cout << "d1应该是1900.01.01.00.00.00，  实际为：" << d1 << endl;

		wait_for_enter();
	}

	if (1)  {
		DateTime d1((long long)0);
		DateTime d2((long long) - 1);

		cout << "转换构造函数测试" << endl;

		cout << "d1应该是1900.01.01.00.00.00，  实际为：";
		d1.show();
		cout << "d2应该是2099.12.31.23.59.59，  实际为：";
		d2.show();

		wait_for_enter();
	}

	if (1)  {
		DateTime d1(1900, 01, 01, 0, 0, 0);
		DateTime d2(1900, 01, 02, 0, 0, 2);

		cout << "类型转换函数测试，包括合法及非法值" << endl;

		cout << "d1应该是0，    实际为：" << (long long)(d1) << endl;
		cout << "d2应该是86402，实际为：" << (long long)(d2) << endl;

		wait_for_enter();
	}

	if (1)  {
		DateTime d1(2022, 11, 10, 0, 0, 0);
		DateTime d2;

		cout << "测试+/- n" << endl;

		d2 = d1 + (long long)86427;
		cout << "d2应该是2022.11.11.00.00.27，    实际为：" << d2 << endl;

		d1.set(1900, 1, 1, 0, 0, 3);
		d2 = d1 - (long long)4;
		cout << "d2应该是2099.12.31.23.59.59，    实际为：" << d2 << endl;

		d1.set(1900, 1, 1, 0, 0, 2);
		d2.set(1900, 1, 1, 0, 0, 4);
		d2 = d2 - d1;
		cout << "d2应该是1900.01.01.00.00.02，    实际为：" << d2 << endl;

		wait_for_enter();
	}

	if (1)  {
		DateTime d1(2022, 11, 10, 0, 0, 0);
		DateTime d2;

		cout << "测试++/-- " << endl;

		d2 = d1++;
		cout << "d1应该是2022.11.10.00.00.01，    实际为：" << d1 << endl;
		cout << "d2应该是2022.11.10.00.00.00，    实际为：" << d2 << endl;

		d2 = d1--;
		cout << "d1应该是2022.11.10.00.00.00，    实际为：" << d1 << endl;
		cout << "d2应该是2022.11.10.00.00.01，    实际为：" << d2 << endl;

		d2 = --d1;
		cout << "d1应该是2022.11.09.23.59.59，    实际为：" << d1 << endl;
		cout << "d2应该是2022.11.09.23.59.59，    实际为：" << d2 << endl;

		d2 = d1--;
		cout << "d1应该是2022.11.09.23.59.58，    实际为：" << d1 << endl;
		cout << "d2应该是2022.11.09.23.59.59，    实际为：" << d2 << endl;

		wait_for_enter();
	}

	if (1)  {
		/* 测试比较运算符 */
		DateTime d1(2022, 11, 10, 22, 30, 30);
		DateTime d2(2022, 11, 10, 22, 30, 30);
		DateTime d3(2022, 10, 29, 20, 32, 31);

		cout << "测试比较运算符" << endl;

		cout << "比较结果应为0，实际为：" << (d1 > d2) << endl;
		cout << "比较结果应为1，实际为：" << (d1 >= d2) << endl;
		cout << "比较结果应为0，实际为：" << (d1 < d2) << endl;
		cout << "比较结果应为1，实际为：" << (d1 <= d2) << endl;
		cout << "比较结果应为1，实际为：" << (d1 == d2) << endl;
		cout << "比较结果应为0，实际为：" << (d1 != d2) << endl;

		cout << "比较结果应为1，实际为：" << (d1 > d3) << endl;
		cout << "比较结果应为1，实际为：" << (d1 >= d3) << endl;
		cout << "比较结果应为0，实际为：" << (d1 < d3) << endl;
		cout << "比较结果应为0，实际为：" << (d1 <= d3) << endl;
		cout << "比较结果应为0，实际为：" << (d1 == d3) << endl;
		cout << "比较结果应为1，实际为：" << (d1 != d3) << endl;

		wait_for_enter();
	}

	return 0;
}
