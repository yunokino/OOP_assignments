/*2152041 计科 王浩*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int usage(const char* const procname)
{
	cout << "Usage: " << procname << " 要检查的学号/all 匹配学号/all 源程序名/all 相似度阀值(60-100) 输出(filename/screen)" << endl << endl;
	cout << "e.g. : " << procname << " 2159999 2159998 all       80 screen" << endl;
	cout << "       " << procname << " 2159999 all     14-b1.cpp 75 result.txt" << endl;
	cout << "       " << procname << " all     all     14-b2.cpp 80 check.dat" << endl;
	cout << "       " << procname << " all     all     all       85 screen" << endl;

	return 0;
}

int check_student(const char *inspect_stu_num, const char *match_stu_name)
{
	if (!strcmp(inspect_stu_num, "all"))//若检查是all
	{
		if (strcmp(match_stu_name, "all"))//若匹配不是all
		{
			if (strlen(match_stu_name) != 7)
			{
				cout << "要匹配的学号不是7位" << endl;
				return 1;
			}
			else
			{
				for (int i = 0; i < 6; i++)
				{
					if (match_stu_name[i] < '0' || match_stu_name[i] > '9')
					{
						cout << "要匹配的学号不是7位数字" << endl;
						return 1;
					}
				}
			}
			cout << "检查学号是all，匹配学号必须是all" << endl;
			return 1;
		}
	}
	else if (strcmp(inspect_stu_num, "all"))//若检查不是all
	{
		if (strlen(inspect_stu_num) != 7)//若检查不是7位
		{
			cout << "要检查的学号不是7位" << endl;
			return 1;
		}
		else
		{
			for (int i = 0; i < 6; i++)//若检查不是7位数字
			{
				if (inspect_stu_num[i] < '0' || inspect_stu_num[i] > '9')
				{
					cout << "要检查的学号不是7位数字" << endl;
					return 1;
				}
			}
			if (strcmp(match_stu_name, "all"))//检查正确后，若匹配不是all
			{
				if (strlen(match_stu_name) != 7)
				{
					cout << "要匹配的学号不是7位" << endl;
					return 1;
				}
				else
				{
					for (int i = 0; i < 6; i++)
					{
						if (match_stu_name[i] < '0' || match_stu_name[i] > '9')
						{
							cout << "要匹配的学号不是7位数字" << endl;
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

int check_file(const char*file_name)
{
	if (strlen(file_name) > 32)
	{
		cout << "源程序文件名超过了32字节" << endl;
		return 1;
	}
	return 0;
}

int check_similarity(char* similarity)
{
	if ((strlen(similarity) == 3 && !strcmp(similarity, "100")) ||
		(strlen(similarity) == 2 && similarity[0] >= '6'&&similarity[0] <= '9' && similarity[1] >= '0' && similarity[1] <= '9'))
	{
		
		return 0;
	}
	else
	{
		strcpy(similarity, "80");
		return 0;
	}
}

int check_output(const char* output)
{
	if(strcmp(output,"screen"))
		return 0;
	else
	{
		if (strlen(output) > 32)
		{
			cout << "输出结果文件名超过了32字节" << endl;
			return 1;
		}		
	}
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 6)
	{
		usage(argv[0]);
		return 0;
	}
	if (check_student(argv[1], argv[2]))
		return 0;
	if(check_file(argv[3]))
		return 0;
	if(check_similarity(argv[4]))
		return 0;
	if(check_output(argv[5]))
		return 0;
	cout << "参数检查通过" << endl;
	cout << "检查学号：" << argv[1] << endl;
	cout << "匹配学号：" << argv[2] << endl;
	cout << "源文件名：" << argv[3] << endl;
	cout << "匹配阈值：" << argv[4] << endl;
	cout << "输出目标：" << argv[5] << endl;
	return 0;
}