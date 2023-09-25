/* 2152041 �ƿ� ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int check_file(const char* str);
int convert_file(const char* pre_file, const char* next_file, int trans_way);

int main(int argc, char* argv[])
{
	if (argc != 3 && argc != 5)
	{
		printf("901.��15ģ�� ��ҵ - PART1\\15-b1-demo.exe\n");
		printf("Usage : %s --check �ļ��� | --convert{ wtol | ltow } Դ�ļ��� Ŀ���ļ���\n", argv[0]);
		printf("%s --check a.txt\n",argv[0]);
		printf("%s --convert wtol a.win.txt a.linux.txt\n", argv[0]);
		printf("%s --convert ltow a.linux.txt a.win.txt\n", argv[0]);
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
			printf("Windows��ʽ\n");
			break;
		case 1:
			printf("Linux��ʽ\n");
			break;
		case 2:
			printf("�ļ���ʽ�޷�ʶ��\n");
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
				printf("�ļ���ʽ�޷�ʶ��\n");
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
				printf("�ļ���ʽ�޷�ʶ��\n");
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
	FILE* in = fopen(str, "rb");
	if (in == NULL)
	{
		printf("�ļ���ʧ��\n");
		return -1;
	}

	char ch = '0';//�����ļ��ֽ�
	char pre_ch = ch;//��¼ǰ���ֽ�����
	while ((ch = fgetc(in)) != EOF)
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
	fclose(in);
	return file_os;
}

int convert_file(const char* pre_file, const char* next_file, int trans_way)
{
	/* trans_way 0����win-linux�� 1����linux-win */
	FILE* in = fopen(pre_file, "rb");
	FILE* out = fopen(next_file, "wb");

	if (in == NULL || out == NULL)
	{
		printf("�ļ���ʧ��\n");
		return -1;
	}
	char ch = '0';//�����ļ��ֽ�

	while ((ch = fgetc(in)) != EOF)
	{
		if ((int)ch == 0x0A || (int)ch == 0x0D)
		{
			if (!trans_way && (int)ch != 0x0D)
			{
				fputc(ch, out);
			}
			else if (trans_way && (int)ch == 0x0A)
			{
				fputc((char)0x0D, out);
				fputc(ch, out);
				//out << (char)0x0D << ch;
			}
			else;
		}
		else
		{
			fputc(ch, out);
		}

	}
	fclose(in);
	fclose(out);

	return 0;
}