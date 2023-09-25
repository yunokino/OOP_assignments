/* 2152041 计科 王浩 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int output(const char* pre_file, const char* next_file);

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		printf("Usage : %s --infile hex格式文件 --outfile bin格式文件\n", argv[0]);
		printf("%s  --infile a.hex --outfile a.bin\n", argv[0]);
		return -1;
	}
	if (!strcmp(argv[1], "--infile"))
	{
		if (output(argv[2], argv[4]) == -1)
		{
			return -1;
		}
	}
	else if (!strcmp(argv[1], "--outfile"))
	{
		if (output(argv[4], argv[2]) == -1)
		{
			return -1;
		}
	}
	else;

	return 0;
}

int output(const char* pre_file, const char* next_file)
{
	FILE* in = fopen(pre_file, "rb");
	FILE* out = fopen(next_file, "wb");
	char buffer[20];
	if (in == NULL || out == NULL)
	{
		printf("文件打开失败\n");
		return -1;
	}
	char tmp[2];
	int num = 0;
	int end = 0;
	while (1)
	{
		int n = fread(buffer, 1, 10, in);
		if (n < 10)
			break;
		for (int i = 0; i < 16; i++)
		{
			fread(tmp, 2, 1, in);
			if (tmp[0] == '-')
			{
				i--;
				continue;
			}
			if (tmp[0] == ' ' && tmp[1] == ' ')
			{
				end = 1;
				break;
			}
			for (int i = 0; i < 2; i++)
			{
				if (tmp[i] >= 'a')
				{
					num = num * 16 + (tmp[i] - 'a' + 10);
				}
				else
				{
					num = num * 16 + tmp[i] - '0';
				}
			}
			fputc(num, out);
			
			num = 0;
			fread(buffer, 1, 1, in);
		}
		if (end == 1)
			break;
		fread(buffer, 20, 1, in);
#ifdef __linux 
		fread(buffer, 1, 1, in);
#else
		fread(buffer, 2, 1, in);
#endif
	}
	
	fclose(in);
	fclose(out);
	return 0;
}
