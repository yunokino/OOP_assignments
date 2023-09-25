/* 2152041 计科 王浩 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <sstream>
#include "../include/class_aat.h"
#include "../include/cmd_console_tools.h"
#include "txt_compare.h"
#include <string>
#include <fstream>
using namespace std;

/* 允许添加需要的内容 */
void trim(string& str, const string type)
{
	if (str.empty())
		return;
	int left_end = 0;
	int right_start = (int)str.size();
	for (int i = 0; str[i] == ' '; i++)
		left_end++;
	for (int i = (int)str.size() - 1; i>= 0 &&(str[i] == ' ' || str[i] == '\r' || str[i] == '\t'|| str[i] == '\v' || str[i] == '\b' || str[i] == '\a'); i--)
		right_start--;
	if (type == "none")
	{
		return;
	}
	else if (type == "left")
	{
		string tmp = "";
		for (int i = left_end; i < (int)str.size(); i++)
			tmp += str[i];
		str = tmp;
	}
	else if (type == "right")
	{
		string tmp = "";
		for (int i = 0; i < right_start; i++)
			tmp += str[i];
		str = tmp;
	}
	else if (type == "all")
	{
		string tmp = "";
		for (int i = left_end; i < right_start; i++)
			tmp += str[i];
		str = tmp;
	}
	else;
}

int check_file(const char* str)//检查文件格式
{
	int file_os = 2;//0为windows，1为linux，2为无法识别
	ifstream in(str, ios::in | ios::binary);
	if ((int)in.is_open() == -1)
	{
		cout << "文件打开失败" << endl;
		return -1;
	}
	char ch = '0';//遍历文件字节
	char pre_ch = ch;//记录前置字节内容
	while ((ch = in.get()) != EOF)
	{
		if ((int)ch == 0x0A)
		{
			if ((int)pre_ch == 0x0D && file_os == 1)
			{
				file_os = 2;
				break;
			}
			else if ((int)pre_ch != 0x0D && file_os == 0)
			{
				file_os = 2;
				break;
			}
			else if ((int)pre_ch == 0x0D)
			{
				file_os = 0;
			}
			else if ((int)pre_ch != 0x0D)
			{
				file_os = 1;
			}
			else;
		}
		pre_ch = ch;
	}
	in.close();
	return file_os;
}

void print_line(string line,int*diff)
{
	if (line.size() == 1 && line[0] == char(EOF))
	{
		cout << "<EOF>" << endl;
		return;
	}
	for (int i = 0; i < (int)line.size(); i++)
	{
		if (diff[i] == 1)
			cct_setcolor(14, 4);
		if (line[i] == '\a' || line[i] == '\r' || line[i] == '\n' || line[i] == '\v'
			|| line[i] == '\b' || line[i] == '\t')
			cout << "X";
		else
			cout << line[i];
		cct_setcolor();
	}
	if (line.size() == 0)
	{
		if(diff[0] = 1)
			cct_setcolor(14, 4);
		cout << "<EMPTY>";
		cct_setcolor();
	}
	cout << "<CR>" << endl;
}

void print_hex(string line)
{
	if (line.size() == 1 && line[0] == char(EOF))
	{
		cout << "<EOF>" << endl;
		return;
	}
	if (line.empty())
	{
		cout << "<EMPTY>" << endl;
		return;
	}
	int count = 0;
	int store_line[16] = { 0 };
	/* 请原谅我直接将前面的C方式代码拿过来了... */
	while (count < (int)line.size())
	{
		if (count % 16 == 0)
		{
			printf("%08x", count);
			printf("  ");
			for (int j = 0; j < 16; j++)
			{
				store_line[j] = 1000;//用一个ch达不到的值来标记尚未储存的状态
			}
		}
		store_line[count % 16] = (int)line[count];
		if (count % 16 == 8)
			printf("- ");
		printf("%02x ", (unsigned char)line[count]);
		if (count % 16 == 15)
		{
			printf("    ");
			for (int j = 0; j < 16; j++)
			{
				if (store_line[j] != 1000)
				{
					if ((store_line[j] < 33 || store_line[j] > 126))
						printf(".");
					else
						printf("%c", store_line[j]);
				}
			}
			printf("\n");
		}
		count++;
	}
	/* 处理最后一行提前终止下的输出 */
	if (count % 16 != 0)
	{
		while (count % 16 != 0)
		{
			if (count % 16 == 8)
				printf("  ");
			printf("   ");
			count++;
		}
		printf("    ");
		for (int j = 0; j < 15; j++)
		{
			if (store_line[j] != 1000)
			{
				if ((store_line[j] < 33 || store_line[j] > 126))
					printf(".");
				else
					printf("%c", store_line[j]);
			}
		}
		printf("\n");
	}
}

