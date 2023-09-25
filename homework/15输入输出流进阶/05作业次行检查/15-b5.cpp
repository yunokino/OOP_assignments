/* 2152041 计科 王浩 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstring>
//允许添加需要的系统头文件 
using namespace std;

/* 1、允许自定义类型
   2、不允许定义全局变量（不含只读及宏定义）
   3、允许自定义函数，但所有的自定义函数中（含second_line_check中的read_stulist等五个函数）不允许任何的cout出现
   4、除main函数外，不允许使用goto语句

*/
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

const char* parameter[4] = { "--secondline","--courseid","--filename","--debug" };
static void usage(const char* const procname);//声明一下
int check_main_parameter(const char *str)
{
	for (int i = 0; i < 4; i++)
	{
		if (!strcmp(parameter[i], str))
		{
			if (i == 0)
				return 0;//参数为seondline,不需要附加参数
			else if (i == 1)
				return 1;//参数为debug
			else if (i == 2)
				return 2;//参数为需要附加参数的主参数
			else if (i == 3)
				return 3;
		}
	}
	return -1;//不是主参数
}

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

void err_out(const char *error_info,ostringstream& msg,const char* str, int way)
{
	usage(error_info);
	if (way == 0)
	{
		msg.str("");
		msg << "参数[" << str << "]重复";
	}
	else if (way == 1)
	{
		msg.str("");
		msg << "参数[" << str << "]缺少附加参数. (类型:string)";
	}
	else if (way == 2)
	{
		msg.str("");
		msg << "必须指定参数[" << str << "]";
	}
	else if (way == 3)
	{
		msg.str("");
		msg << "参数[" << str << "]非法.";
	}
	else if (way == 4)
	{
		msg.str("");
		msg << "参数[" << str << "]格式非法.";
	}
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

int check_repeat(student* p, int friend_count,const char* stu_num)
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

int bubble_sort(student* my_friend,int friend_count)
{
	for (int i = 0; i < friend_count-1; i++)
		for (int j = 0; j < friend_count - i - 1; j++)
		{
			if (strcmp(my_friend[j].stu_num, my_friend[j + 1].stu_num) > 0)
			{
				swap(my_friend[j], my_friend[j + 1]);
			}
		}

	return 0;
}

int both_check(student *head, student p, const char* my_stunum, const char *my_name)
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
	while (content[i]!='\0')
	{
		if (content[i] == '*' && content[i + 1] == '/')
			return 1;
		i++;
	}
	return 0;
}

