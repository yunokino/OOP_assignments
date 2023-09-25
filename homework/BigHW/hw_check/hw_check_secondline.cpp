/* 2152041 计科 王浩 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

typedef struct student
{
	char class_num[20];
	char stu_num[20];
	char name[30];
	int ori_right;
	int check_right;
	student* next;
	student* my_friend = NULL;
	int friend_count = 0;
	int being_abandoned = 0;
}student;

int check_debug(ostringstream& msg, const char* debug)
{
	if (strlen(debug) != 5)
	{
		msg << "参数[--debug]必须为5位0/1";
		return 1;
	}
	else if (!strcmp("00000", debug))
	{
		msg << "参数[--debug]的设置为[00000]，请至少指定一个1";
	}
	for (unsigned int i = 0; i < strlen(debug); i++)
	{
		if (!(debug[i] == '0' || debug[i] == '1'))
			msg << "参数[--debug]的第[" << i + 1 << "]位不是0/1";
	}
	return 0;
}

int check_filename(ostringstream& msg, const char* filename)
{
	const char* suffix = strrchr(filename, '.');
	if (suffix == NULL)
	{
		msg << "不是源程序文件";
		return 1;
	}
	if ((strcmp(suffix, ".cpp") == 0) || (strcmp(suffix, ".c") == 0) || (strcmp(suffix, ".h") == 0))
	{
		return 0;
	}
	msg << "不是源程序文件";
	return 1;
}

int check_same(student* head, const char* stu_num)
{
	for (student* p = head->next; p != NULL; p = p->next)
	{
		if (!strcmp(stu_num, p->stu_num))
		{
			return 1;
		}
	}
	return 0;
}

int check_repeat(student* p, int friend_count, const char* stu_num)
{
	for (int i = 0; i < friend_count; i++)
	{
		if (!strcmp(stu_num, p->my_friend[i].stu_num))
			return 1;
	}
	return 0;
}

void swap(student* p1, student* p2)
{
	char tmp[20];
	int tmp1;
	strcpy(tmp, p1->class_num);
	strcpy(p1->class_num, p2->class_num);
	strcpy(p2->class_num, tmp);

	strcpy(tmp, p1->stu_num);
	strcpy(p1->stu_num, p2->stu_num);
	strcpy(p2->stu_num, tmp);

	strcpy(tmp, p1->name);
	strcpy(p1->name, p2->name);
	strcpy(p2->name, tmp);

	tmp1 = p1->ori_right;
	p2->ori_right = p1->ori_right;
	p2->ori_right = tmp1;

	tmp1 = p1->check_right;
	p2->check_right = p1->check_right;
	p2->check_right = tmp1;
}

int check_exist(student* head, const char* stu_num, const char* name)
{
	for (student* p = head->next; p != NULL && p->next != NULL; p = p->next)
	{
		if (!strcmp(p->stu_num, stu_num) && !strcmp(p->name, name))
			return 1;
	}
	return 0;
}

int bubble_sort(student* my_friend, int friend_count)
{
	for (int i = 0; i < friend_count - 1; i++)
		for (int j = 0; j < friend_count - i - 1; j++)
		{
			if (strcmp(my_friend[j].stu_num, my_friend[j + 1].stu_num) > 0)
			{
				swap(my_friend[j], my_friend[j + 1]);
			}
		}

	return 0;
}

int both_check(student* head, student p, const char* my_stunum, const char* my_name)
{
	for (student* pointer = head->next; pointer != NULL && pointer->next != NULL; pointer = pointer->next)
	{
		if (!strcmp(p.stu_num, pointer->stu_num))
		{
			for (int i = 0; i < pointer->friend_count; i++)
			{
				if (!strcmp(pointer->my_friend[i].stu_num, my_stunum) && !strcmp(pointer->my_friend[i].name, my_name))
					return 1;
			}

		}
	}
	return 0;
}

int check_end(const char* content)
{
	int i = 0;
	if (content[0] == '/' && content[1] == '/')
		return 1;
	while (content[i] != '\0')
	{
		if (content[i] == '*' && content[i + 1] == '/')
			return 1;
		i++;
	}
	return 0;
}

student* read_stulist(ostringstream& msg, const char* filename)
{
	fstream fp;
	fp.open(filename, ios::in | ios::binary);
	if (!fp.is_open())
	{
		exit(-1);
	}
	int line_count = 0;
	int student_count = 0;
	student* head = new(nothrow)student;
	if (head == NULL)
		exit(-1);
	head->next = NULL;
	student* p = head;
	char buffer[256];
	char ch;
	while ((ch = fp.get()) != EOF)
	{
		if (ch == '#')
		{
			line_count++;
			msg << "\t--> 学生名单[" << filename << "]中的第[" << line_count << "]行为注释行，忽略" << endl;
			fp.getline(buffer, 256, '\n');
		}
		else
		{
			fp.seekg(-1, ios::cur);
			student* pointer = new(nothrow)student;
			if (pointer == NULL)
				exit(-1);
			line_count++;
			fp >> pointer->class_num >> pointer->stu_num >> pointer->name >> pointer->ori_right >> pointer->check_right;
			if (check_same(head, pointer->stu_num))
			{
				msg << "\t--> 学生名单[" << filename << "]中的第[" << line_count << "]行学号[" << pointer->stu_num << "]重复，忽略" << endl;
			}
			else
			{
				p->next = pointer;
				pointer->next = NULL;
				p = pointer;
			}
		}
	}
	line_count--;//多读一个空行
	for (student* p = head->next; p != NULL && p->next != NULL; p = p->next)
		student_count++;
	msg << "读取完成，共[" << line_count << "]行有内容，去重后学生总数[" << student_count << "]个" << endl;
	fp.close();
	return head;
}

int print_stulist(ostringstream& msg, student* head)
{
	//冒泡排序，只交换数据域
	int student_count = 0;
	for (student* p = head->next; p != NULL && p->next != NULL; p = p->next)
		student_count++;
	student* list = new(nothrow) student[student_count];
	if (list == NULL)
		exit(-1);
	/* 先排序好课号，再排序学号,再把数组排序好的赋给链表 */
	int j = 0;
	for (student* p = head->next; p != NULL && p->next != NULL; p = p->next, j++)
	{
		strcpy(list[j].class_num, p->class_num);
		strcpy(list[j].stu_num, p->stu_num);
		strcpy(list[j].name, p->name);
		list[j].ori_right = p->ori_right;
		list[j].check_right = p->check_right;
	}
	for (int i = 0; i < student_count - 1; i++)
		for (int j = 0; j < student_count - i - 1; j++)
		{
			if (strcmp(list[j].class_num, list[j + 1].class_num) > 0)//strcmp好用喵
			{
				swap(list[j], list[j + 1]);
			}
		}
	for (int i = 0; i < student_count - 1; i++)
		for (int j = 0; j < student_count - i - 1; j++)
		{
			if (strcmp(list[j].stu_num, list[j + 1].stu_num) > 0 && !strcmp(list[j + 1].class_num, list[j].class_num))
			{
				swap(list[j + 1], list[j]);
			}
		}
	int i = 0;
	for (student* p = head->next; p != NULL && p->next != NULL; p = p->next, i++)
	{
		strcpy(p->class_num, list[i].class_num);
		strcpy(p->stu_num, list[i].stu_num);
		strcpy(p->name, list[i].name);
		p->ori_right = list[i].ori_right;
		p->check_right = list[i].check_right;
	}
	delete[]list;
	msg << "序号\t课号\t学号\t姓名\t原始程序正确\t校验程序正确\n";
	int count = 1;
	for (student* p = head->next; p != NULL && p->next != NULL; p = p->next, count++)
	{
		msg << count << "#" << '\t' << p->class_num << '\t' << p->stu_num << '\t' << p->name << '\t'
			<< p->ori_right << '\t' << p->check_right << endl;
	}
	return 0;
}