void print_ruler(int len)
{
	int count = 0;
	for (int i = 0; i < len + 4; i++)
		if (i % 10 == 0)
			count++;
	for (int i = 0; i < 8; i++)
		cout << " ";
	for (int i = 0; i < count*10; i++)
		cout << "-";
	cout << endl;
	for (int i = 0; i < 8; i++)
		cout << " ";
	int tmp = 0;
	for (int i = 0; i < count*10; i++)
		if (i % 10 == 0)
		{
			cout << left << setw(10) << tmp;
			tmp++;
		}
	cout << endl;
	for (int i = 0; i < 8; i++)
		cout << " ";
	for (int i = 0; i < count*10; i++)
		cout << i % 10;
	cout << endl;
	for (int i = 0; i < 8; i++)
		cout << " ";
	for (int i = 0; i < count * 10; i++)
		cout << "-";
	cout << endl;
}

int compare_line(string line1, string line2, const args_analyse_tools* args,int line_count1,int line_count2,int &diff_count)
{
	if (line1 == line2)
	{
		if (args[1].existed())//如果debug，那么相同的也要打印
		{
			cout << "第[" << line_count1 << " / " << line_count2 << "]行 - 一致 : ";
			if (line1.empty() || (line1.size() == 1 && line1[0] == char(EOF)))
				cout << "<EMPTY>";
			else
				cout << line1 ;
			cout << "<CR>" << endl;
			cout << endl;
		}
		return 1;
	}
	if (args[10].get_string() == "none" && !args[1].existed())
		return 0;
	diff_count++;
	int* diff = new int[max(line1.size(), line2.size())];
	for (int i = 0; i < (int)max(line1.size(), line2.size()); i++)
		diff[i] = 0;//初始化
	if (line1.size() == line2.size())//两行等长
	{
		int first_diff = 1;
		int exist_eof = (line1.size() == 1 && line1[0] == char(EOF)) || (line2.size() == 1 && line2[0] == char(EOF));
		cout << "第["<<line_count1<<" / "<<line_count2<<"]行 -";
		for (int i = 0; i < (int)line1.size(); i++)
		{
			if (line1[i] != line2[i])
			{
				if (first_diff)
				{
					first_diff = 0;
					cout << "从第" << i << "个字符开始有差异:" << endl;
				}
				diff[i] = 1;
			}
		}
	}
	else
	{
		/* 先比较前半部分 */
		int first_diff = 1;
		int exist_eof = (line1.size() == 1 && line1[0] == char(EOF)) || (line2.size() == 1 && line2[0] == char(EOF));
		cout << "第[" << line_count1 << " / " << line_count2 << "]行 -";
		for (int i = 0; i < (int)min(line1.size(),line2.size()); i++)
		{
			if (line1[i] != line2[i])
			{
				if (first_diff && !exist_eof)
				{
					cout << "从第" << i << "个字符开始有差异:" << endl;
					first_diff = 0;
				}
				diff[i] = 1;
			}
		}
		if (exist_eof)
			first_diff = 1;
		if (first_diff == 1)
			cout << "文件" << ((line1 > line2) ? "1" : "2") << "的尾部有多余字符:" << endl;
		for (int i = min(line1.size(), line2.size()); i < (int)max(line1.size(), line2.size());i++)
			diff[i] = 1;
	}
	if (args[10].get_string() == "detailed")
	{
		print_ruler(max(line1.size(), line2.size()));
	}
	cout << "文件1 : ";
	print_line(line1, diff);
	cout << "文件2 : ";
	print_line(line2, diff);
	if (args[10].get_string() == "detailed")
	{
		cout << "文件1(HEX):" << endl;
		print_hex(line1);
		cout << "文件2(HEX):" << endl;
		print_hex(line2);
	}
	cout << endl;
	delete[]diff;
	return 0;
}

