/* 2152041 �ƿ� ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
//�ɸ�����Ҫ�ټ���������Ҫ��ͷ�ļ�
#include "../include/class_aat.h"
using namespace std;

/* ���������������������Ҳ���Խ��Զ��庯����������cpp�� */
int check_ip(const char* ip)
{
	bool right = 1;
	int num = 0;
	int count = 0;
	for (int i = 0; ; i++)
	{
		if (ip[i] == '.' || ip[i] == '\0')
		{
			if (num < 0 || num >255)
				return -1;
			if (ip[i] == '.' && ip[i + 1] == '\0')
				return -1;
			num = 0;
			count++;
			if (ip[i] == '\0')
				break;
		}
		else if (ip[i] >= '0' && ip[i] <= '9')
		{
			num = num * 10 + ip[i] - '0';
		}
		else
			return -1;
	}
	if (count != 4)
		return -1;
	if (right)
		return 0;
	else
		return -1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main(int argc, char* argv[])
{
	args_analyse_tools args[] = {
		args_analyse_tools("--l",      ST_EXTARGS_TYPE::int_with_default, 1, 64,32,64000),
		args_analyse_tools("--n",      ST_EXTARGS_TYPE::int_with_default, 1, 4,1,1024),
		args_analyse_tools("--t",      ST_EXTARGS_TYPE::boolean,       0, false),
		args_analyse_tools()  //���һ�������ڽ���
	};
	if (argc < 2)
	{
		args_analyse_print(args);
		return -1;
	}
	int cur_argc = args_analyse_process(argc, argv, args, 1);
	if (cur_argc < 0)
		return -1;
	if (argc == cur_argc || cur_argc != argc - 1 || check_ip(argv[cur_argc]) == -1)//��·����������ᱨ���
	{
		cout << "IP��ַ����" << endl;
		return -1;
	}
	cout << "�������ͨ��" << endl;
	cout << "-l ������" << args[0].get_int() << endl;
	cout << "-n ������" << args[1].get_int() << endl;
	cout << "-t ������" << args[2].existed() << endl;
	cout << "IP��ַ��" << argv[cur_argc] << endl;
	return 0;
}

