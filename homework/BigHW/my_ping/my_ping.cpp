/* 2152041 计科 王浩 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
//可根据需要再加入其它需要的头文件
#include "../include/class_aat.h"
using namespace std;

/* 运行自行添加其它函数，也可以将自定义函数放在其它cpp中 */
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main(int argc, char* argv[])
{
	args_analyse_tools args[] = {
		args_analyse_tools("--l",      ST_EXTARGS_TYPE::int_with_default, 1, 64,32,64000),
		args_analyse_tools("--n",      ST_EXTARGS_TYPE::int_with_default, 1, 4,1,1024),
		args_analyse_tools("--t",      ST_EXTARGS_TYPE::boolean,       0, false),
		args_analyse_tools()  //最后一个，用于结束
	};
	if (argc < 2)
	{
		args_analyse_print(args);
		return -1;
	}
	int cur_argc = args_analyse_process(argc, argv, args, 1);
	if (cur_argc < 0)
		return -1;
	if (argc == cur_argc || cur_argc != argc - 1 || check_ip(argv[cur_argc]) == -1)//短路运算符，不会报错的
	{
		cout << "IP地址错误" << endl;
		return -1;
	}
	cout << "参数检查通过" << endl;
	cout << "-l 参数：" << args[0].get_int() << endl;
	cout << "-n 参数：" << args[1].get_int() << endl;
	cout << "-t 参数：" << args[2].existed() << endl;
	cout << "IP地址：" << argv[cur_argc] << endl;
	return 0;
}

