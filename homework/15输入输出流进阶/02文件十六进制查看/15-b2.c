/* 2152041 计科 王浩 */
/* 2154301 黄昱翔 2054403 韩君诺 2152215 徐艺洲 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int output(const char* pre_file,const char*next_file, int out_way);

int main(int argc, char* argv[])
{
	if (argc != 3 && argc != 5)
	{
		printf("Usage : %s --infile 原始文件 [--outfile hex格式文件 ]\n",argv[0]);
		printf("%s --infile a.docx\n",argv[0]);
		printf("%s --infile a.docx --outfile a.hex\n",argv[0]);
		return -1;
	}
	if (!strcmp(argv[1], "--infile"))
	{
		if (argc == 3)
		{
			if (output(argv[2],"\0", 0) == -1)
			{
				return -1;
			}

		}
		else if (argc == 5)
		{
			if (output(argv[2], argv[4], 1) == -1)
			{
				return -1;
			}
		}
		else;
	}
	else if (!strcmp(argv[1], "--outfile"))
	{
		if (output(argv[4], argv[2], 1) == -1)
		{
			return -1;
		}
	}
	else;
	return 0;
}

int output(const char* pre_file, const char* next_file, int out_way)
{
	//out_way 0代表输出到屏幕上，1代表输出到文件里
	if (out_way == 0)
	{
		FILE* in = fopen(pre_file, "rb");
		if (in == NULL)
		{
			printf("文件打开失败\n");
			return -1;
		}
		int i = 0;
		int ch = '0';//遍历文件字节
		int store_line[16];
		
		while ((ch = fgetc(in)) != EOF)
		{
			if (i % 16 == 0)
			{
				printf("%08x", i);
				printf("  ");
				for (int j = 0; j < 16; j++)
				{
					store_line[j] = 1000;//用一个ch达不到的值来标记尚未储存的状态
				}
			}
			store_line[i % 16] = (int)ch;
			if (i % 16 == 8)
				printf("- ");
			printf("%02x ", (int)ch);
			if (i % 16 == 15)
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
			}
			i++;
		}
		/* 处理最后一行因EOF提前终止下的输出 */
		if (i % 16 != 0)
		{
			while (i % 16 != 0)
			{
				if (i % 16 == 8)
					printf("  ");
				printf("   ");
				i++;
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
		}

		/*************分隔********************/
		fclose(in);
	}
	else if (out_way == 1)
	{
		FILE* in = fopen(pre_file, "rb");
		FILE* out = fopen(next_file, "wb");
		if (in == NULL || out == NULL)
		{
			printf("文件打开失败\n");
			return -1;
		}
		int i = 0;
		int ch = '0';//遍历文件字节
		int store_line[16];

		while ((ch = fgetc(in)) != EOF)
		{
			if (i % 16 == 0)
			{
				fprintf(out, "%08x", i);	
				fprintf(out,"  ");
				for (int j = 0; j < 16; j++)
				{
					store_line[j] = 1000;//用一个ch达不到的值来标记尚未储存的状态
				}
			}
			store_line[i % 16] = (int)ch;
			if (i % 16 == 8)
				fprintf(out, "- ");
			fprintf(out, "%02x ", (int)ch);
			if (i % 16 == 15)
			{
				fprintf(out, "    ");
				for (int j = 0; j < 16; j++)
				{
					if (store_line[j] != 1000)
					{
						if ((store_line[j] < 33 || store_line[j] > 126))
							fprintf(out, ".");
						else
							fprintf(out, "%c", store_line[j]);
					}
				}
#ifdef __linux
				fprintf(out, "\n");
#else
				fprintf(out, "\r\n");
#endif
			}
			i++;
		}
		/* 处理最后一行因EOF提前终止下的输出 */
		if (i % 16 != 0)
		{
			while (i % 16 != 0)
			{
				if (i % 16 == 8)
					fprintf(out, "  ");
				fprintf(out, "   ");
				i++;
			}
			fprintf(out, "    ");
			for (int j = 0; j < 15; j++)
			{
				if (store_line[j] != 1000)
				{
					if ((store_line[j] < 33 || store_line[j] > 126))
						fprintf(out, ".");
					else
						fprintf(out, "%c", store_line[j]);
				}
			}
		}
#ifdef __linux
		fprintf(out, "\n\n");
#else
		fprintf(out, "\r\n\r\n");
#endif
		/*************分隔********************/
		
		fclose(out);
		fclose(in);
	}
	else;

	return 0;
}
