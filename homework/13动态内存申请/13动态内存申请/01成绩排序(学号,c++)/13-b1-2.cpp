/* 2152041 计科 王浩 */
#include<iostream>
#include<fstream>
using namespace std;

struct student
{
	int no;
	char name[9];
	int score;
	int rank;
};

int main()
{
	ifstream fin;
	int num;
	fin.open("student.txt", ios::in);
	if (!fin.is_open())
	{
		printf("打开文件失败\n");
		return -1;
	}
	fin >> num;
	struct student* pointer = new (nothrow)student[num];
	if (pointer == NULL)
		return -1;
	for (int i = 0; i < num; i++)
	{
		fin >> (pointer + i)->no >> (pointer + i)->name >> (pointer + i)->score;
	}
	for (int i = 0; i < num - 1; i++)
		for (int j = 0; j < num - 1 - i; j++)
		{
			if ((pointer + j)->score < (pointer + j + 1)->score)
			{
				int tmp_no, tmp_score;
				char tmp_name[9];
				tmp_no = (pointer + j)->no;
				(pointer + j)->no = (pointer + j + 1)->no;
				(pointer + j + 1)->no = tmp_no;
				for (int k = 0; k < 8; k++)
				{
					tmp_name[k] = (pointer + j)->name[k];
					(pointer + j)->name[k] = (pointer + j + 1)->name[k];
					(pointer + j + 1)->name[k] = tmp_name[k];
				}
				tmp_score = (pointer + j)->score;
				(pointer + j)->score = (pointer + j + 1)->score;
				(pointer + j + 1)->score = tmp_score;
			}
		}
	int old_rank = 0;
	for (int i = 0; i < num; i++)
	{
		if (i == 0)
		{
			old_rank = 1;
			(pointer + i)->rank = 1;
		}
		else
		{
			if ((pointer + i)->score == (pointer + i - 1)->score)
				(pointer + i)->rank = old_rank;
			else
			{
				(pointer + i)->rank = i + 1;
				old_rank = i + 1;
			}
		}
	}
	for (int i = 0; i < num - 1; i++)
		for (int j = 0; j < num - 1 - i; j++)
		{
			if ((pointer + j)->no > (pointer + j + 1)->no)
			{
				int tmp_no, tmp_score, tmp_rank;
				char tmp_name[9];
				tmp_no = (pointer + j)->no;
				(pointer + j)->no = (pointer + j + 1)->no;
				(pointer + j + 1)->no = tmp_no;
				for (int k = 0; k < 8; k++)
				{
					tmp_name[k] = (pointer + j)->name[k];
					(pointer + j)->name[k] = (pointer + j + 1)->name[k];
					(pointer + j + 1)->name[k] = tmp_name[k];
				}
				tmp_score = (pointer + j)->score;
				(pointer + j)->score = (pointer + j + 1)->score;
				(pointer + j + 1)->score = tmp_score;
				tmp_rank = (pointer + j)->rank;
				(pointer + j)->rank = (pointer + j + 1)->rank;
				(pointer + j + 1)->rank = tmp_rank;
			}
		}
	for (int i = 0; i < num; i++)
	{
		cout << (pointer + i)->no <<" " << (pointer + i)->name<<" " << (pointer + i)->score <<" " << (pointer + i)->rank << endl;
	}
	fin.close();
	delete []pointer;
	return 0;
}