void print_tips(int diff_count, const string type)
{
	if (diff_count != 0)
	{
		cout << "====================================================================================================" << endl;
		cout << "在指定检查条件下共" << diff_count << "行有差异." << endl;
		cout << "阅读提示：" << endl;
		cout << "	1、空行用<EMPTY>标出" << endl;
		cout << "	2、文件结束用<EOF>标出" << endl;
		cout << "	3、两行相同列位置的差异字符用亮色标出" << endl;
		cout << "	4、每行中的CR/LF/VT/BS/BEL用X标出(方便看清隐含字符)" << endl;
		cout << "	5、每行尾的多余的字符用亮色标出，CR/LF/VT/BS/BEL用亮色X标出(方便看清隐含字符)" << endl;
		cout << "	6、每行最后用<CR>标出(方便看清隐含字符)" << endl;
		cout << "	7、中文因为编码问题，差异位置可能报在后半个汉字上，但整个汉字都亮色标出" << endl;
		if (type == "normal")
			cout << "	8、用--display detailed可以得到更详细的信息" << endl;
		cout << "====================================================================================================" << endl;
	}
	else
	{
		cout << "在指定条件下文件完全一致" << endl;
		cout << "====================================================================================================" << endl;
	}
}

void print_debug(const args_analyse_tools* args,int file_bytes1,int file_bytes2,int os1,int os2,int line_count1,int line_count2,int max_len1,int max_len2)//打印debug信息
{
	args_analyse_print(args);
	for (int i = 1; args[i].get_name() != ""; i++)
	{
		cout << left << setw(19) << args[i].get_name() <<" : " ;
		if (args[i].get_name() == "--file1" || args[i].get_name() == "--file2" || args[i].get_name() == "--trim" || args[i].get_name() == "--display")
			cout << args[i].get_string() << endl;
		else
			cout << args[i].get_int() << endl;
	}
	cout << endl;
	cout << "第1个文件的基本信息：" << endl;
	cout << "====================================================================================================" << endl;
	cout << "文 件 名：" <<args[2].get_string() << endl;
	cout << "大    小："<<file_bytes1<<endl;
	cout << "行    数："<<line_count1 << endl;
	cout << "最大行长："<<max_len1 << endl;
	cout << "文件格式：" ;
	if (os1 == 0)
		cout << "Windows" << endl;
	else if (os1 == 1)
		cout << "Linux" << endl;
	else
		cout << "无法识别" << endl;
	cout << "====================================================================================================" << endl;
	cout << endl;
	cout << "第2个文件的基本信息：" << endl;
	cout << "====================================================================================================" << endl;
	cout << "文 件 名：" << args[3].get_string() << endl;
	cout << "大    小：" <<file_bytes2<< endl;
	cout << "行    数："<<line_count2 << endl;
	cout << "最大行长："<<max_len2 << endl;
	cout << "文件格式：" ;
	if (os2 == 0)
		cout << "Windows" << endl;
	else if (os2 == 1)
		cout << "Linux" << endl;
	else
		cout << "无法识别" << endl;
	cout << "====================================================================================================" << endl;
	/* 比较结果输出： */
	cout << endl << endl;
	cout << "比较结果输出：" << endl;
	cout << "====================================================================================================" << endl;
}

