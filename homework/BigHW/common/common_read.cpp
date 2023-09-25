/* 2152041 计科 王浩 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <conio.h>
#include <io.h>
#include "../include/cmd_console_tools.h"
#include "../include/common_read.h"
#include "../include/cmd_gmw_tools.h"
using namespace std;
int read_file(string*file_name)
{
	const char* to_search = "./book/*.txt";
	int i = 0;
	long handle;
	struct _finddata_t fileinfo;
	handle = _findfirst(to_search, &fileinfo);
	if (handle == -1)
		return -1;
	file_name[i] = fileinfo.name;
	i++;
	while (!_findnext(handle, &fileinfo))
	{
		file_name[i] = fileinfo.name;
		i++;
	}
	for (int j = 0; file_name[j] != ""; j++)
	{
		int pos = file_name[j].find(".txt");
		if (pos > -1)
			file_name[j].erase(pos, 4);
	}
	_findclose(handle);
	return 0;
}

int choose_file(string* file_name)
{
	int choice = 0;
	cct_showstr(frame_start+1, frame_start, "请选择文件");
	cct_showstr(frame_start, frame_start+1, "╔════════╗");
	for (int i = 1; i < 15; i++)
	{
		cct_showstr(frame_start, frame_start+1 + i, "║");
		cct_showstr(frame_end, frame_start+1 + i, "║");
	}
	cct_showstr(frame_start, frame_start + frame_height, "╚════════╝");
	while (true)
	{
		int a = 0, b = 0;
		int start = 0;
		if (choice >= 13)
			start = choice - 12;
		for (int i = start; i < start + 13; i++)
		{
			if (i == choice)
				cct_showstr(frame_start + 2, frame_start + 2 + i - start, file_name[i].c_str(), 14, 0, 1, 15);
			else
				cct_showstr(frame_start + 2, frame_start + 2 + i - start, file_name[i].c_str(), 0, 7, 1, 15);
		}
		a = _getch();
		if (a == 13)
			break;
		if (a == 224)
		{
			b = _getch();
			if (b == 72)
			{
				choice--;
				if (choice < 0)
					choice = 0;
			}
			else if (b == 80)
			{
				choice++;
				if (file_name[choice] == "")
					choice--;
			}
			else;
		}
	}
	string tmp = "选择了[" + file_name[choice] + ".txt]，按回车键继续";
	cct_showstr(frame_start, frame_start + frame_height + 2, tmp.c_str());
	while (_getch() != '\r');
	return choice;
}

void print_pages(string txt,int line,int format)
{
	cct_cls();
	int pos = 0;
	int count = 0;
	if (format == 1)
	{
		for (unsigned int i = 0; i < txt.size(); )
		{
			if (txt[i] == '\r' && (txt[i+2]!=' '&&txt[i+2]!='\t'))
			{
				txt.erase(i, 2);
				continue;
			}
			i++;
		}
	}
	int start = 0, end = txt.size();
	for (unsigned int i = 0; i < txt.size(); i++)
	{
		if (txt[i] == '\r')
		{
				count++;
				if (count == line)
					start = i;
				else if (count == line + 28)
					end = i;
				else;
		}
	}
	string tmp = txt.substr(start, end);
	cct_showstr(0, 2, tmp.c_str(), 0, 7);
}

int read_progress(string file_name)
{
	fstream fp;
	string file = "./book/position.sav";
	fp.open(file.c_str(), ios::in|ios::binary);
	if (!fp.is_open())
		return 0;
	string tmp;
	while (getline(fp, tmp))
	{
		if (tmp == "[" + file_name + ".txt]\r" || tmp == "[" + file_name + ".txt]")
		{
			getline(fp, tmp);
			return stoi(tmp);
		}
	}
	fp.close();
	return 0;
}

void change_progress(int progress, string file_name)
{
	ifstream fin;
	ofstream fout;
	string content;
	fin.open("./book/position.sav", ios::in | ios::binary);
	char ch;
	while ((ch = fin.get()) != EOF)
		content += ch;
	fin.close();
	fout.open("./book/position.sav", ios::out | ios::binary | ios::trunc);
	int pos = content.find("["+file_name+".txt]");
	if (pos != -1)
	{
		pos += file_name.size() + 7;
		int record = 0;
		int tmp = pos;
		while (content[tmp] >= '0' && content[tmp] <= '9')
		{
			record++;
			tmp++;
		}
		content.erase(pos, record);
		content.insert(pos, to_string(progress));
	}
	fout.write(content.c_str(), content.size());
	fout.close();
}

int read(string file_name)
{
	fstream fp;
	string file = "./book/"+file_name + ".txt";
	string txt;
	fp.open(file.c_str(), ios::in | ios::binary);
	if (!fp.is_open())
		return - 1;
	int format = 0;
	char ch;
	while ((ch = fp.get())!=EOF)
		txt += ch;
	int line = 0;
	cct_setcursor(CURSOR_INVISIBLE);
	int loop = 1;
	int progress = read_progress(file_name);
	int count = 0;
	for (unsigned int i = 0; i < txt.size(); i++)
		if (txt[i] == '\n')
			count++;	
	for (int i = 0; i < progress; i++)
	{
		if (txt[i] == '\r')
			line++;
	}
	print_pages(txt, line, format);
	while (loop)
	{
		cct_showstr(0, 0, "上下箭头翻页，s键跳转进度，n键结束此次阅读，q键退出阅读，f键进行格式转化");
		string now_progress = "当前进度 : " + to_string(double(line)/double(count)) + "%";
		cct_showstr(0, 1, now_progress.c_str());
		int a = _getch();
		if (a == 224)
		{
			int b = _getch();
			if (b == 72)
			{
				line--;
				if (line < 0)
					line = 0;
				print_pages(txt,line, format);
			}
			else if (b == 80)
			{
				line++;
				if (line + 1 > count)
					line = count - 1;
				print_pages(txt, line, format);
			}
			else;
		}
		else
		{
			if (a == 'q' || a == 'Q')
			{
				fp.close();
				int tmp = (int)((double)line / (double)count * txt.size());
				change_progress(tmp, file_name);
				return 'q';
			}
			else if (a == 'n' || a == 'N')
			{
				loop = 0;
				int tmp = (int)((double)line / (double)count * txt.size());
				change_progress(tmp,file_name);
			}
			else if (a == 's' || a == 'S')
			{
				cct_cls();
				cout << "请输入要跳转的进度(浮点数) : " ;
				double headway = 0;
				cin >> headway;
				line = (int)(count * headway);
				print_pages(txt,line, format);
			}
			else if (a == 'f' || a == 'F')
			{
				format = format ? format - 1 : format + 1;
				print_pages(txt, line, format);
			}
			else;
		}
	}
	fp.close();
	return 0;
}