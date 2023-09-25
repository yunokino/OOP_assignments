/* 2152041 计科 王浩 */
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

int check_file(const char* str);
int convert_file(const char* pre_file, const char* next_file, bool trans_way);

int main(int argc, char* argv[])
{
	if (argc != 3 && argc != 5)
	{
		cout << "901.第15模块 作业 - PART1\\15-b1-demo.exe" << endl;
		cout<<"Usage : "<<argv[0]<<" --check 文件名 | --convert{ wtol | ltow } 源文件名 目标文件名"<<endl;
		cout << argv[0]<<" --check a.txt" << endl;
		cout<<argv[0]<<" --convert wtol a.win.txt a.linux.txt"<<endl;
		cout<<argv[0]<<" --convert ltow a.linux.txt a.win.txt" << endl;
		return -1;
	}

	if (!strcmp(argv[1], "--check"))
	{
		int file_os = check_file(argv[2]);//0为windows，1为linux，2为无法识别
		if (file_os == -1)
			return -1;
		switch (file_os)
		{
		case 0:
			cout << "Windows格式" << endl;
			break;
		case 1:
			cout << "Linux格式" << endl;
			break;
		case 2:
			cout << "文件格式无法识别" << endl;
			break;
		default:
			break;
		}

	}
	else if (!strcmp(argv[1], "--convert"))
	{
		if (!strcmp(argv[2], "wtol"))
		{
			int file_os = check_file(argv[3]);
			if (file_os != 0)
			{
				cout << "文件格式无法识别" << endl;
				return -1;
			}
			if (convert_file(argv[3], argv[4], 0) == -1)
				return -1;
		}
		else if (!strcmp(argv[2], "ltow"))
		{
			int file_os = check_file(argv[3]);
			if (file_os != 1)
			{
				cout << "文件格式无法识别" << endl;
				return -1;
			}
			if (convert_file(argv[3], argv[4], 1) == -1)
				return -1;
		}
		else;
	}
	else;

	return 0;
}

int check_file(const char* str)
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

int convert_file(const char* pre_file, const char* next_file, bool trans_way)
{
	/* trans_way 0代表win-linux， 1代表linux-win */
	ifstream in(pre_file, ios::in | ios::binary);
	ofstream out(next_file, ios::out | ios::binary);
	if ((int)in.is_open() == -1 || (int)out.is_open() == -1)
	{
		cout << "文件打开失败" << endl;
		return -1;
	}
	char ch = '0';//遍历文件字节

	while ((ch = in.get()) != EOF)
	{
		if ((int)ch == 0x0A || (int)ch == 0x0D)
		{
			if (!trans_way && (int)ch != 0x0D)
			{
				out << ch;
			}
			else if (trans_way && (int)ch == 0x0A)
			{
				out << (char)0x0D << ch;
			}
			else;
		}
		else
		{
			out << ch;
		}

	}
	in.close();
	out.close();
	return 0;
}
