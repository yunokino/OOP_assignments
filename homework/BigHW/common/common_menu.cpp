/* 计科 2152041 王浩 */
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
		cout << "0.退出" << endl;
		break;
	case 1:
		cout << "1.命令行找出可合成项并标识（非递归）" << endl;
		break;
	case 2:
		cout << "2.命令行找出可合成项并标识（递归）" << endl;
		break;
	case 3:
		cout << "3.命令行完成一次合成（分步骤显示）" << endl;
		break;
	case 4:
		cout << "4.命令行完整版（分步骤显示）" << endl;
		break;
	case 5:
		cout << "5.伪图形界面显示初始数组（无分隔线）" << endl;
		break;
	case 6:
		cout << "6.伪图形界面显示初始数组（有分隔线）" << endl;
		break;
	case 7:
		cout << "7.伪图形界面下用箭头键/鼠标选择当前色块" << endl;
		break;
	case 8:
		cout << "8.伪图形界面完成一次合成（分步骤）" << endl;
		break;
	case 9:
		cout << "9.伪图形界面完整版(支持鼠标)" << endl;
		break;
	case 49:
		cout << "A.命令行找出可消除项并标识" << endl;
		break;
	case 50:
		cout << "B.命令行完成一次消除（分步骤显示）" << endl;
		break;
	case 51:
		cout << "C.命令行完成一关（分步骤显示）" << endl;
		break;
	case 52:
		cout << "D.伪图形界面下用鼠标选择一个色块（无分隔线）" << endl;
		break;
	case 53:
		cout << "E.伪图形界面下用鼠标选择一个色块（有分隔线）" << endl;
		break;
	case 54:
		cout << "F.伪图形界面完成一次消除（分步骤）" << endl;
		break;
	case 55:
		cout << "G.伪图形界面完整版" << endl;
		break;
	case 65:
		cout << "Q.退出" << endl;
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
	max_length -= 1;//删去末尾零带来的长度
	print_line(max_length);
	cout << endl;
	options = con_options;
	while (*options)
	{
		single_choice_print(*options);
		options++;
	}
	print_line(max_length);
	cout << endl << "[请选择:]";
	cin >> pick_choice;
	return pick_choice;
}