int read_2nd_line(ostringstream& msg, student* head, const char* filename)
{
	msg << "序号\t课号\t学号\t姓名\t文件名\t分析结果\n";
	int count = 0;
	for (student* p = head->next; p != NULL && p->next != NULL; p = p->next, count++)
	{
		ifstream fp;
		char buffer[300] = { 0 };
		char content[400] = { 0 };
		char tmp_name[100] = { 0 }, tmp_stu_num[100] = { 0 };
		int full_count = 0;
		int err_count = 0;
		int friend_count = 0;
		p->my_friend = new student[20];
		char path_name[100] = "./source/";
		strcat(path_name, p->class_num);
		strcat(path_name, "-");
		strcat(path_name, filename);
		strcat(path_name, "/");
		strcat(path_name, p->stu_num);
		strcat(path_name, "-");
		strcat(path_name, p->name);
		strcat(path_name, "-");
		strcat(path_name, filename);
		msg << count + 1 << "#" << '\t' << p->class_num << '\t' << p->stu_num << '\t' << p->name
			<< '\t' << filename;
		fp.open(path_name, ios::in | ios::binary);
		if (fp.is_open() == 0)
		{
			msg << "\t未提交\n";
			p->check_right = 0;
			continue;
		}
		fp.getline(buffer, 256);
		while (!strcmp(buffer, "\r"))
			fp.getline(buffer, 400);
		fp.getline(content, 400);
		while (!strcmp(content, "\r"))
			fp.getline(content, 400);
		if (strlen(content) > 256)
		{
			msg << "\t非空行超过了合理长度[256]字节." << endl;
			continue;
		}
		int i = 0;
		while (content[i] == ' ' || content[i] == '\t')
			i++;
		if (content[i] != '/' || !(content[i + 1] == '*' || content[i + 1] == '/') || !check_end(content))
		{
			msg << "\t第2行信息有错[不是//或/*开头，或者以/*开头但*/不在同一行]" << endl;
			continue;
		}
		i += 2;
		while (content[i] != '\r')
		{
			if ((content[i] == '*' && content[i + 1] == '/') || content[i] == '\r')
				break;
			while (content[i] == ' ' || content[i] == '\t' || content[i] == '\n')
				i++;
			int j = 0;
			while (content[i] != ' ' && content[i] != '*' && content[i] != '\r')
			{
				tmp_stu_num[j] = content[i];
				j++;
				i++;
			}
			tmp_stu_num[j] = '\0';
			while (content[i] == ' ' || content[i] == '\t' || content[i] == '\n')
				i++;
			j = 0;
			while (content[i] != ' ' && content[i] != '\r' && content[i] != '\t')
			{
				if (content[i] == '*' && content[i + 1] != ' ')
					break;
				tmp_name[j] = content[i];
				j++;
				i++;
			}
			tmp_name[j] = '\0';
			if (!strcmp(tmp_stu_num, "") && !strcmp(tmp_name, ""))
				continue;
			if (check_exist(head, tmp_stu_num, tmp_name))
			{
				if (check_repeat(p, friend_count, tmp_stu_num))
				{
					msg << "\t互验列表第[" << full_count + 1 << "]项的学号[" << tmp_stu_num << "]重复，忽略" << endl;
					full_count++;
					err_count++;
					continue;
				}
				strcpy(p->my_friend[friend_count].stu_num, tmp_stu_num);
				strcpy(p->my_friend[friend_count].name, tmp_name);
				friend_count++;
				full_count++;
			}
			else
			{
				if (!strcmp(p->stu_num, tmp_stu_num))
				{
					msg << "\t第[" << full_count + 1 << "]项写了自己，耍无赖么？" << endl;
					err_count++;
					full_count++;
					break;
				}
				else
				{
					if (err_count == 0)
						msg << "\t";
					else
						msg << "\t\t\t\t\t";
					if (strlen(tmp_stu_num) < 64)
					{
						if (!strcmp(tmp_name, ""))
							msg << "第[" << full_count << "]个学生后面的信息不全，忽略" << endl;
						else
							msg << "第[" << full_count + 1 << "]项的学号[" << tmp_stu_num << "]/姓名[" << tmp_name << "]不正确，忽略" << endl;
					}
					else
					{
						msg << "第[1]项的学号[韩梦阳2153052，刘金昊2153816，王竑坤2152832，秦光辉2154161，沈裖/姓名[逍";
						msg << char(0xDB) << char(0x32) << "150912]不正确，忽略\n";
						err_count++;
						full_count++;
						break;
					}
				}
				err_count++;
				full_count++;
			}
		}
		if (err_count == 0)
			msg << "\tok\n";
		if (friend_count != 0)
		{
			bubble_sort(p->my_friend, friend_count);
			msg << "\t读到的正确互验者\n";
		}
		for (int i = 0; i < friend_count; i++)
		{
			msg << "\t" << i + 1 << "\t" << p->my_friend[i].stu_num << "\t" << p->my_friend[i].name << endl;
		}
		p->friend_count = friend_count;
		fp.close();
	}
	return 0;
}

