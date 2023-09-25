/* 2152041 王浩 信07 */

/* 允许按需加入系统的宏定义、需要的头文件等 */
#include <iostream>
#include<iomanip>
#include <fstream>
#include<cstring>
using namespace std;

#define MAX_STU_NUM			256	//约定最大人数为256人（两轮的总和，包括退选、补选）
#define MAX_NAME_LEN			32	//学生姓名的最大长度不超过16个汉字
#define MAX_FILENAME_LEN		256	//文件名的最大长度

/* stu_info 类存放每个学生的信息，包括学号、姓名、其它需要的私有信息，已有内容不准动，可加入符合限制要求的新内容 */
class stu_list;
class stu_info {
private:
	int  stu_no;			//学号
	char stu_name[MAX_NAME_LEN];	//姓名
	int  second_stu_no;			//学号
	char second_stu_name[MAX_NAME_LEN];
	char in_class;
	char second_in_class[10];
	friend class stu_list;
	/* 允许按需加入private数据成员、成员函数以及其它需要的内容 */

public:
	/* 本类不允许定义任何的公有数据成员、成员函数 */
};

/* stu_list 类整个选课信息，已有内容不准动，可加入符合限制要求的新内容 */
class stu_list {
private:
	stu_info stu[MAX_STU_NUM + 1];
	int number;

	/* 允许按需加入private数据成员和成员函数 */

public:
	int read(const char* filename, const int append = 0);	//从文件中读入选课信息并进行处理，第2个参数值为0表示覆盖方式，1表示追加方式
	int print(const char* prompt = NULL);		//打印当前读入的选课名单
	/* 允许按需加入其它public成员函数 */
	int first_judge(int i, int number, int* a)
	{
		int is_in = 0;
		for (int k = 0; k <= number-1; k++)
		{
			if (stu[i].second_stu_no == stu[k].stu_no) {
				(*a) = k;
				is_in = 1;
				break;
			}
		}
		return is_in;
	}
	int second_judge(int j, int i)
	{
		int n, is_in = 0;
		for (n = 0; n < i; n++)
		{
			if (stu[n].second_stu_no == stu[j].stu_no) {
				is_in = 1;
				break;
			}
		}
		return is_in;
	}
};
int stu_list::read(const char* filename, const int append)
{
	int i,j, a;
	if (append == 0)
		number = 0;
	ifstream infile(filename, ios::in);
	if (!infile.is_open())
	{
		cout << "输入文件" << filename << "打开失败!" << endl;
		infile.close();
	}
	else
	{
		if (append == 0) {
			for (;!infile.eof(); number++)
			{
				infile >> stu[number].stu_no;
				infile >> stu[number].stu_name;
				stu[number].in_class = 'Y';
			}

		}
		else {
			number--;
			for (i = 0; !infile.eof(); i++)
			{
				infile >> stu[i].second_stu_no;
				infile >> stu[i].second_stu_name;
				if (first_judge(i, number, &a) == 0 && stu[i].second_stu_no > 0)
				{
					stu[number].stu_no = stu[i].second_stu_no;
					strcpy_s(stu[number].stu_name, stu[i].second_stu_name);
					stu[number].in_class = '/';
					strcpy_s(stu[number].second_in_class, "补选");
					number++;
				}
				else if (first_judge(i, number, &a) == 1 && stu[i].second_stu_no > 0)
					strcpy_s(stu[a].second_in_class, "Y");
				else;
			}
			for (j = 0; j <= number-1; j++)
			{
				if (second_judge(j, i) == 0)
					strcpy_s(stu[j].second_in_class, "退课");
				else if (second_judge(j, i) == 1 && stu[j].in_class != '/')
					strcpy_s(stu[j].second_in_class, "Y");
				else;
			}
		}
	}
	if (append == 1) {
		int t;
		char name[40];
		char state;
		char first[10];
		for (int i = 0;i < number - 1; i++) {
			for (int j = 0; j < number - (i + 1); j++) 
			{
				if (stu[j].stu_no > stu[j + 1].stu_no)
				{
					t = stu[j].stu_no;
					stu[j].stu_no = stu[j + 1].stu_no;
					stu[j + 1].stu_no = t;
					strcpy_s(name, stu[j].stu_name);
					strcpy_s(stu[j].stu_name, stu[j + 1].stu_name);
					strcpy_s(stu[j + 1].stu_name, name);
					state = stu[j].in_class;
					stu[j].in_class = stu[j + 1].in_class;
					stu[j + 1].in_class = state;
					strcpy_s(first, stu[j].second_in_class);
					strcpy_s(stu[j].second_in_class, stu[j + 1].second_in_class);
					strcpy_s(stu[j + 1].second_in_class, first);
				}
			}
		}
	}
	return 0;
}

int stu_list::print(const char* prompt)
{
	cout << prompt << endl;
	cout << "===========================================================" << endl;
	cout << "序号 学号    姓名                             第一轮 第二轮" << endl;
	cout << "===========================================================" << endl;
	for (int k = 0; k <= number - 1; k++)
	{
		cout << left << setw(5) << k + 1;
		cout << stu[k].stu_no << " ";
		cout << setw(10) <<stu[k].stu_name<< "                       ";
		cout << stu[k].in_class << "      ";
		cout << stu[k].second_in_class << endl;
	}
	cout << "===========================================================" << endl;
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数不准动
***************************************************************************/
int main()
{
	char file1[MAX_FILENAME_LEN], file2[MAX_FILENAME_LEN];

	cout << "请输入前一轮选课的数据文件 : ";
	cin >> file1;
	cout << "请输入后一轮选课的数据文件 : ";
	cin >> file2;

	stu_list list;

	/* 读入第一个数据文件 */
	if (list.read(file1) < 0)
		return -1;

	/* 读入第二个数据文件，参数2的值为1表示追加方式 */
	if (list.read(file2, 1) < 0)
		return -1;

	list.print("最终选课名单");

	return 0;
}