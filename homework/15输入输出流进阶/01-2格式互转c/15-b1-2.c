/* 2152041 计科 王浩 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int check_file(const char* str);
int convert_file(const char* pre_file, const char* next_file, int trans_way);

int main(int argc, char* argv[])
{
	if (argc != 3 && argc != 5)
	{
		printf("901.第15模块 作业 - PART1\\15-b1-demo.exe\n");
		printf("Usage : %s --check 文件名 | --convert{ wtol | ltow } 源文件名 目标文件名\n", argv[0]);
		printf("%s --check a.txt\n",argv[0]);
		printf("%s --convert wtol a.win.txt a.linux.txt\n", argv[0]);
		printf("%s --convert ltow a.linux.txt a.win.txt\n", argv[0]);
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
			printf("Windows格式\n");
			break;
		case 1:
			printf("Linux格式\n");
			break;
		case 2:
			printf("文件格式无法识别\n");
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
				printf("文件格式无法识别\n");
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
				printf("文件格式无法识别\n");
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
	FILE* in = fopen(str, "rb");
	if (in == NULL)
	{
		printf("文件打开失败\n");
		return -1;
	}

	char ch = '0';//遍历文件字节
	char pre_ch = ch;//记录前置字节内容
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
	/* trans_way 0代表win-linux， 1代表linux-win */
	FILE* in = fopen(pre_file, "rb");
	FILE* out = fopen(next_file, "wb");

	if (in == NULL || out == NULL)
	{
		printf("文件打开失败\n");
		return -1;
	}
	char ch = '0';//遍历文件字节

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