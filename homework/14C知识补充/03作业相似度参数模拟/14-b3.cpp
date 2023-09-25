/*2152041 �ƿ� ����*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int usage(const char* const procname)
{
	cout << "Usage: " << procname << " Ҫ����ѧ��/all ƥ��ѧ��/all Դ������/all ���ƶȷ�ֵ(60-100) ���(filename/screen)" << endl << endl;
	cout << "e.g. : " << procname << " 2159999 2159998 all       80 screen" << endl;
	cout << "       " << procname << " 2159999 all     14-b1.cpp 75 result.txt" << endl;
	cout << "       " << procname << " all     all     14-b2.cpp 80 check.dat" << endl;
	cout << "       " << procname << " all     all     all       85 screen" << endl;

	return 0;
}

int check_student(const char *inspect_stu_num, const char *match_stu_name)
{
	if (!strcmp(inspect_stu_num, "all"))//�������all
	{
		if (strcmp(match_stu_name, "all"))//��ƥ�䲻��all
		{
			if (strlen(match_stu_name) != 7)
			{
				cout << "Ҫƥ���ѧ�Ų���7λ" << endl;
				return 1;
			}
			else
			{
				for (int i = 0; i < 6; i++)
				{
					if (match_stu_name[i] < '0' || match_stu_name[i] > '9')
					{
						cout << "Ҫƥ���ѧ�Ų���7λ����" << endl;
						return 1;
					}
				}
			}
			cout << "���ѧ����all��ƥ��ѧ�ű�����all" << endl;
			return 1;
		}
	}
	else if (strcmp(inspect_stu_num, "all"))//����鲻��all
	{
		if (strlen(inspect_stu_num) != 7)//����鲻��7λ
		{
			cout << "Ҫ����ѧ�Ų���7λ" << endl;
			return 1;
		}
		else
		{
			for (int i = 0; i < 6; i++)//����鲻��7λ����
			{
				if (inspect_stu_num[i] < '0' || inspect_stu_num[i] > '9')
				{
					cout << "Ҫ����ѧ�Ų���7λ����" << endl;
					return 1;
				}
			}
			if (strcmp(match_stu_name, "all"))//�����ȷ����ƥ�䲻��all
			{
				if (strlen(match_stu_name) != 7)
				{
					cout << "Ҫƥ���ѧ�Ų���7λ" << endl;
					return 1;
				}
				else
				{
					for (int i = 0; i < 6; i++)
					{
						if (match_stu_name[i] < '0' || match_stu_name[i] > '9')
						{
							cout << "Ҫƥ���ѧ�Ų���7λ����" << endl;
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
		cout << "Դ�����ļ���������32�ֽ�" << endl;
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
			cout << "�������ļ���������32�ֽ�" << endl;
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
	cout << "�������ͨ��" << endl;
	cout << "���ѧ�ţ�" << argv[1] << endl;
	cout << "ƥ��ѧ�ţ�" << argv[2] << endl;
	cout << "Դ�ļ�����" << argv[3] << endl;
	cout << "ƥ����ֵ��" << argv[4] << endl;
	cout << "���Ŀ�꣺" << argv[5] << endl;
	return 0;
}