student* read_stulist(ostringstream& msg, const char*filename)
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
	student *p =head;
	char buffer[256];
	char ch;
	while ((ch = fp.get())!=EOF)
	{
		if (ch == '#')
		{
			line_count++;
			msg << "\t--> 学生名单[" << filename << "]中的第[" << line_count<< "]行为注释行，忽略" << endl;
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
				msg << "\t--> 学生名单["<<filename<<"]中的第["<<line_count<<"]行学号["<<pointer->stu_num<<"]重复，忽略" << endl;
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
	msg << "读取完成，共["<<line_count<<"]行有内容，去重后学生总数["<<student_count<<"]个" << endl;
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
	for(int i = 0; i < student_count - 1; i++)
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
			if (strcmp(list[j].stu_num, list[j+1].stu_num) > 0 && !strcmp(list[j+1].class_num, list[j].class_num))
			{
				swap(list[j+1], list[j]);
			}
		}
	int i = 0;
	for (student* p = head->next; p != NULL && p->next != NULL; p = p->next, i++)
	{
		strcpy(p->class_num , list[i].class_num);
		strcpy(p->stu_num , list[i].stu_num);
		strcpy(p->name , list[i].name);
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

int read_2nd_line(ostringstream& msg, student* head, const char*filename)
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
		msg << count + 1<< "#" << '\t' << p->class_num << '\t' << p->stu_num << '\t' << p->name
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
		while(!strcmp(content, "\r"))
			fp.getline(content, 400);
		if (strlen(content) > 256)
		{
			msg << "\t非空行超过了合理长度[256]字节." << endl;
			continue;
		}
		int i = 0;
		while (content[i] == ' ' || content[i] == '\t')
			i++;
		if (content[i] != '/' || !(content[i+1] == '*' || content[i+1] == '/') || !check_end(content))
		{
			msg << "\t第2行信息有错[不是//或/*开头，或者以/*开头但*/不在同一行]" << endl;
			continue;
		}
		i += 2;
		while (content[i] != '\r')
		{
			if ((content[i] == '*' && content[i + 1] == '/')||content[i] == '\r')
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
			while (content[i] != ' '  && content[i] != '\r' && content[i] != '\t')
			{
				if (content[i] == '*' && content[i + 1] != ' ')
					break;
				tmp_name[j] = content[i];
				j++;
				i++;
			}
			tmp_name[j] = '\0';
			if (!strcmp(tmp_stu_num, "" )&& !strcmp(tmp_name , ""))
				continue;
			if (check_exist(head, tmp_stu_num, tmp_name))
			{
				if (check_repeat(p, friend_count, tmp_stu_num))
				{
					msg << "\t互验列表第["<< full_count + 1 <<"]项的学号["<< tmp_stu_num << "]重复，忽略" << endl;
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
				if (!strcmp(p->stu_num ,tmp_stu_num))
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
						msg << char(0xDB)<<char(0x32) << "150912]不正确，忽略\n";
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
			msg << "\t" << i + 1 <<"\t"<< p->my_friend[i].stu_num <<"\t" << p->my_friend[i].name << endl;
		}
		p->friend_count = friend_count;
		fp.close();
	}
	return 0;
}

int print_2nd_line(ostringstream& msg, student*head)
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
				msg << "\t$" << friend_count + 1 << "\t" << p->my_friend[i].stu_num << "\t" << p->my_friend[i].name<<"\t" << "ok" << endl;
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
		msg << "\t" <<p->being_abandoned * (-100);
		score -= p->being_abandoned * 100;
		if (p->friend_count < 5)
			minus_score -= (5 - p->friend_count) * 20;
		for (int i = 0; i < p->friend_count; i++)
		{
			for (student* pointer = head->next; pointer != NULL && pointer->next != NULL; pointer = pointer->next)
			{
				if (!strcmp(p->my_friend[i].stu_num, pointer->stu_num))
				{
					minus_score -= pointer->ori_right ? 0: 20;
				}
			}
		}
		score += minus_score;
		msg << "\t" << minus_score << "\t" << score << endl;
	}
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：除了5句cout之外，不允许任何的cout语句
***************************************************************************/
static int second_line_check(ostringstream &msg , const char*debug, const char*courseid, const char*filename) //参数自行约定，其中有一个是debug[5] 
{

	 /* 允许加入其它语句，但不能有cout */
	char path_name[100] = "./source/";
	strcat(path_name, courseid);
	strcat(path_name, ".dat");
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
			if(p->my_friend!=NULL)
				delete[] p->my_friend;
			if (p != NULL)
				delete p;
			p = tmp;
		}
		return 0;
}

