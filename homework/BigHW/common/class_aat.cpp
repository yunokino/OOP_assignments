/* 2152041 计科 王浩 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//如有必要，可以加入其它头文件
using namespace std;

#if !ENABLE_LIB_AAT_TOOLS //不使用lib才有效

/* ---------------------------------------------------------------
	 允许加入其它需要static函数（内部工具用）
   ---------------------------------------------------------------- */
static void err_out(const char*str,int type, const char*str2 = NULL)
{
	if (type == 0)
		cout << "参数[" << str << "]非法" << endl;
	else if (type == 1)
		cout << "参数[" << str << "]格式非法" << endl;
	else if (type == 2)
		cout << "参数[" << str << "]重复" << endl;
	else if (type == 3)
		cout << "参数[" << str << "]的附加参数不足";
	else if (type == 4)
		cout << "参数[" << str << "]的附加参数不是整数";
	else if (type == 5)
		cout << "参数["<<str<<"]的附加参数值("<<str2<<")非法";
}

static int find_location(args_analyse_tools* const args,const char*name)
{
	for (int i = 0; args[i].get_name() != ""; i++)
	{
		if (args[i].get_name() == string(name))
			return i;
	}
	return -1;
}

static string int_to_ipaddr(int ip_num)
{
	string ip = "";
	for (int i = 0; i < 4; i++)
	{
		int addr = 0;
		addr = (ip_num >> (3 - i) * 8) & (0xFF);
		ip += to_string(addr);
		if (i != 3)
			ip += ".";
	}
	return ip; //此句根据需要修改
}

static int check_extra_parameter(const char* str, int type, int*int_set = NULL,string *str_set = NULL)
{
	if (type == 1)//检查int型
	{
		int num = 0;
		for (int i = 0; str[i] != '\0'; i++)
		{
			if (i == 0 && str[i] == '-')
				continue;
			if (!(str[i] >= '0' && str[i] <= '9'))
				return -1;
			num = num * 10 + str[i] - '0';
		}
		num = (str[0] == '-' ? -num : num);
		return num;
	}
	else if (type == 2)
	{
		int num = 0;
		for (int i = 0; str[i] != '\0'; i++)
		{
			if (i == 0 && str[i] == '-')
				continue;
			if (!(str[i] >= '0' && str[i] <= '9'))
				return -1;
			num = num * 10 + str[i] - '0';
		}
		num = (str[0] == '-' ? -num : num);
		for (int j = 0; int_set[j] != INVALID_INT_VALUE_OF_SET; j++)
		{
			if (int_set[j] == num)
				return num;
		}
		return -2;
	}
	else if (type == 3)
	{
		for (int j = 0; str_set[j] != ""; j++)
		{
			if (str_set[j] == str)
				return 0;
		}
		return 1;
	}
	else if (type == 4)
	{
		int num = 0;
		int count = 0;
		for (int i = 0; ; i++)
		{
			if (str[i] == '.' || str[i] == '\0')
			{
				if (num < 0 || num >255)
					return -1;
				if (str[i] == '.' && str[i + 1] == '\0')
					return -1;
				num = 0;
				count++;
				if (str[i] == '\0')
					break;
			}
			else if (str[i] >= '0' && str[i] <= '9')
			{
				num = num * 10 + str[i] - '0';
			}
			else
				return -1;
		}
		if (count != 4)
			return -1;
	}
	return 0;
}

/***************************************************************************
	 函数名称：
	 功    能：
	 输入参数：
	 返 回 值：
	 说    明：null
	***************************************************************************/
