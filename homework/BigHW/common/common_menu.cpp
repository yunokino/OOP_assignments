/* �ƿ� 2152041 ���� */
#include<iostream>
using namespace std;

int choice_length(char a)
{
	a = tolower(a);
	a -= '0';
	switch (a)
	{
	case 0:
		return 7;
	case 1:
		return 37;
	case 2:
		return 35;
	case 3:
		return 35;
	case 4:
		return 29;
	case 5:
		return 37;
	case 6:
		return 37;
	case 7:
		return 40;
	case 8:
		return 35;
	case 9:
		return 29;
	case 49:
		return 27;
	case 50:
		return 35;
	case 51:
		return 31;
	case 52:
		return 45;
	case 53:
		return 45;
	case 54:
		return 35;
	case 55:
		return 19;
	case 65:
		return 7;
	default:
		return 0;
	}
}

void single_choice_print(char a)
{
	a = tolower(a);
	a -= '0';
	switch (a)
	{
	case 0:
		cout << "0.�˳�" << endl;
		break;
	case 1:
		cout << "1.�������ҳ��ɺϳ����ʶ���ǵݹ飩" << endl;
		break;
	case 2:
		cout << "2.�������ҳ��ɺϳ����ʶ���ݹ飩" << endl;
		break;
	case 3:
		cout << "3.���������һ�κϳɣ��ֲ�����ʾ��" << endl;
		break;
	case 4:
		cout << "4.�����������棨�ֲ�����ʾ��" << endl;
		break;
	case 5:
		cout << "5.αͼ�ν�����ʾ��ʼ���飨�޷ָ��ߣ�" << endl;
		break;
	case 6:
		cout << "6.αͼ�ν�����ʾ��ʼ���飨�зָ��ߣ�" << endl;
		break;
	case 7:
		cout << "7.αͼ�ν������ü�ͷ��/���ѡ��ǰɫ��" << endl;
		break;
	case 8:
		cout << "8.αͼ�ν������һ�κϳɣ��ֲ��裩" << endl;
		break;
	case 9:
		cout << "9.αͼ�ν���������(֧�����)" << endl;
		break;
	case 49:
		cout << "A.�������ҳ����������ʶ" << endl;
		break;
	case 50:
		cout << "B.���������һ���������ֲ�����ʾ��" << endl;
		break;
	case 51:
		cout << "C.���������һ�أ��ֲ�����ʾ��" << endl;
		break;
	case 52:
		cout << "D.αͼ�ν����������ѡ��һ��ɫ�飨�޷ָ��ߣ�" << endl;
		break;
	case 53:
		cout << "E.αͼ�ν����������ѡ��һ��ɫ�飨�зָ��ߣ�" << endl;
		break;
	case 54:
		cout << "F.αͼ�ν������һ���������ֲ��裩" << endl;
		break;
	case 55:
		cout << "G.αͼ�ν���������" << endl;
		break;
	case 65:
		cout << "Q.�˳�" << endl;
		break;
	}
}

void print_line(int max_length)
{
	for (; max_length >= 0; max_length--)
	{
		cout << "-";
	}
}

char menu(const char* options)
{
	char pick_choice;
	int max_length = 0, str_length = 0;
	const char* con_options = options;
	while (*options)
	{
		str_length = choice_length(*options);
		if (str_length > max_length)
		{
			max_length = str_length;
		}
		options++;
	}
	max_length -= 1;//ɾȥĩβ������ĳ���
	print_line(max_length);
	cout << endl;
	options = con_options;
	while (*options)
	{
		single_choice_print(*options);
		options++;
	}
	print_line(max_length);
	cout << endl << "[��ѡ��:]";
	cin >> pick_choice;
	return pick_choice;
}