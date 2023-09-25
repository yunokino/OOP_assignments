/*2152041 计科 王浩*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

typedef struct paramter
{
	char ip[16];
	int l = 64;
	int n = 4;
	bool t = 0;
}paramter;

int usage(const char* const procname)
{
	cout << "Usage: ";
	cout << procname << " [-l 大小] [-n 数量] [-t] IP地址" << endl;
	cout << "       ==================================" << endl;
	cout << "       参数 附加参数 范围        默认值" << endl;
	cout << "       ==================================" << endl;
	cout << "       -l    1       [32..64000] 64" << endl;
	cout << "       -n    1       [1..1024]   4" << endl;
	cout << "       -t    0       [0..1]      0" << endl;
	cout << "       ==================================" << endl;
	return 0;
}

int check_ip(const char* ip, paramter &check)
{
	bool right = 1;
	int count = 0;
	int num = -1;
	if (ip[0] >= '0' && ip[0] <= '9')
		num = 0;
	for (unsigned int i = 0; i < strlen(ip); i++)
	{
		if (ip[i] != '.')
		{
			if (ip[i] < '0' || ip[i] > '9')
			{
				right = 0;
				break;
			}
			num *= 10;
			num += ip[i] - '0';
		}
		else
		{
			if (ip[i + 1] < '0' || ip[i + 1] > '9')
			{
				right = 0;
				break;
			}
			if (num < 0 || num > 255)
				right = 0;
			else
			{
				count++;
				num = 0;
			}
		}
	}
	if (num < 0 || num > 255)
		right = 0;
	else
		count++;
	if (count != 4)
		right = 0;
	if (right)
	{
		strcpy(check.ip, ip);
		return 0;
	}
	else
	{
		cout << "IP地址错误" << endl;
		return 1;
	}
}

int check_range(const char* num, int max, int min,int &content)
{
	int tmp = 0;
	for (unsigned int i = 0; i < strlen(num); i++)
	{
		if (num[i] < '0' || num[i] > '9')
			return 1;
		tmp *= 10;
		tmp += num[i] - '0';
	}
	if (tmp < min || tmp > max)
		return 1;
	else
	{
		content = tmp;
		return 0;
	}
}

int main(int argc, char *argv[])
{
	paramter check;
	if (argc < 2)
	{
		usage(argv[0]);
		return 0;
	}
	if(check_ip(argv[argc - 1], check))
		return 0;
	for (int i = 1; i < argc - 1; i++)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
			case 'l':
				if (argv[++i][0] == '-' || i == argc - 1)
				{
					cout << "参数-l没有后续参数" << endl;
					return 0;
				}
				if (check_range(argv[i], 64000, 32, check.l))
				{
					check.l = 64;
				}
				break;
			case 'n':
				if (argv[++i][0] == '-' || i == argc - 1)
				{
					cout << "参数-n没有后续参数" << endl;
					return 0;
				}
				if (check_range(argv[i], 1024, 1,check.n))
				{
					check.n = 4;
				}
				break;
			case 't':
				check.t = true;
				break;
			default:
				cout << "参数" << argv[i] << "不存在" << endl;
				return 0;
				break;
			}
		}
		else
		{
			cout << "参数" << argv[i] << "不是以-开头的合法参数" << endl;
			return 0;
		}
	}
	cout << "参数检查通过" << endl;
	cout << "-l 参数：" << check.l << endl;
	cout << "-n 参数：" << check.n << endl;
	cout << "-t 参数：" << check.t << endl;
	cout << "IP地址：" << check.ip << endl;
	return 0;
}