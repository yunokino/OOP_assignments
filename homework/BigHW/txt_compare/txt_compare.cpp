/* 2152041 �ƿ� ���� */
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

/* ���������Ҫ������ */
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

int check_file(const char* str)//����ļ���ʽ
{
	int file_os = 2;//0Ϊwindows��1Ϊlinux��2Ϊ�޷�ʶ��
	ifstream in(str, ios::in | ios::binary);
	if ((int)in.is_open() == -1)
	{
		cout << "�ļ���ʧ��" << endl;
		return -1;
	}
	char ch = '0';//�����ļ��ֽ�
	char pre_ch = ch;//��¼ǰ���ֽ�����
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
	/* ��ԭ����ֱ�ӽ�ǰ���C��ʽ�����ù�����... */
	while (count < (int)line.size())
	{
		if (count % 16 == 0)
		{
			printf("%08x", count);
			printf("  ");
			for (int j = 0; j < 16; j++)
			{
				store_line[j] = 1000;//��һ��ch�ﲻ����ֵ�������δ�����״̬
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
	/* �������һ����ǰ��ֹ�µ���� */
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
		if (args[1].existed())//���debug����ô��ͬ��ҲҪ��ӡ
		{
			cout << "��[" << line_count1 << " / " << line_count2 << "]�� - һ�� : ";
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
		diff[i] = 0;//��ʼ��
	if (line1.size() == line2.size())//���еȳ�
	{
		int first_diff = 1;
		int exist_eof = (line1.size() == 1 && line1[0] == char(EOF)) || (line2.size() == 1 && line2[0] == char(EOF));
		cout << "��["<<line_count1<<" / "<<line_count2<<"]�� -";
		for (int i = 0; i < (int)line1.size(); i++)
		{
			if (line1[i] != line2[i])
			{
				if (first_diff)
				{
					first_diff = 0;
					cout << "�ӵ�" << i << "���ַ���ʼ�в���:" << endl;
				}
				diff[i] = 1;
			}
		}
	}
	else
	{
		/* �ȱȽ�ǰ�벿�� */
		int first_diff = 1;
		int exist_eof = (line1.size() == 1 && line1[0] == char(EOF)) || (line2.size() == 1 && line2[0] == char(EOF));
		cout << "��[" << line_count1 << " / " << line_count2 << "]�� -";
		for (int i = 0; i < (int)min(line1.size(),line2.size()); i++)
		{
			if (line1[i] != line2[i])
			{
				if (first_diff && !exist_eof)
				{
					cout << "�ӵ�" << i << "���ַ���ʼ�в���:" << endl;
					first_diff = 0;
				}
				diff[i] = 1;
			}
		}
		if (exist_eof)
			first_diff = 1;
		if (first_diff == 1)
			cout << "�ļ�" << ((line1 > line2) ? "1" : "2") << "��β���ж����ַ�:" << endl;
		for (int i = min(line1.size(), line2.size()); i < (int)max(line1.size(), line2.size());i++)
			diff[i] = 1;
	}
	if (args[10].get_string() == "detailed")
	{
		print_ruler(max(line1.size(), line2.size()));
	}
	cout << "�ļ�1 : ";
	print_line(line1, diff);
	cout << "�ļ�2 : ";
	print_line(line2, diff);
	if (args[10].get_string() == "detailed")
	{
		cout << "�ļ�1(HEX):" << endl;
		print_hex(line1);
		cout << "�ļ�2(HEX):" << endl;
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
		cout << "��ָ����������¹�" << diff_count << "���в���." << endl;
		cout << "�Ķ���ʾ��" << endl;
		cout << "	1��������<EMPTY>���" << endl;
		cout << "	2���ļ�������<EOF>���" << endl;
		cout << "	3��������ͬ��λ�õĲ����ַ�����ɫ���" << endl;
		cout << "	4��ÿ���е�CR/LF/VT/BS/BEL��X���(���㿴�������ַ�)" << endl;
		cout << "	5��ÿ��β�Ķ�����ַ�����ɫ�����CR/LF/VT/BS/BEL����ɫX���(���㿴�������ַ�)" << endl;
		cout << "	6��ÿ�������<CR>���(���㿴�������ַ�)" << endl;
		cout << "	7��������Ϊ�������⣬����λ�ÿ��ܱ��ں��������ϣ����������ֶ���ɫ���" << endl;
		if (type == "normal")
			cout << "	8����--display detailed���Եõ�����ϸ����Ϣ" << endl;
		cout << "====================================================================================================" << endl;
	}
	else
	{
		cout << "��ָ���������ļ���ȫһ��" << endl;
		cout << "====================================================================================================" << endl;
	}
}

void print_debug(const args_analyse_tools* args,int file_bytes1,int file_bytes2,int os1,int os2,int line_count1,int line_count2,int max_len1,int max_len2)//��ӡdebug��Ϣ
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
	cout << "��1���ļ��Ļ�����Ϣ��" << endl;
	cout << "====================================================================================================" << endl;
	cout << "�� �� ����" <<args[2].get_string() << endl;
	cout << "��    С��"<<file_bytes1<<endl;
	cout << "��    ����"<<line_count1 << endl;
	cout << "����г���"<<max_len1 << endl;
	cout << "�ļ���ʽ��" ;
	if (os1 == 0)
		cout << "Windows" << endl;
	else if (os1 == 1)
		cout << "Linux" << endl;
	else
		cout << "�޷�ʶ��" << endl;
	cout << "====================================================================================================" << endl;
	cout << endl;
	cout << "��2���ļ��Ļ�����Ϣ��" << endl;
	cout << "====================================================================================================" << endl;
	cout << "�� �� ����" << args[3].get_string() << endl;
	cout << "��    С��" <<file_bytes2<< endl;
	cout << "��    ����"<<line_count2 << endl;
	cout << "����г���"<<max_len2 << endl;
	cout << "�ļ���ʽ��" ;
	if (os2 == 0)
		cout << "Windows" << endl;
	else if (os2 == 1)
		cout << "Linux" << endl;
	else
		cout << "�޷�ʶ��" << endl;
	cout << "====================================================================================================" << endl;
	/* �ȽϽ������� */
	cout << endl << endl;
	cout << "�ȽϽ�������" << endl;
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
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

	msg << setw(wkey) << ' ' << "��ѡ�" << endl;
	msg << setw(wopt) << ' ' << "--file1 name1              : ָ��Ҫ�Ƚϵĵ�1���ļ�������ѡ��" << endl;
	msg << setw(wopt) << ' ' << "--file2 name2              : ָ��Ҫ�Ƚϵĵ�2���ļ�������ѡ��" << endl;
	msg << endl;

	msg << setw(wkey) << ' ' << "��ѡ�" << endl;
	msg << setw(wopt) << ' ' << "--trim none/left/right/all     : ָ��ÿ�еĿո�/tab�ĺ��Է�ʽ���޴�����Ĭ��Ϊnone��" << endl;
	msg << setw(wopt) << ' ' << "\tnone   : ÿ�о��ϸ�ƥ��" << endl;
	msg << setw(wopt) << ' ' << "\tleft   : ÿ�о�����ͷ���ո�" << endl;
	msg << setw(wopt) << ' ' << "\tright  : ÿ�о�����β���ո�" << endl;
	msg << setw(wopt) << ' ' << "\tall    : ÿ�о�����ͷβ�ո�" << endl;
	msg << setw(wopt) << ' ' << "--lineoffset n                 : ָ���ļ���λ���������޴�����nΪ0��" << endl;
	msg << setw(wopt) << ' ' << "\tȡֵ[-100..100]��������ʾ����file1��ǰn�У�������ʾ����file2��ǰn��" << endl;
	msg << setw(wopt) << ' ' << "--ignore_blank                 : �����ļ���--trim������п���(�޴����򲻺���)" << endl;
	msg << setw(wopt) << ' ' << "--CR_CRLF_not_equal            : ������Windows/Linux�ļ��Ļ��з�����(�޴�������Բ���)" << endl;
	msg << setw(wopt) << ' ' << "--max_diff m                   : ָ���ļ���λ���������޴�����mΪ0��" << endl;
	msg << setw(wopt) << ' ' << "\tȡֵ[0..100]����ʾ��m����ͬ����������У����ٽ��к����ıȽ�" << endl;
	msg << setw(wopt) << ' ' << "--max_line x                   : ָ���ļ��Ƚϵ�����������޴�����xΪ0��" << endl;
	msg << setw(wopt) << ' ' << "\tȡֵ[0..10000]����ʾ�Ƚ�x�к���������У����ٽ��к����ıȽ�" << endl;
	msg << setw(wopt) << ' ' << "--display none/normal/detailed : ָ����ʾ����Ϣ���޴�����Ĭ��Ϊnone��" << endl;
	msg << setw(wopt) << ' ' << "\tnone   : ��һ��ƥ��������ʾ" << endl;
	msg << setw(wopt) << ' ' << "\tnormal : ÿ�������и���������Ϣ" << endl;
	msg << setw(wopt) << ' ' << "\tdetailed  : ÿ�������и�������ϸ�Ĳ�����Ϣ" << endl;
	msg << endl;

	msg << "e.g.   " << procname << " --file1 my.txt --file2 std.txt" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬��һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --trim all" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ÿ�о�ȥ��ͷβ�ո񣬽�һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --lineoffset -2" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt������my.txt��ǰ2��(��my.txt�ĵ�3����std.txt�ĵ�1�н��бȽϣ�ÿ���ϸ�ƥ��)����һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --trim left --lineoffset 3" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt������std.txt��ǰ3��(��my.txt�ĵ�1����std.txt�ĵ�4�н��бȽ�)��ÿ��ȥ��ͷ���ո񣬽�һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --ignore_blank" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt�������ļ��е����п��У���һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --ignore_blank --trim right" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt�������ļ���ȥ��ͷβ�ո������п��У���һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --max_diff 3" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬��3�в�ƥ���������У���һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --max_line 7" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬���Ƚ�ǰ7�У���һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --CR_CRLF_not_queal" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬������Windows/Linux���ļ����죬��һ�����" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --display normal" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬��ƥ�������ʾ��Ϣ" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --display detailed" << endl;
	msg << setw(wopt) << ' ' << " : �Ƚ�my.txt��std.txt��ȫ��ƥ�䣬��ƥ�������ʾ��ϸ��Ϣ" << endl;
	msg << endl;
	cout << msg.str() << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main(int argc, char** argv)
{
	/* ��Ϊ������ lib_aat_tools.lib���˴��ȼ���С�Ƿ����Ҫ�� */
	if (sizeof(args_analyse_tools) != 200) {
		cout << "class args_analyse_tools ����200�ֽڣ����ʹ�� lib_aat_tools.lib �еĺ�������ܳ���" << endl;
		return -1;
	}

	/* ָ��ȥ���ո�ķ�ʽ */
	const string TrimType[] = { "none",	"left",	"right",	"all", "" };
	/* ָ����Ϣ����ʾ��ʽ */
	const string DisplayType[] = { "none",	"normal",	"detailed", "" };
	args_analyse_tools args[] = {
		args_analyse_tools("--help",				ST_EXTARGS_TYPE::boolean, 0, false),		//��ʾ������Ϣ
		args_analyse_tools("--debug",				ST_EXTARGS_TYPE::boolean, 0, false),		//��ʾ������Ϣ����Ҫ����demo��ȫ��ͬ��
		args_analyse_tools("--file1",				ST_EXTARGS_TYPE::str, 1, string("")),		//���ڱȽϵ��ļ���1
		args_analyse_tools("--file2",				ST_EXTARGS_TYPE::str, 1, string("")),		//���ڱȽϵ��ļ���2
		args_analyse_tools("--trim",				ST_EXTARGS_TYPE::str_with_set_error, 1, 0, TrimType),		//�ո�ıȽϷ�ʽ
		args_analyse_tools("--lineoffset",		ST_EXTARGS_TYPE::int_with_default,   1, 0, -100, 100),		//ָ�������ļ����в�
		args_analyse_tools("--ignore_blank",		ST_EXTARGS_TYPE::boolean, 0, false),							//���Կ���
		args_analyse_tools("--CR_CRLF_not_equal",	ST_EXTARGS_TYPE::boolean, 0, false),							//
		args_analyse_tools("--max_diff",			ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 100),			//�Ƚϵ�����������������ֹͣ
		args_analyse_tools("--max_line",			ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 10000),			//�Ƚϵĺ���
		args_analyse_tools("--display",			ST_EXTARGS_TYPE::str_with_set_error, 1, 0, DisplayType),		//��ʾ����ķ�ʽ
		args_analyse_tools()  //���һ�������ڽ���
	};
	int cur_argc, ret = 0;

	//���һ������0����ʾ��ѡ������⣬û����������
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//������Ϣ�ں������Ѵ�ӡ
		args_analyse_print(args);
		usage(argv[0]);
		return -1;
	}

	/* �������� */
	if (args[0].existed())//��ӡhelp��Ϣ�����ȼ����
	{
		args_analyse_print(args);
		usage(argv[0]);
		return 0;
	}
	if (!(args[2].existed() && args[3].existed()))//file1��file2������
	{
		usage(argv[0]);
		return -1;
	}
	if (args[4].existed() && (args[7].get_string() == "right"|| args[7].get_string() == "all"))
	{
		usage(argv[0]);
		cout << "����[--CR_CRLF_not_equal]���ܺ�[--trim right/all]ͬʱ����." << endl;
		return 0;
	}
	int os1 = check_file(args[2].get_string().c_str());
	int os2 = check_file(args[3].get_string().c_str());
	fstream file1, file2;
	file1.open(args[2].get_string(),ios::in|ios::binary);
	file2.open(args[3].get_string(),ios::in|ios::binary);
	if (!file1.is_open())
	{
		cout << "��һ���ļ�["<< args[2].get_string() <<"]�޷���" << endl;
		return -1;
	}
	if (!file2.is_open())
	{
		cout << "�ڶ����ļ�[" << args[3].get_string() << "]�޷���" << endl;
		return -1;
	}
	/* ���ж�ȡ */
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
	//��ȡ�м���
	if (args[1].existed())//��ӡdebug��Ϣ
		print_debug(args, file1_bytes, file2_bytes, os1, os2, line_count1, line_count2, max_len1, max_len2);
	line_count1 = 0;
	line_count2 = 0;
	int diff_count = 0;//��ͬ�м���
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
			cout << "�ļ���ͬ." << endl;
			break;
		}
		if (file1.eof() || file2.eof())//������EOFӦ�������EMPTY
			break;
		if (args[9].get_int() != 0 && (line_count1 > args[9].get_int() || line_count2 > args[9].get_int()))//���������������Ѵﵽ
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
		cout << "�ļ���ͬ." << endl;
	file1.close();
	file2.close();
	return 0;
}

/* �����ļ�׼��
	1.txt �������ļ�
	2.txt ����1.txt�Ļ����ϣ�ĳЩ��ǰ���޿ո�
	3.txt ����1.txt�Ļ����ϣ�ĳЩ�к����޿ո�
	4.txt ����1.txt�Ļ����ϣ����һ��û�лس�
	5.txt ����1.txt�Ļ����ϣ���һЩ����
	6.txt ����1.txt�Ļ����ϣ���һЩ���У�����ĳЩ���пո��tab
	7.txt ����1.txt��ȫ��ͬ
	8.txt ����1.txt��Linux��ʽ��

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

rem ����ͬ������
txt_compare --file1 1.txt --file2 2.txt
txt_compare --file1 1.txt --file2 2.txt --trim right
txt_compare --file1 1.txt --file2 5.txt
txt_compare --file1 1.txt --file2 5.txt --trim right
txt_compare --file1 1.txt --file2 6.txt
txt_compare --file1 1.txt --file2 6.txt --ignore_blank
txt_compare --file1 1.txt --file2 8.txt --CR_CRLF_not_equal

*/