args_analyse_tools::args_analyse_tools()
{
	args_name = "";
	extargs_type = ST_EXTARGS_TYPE::null;
	extargs_num = 0;

	extargs_bool_default = 0;

	extargs_int_default = 0;	//int型额外参数的缺省值（default）
	extargs_int_min = 0;		//int型额外参数的最小值（min）
	extargs_int_max = 0;		//int型额外参数的最大值（max）
	extargs_int_set = NULL;		//int型额外参数的集合（提示：只是一个指针哦）

	extargs_string_default = "";	//string型额外参数的缺省值(含ipaddr)
	extargs_string_set = NULL;		//string型额外参数的集合（提示：只是一个指针哦）

	extargs_ipaddr_default = 0;		//IP地址缺省值

	args_existed = 0;				//本参数是否出现过（防止相同参数 -n ** -n ** 重复出现）
	extargs_int_value = 0;			//int型额外参数读到的值
	extargs_string_value = "";		//string型额外参数读到的值
	extargs_ipaddr_value = 0;	//IP地址额外参数读到的值（IP地址的内部存储为此形式，字符串形式需要转换）

}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：boolean
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;

	extargs_bool_default = def;

	extargs_int_default = 0;	//int型额外参数的缺省值（default）
	extargs_int_min = 0;		//int型额外参数的最小值（min）
	extargs_int_max = 0;		//int型额外参数的最大值（max）
	extargs_int_set = NULL;		//int型额外参数的集合（提示：只是一个指针哦）

	extargs_string_default = "";	//string型额外参数的缺省值(含ipaddr)
	extargs_string_set = NULL;		//string型额外参数的集合（提示：只是一个指针哦）

	extargs_ipaddr_default = 0;		//IP地址缺省值

	/* 下面这些是变量 */
	args_existed = 0;				//本参数是否出现过（防止相同参数 -n ** -n ** 重复出现）
	extargs_int_value = 0;			//int型额外参数读到的值
	extargs_string_value = "";		//string型额外参数读到的值
	extargs_ipaddr_value = 0;	//IP地址额外参数读到的值（IP地址的内部存储为此形式，字符串形式需要转换）

}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_default、int_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;

	extargs_bool_default = 0;

	extargs_int_default = def;	//int型额外参数的缺省值（default）
	extargs_int_min = _min;		//int型额外参数的最小值（min）
	extargs_int_max = _max;		//int型额外参数的最大值（max）
	extargs_int_set = NULL;		//int型额外参数的集合（提示：只是一个指针哦）

	extargs_string_default = "";	//string型额外参数的缺省值(含ipaddr)
	extargs_string_set = NULL;		//string型额外参数的集合（提示：只是一个指针哦）

	extargs_ipaddr_default = 0;		//IP地址缺省值

	/* 下面这些是变量 */
	args_existed = 0;				//本参数是否出现过（防止相同参数 -n ** -n ** 重复出现）
	extargs_int_value = def;			//int型额外参数读到的值
	extargs_string_value = "";		//string型额外参数读到的值
	extargs_ipaddr_value = 0;	//IP地址额外参数读到的值（IP地址的内部存储为此形式，字符串形式需要转换）

}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_set_default、int_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;

	extargs_bool_default = 0;

	extargs_int_default = *(set+def_of_set_pos);	//int型额外参数的缺省值（default）
	extargs_int_min = 0;		//int型额外参数的最小值（min）
	extargs_int_max = 0;		//int型额外参数的最大值（max）
	int count = 0;
	while (set[count] != INVALID_INT_VALUE_OF_SET)
		count++;
	extargs_int_set = new(nothrow)int[count+1];		//int型额外参数的集合（提示：只是一个指针哦）
	if (extargs_int_set == NULL)
		return;
	for (int i = 0; i < count + 1; i++)
		extargs_int_set[i] = set[i];
	extargs_string_default = "";	//string型额外参数的缺省值(含ipaddr)
	extargs_string_set = NULL;		//string型额外参数的集合（提示：只是一个指针哦）

	extargs_ipaddr_default = 0;		//IP地址缺省值

	/* 下面这些是变量 */
	args_existed = 0;				//本参数是否出现过（防止相同参数 -n ** -n ** 重复出现）
	extargs_int_value = extargs_int_default;			//int型额外参数读到的值
	extargs_string_value = "";		//string型额外参数读到的值
	extargs_ipaddr_value = 0;	//IP地址额外参数读到的值（IP地址的内部存储为此形式，字符串形式需要转换）
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str、ipaddr_with_default、ipaddr_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const string def)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;

	extargs_bool_default = 0;

	extargs_int_default = 0;	//int型额外参数的缺省值（default）
	extargs_int_min = 0;		//int型额外参数的最小值（min）
	extargs_int_max = 0;		//int型额外参数的最大值（max）
	extargs_int_set = NULL;		//int型额外参数的集合（提示：只是一个指针哦）

	extargs_string_default = def;	//string型额外参数的缺省值(含ipaddr)
	extargs_string_set = NULL;		//string型额外参数的集合（提示：只是一个指针哦）

	if (type == ST_EXTARGS_TYPE::ipaddr_with_default)
	{
		unsigned int ipaddr = 0;
		unsigned int hex_ipaddr = 0;
		for (int i = 0; ; i++)
		{
			if (def[i] == '.' || def[i] == '\0')
			{
				hex_ipaddr = hex_ipaddr << 8 | ipaddr;
				ipaddr = 0;
				if (def[i] == '\0')
					break;
			}
			else
				ipaddr = ipaddr * 10 + def[i] - '0';
		}

		extargs_ipaddr_default = hex_ipaddr;
	}
	else
		extargs_ipaddr_default = 0;//IP地址缺省值

	/* 下面这些是变量 */
	args_existed = 0;				//本参数是否出现过（防止相同参数 -n ** -n ** 重复出现）
	extargs_int_value = 0;			//int型额外参数读到的值
	extargs_string_value = extargs_string_default;		//string型额外参数读到的值
	extargs_ipaddr_value = extargs_ipaddr_default;	//IP地址额外参数读到的值（IP地址的内部存储为此形式，字符串形式需要转换）

}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str_with_set_default、str_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;

	extargs_bool_default = 0;

	extargs_int_default = 0;	//int型额外参数的缺省值（default）
	extargs_int_min = 0;		//int型额外参数的最小值（min）
	extargs_int_max = 0;		//int型额外参数的最大值（max）
	extargs_int_set = NULL;		//int型额外参数的集合（提示：只是一个指针哦）

	extargs_string_default = set[def_of_set_pos];	//string型额外参数的缺省值(含ipaddr)
	int count = 0;
	while (set[count] != "")
		count++;
	extargs_string_set = new string [count+1];		//string型额外参数的集合（提示：只是一个指针哦）
	for (int i = 0; i < count + 1; i++)
		extargs_string_set[i] = set[i];

	extargs_ipaddr_default = 0;		//IP地址缺省值

	/* 下面这些是变量 */
	args_existed = 0;				//本参数是否出现过（防止相同参数 -n ** -n ** 重复出现）
	extargs_int_value = extargs_int_default;			//int型额外参数读到的值
	extargs_string_value = extargs_string_default;		//string型额外参数读到的值
	extargs_ipaddr_value = extargs_ipaddr_default;	//IP地址额外参数读到的值（IP地址的内部存储为此形式，字符串形式需要转换）

}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
args_analyse_tools::~args_analyse_tools()
{
	if (extargs_int_set)
		delete[] extargs_int_set;
	if (extargs_string_set)
		delete[] extargs_string_set;
}

