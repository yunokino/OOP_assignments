/* 2152041 王浩 信07 */
#include <iostream>
#include<iomanip>
#include<conio.h>
using namespace std;

int main()
{
	system("mode con cols=120 lines=35");
	struct KFC
	{
		char pick_order;
		char order_name[20];
		double order_price;
	};
	struct SPECIAL
	{
		char special_choice[15];
		char special_name[21];
		double special_price;
	};
	while (1)
	{
		const struct KFC list[] =
		{
	{'A', "香辣鸡腿堡",         18.5},
	{'B', "劲脆鸡腿堡",         18.5},
	{'C', "新奥尔良烤鸡腿堡",   19},
	{'D', "老北京鸡肉卷",       17},
	{'E', "川辣嫩牛卷",         19.5},
	{'F', "深海鳕鱼堡",         18.5},
	{'G', "吮指原味鸡(1块)",    11.5},
	{'H', "芝芝肉酥热辣脆皮鸡", 12.5},
	{'I', "新奥尔良烤翅(2块)",  12.5},
	{'J', "劲爆鸡米花",         11.5},
	{'K', "香辣鸡翅(2块)",      12.0},
	{'L', "藤椒无骨大鸡柳(2块)",12.5},
	{'M', "鲜蔬色拉",           13},
	{'N', "薯条(小)",           9},
	{'O', "薯条(中)",           12},
	{'P', "薯条(大)",           14},
	{'Q', "芙蓉蔬荟汤",         9},
	{'R', "原味花筒冰激凌",     6},
	{'S', "醇香土豆泥",         7},
	{'T', "香甜粟米棒",         9.0},
	{'U', "葡式蛋挞",           8.0},
	{'V', "百事可乐(小)",       7.0},
	{'W', "百事可乐(中)",       9.5},
	{'X', "百事可乐(大)",       11.5},
	{'Y', "九珍果汁饮料",       12.5},
	{'Z', "纯纯玉米饮",         11.5},
	{'\0', NULL,                0}
		};

		const struct SPECIAL special[] =
		{
			//{"ANV", "香辣鸡腿堡工作日午餐",  24}, //如果有需要，放开此项，注释掉下一行的“BMV”优惠，观察优惠菜单是否发生了变化
			{"BMV", "劲脆鸡腿堡超值套餐",    26},
			{"ABCGGIIKKOUWWW", "超值全家桶", 115},
			{"KIIRRJUWW", "缤纷小吃桶",      65},
			{"JJ","劲爆鸡米花(2份小)",       12.5},
			{NULL, NULL, 0}
		};
		cout << "=============================================================" << endl;
		cout << "	                  KFC 2021秋季菜单" << endl;
		cout << "=============================================================" << endl;
		for (int i = 0; i <= 25; i++)
		{
			if (i % 2 == 0)
				cout << " " << list[i].pick_order << " " << left << setw(20) << list[i].order_name << setw(7) << list[i].order_price << "|";
			else
				cout << " " << list[i].pick_order << " " << left << setw(20) << list[i].order_name << setw(7) << list[i].order_price << endl;
		}
		cout << "【优惠信息】：" << endl;
		for (int i = 0; special[i].special_price != 0; i++)
		{
			int special_count[26] = { 0 };
			for (int j = 0; special[i].special_choice[j] != '\0'; j++)
				special_count[(int)(special[i].special_choice[j]) - 65]++;
			cout << special[i].special_name << "=";
			for (int j = 0; j <= 25; j++)
			{
				if (special_count[j] != 0)
				{
					if (special_count[j] == 1)
						cout << list[j].order_name;
					else
						cout << list[j].order_name << "*" << special_count[j];
				}
				for (int k = j + 1; k <= 25; k++)
				{
					if (special_count[j] != 0 && special_count[k] != 0)
					{
						cout << "+";
						break;
					}
				}
			}
			cout << "=" << special[i].special_price;
			cout << endl;
		}
		cout << "【输入规则说明】：";
		cout << "ANV=香辣鸡腿堡+薯条(小)+百事可乐(小)/akaak=香辣鸡腿堡*3+香辣鸡翅*2" << endl;
		cout << "字母不分大小写，不限顺序，单独输入0则退出程序" << endl;
		cout << endl;
		cout << "请点单 :";
		char order[51] = { 0 };
		double total_price = 0;
		for (int i = 0; i <= 49; i++)
		{
			order[i] = getchar();
			if (order[i] >= 'a' && order[i] <= 'z')
				order[i] -= 32;
			if (order[i] == '\n')
				break;
		}
		if (order[0] == '0')
			break;
		cout << "您的点餐=";
		int list_count[26] = { 0 };
		for (int j = 0; order[j] != '\0'; j++)
		{
			list_count[(int)(order[j]) - 65]++;
			total_price += list[(int)(order[j]) - 65].order_price;
		}
		for (int i = 0; special[i].special_price != 0; i++)
		{
			int special_count[26] = { 0 };
			bool is_same = 1;
			for (int j = 0; special[i].special_choice[j] != '\0'; j++)
				special_count[(int)(special[i].special_choice[j]) - 65]++;
			for (int j = 0; j <= 25; j++)
			{
				if (list_count[j] != special_count[j])
				{
					is_same = 0;
					break;
				}
			}
			if (is_same)
			{
				total_price = special[i].special_price;
				break;
			}
		}
		for (int j = 0; j <= 25; j++)
		{
			if (list_count[j] != 0)
			{
				if (list_count[j] == 1)
					cout << list[j].order_name;
				else
					cout << list[j].order_name << "*" << list_count[j];
			}
			for (int k = j + 1; k <= 25; k++)
			{
				if (list_count[j] != 0 && list_count[k] != 0)
				{
					cout << "+";
					break;
				}
			}
		}
		cout << endl;
		cout << "共计：" << total_price << endl;
		cout << "点单完成，按任意键继续." << endl;
		_getch();
		system("cls");
	}
	return 0;
}
/*
#include <iostream>
#include<iomanip>
#include<conio.h>
using namespace std;

int main()
{
	system("mode con cols=120 lines=35");
	struct KFC
	{
		char pick_order;
		char order_name[20];
		double order_price;
	};
	struct SPECIAL
	{
		char special_choice[15];
		char special_name[21];
		double special_price;
	};
	while (1)
	{
		const struct KFC list[] =
		{
	{'A', "香辣鸡腿堡",         18.5},
	{'B', "劲脆鸡腿堡",         18.5},
	{'C', "新奥尔良烤鸡腿堡",   19},
	{'D', "老北京鸡肉卷",       17},
	{'E', "川辣嫩牛卷",         19.5},
	{'F', "深海鳕鱼堡",         18.5},
	{'G', "吮指原味鸡(1块)",    11.5},
	{'H', "芝芝肉酥热辣脆皮鸡", 12.5},
	{'I', "新奥尔良烤翅(2块)",  12.5},
	{'J', "劲爆鸡米花",         11.5},
	{'K', "香辣鸡翅(2块)",      12.0},
	{'L', "藤椒无骨大鸡柳(2块)",12.5},
	{'M', "鲜蔬色拉",           13},
	{'N', "薯条(小)",           9},
	{'O', "薯条(中)",           12},
	{'P', "薯条(大)",           14},
	{'Q', "芙蓉蔬荟汤",         9},
	{'R', "原味花筒冰激凌",     6},
	{'S', "醇香土豆泥",         7},
	{'T', "香甜粟米棒",         9.0},
	{'U', "葡式蛋挞",           8.0},
	{'V', "百事可乐(小)",       7.0},
	{'W', "百事可乐(中)",       9.5},
	{'X', "百事可乐(大)",       11.5},
	{'Y', "九珍果汁饮料",       12.5},
	{'Z', "纯纯玉米饮",         11.5},
	{'\0', NULL,                0}
		};

		const struct SPECIAL special[] =
		{
			//{"ANV", "香辣鸡腿堡工作日午餐",  24}, //如果有需要，放开此项，注释掉下一行的“BMV”优惠，观察优惠菜单是否发生了变化
			{"BMV", "劲脆鸡腿堡超值套餐",    26},
			{"ABCGGIIKKOUWWW", "超值全家桶", 115},
			{"KIIRRJUWW", "缤纷小吃桶",      65},
			{"JJ","劲爆鸡米花(2份小)",       12.5},
			{NULL, NULL, 0}
		};
		cout << "=============================================================" << endl;
		cout << "	                  KFC 2021秋季菜单" << endl;
		cout << "=============================================================" << endl;
		for (int i = 0; i <= 25; i++)
		{
			if (i % 2 == 0)
				cout << " " << list[i].pick_order << " " << left << setw(20) << list[i].order_name << setw(7) << list[i].order_price << "|";
			else
				cout << " " << list[i].pick_order << " " << left << setw(20) << list[i].order_name << setw(7) << list[i].order_price << endl;
		}
		cout << "【优惠信息】：" << endl;
		for (int i = 0; special[i].special_price != 0; i++)
		{
			int special_count[26] = { 0 };
			for (int j = 0; special[i].special_choice[j] != '\0'; j++)
				special_count[(int)(special[i].special_choice[j]) - 65]++;
			cout << special[i].special_name << "=";
			for (int j = 0; j <= 25; j++)
			{
				if (special_count[j] != 0)
				{
					if (special_count[j] == 1)
						cout << list[j].order_name;
					else
						cout << list[j].order_name << "*" << special_count[j];
				}
				for (int k = j + 1; k <= 25; k++)
				{
					if (special_count[j] != 0 && special_count[k] != 0)
					{
						cout << "+";
						break;
					}
				}
			}
			cout << "=" << special[i].special_price;
			cout << endl;
		}
		cout << "【输入规则说明】：";
		cout << "ANV=香辣鸡腿堡+薯条(小)+百事可乐(小)/akaak=香辣鸡腿堡*3+香辣鸡翅*2" << endl;
		cout << "字母不分大小写，不限顺序，单独输入0则退出程序" << endl;
		cout << endl;
		cout << "请点单 :";
		char order[27] = { 0 };
		double total_price = 0;
		for (int i = 0; i <= 26; i++)
		{
			order[i] = getchar();
			if (order[i] >= 'a' && order[i] <= 'z')
				order[i] -= 32;
			if (order[i] == '\n')
				break;
		}
		if (order[0] == '0')
			break;
		cout << "您的点餐=";
		int list_count[26] = { 0 };
		for (int j = 0; order[j] != '\0'; j++)
		{
			list_count[(int)(order[j]) - 65]++;
			total_price += list[(int)(order[j]) - 65].order_price;
		}
		for (int i = 0; special[i].special_price != 0; i++)
		{
			int special_count[26] = { 0 };
			bool is_same = 1;
			for (int j = 0; special[i].special_choice[j] != '\0'; j++)
				special_count[(int)(special[i].special_choice[j]) - 65]++;
			for (int j = 0; j <= 25; j++)
			{
				if (list_count[j] != special_count[j])
				{
					is_same = 0;
					break;
				}
			}
			if (is_same)
			{
				total_price = special[i].special_price;
				break;
			}
		}
		for (int j = 0; j <= 25; j++)
		{
			if (list_count[j] != 0)
			{
				if (list_count[j] == 1)
					cout << list[j].order_name;
				else
					cout << list[j].order_name << "*" << list_count[j];
			}
			for (int k = j + 1; k <= 25; k++)
			{
				if (list_count[j] != 0 && list_count[k] != 0)
				{
					cout << "+";
					break;
				}
			}
		}
		cout << endl;
		cout << "共计：" << total_price << endl;
		cout << "点单完成，按任意键继续." << endl;
		_getch();
		system("cls");
	}
	return 0;
}*/