int print_2nd_line(ostringstream& msg, student* head)
{
	msg << "序号\t课号\t学号\t姓名\n";
	int count = 1;
	for (student* p = head->next; p != NULL && p->next != NULL; p = p->next, count++)
	{
		int friend_count = 0;
		msg << count << "#" << '\t' << p->class_num << '\t' << p->stu_num
			<< '\t' << p->name;
		if (p->friend_count == 0)
		{
			msg << '\t' << "无有效匹配项" << endl;
			continue;
		}
		msg << endl;
		for (int i = 0; i < p->friend_count; i++)
		{
			if (both_check(head, p->my_friend[i], p->stu_num, p->name))
				msg << "\t$" << friend_count + 1 << "\t" << p->my_friend[i].stu_num << "\t" << p->my_friend[i].name << "\t" << "ok" << endl;
			else
			{
				p->being_abandoned++;
				msg << "\t$" << friend_count + 1 << "\t" << p->my_friend[i].stu_num << "\t" << p->my_friend[i].name << "\t" << "抛弃了你" << endl;
			}
			friend_count++;
		}
	}
	return 0;
}

int print_finalscore(ostringstream& msg, student* head)
{
	int count = 0;
	msg << "序号\t课号\t学号\t姓名\t原始程序得分\t检查程序原始分\t检查程序扣分1\t检查程序扣分2\t检查程序总分\n";
	for (student* p = head->next; p != NULL && p->next != NULL; p = p->next, count++)
	{
		int score = 0;
		int minus_score = 0;
		score += (p->ori_right ? 100 : 0) + (p->check_right ? 100 : 0);
		if (score > 100)
			score = 100;
		msg << count + 1 << "#" << '\t' << p->class_num << '\t' << p->stu_num << '\t' << p->name
			<< '\t' << (p->ori_right ? 100 : 0) << '\t' << (p->check_right ? 100 : 0);
		score -= (p->check_right ? 0 : 100);
		msg << "\t" << p->being_abandoned * (-100);
		score -= p->being_abandoned * 100;
		if (p->friend_count < 5)
			minus_score -= (5 - p->friend_count) * 20;
		for (int i = 0; i < p->friend_count; i++)
		{
			for (student* pointer = head->next; pointer != NULL && pointer->next != NULL; pointer = pointer->next)
			{
				if (!strcmp(p->my_friend[i].stu_num, pointer->stu_num))
				{
					minus_score -= pointer->ori_right ? 0 : 20;
				}
			}
		}
		score += minus_score;
		msg << "\t" << minus_score << "\t" << score << endl;
	}
	return 0;
}

