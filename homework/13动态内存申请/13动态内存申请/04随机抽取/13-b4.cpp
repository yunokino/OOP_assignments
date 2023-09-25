/* 2152041 计科 王浩 */
#include<iostream>
#include<cstdlib>
#include<ctime> 
#include<fstream>
using namespace std;

struct student
{
	char no[11];
	char name[10];
	char school[10];
};

int main()
{
	srand((unsigned int)time(NULL));
	ifstream fin;
	ofstream fout;
	fin.open("stulist.txt", ios::in);
	fout.open("result.txt", ios::out);
	if (fin.is_open() == 0)
	{
		cout << "打开输入文件失败" << endl;
		return -1;
	}
	if (fout.is_open() == 0)
	{
		cout << "打开输出文件失败" << endl;
		fin.close();
		return -1;
	}
	int in_num,total_num;
	fin >> in_num >> total_num;
	/* 储存读入的报名学生信息 */
	struct student* p = new(nothrow) struct student[total_num];
	for (int i = 0; i < total_num; i++)
	{
		fin >> (p + i)->no >> (p + i)->name >> (p + i)->school;
	}
	int count = 0;
	int* mark = new(nothrow) int[in_num];
	while (count < in_num)
	{
		int i = rand() % in_num;
		bool is_pick = 0;
		for (int j = 0; j < count; j++)
		{
			if (i == mark[j])
				is_pick = 1;
		}
		if(!is_pick)
		{
			mark[count] = i;
			count++;
			fout << (p + i)->no << " " << (p + i)->name << " " << (p + i)->school << endl;
		}
	}
	fin.close();
	fout.close();
	delete[]mark;
	delete[]p;
	/* 选择连续空间当数组用
	一方面，操作起来更加方便快捷
	另一方面，代码逻辑更加清晰
	*/
	return 0;
}
