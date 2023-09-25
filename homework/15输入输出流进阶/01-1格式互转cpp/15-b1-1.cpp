/* 2152041 �ƿ� ���� */
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
		cout << "901.��15ģ�� ��ҵ - PART1\\15-b1-demo.exe" << endl;
		cout<<"Usage : "<<argv[0]<<" --check �ļ��� | --convert{ wtol | ltow } Դ�ļ��� Ŀ���ļ���"<<endl;
		cout << argv[0]<<" --check a.txt" << endl;
		cout<<argv[0]<<" --convert wtol a.win.txt a.linux.txt"<<endl;
		cout<<argv[0]<<" --convert ltow a.linux.txt a.win.txt" << endl;
		return -1;
	}

	if (!strcmp(argv[1], "--check"))
	{
		int file_os = check_file(argv[2]);//0Ϊwindows��1Ϊlinux��2Ϊ�޷�ʶ��
		if (file_os == -1)
			return -1;
		switch (file_os)
		{
		case 0:
			cout << "Windows��ʽ" << endl;
			break;
		case 1:
			cout << "Linux��ʽ" << endl;
			break;
		case 2:
			cout << "�ļ���ʽ�޷�ʶ��" << endl;
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
				cout << "�ļ���ʽ�޷�ʶ��" << endl;
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
				cout << "�ļ���ʽ�޷�ʶ��" << endl;
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

int convert_file(const char* pre_file, const char* next_file, bool trans_way)
{
	/* trans_way 0����win-linux�� 1����linux-win */
	ifstream in(pre_file, ios::in | ios::binary);
	ofstream out(next_file, ios::out | ios::binary);
	if ((int)in.is_open() == -1 || (int)out.is_open() == -1)
	{
		cout << "�ļ���ʧ��" << endl;
		return -1;
	}
	char ch = '0';//�����ļ��ֽ�

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