int check_blank(string line)
{
	for (int i = 0; i < (int)line.size(); i++)
	{
		if (line[i] != '\a' && line[i] != '\r' && line[i] != '\n' && line[i] != '\v'
			&& line[i] != '\b' && line[i] != ' ' && line[i] != '\t')
			return 0;
	}
	return 1;
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static void usage(const char* const procname)
{
	ostringstream msg;
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	msg << procname << "-Ver1.0.0" << endl;
	msg << endl;

	msg << "Usage: " << procname << " --file1 xxx --file2 xxx [ --trim none/left/rigth/all | --lineoffset -100..100 | --ignore_blank | --max_diff 0..100 | --display none/normal/detailed ]" << endl;

	msg << setw(wkey) << ' ' << "必选项：" << endl;
	msg << setw(wopt) << ' ' << "--file1 name1              : 指定要比较的第1个文件名（必选）" << endl;
	msg << setw(wopt) << ' ' << "--file2 name2              : 指定要比较的第2个文件名（必选）" << endl;
	msg << endl;

	msg << setw(wkey) << ' ' << "可选项：" << endl;
	msg << setw(wopt) << ' ' << "--trim none/left/right/all     : 指定每行的空格/tab的忽略方式（无此项则默认为none）" << endl;
	msg << setw(wopt) << ' ' << "\tnone   : 每行均严格匹配" << endl;
	msg << setw(wopt) << ' ' << "\tleft   : 每行均忽略头部空格" << endl;
	msg << setw(wopt) << ' ' << "\tright  : 每行均忽略尾部空格" << endl;
	msg << setw(wopt) << ' ' << "\tall    : 每行均忽略头尾空格" << endl;
	msg << setw(wopt) << ' ' << "--lineoffset n                 : 指定文件错位的行数（无此项则n为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[-100..100]，负数表示忽略file1的前n行，正数表示忽略file2的前n行" << endl;
	msg << setw(wopt) << ' ' << "--ignore_blank                 : 忽略文件中--trim后的所有空行(无此项则不忽略)" << endl;
	msg << setw(wopt) << ' ' << "--CR_CRLF_not_equal            : 不忽略Windows/Linux文件的换行符差异(无此项则忽略差异)" << endl;
	msg << setw(wopt) << ' ' << "--max_diff m                   : 指定文件错位的行数（无此项则m为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[0..100]，表示满m个不同行则结束运行，不再进行后续的比较" << endl;
	msg << setw(wopt) << ' ' << "--max_line x                   : 指定文件比较的最大行数（无此项则x为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[0..10000]，表示比较x行后则结束运行，不再进行后续的比较" << endl;
	msg << setw(wopt) << ' ' << "--display none/normal/detailed : 指定显示的信息（无此项则默认为none）" << endl;
	msg << setw(wopt) << ' ' << "\tnone   : 仅一行匹配与否的提示" << endl;
	msg << setw(wopt) << ' ' << "\tnormal : 每个差异行给出差异信息" << endl;
	msg << setw(wopt) << ' ' << "\tdetailed  : 每个差异行给出更详细的差异信息" << endl;
	msg << endl;

	msg << "e.g.   " << procname << " --file1 my.txt --file2 std.txt" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --trim all" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，每行均去除头尾空格，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --lineoffset -2" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略my.txt的前2行(即my.txt的第3行与std.txt的第1行进行比较，每行严格匹配)，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --trim left --lineoffset 3" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略std.txt的前3行(即my.txt的第1行与std.txt的第4行进行比较)，每行去除头部空格，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --ignore_blank" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略文件中的所有空行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --ignore_blank --trim right" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略文件中去除头尾空格后的所有空行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --max_diff 3" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，有3行不匹配后结束运行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --max_line 7" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，仅比较前7行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --CR_CRLF_not_queal" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，不忽略Windows/Linux的文件差异，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --display normal" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，不匹配的行显示信息" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --display detailed" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，不匹配的行显示详细信息" << endl;
	msg << endl;
	cout << msg.str() << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main(int argc, char** argv)
{
	/* 因为引入了 lib_aat_tools.lib，此处先检查大小是否符合要求 */
	if (sizeof(args_analyse_tools) != 200) {
		cout << "class args_analyse_tools 不是200字节，如果使用 lib_aat_tools.lib 中的函数则可能出错" << endl;
		return -1;
	}

	/* 指定去除空格的方式 */
	const string TrimType[] = { "none",	"left",	"right",	"all", "" };
	/* 指定信息的显示方式 */
	const string DisplayType[] = { "none",	"normal",	"detailed", "" };
	args_analyse_tools args[] = {
		args_analyse_tools("--help",				ST_EXTARGS_TYPE::boolean, 0, false),		//显示帮助信息
		args_analyse_tools("--debug",				ST_EXTARGS_TYPE::boolean, 0, false),		//显示调试信息（不要求与demo完全相同）
		args_analyse_tools("--file1",				ST_EXTARGS_TYPE::str, 1, string("")),		//用于比较的文件名1
		args_analyse_tools("--file2",				ST_EXTARGS_TYPE::str, 1, string("")),		//用于比较的文件名2
		args_analyse_tools("--trim",				ST_EXTARGS_TYPE::str_with_set_error, 1, 0, TrimType),		//空格的比较方式
		args_analyse_tools("--lineoffset",		ST_EXTARGS_TYPE::int_with_default,   1, 0, -100, 100),		//指定左右文件的行差
		args_analyse_tools("--ignore_blank",		ST_EXTARGS_TYPE::boolean, 0, false),							//忽略空行
		args_analyse_tools("--CR_CRLF_not_equal",	ST_EXTARGS_TYPE::boolean, 0, false),							//
		args_analyse_tools("--max_diff",			ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 100),			//比较的最大错误数，超出则停止
		args_analyse_tools("--max_line",			ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 10000),			//比较的函数
		args_analyse_tools("--display",			ST_EXTARGS_TYPE::str_with_set_error, 1, 0, DisplayType),		//显示差异的方式
		args_analyse_tools()  //最后一个，用于结束
	};
	int cur_argc, ret = 0;

	//最后一个参数0，表示除选项参数外，没有其它参数
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//错误信息在函数中已打印
		args_analyse_print(args);
		usage(argv[0]);
		return -1;
	}

	/* 后续代码 */
	if (args[0].existed())//打印help信息，优先级最高
	{
		args_analyse_print(args);
		usage(argv[0]);
		return 0;
	}
	if (!(args[2].existed() && args[3].existed()))//file1或file2不存在
	{
		usage(argv[0]);
		return -1;
	}
	if (args[4].existed() && (args[7].get_string() == "right"|| args[7].get_string() == "all"))
	{
		usage(argv[0]);
		cout << "参数[--CR_CRLF_not_equal]不能和[--trim right/all]同时存在." << endl;
		return 0;
	}
	int os1 = check_file(args[2].get_string().c_str());
	int os2 = check_file(args[3].get_string().c_str());
	fstream file1, file2;
	file1.open(args[2].get_string(),ios::in|ios::binary);
	file2.open(args[3].get_string(),ios::in|ios::binary);
	if (!file1.is_open())
	{
		cout << "第一个文件["<< args[2].get_string() <<"]无法打开" << endl;
		return -1;
	}
	if (!file2.is_open())
	{
		cout << "第二个文件[" << args[3].get_string() << "]无法打开" << endl;
		return -1;
	}
	/* 逐行读取 */
	string line1, line2,buffer;
	int file1_bytes = 0, file2_bytes = 0;
	char ch1, ch2;
	while ((ch1 = file1.get()) != EOF)
		file1_bytes++;
	while ((ch2 = file2.get()) != EOF)
		file2_bytes++;
	file1.clear();
	file2.clear();
	file1.seekg(0, ios::beg);
	file2.seekg(0, ios::beg);
	string tmp;
	int line_count1 = 0, line_count2 = 0, max_len1 = 0, max_len2 = 0;
	while (getline(file1,tmp))
	{
		line_count1++;
		if ((int)tmp.size() > max_len1)
			max_len1 = (int)tmp.size();
	}
	while (getline(file2, tmp))
	{
		line_count2++;
		if ((int)tmp.size() > max_len2)
			max_len2 = (int)tmp.size();
	}
	file1.clear();
	file2.clear();
	file1.seekg(0, ios::beg);
	file2.seekg(0, ios::beg);
	//读取行计数
	if (args[1].existed())//打印debug信息
		print_debug(args, file1_bytes, file2_bytes, os1, os2, line_count1, line_count2, max_len1, max_len2);
	line_count1 = 0;
	line_count2 = 0;
	int diff_count = 0;//不同行计数
	int same = 1;
	int offset = args[5].get_int();
	while (offset != 0)
	{
		if (offset < 0)
		{
			getline(file1, buffer);
			offset++;
		}
		else if (offset > 0)
		{
			getline(file2, buffer);
			offset--;
		}
		else;
	}
	while (1)
	{
		getline(file1, line1);
		getline(file2, line2);
		line_count1++;
		line_count2++;
		/*if (line_count == 10)
			getchar();*/
		trim(line1, args[4].get_string());
		trim(line2, args[4].get_string());
		if (args[6].existed())
		{
			while (line1 == "")
			{
				getline(file1, line1);
				if(check_blank(line1))
					trim(line1, "all");
				line_count1++;
				if (file1.eof() && line1.empty())
					line1 = char(EOF);
			}
			while (line2 == "")
			{
				getline(file2, line2);
				if (check_blank(line2))
					trim(line2, "all");
				line_count2++;
				if (file2.eof() && line2.empty())
					line2 = char(EOF);
			}
			trim(line1, args[4].get_string());
			trim(line2, args[4].get_string());
		}
		if (!args[7].existed())
		{
			if (!line1.empty() && line1[line1.size() - 1] == '\r')
				line1.erase(line1.size() - 1);
			if (!line2.empty() && line2[line2.size() - 1] == '\r')
				line2.erase(line2.size() - 1);
		}
		if (file1.eof() && line1.empty())
			line1 = char(EOF);
		if (file2.eof() && line2.empty())
			line2 = char(EOF);
		same = compare_line(line1, line2,args,line_count1,line_count2,diff_count);
		if (same == 0 && args[10].get_string() == "none" && !args[1].existed())
		{
			cout << "文件不同." << endl;
			break;
		}
		if (file1.eof() || file2.eof())//两个都EOF应该是输出EMPTY
			break;
		if (args[9].get_int() != 0 && (line_count1 > args[9].get_int() || line_count2 > args[9].get_int()))//行数存在上限且已达到
			break;
		if (args[8].existed() && diff_count >= args[8].get_int())
			break;
	}
	if (args[1].existed() || args[10].get_string() == "normal" || args[10].get_string() == "detailed")
	{
		if(!args[1].existed())
			print_tips(diff_count, args[10].get_string());
		else
		{
			if(args[10].get_string() == "detailed")
				print_tips(diff_count, "detailed");
			else
				print_tips(diff_count, "normal");
		}
	}
	if (same == 1 && args[10].get_string() == "none" && !args[1].existed())
		cout << "文件相同." << endl;
	file1.close();
	file2.close();
	return 0;
}

/* 测试文件准备
	1.txt ：正常文件
	2.txt ：在1.txt的基础上，某些行前面无空格
	3.txt ：在1.txt的基础上，某些行后面无空格
	4.txt ：在1.txt的基础上，最后一行没有回车
	5.txt ：在1.txt的基础上，多一些空行
	6.txt ：在1.txt的基础上，多一些空行，其中某些行有空格和tab
	7.txt ：和1.txt完全相同
	8.txt ：是1.txt的Linux格式版

txt_compare --file1 1.txt --file2 2.txt --trim left
txt_compare --file1 1.txt --file2 2.txt --trim all
txt_compare --file1 2.txt --file2 3.txt --trim all
txt_compare --file1 1.txt --file2 4.txt --trim right --ignore_blank
txt_compare --file1 1.txt --file2 4.txt --trim all --ignore_blank
txt_compare --file1 2.txt --file2 4.txt --trim all --ignore_blank
txt_compare --file1 3.txt --file2 4.txt --trim right --ignore_blank
txt_compare --file1 3.txt --file2 4.txt --trim all --ignore_blank
txt_compare --file1 1.txt --file2 5.txt --trim right --ignore_blank
txt_compare --file1 1.txt --file2 6.txt --ignore_blank --trim right
txt_compare --file1 5.txt --file2 6.txt --ignore_blank --trim all
txt_compare --file1 1.txt --file2 7.txt
txt_compare --file1 1.txt --file2 8.txt

rem 不相同的例子
txt_compare --file1 1.txt --file2 2.txt
txt_compare --file1 1.txt --file2 2.txt --trim right
txt_compare --file1 1.txt --file2 5.txt
txt_compare --file1 1.txt --file2 5.txt --trim right
txt_compare --file1 1.txt --file2 6.txt
txt_compare --file1 1.txt --file2 6.txt --ignore_blank
txt_compare --file1 1.txt --file2 8.txt --CR_CRLF_not_equal

*/