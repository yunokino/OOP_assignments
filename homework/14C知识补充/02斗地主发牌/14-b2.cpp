/*2152041 计科 王浩*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
/* 如果有需要，此处可以添加头文件 */

using namespace std;

/* 允许定义常变量/宏定义，但不允许定义全局变量 */
/* 定义花色 */
#ifdef __linux//Linux
const char suit[4] = { 'H','D','C','S' };
#else
const char suit[4] = { '','','','' };
#endif
/* 定义扑克牌的内容 */
const char poker_content[13] = { '3','4','5','6','7','8','9','T','J','Q','K','A','2' };
const char special_poker[2][5] = { "BJ","RJ" };
/* 可以添加自己需要的函数 */

/***************************************************************************
  函数名称：
  功    能：打印某个玩家的牌面信息，如果是地主，后面加标记
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int print(const char* prompt, const bool landlord, const unsigned long long player)
{
	/* 只允许定义不超过三个基本类型的简单变量，不能定义数组变量、结构体、string等 */
	cout << prompt;
	for (int i = 0; i < 54; i++)
	{
		if (player >> i & (unsigned long long)(1))
		{
			if (i < 52)
			{
				cout << suit[i % 4];
				cout << poker_content[i / 4];
			}
			else
			{
				cout << special_poker[i % 4];
			}
			cout << " ";
		}
	}
	if (landlord)
		cout << "(地主)";
	cout << endl;
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：发牌（含键盘输入地主）
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int deal(unsigned long long* player)
{
	/* 只允许定义不超过十个基本类型的简单变量，不能定义数组变量、结构体、string等 */
	srand(unsigned(time(NULL)));
	int poker_location;
	unsigned long long tmp = 1;
	for(int i = 0;i < 17;i++)
	{
		/* 每个牌按轮次发送 */
		for (int j = 0; j < 3; j++)
		{
			while (1)
			{
				poker_location = rand() % 54;
				/* 如果这个牌没有被发过，那么退出 */
				if (!(( player[0] >> poker_location &tmp)| (player[1] >> poker_location & tmp)
					| (player[2] >> poker_location & tmp)))
					break;
			}
			player[j] |= tmp << poker_location;
		}
		cout << "第"<<i + 1<<"轮结束：" << endl;
		print("甲的牌：", 0, player[0]);
		print("乙的牌：", 0, player[1]);
		print("丙的牌：", 0, player[2]);
	}
	/* 键入地主 */
	int landlord;
	cout << "请选择一个地主[0-2]：" << endl;
	while (1)
	{
		cin >> landlord;
		if (cin.fail() || landlord < 0 || landlord > 2)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		break;
	}
	for (int i = 0; i < 54; i++)
	{
		if (!((player[0] >> i & tmp) | (player[1] >> i & tmp) 
			| (player[2] >> i & tmp)))
			player[landlord] |= tmp << i;
	}
	return landlord; //此处修改为选定的地主(0-2)
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数，不准修改
 ***************************************************************************/
int main()
{
	unsigned long long player[3] = { 0 }; //存放三个玩家的发牌信息
	int landlord; //返回0-2表示哪个玩家是地主

	cout << "按回车键开始发牌";
	while (getchar() != '\n')
		;

	landlord = deal(player);
	print("甲的牌：", (landlord == 0), player[0]);
	print("乙的牌：", (landlord == 1), player[1]);
	print("丙的牌：", (landlord == 2), player[2]);

	return 0;
}
