/* 2152041 计科 王浩 */
#include <iostream>
#include <string>
#include <fstream>
#include <io.h>
#include "../include/cmd_console_tools.h"
#include "../include/common_read.h"
using namespace std;
int main()
{
	string file_name[MAX] = {""};
	cct_setconsoleborder(80, 30, 9999, 9999);
	/* 读取文件，选取文件 */
	if (read_file(file_name) == -1)
		return -1;
	/* 文本文件阅读 */
	const char* name = "./book/position.sav";
	fstream fp;
	ifstream check;
	check.open(name, ios::in | ios::binary);
	if (!check.is_open())
	{
		fp.open(name, ios::out | ios::binary | ios::app);
		for (int i = 0; file_name[i] != "";i++)
		{
			string tmp = "[" + file_name[i] + ".txt]\n0\n\n";
			fp << tmp;
		}
		fp.close();
	}
	check.close();
	int loop = 1;
	while (loop)
	{
		cct_cls();
		int branch = choose_file(file_name);
		cct_cls();
		int result = read(file_name[branch]);
		if (result == 113)
			loop = 0;
		if (result == -1)
			return -1;
	}
	return 0;
}