/* ---------------------------------------------------------------
	 允许AAT中自定义成员函数的实现（private）
   ---------------------------------------------------------------- */

/***************************************************************************
	 函数名称：
	 功    能：
	 输入参数：
	 返 回 值：
	 说    明：已实现，不要动
	***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return args_name;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：加!!后，只能是0/1
			已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!args_existed;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return extargs_int_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return extargs_string_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return extargs_ipaddr_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：将 extargs_ipaddr_value 的值从 0x7f000001 转为 "127.0.0.1"
 ***************************************************************************/
const string args_analyse_tools::get_str_ipaddr() const
{
	string ip = int_to_ipaddr(extargs_ipaddr_value);;
	return ip; //此句根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：follow_up_args：是否有后续参数
			./log_login --limit 10 --user root                    ：无后续参数，置0
			./ulimits_check --memory 256 --cpu 1 [./log_login ***]：有后续参数，置1
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_process(const int argc, const char* const* const argv, args_analyse_tools* const args, const int follow_up_args)
{
	int loop = 1;
	int pos = 1;//从1开始判断参数
	for (; pos < argc; pos++)//开始分析
	{
		if (!strncmp(argv[pos],"--",2))
		{
			int type = find_location(args, argv[pos]);
			if (type != -1)
			{
				if (args[type].extargs_type == ST_EXTARGS_TYPE::boolean)
					type = 0;
				else if (args[type].extargs_type == ST_EXTARGS_TYPE::int_with_default)
					type = 1;
				else if (args[type].extargs_type == ST_EXTARGS_TYPE::int_with_error)
					type = 2;
				else if (args[type].extargs_type == ST_EXTARGS_TYPE::int_with_set_default)
					type = 3;
				else if (args[type].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
					type = 4;
				else if (args[type].extargs_type == ST_EXTARGS_TYPE::str)
					type = 5;
				else if (args[type].extargs_type == ST_EXTARGS_TYPE::str_with_set_default)
					type = 6;
				else if (args[type].extargs_type == ST_EXTARGS_TYPE::str_with_set_error)
					type = 7;
				else if (args[type].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default)
					type = 8;
				else if (args[type].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error)
					type = 9;
				else;
			}
			int i = find_location(args, argv[pos]);
			int num = 0;
			unsigned int ipaddr = 0;
			unsigned int hex_ipaddr = 0;
			switch (type)
			{
			case -1:
				err_out(argv[pos], 0);
				return -1;
				break;
			case 0://bool型

				if (!args[i].args_existed)
					args[i].args_existed = 1;
				else
				{
					err_out(argv[pos], 2);
					return -1;
				}
				break;
			case 1://intdef
			case 2://interr
				if (args[i].args_existed)
				{
					err_out(argv[pos], 2);
					return -1;
				}
				if (pos == argc - 1 || !strncmp("--", argv[pos + 1], 2))
				{
					err_out(argv[pos], 3);
					cout << "(类型:int,范围[";
					cout << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "]";
					if (type == 1)
						cout << "缺省:" << args[i].extargs_int_default;
					cout << ")" << endl;
					return -1;
				}
				num = check_extra_parameter(argv[pos + 1], 1);
				if (num == -1)
				{
					err_out(argv[pos], 4);
					cout << "(类型:int,范围[";
					cout << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "]";
					if (type == 1)
						cout << "缺省:" << args[i].extargs_int_default;
					cout << ")" << endl;
					return -1;
				}
				if (num < args[i].extargs_int_min || num > args[i].extargs_int_max)
				{
					if (type == 1)
					{
						args[i].extargs_int_value = args[i].extargs_int_default;
						args[i].args_existed = 1;
						pos += args[i].extargs_num;
						break;
					}
					else if (type == 2)
					{
						err_out(argv[pos], 5, argv[pos + 1]);
						cout << "(类型:int,范围[";
						cout << args[i].extargs_int_min << ".." << args[i].extargs_int_max << "]";
						cout << ")" << endl;
						return -1;
					}
				}
				args[i].extargs_int_value = num;
				args[i].args_existed = 1;
				pos += args[i].extargs_num;
				break;
			case 3://intsetdef
			case 4://intseterr
				if (args[i].args_existed)
				{
					err_out(argv[pos], 2);
					return -1;
				}
				if (pos == argc - 1 || !strncmp("--", argv[pos + 1], 2))
				{
					err_out(argv[pos], 3);
					cout << "(类型:int,可取值[";
					for (int j = 0; args[i].extargs_int_set[j] != INVALID_INT_VALUE_OF_SET; j++)
					{
						if (args[i].extargs_int_set[j + 1] != INVALID_INT_VALUE_OF_SET)
							cout << args[i].extargs_int_set[j] << "/";
						else
							cout << args[i].extargs_int_set[j];
					}
					cout << "]";
					if (type == 3)
						cout << " 缺省:" << args[i].extargs_int_default;
					cout << ")" << endl;
					return -1;
				}
				num = check_extra_parameter(argv[pos + 1], 2, args[i].extargs_int_set);
				if (num == -1)
				{
					err_out(argv[pos], 4);
					cout << "(类型:int,可取值[";
					for (int j = 0; args[i].extargs_int_set[j] != INVALID_INT_VALUE_OF_SET; j++)
					{
						if (args[i].extargs_int_set[j + 1] != INVALID_INT_VALUE_OF_SET)
							cout << args[i].extargs_int_set[j] << "/";
						else
							cout << args[i].extargs_int_set[j];
					}
					cout << "]";
					if (type == 3)
						cout << " 缺省:" << args[i].extargs_int_default;
					cout << ")" << endl;
					return -1;
				}
				if (num == -2)
				{
					if (type == 3)
					{
						args[i].extargs_int_value = args[i].extargs_int_default;
						args[i].args_existed = 1;
						pos += args[i].extargs_num;
						break;
					}
					else if (type == 4)
					{
						err_out(argv[pos], 5, argv[pos + 1]);
						cout << "(类型:int,可取值[";
						for (int j = 0; args[i].extargs_int_set[j] != INVALID_INT_VALUE_OF_SET; j++)
						{
							if (args[i].extargs_int_set[j + 1] != INVALID_INT_VALUE_OF_SET)
								cout << args[i].extargs_int_set[j] << "/";
							else
								cout << args[i].extargs_int_set[j];
						}
						cout << "])" << endl;
						return -1;
					}
				}
				args[i].extargs_int_value = num;
				args[i].args_existed = 1;
				pos += args[i].extargs_num;
				break;
			case 5://Str1
				if (args[i].args_existed)
				{
					err_out(argv[pos], 2);
					return -1;
				}
				if (pos == argc - 1 || !strncmp("--", argv[pos + 1], 2))
				{
					err_out(argv[pos], 3);
					cout << "(类型:string " ;
					if (args[i].extargs_string_default!="")
						cout << "缺省:" << args[i].extargs_string_default;
					cout << ")" << endl;
					return -1;
				}
				args[i].args_existed = 1;
				args[i].extargs_string_value = argv[pos+1];
				pos += args[i].extargs_num;
				break;
			case 6://StringSETWithDefault
			case 7://StringSETWithError
				if (args[i].args_existed)
				{
					err_out(argv[pos], 2);
					return -1;
				}
				if (pos == argc - 1 || !strncmp("--", argv[pos + 1], 2))
				{
					err_out(argv[pos], 3);
					cout << "(类型:string ";
					cout << "可取值[";
					for (int j = 0; args[i].extargs_string_set[j] != ""; j++)
					{
						if (args[i].extargs_string_set[j + 1] != "")
							cout << args[i].extargs_string_set[j] << "/";
						else
							cout << args[i].extargs_string_set[j];
					}
					cout << "] ";
					if (type == 6)
						cout << "缺省:" << args[i].extargs_string_default;
					cout << ")" << endl;
					return -1;
				}
				if (check_extra_parameter(argv[pos + 1], 3, NULL, args[i].extargs_string_set))
				{
					if (type == 6)
					{
						args[i].args_existed = 1;
						args[i].extargs_string_value = args[i].extargs_string_default;
						pos += args[i].extargs_num;
						break;
					}
					else if (type == 7)
					{
						err_out(argv[pos], 5, argv[pos + 1]);
						cout << "(类型:string ";
						cout << "可取值[";
						for (int j = 0; args[i].extargs_string_set[j] != ""; j++)
						{
							if (args[i].extargs_string_set[j + 1] != "")
								cout << args[i].extargs_string_set[j] << "/";
							else
								cout << args[i].extargs_string_set[j];
						}
						cout << "])" << endl;
						return -1;
					}
					else;
				}
				args[i].args_existed = 1;
				args[i].extargs_string_value = argv[pos + 1];
				pos+=args[i].extargs_num;
				break;
			case 8://IPAddrWithDefault
			case 9://IPAddrWithError
				if (args[i].args_existed)
				{
					err_out(argv[pos], 2);
					return -1;
				}
				if (pos == argc - 1 || !strncmp("--", argv[pos + 1], 2))
				{
					err_out(argv[pos], 3);
					cout << "(类型:IP地址 ";
					if (type == 8)
						cout << "缺省:" << args[i].extargs_ipaddr_default;
					cout << ")" << endl;
					return -1;
				}
				num = check_extra_parameter(argv[pos + 1], 4);
				if (num == -1)
				{
					if (type == 8)
					{
						args[i].extargs_ipaddr_value = args[i].extargs_ipaddr_default;
						args[i].args_existed = 1;
						pos += args[i].extargs_num;
						break;
					}
					else if (type == 9)
					{
						err_out(argv[pos], 5, argv[pos + 1]);
						cout << "(类型:IP地址 )" << endl;
						return -1;
					}
				}
				for (int i = 0; ; i++)
				{
					if (argv[pos + 1][i] == '.' || argv[pos + 1][i] == '\0')
					{
						hex_ipaddr = hex_ipaddr << 8 | ipaddr;
						ipaddr = 0;
						if (argv[pos + 1][i] == '\0')
							break;
					}
					else
						ipaddr = ipaddr * 10 + argv[pos + 1][i] - '0';
				}
				args[i].extargs_ipaddr_value = hex_ipaddr;
				args[i].args_existed = 1;
				pos += args[i].extargs_num;
				break;
			default:
				break;
			}
		}
		else
		{
			//在check_main_parameter时检查他们的附加参数，故出现此情况时已经非法
			if (follow_up_args)
				break;
			err_out(argv[pos], 1);
			return -1;
		}
	}
	return pos; //此句根据需要修改
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_print(const args_analyse_tools* const args)
{
	int name_len = 0;
	for (int i = 0; args[i].extargs_type != ST_EXTARGS_TYPE::null; i++)
	{
		if (name_len < (int)args[i].args_name.size())
			name_len = (int)args[i].args_name.size();
	}
	name_len++;
	int type_len = 22;
	int default_len = 17;
	int exists_len = 7;
	int value_len = 17;
	cout << "================================================================================================================" << endl;
	cout << left<<setw(name_len) << "name" << setw(type_len) << "type" << setw(default_len) << "default"
		<< setw(exists_len) << "exists" << setw(value_len) << "value" << setw(0) << "range/set" << endl;
	cout << "================================================================================================================" << endl;
	for (int i = 0; args[i].extargs_type != ST_EXTARGS_TYPE::null; i++)
	{
		cout << left << setw(name_len) << args[i].args_name ; 
		if (args[i].extargs_type == ST_EXTARGS_TYPE::boolean)
		{
			cout << setw(type_len) << "Bool";
			cout << setw(default_len) << (args[i].extargs_bool_default?"true":"false");
			cout << setw(exists_len) << args[i].args_existed;
			cout << setw(value_len) <<(args[i].args_existed?"true":"/");
			cout << setw(0) << "/" << endl;
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_default 
			|| args[i].extargs_type == ST_EXTARGS_TYPE::int_with_error)
		{
			if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_default)
			{
				cout << setw(type_len) << "IntWithDefault";
				cout << setw(default_len) << args[i].extargs_int_default;
			}
			else
			{
				cout << setw(type_len) << "IntWithError";
				cout << setw(default_len) << "/";
			}
			cout << setw(exists_len) << args[i].args_existed;
			if (args[i].args_existed)
				cout << setw(value_len) << args[i].extargs_int_value;
			else
				cout << setw(value_len) << "/";
			cout << setw(0) << "["<<args[i].extargs_int_min<<".."<<args[i].extargs_int_max<<"]" << endl;
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_default
			|| args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
		{
			if (args[i].extargs_type == ST_EXTARGS_TYPE::int_with_set_default)
			{
				cout << setw(type_len) << "IntSETWithDefault";
				cout << setw(default_len) << args[i].extargs_int_default;
			}
			else
			{
				cout << setw(type_len) << "IntSETWithError";
				cout << setw(default_len) << "/";
			}
			cout << setw(exists_len) << args[i].args_existed;
			if (args[i].args_existed)
				cout << setw(value_len) << args[i].extargs_int_value;
			else
				cout << setw(value_len) << "/";
			for (int j = 0; args[i].extargs_int_set[j]!=INVALID_INT_VALUE_OF_SET; j++)
			{
				if(args[i].extargs_int_set[j+1] != INVALID_INT_VALUE_OF_SET)
					cout << args[i].extargs_int_set[j]<<"/";
				else
					cout << args[i].extargs_int_set[j] << endl;
			}
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::str)
		{
			cout << setw(type_len) << "String";
			if (args[i].extargs_string_default == "")
				cout << setw(default_len) << "/";
			else
				cout << setw(default_len) << args[i].extargs_string_default;
			cout << setw(exists_len) << args[i].args_existed;
			if (args[i].args_existed)
				cout << setw(value_len) << args[i].extargs_string_value;
			else
				cout << setw(value_len) << "/";
			cout << setw(0) << "/" << endl;
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_default
			|| args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_error)
		{
			if (args[i].extargs_type == ST_EXTARGS_TYPE::str_with_set_default)
			{
				cout << setw(type_len) << "StringSETWithDefault";
				cout << setw(default_len) << args[i].extargs_string_default;
			}
			else
			{
				cout << setw(type_len) << "StringSETWithError";
				cout << setw(default_len) << "/";
			}
			cout << setw(exists_len) << args[i].args_existed;
			if (args[i].args_existed)
				cout << setw(value_len) << args[i].extargs_string_value;
			else
				cout << setw(value_len) << "/";
			for (int j = 0; args[i].extargs_string_set[j] != ""; j++)
			{
				if (args[i].extargs_string_set[j + 1] != "")
					cout << args[i].extargs_string_set[j] << "/";
				else
					cout << args[i].extargs_string_set[j] << endl;
			}
		}
		else if (args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default
			|| args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error)
		{
			if (args[i].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default)
			{
				cout << setw(type_len) << "IPAddrWithDefault";
				cout << setw(default_len) << int_to_ipaddr(args[i].extargs_ipaddr_default);
			}
			else
			{
				cout << setw(type_len) << "IPAddrWithError";
				cout << setw(default_len) << "/";
			}
			cout << setw(exists_len) << args[i].args_existed;
			if (args[i].args_existed)
				cout << setw(value_len) << args[i].get_str_ipaddr();
			else
				cout << setw(value_len) << "/";
			cout << setw(0) << "/" << endl;
		}
		else;
	}
	cout << "================================================================================================================" << endl;
	cout << endl;

	return 0; //此句根据需要修改
}

#endif // !ENABLE_LIB_AAT_TOOLS