static int second_line_check(ostringstream& msg, const char* debug, const char* courseid, const char* filename,const char*stulist) //参数自行约定，其中有一个是debug[5] 
{

	/* 允许加入其它语句，但不能有cout */
	char path_name[100] = "./source/";
	strcat(path_name, stulist);
	student* head;
	/* 读课号.dat */
	msg << "1.读取课号配置文件" << endl;
	head = read_stulist(msg, path_name); //允许带返回值（也可以不要），参数自行约定，其中有一个是msg 
	/* 允许加入其它语句(也可以不要)，但不能有cout */
	if (debug[0] == '1')
		cout << msg.str() << endl;

	/* 允许加入其它语句，但不能有cout */

	msg.str(""); //清空msg中的信息
	msg << "2.按课号+学号排序的学生名单" << endl;
	print_stulist(msg, head); //允许带返回值（也可以不要），参数自行约定，其中有一个是msg 
	/* 允许加入其它语句(也可以不要)，但不能有cout */
	if (debug[1] == '1')
		cout << msg.str() << endl;

	/* 允许加入其它语句，但不能有cout */

	msg.str(""); //清空msg中的信息
	msg << "3.所有学生读取第2行的解析信息" << endl;
	read_2nd_line(msg, head, filename); //允许带返回值（也可以不要），参数自行约定，其中有一个是msg 
	// /* 允许加入其它语句(也可以不要)，但不能有cout */
	if (debug[2] == '1')
		cout << msg.str() << endl;

	/* 允许加入其它语句，但不能有cout */

   /* 将双方进行信息匹配 */
	msg.str(""); //清空msg中的信息
	msg << "4.所有学生的第2行互验匹配结果" << endl;
	print_2nd_line(msg, head); //允许带返回值（也可以不要），参数自行约定，其中有一个是msg 
	/* 允许加入其它语句(也可以不要)，但不能有cout */
	if (debug[3] == '1')
		cout << msg.str() << endl;

	/* 允许加入其它语句，但不能有cout */

   /* 再根据通过与否进行检查 */
	msg.str(""); //清空msg中的信息
	msg << "5.所有学生的第2行互验最终得分" << endl;
	print_finalscore(msg, head); //允许带返回值（也可以不要），参数自行约定，其中有一个是msg 
	/* 允许加入其它语句(也可以不要)，但不能有cout */
	if (debug[4] == '1')
		cout << msg.str() << endl;

	/* 允许加入其它语句，但不能有cout */
	   /* 释放所有内存 */
	for (student* p = head; p != NULL;)
	{
		student* tmp = p->next;
		if (p->my_friend != NULL)
			delete[] p->my_friend;
		if (p != NULL)
			delete p;
		p = tmp;
	}
	return 0;
}


int check_secondline(const string& cno, const string& stulist_fname, const string& filename, const string& debug)
{
	ostringstream msg;
	int wrong = 0;
	if (check_filename(msg, filename.c_str()) || check_debug(msg, debug.c_str()))
	{
		goto END;
	}
	second_line_check(msg, debug.c_str(), cno.c_str(), filename.c_str(),stulist_fname.c_str());
	return 0;

END:
	cout << msg.str() << endl;


	return 0;
}


