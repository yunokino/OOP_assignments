/* 2152041 ���� ��07 */
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
	{'A', "�������ȱ�",         18.5},
	{'B', "���༦�ȱ�",         18.5},
	{'C', "�°¶��������ȱ�",   19},
	{'D', "�ϱ��������",       17},
	{'E', "������ţ��",         19.5},
	{'F', "����㱤",         18.5},
	{'G', "˱ָԭζ��(1��)",    11.5},
	{'H', "֥֥����������Ƥ��", 12.5},
	{'I', "�°¶�������(2��)",  12.5},
	{'J', "�������׻�",         11.5},
	{'K', "��������(2��)",      12.0},
	{'L', "�ٽ��޹Ǵ���(2��)",12.5},
	{'M', "����ɫ��",           13},
	{'N', "����(С)",           9},
	{'O', "����(��)",           12},
	{'P', "����(��)",           14},
	{'Q', "ܽ��������",         9},
	{'R', "ԭζ��Ͳ������",     6},
	{'S', "����������",         7},
	{'T', "�������װ�",         9.0},
	{'U', "��ʽ��̢",           8.0},
	{'V', "���¿���(С)",       7.0},
	{'W', "���¿���(��)",       9.5},
	{'X', "���¿���(��)",       11.5},
	{'Y', "�����֭����",       12.5},
	{'Z', "����������",         11.5},
	{'\0', NULL,                0}
		};

		const struct SPECIAL special[] =
		{
			//{"ANV", "�������ȱ����������",  24}, //�������Ҫ���ſ����ע�͵���һ�еġ�BMV���Żݣ��۲��Żݲ˵��Ƿ����˱仯
			{"BMV", "���༦�ȱ���ֵ�ײ�",    26},
			{"ABCGGIIKKOUWWW", "��ֵȫ��Ͱ", 115},
			{"KIIRRJUWW", "�ͷ�С��Ͱ",      65},
			{"JJ","�������׻�(2��С)",       12.5},
			{NULL, NULL, 0}
		};
		cout << "=============================================================" << endl;
		cout << "	                  KFC 2021�＾�˵�" << endl;
		cout << "=============================================================" << endl;
		for (int i = 0; i <= 25; i++)
		{
			if (i % 2 == 0)
				cout << " " << list[i].pick_order << " " << left << setw(20) << list[i].order_name << setw(7) << list[i].order_price << "|";
			else
				cout << " " << list[i].pick_order << " " << left << setw(20) << list[i].order_name << setw(7) << list[i].order_price << endl;
		}
		cout << "���Ż���Ϣ����" << endl;
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
		cout << "���������˵������";
		cout << "ANV=�������ȱ�+����(С)+���¿���(С)/akaak=�������ȱ�*3+��������*2" << endl;
		cout << "��ĸ���ִ�Сд������˳�򣬵�������0���˳�����" << endl;
		cout << endl;
		cout << "��㵥 :";
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
		cout << "���ĵ��=";
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
		cout << "���ƣ�" << total_price << endl;
		cout << "�㵥��ɣ������������." << endl;
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
	{'A', "�������ȱ�",         18.5},
	{'B', "���༦�ȱ�",         18.5},
	{'C', "�°¶��������ȱ�",   19},
	{'D', "�ϱ��������",       17},
	{'E', "������ţ��",         19.5},
	{'F', "����㱤",         18.5},
	{'G', "˱ָԭζ��(1��)",    11.5},
	{'H', "֥֥����������Ƥ��", 12.5},
	{'I', "�°¶�������(2��)",  12.5},
	{'J', "�������׻�",         11.5},
	{'K', "��������(2��)",      12.0},
	{'L', "�ٽ��޹Ǵ���(2��)",12.5},
	{'M', "����ɫ��",           13},
	{'N', "����(С)",           9},
	{'O', "����(��)",           12},
	{'P', "����(��)",           14},
	{'Q', "ܽ��������",         9},
	{'R', "ԭζ��Ͳ������",     6},
	{'S', "����������",         7},
	{'T', "�������װ�",         9.0},
	{'U', "��ʽ��̢",           8.0},
	{'V', "���¿���(С)",       7.0},
	{'W', "���¿���(��)",       9.5},
	{'X', "���¿���(��)",       11.5},
	{'Y', "�����֭����",       12.5},
	{'Z', "����������",         11.5},
	{'\0', NULL,                0}
		};

		const struct SPECIAL special[] =
		{
			//{"ANV", "�������ȱ����������",  24}, //�������Ҫ���ſ����ע�͵���һ�еġ�BMV���Żݣ��۲��Żݲ˵��Ƿ����˱仯
			{"BMV", "���༦�ȱ���ֵ�ײ�",    26},
			{"ABCGGIIKKOUWWW", "��ֵȫ��Ͱ", 115},
			{"KIIRRJUWW", "�ͷ�С��Ͱ",      65},
			{"JJ","�������׻�(2��С)",       12.5},
			{NULL, NULL, 0}
		};
		cout << "=============================================================" << endl;
		cout << "	                  KFC 2021�＾�˵�" << endl;
		cout << "=============================================================" << endl;
		for (int i = 0; i <= 25; i++)
		{
			if (i % 2 == 0)
				cout << " " << list[i].pick_order << " " << left << setw(20) << list[i].order_name << setw(7) << list[i].order_price << "|";
			else
				cout << " " << list[i].pick_order << " " << left << setw(20) << list[i].order_name << setw(7) << list[i].order_price << endl;
		}
		cout << "���Ż���Ϣ����" << endl;
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
		cout << "���������˵������";
		cout << "ANV=�������ȱ�+����(С)+���¿���(С)/akaak=�������ȱ�*3+��������*2" << endl;
		cout << "��ĸ���ִ�Сд������˳�򣬵�������0���˳�����" << endl;
		cout << endl;
		cout << "��㵥 :";
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
		cout << "���ĵ��=";
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
		cout << "���ƣ�" << total_price << endl;
		cout << "�㵥��ɣ������������." << endl;
		_getch();
		system("cls");
	}
	return 0;
}*/