/***************************************************************************
  函数名称：
  功    能：用ostringstream的示例
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static void usage(const char* const procname)
{
	ostringstream msg;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	msg << "Usage: " << procname << " [ --secondline | --courseid cid | --filename name/all ] | --debug xxxxx" << endl;
	msg << setw(wopt) << ' ' << "--secondline   : 次行检查" << endl;
	msg << setw(wopt) << ' ' << "--courseid     : 课号" << endl;
	msg << setw(wopt) << ' ' << "--filename     : 文件名(不支持all)" << endl;
	msg << setw(wopt) << ' ' << "--debug xxxxx  : 跟5位0/1，从左到右依次表示需要打印[读课号文件 | 学生名单 | 第2行解析 | 互验匹配 | 最终结果]的信息，默认00000" << endl;
	msg << endl;

	msg << "e.g.   " << procname << " --secondline --courseid 100692 --filename 5-b14.c --debug 11111 : 检查100692课程的5-b14.c的第二行(打印所有信息)" << endl;
	msg << "       " << procname << " --secondline --courseid 100692 --filename 5-b14.c --debug 00100 : 检查100692课程的5-b14.c的第二行(打印解析信息)" << endl;
	msg << endl;
	cout << msg.str() << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：1、main函数中如果有输出，也仅限一句cout
			2、受1的限制，如果有需要，允许使用 goto END;(不允许再增加语句标号)
***************************************************************************/
int main(int argc, char** argv)
{
	ostringstream msg;

	/* 进行参数的分析，可以写在main中，也可以写自定义函数(带msg参数进去，函数中不允许cout)，如果有需要，允许goto  */
	/* 读取课号.dat里的数据，去重去空白打印 debug 10000
	   将其排序，按课号和学号顺序打印的学生名单 debug 01000
	   读取所有学生的第二行的解析信息(检测是否存在相应学生和注释的正确性) debug 00100
	   所有学生的第2行互验匹配结果 debug 00010
	   所有学生的初始分和最终得分
	*/
	int check[4] = { 0 };//统计各个参数出现的次数
	int wrong = 0;
	char debug[5] = { '1','1','1','1','1'};//debug选择输出项
	char courseid[100];
	char filename[100];
	if (argc == 1)
	{
		usage(argv[0]);
		goto END;
	}
	for (int i = 1; i < argc; i++)//主参数检查
	{
		switch (check_main_parameter(argv[i]))
		{
		case 0:
			check[0] += 1;
			if (check[0] > 1)
			{
				err_out(argv[0],msg, parameter[0], 0);
				goto END;
			}
			continue;
			break;
		case 1:
			check[1] += 1;
			if (i == argc - 1 || !strncmp("--", argv[i + 1],2))//短路运算符，不会有溢出报错
			{
				err_out(argv[0],msg, parameter[1], 1);
				goto END;
			}
			else if (check[1] > 1)
			{
				err_out(argv[0],msg, parameter[1], 0);
				goto END;
			}
			i++;
			strcpy(courseid, argv[i]);
			continue;
			break;
		case 2:
			check[2] += 1;
			if (i == argc - 1 || !strncmp("--", argv[i + 1], 2))//短路运算符，不会有溢出报错
			{
				err_out(argv[0],msg, parameter[2], 1);
				goto END;
			}
			else if (check[2] > 1)
			{
				err_out(argv[0],msg, parameter[2], 0);
				goto END;
			}
			i++;
			if (check_filename(msg, argv[i]))
			{
				usage(argv[0]);
				goto END;
			}
			strcpy(filename, argv[i]);
			continue;
			break;
		case 3:
			check[3] += 1;
			if (i == argc - 1 || !strncmp("--", argv[i + 1], 2))//短路运算符，不会有溢出报错
			{
				err_out(argv[0],msg, parameter[3], 1);
				msg << "(缺省:11111)";
				goto END;
			}
			else if (check[3] > 1)
			{
				err_out(argv[0],msg, parameter[3], 0);
				goto END;
			}
			i++;
			if (check_debug(msg, argv[i]))
			{
				usage(argv[0]);
				goto END;
			}
			else
				strncpy(debug, argv[i],5);
			continue;
			break;
		default:
			if (!strncmp(argv[i], "--", 2))
			{
				err_out(argv[0], msg, argv[i], 3);
				goto END;
			}
			else
			{
				err_out(argv[0], msg, argv[i], 4);
				goto END;
			}
			break;
		}	
	}
	for (int i = 0; i < 4; i++)
	{
		if (check[i] == 0)
		{
			err_out(argv[0],msg, parameter[i], 2);
			wrong = 1;
			break;
		}
	}
	if (wrong)
		goto END;
	/* 如果参数分析正确，则调用此函数进行检查(具体参数按需设置) */
	second_line_check(msg, debug, courseid, filename);

	 /* 允许加入其它语句，但不能有cout，如果有需要，允许goto */
	return 0;

		END:
	cout << msg.str() << endl;

	return 0;
}

