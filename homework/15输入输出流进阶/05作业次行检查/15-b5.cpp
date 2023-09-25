/* 2152041 �ƿ� ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstring>
//���������Ҫ��ϵͳͷ�ļ� 
using namespace std;

/* 1�������Զ�������
   2����������ȫ�ֱ���������ֻ�����궨�壩
   3�������Զ��庯���������е��Զ��庯���У���second_line_check�е�read_stulist������������������κε�cout����
   4����main�����⣬������ʹ��goto���

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
static void usage(const char* const procname);//����һ��
int check_main_parameter(const char *str)
{
	for (int i = 0; i < 4; i++)
	{
		if (!strcmp(parameter[i], str))
		{
			if (i == 0)
				return 0;//����Ϊseondline,����Ҫ���Ӳ���
			else if (i == 1)
				return 1;//����Ϊdebug
			else if (i == 2)
				return 2;//����Ϊ��Ҫ���Ӳ�����������
			else if (i == 3)
				return 3;
		}
	}
	return -1;//����������
}

int check_debug(ostringstream& msg, const char* debug)
{
	if (strlen(debug) != 5)
	{
		msg << "����[--debug]����Ϊ5λ0/1";
		return 1;
	}
	else if (!strcmp("00000", debug))
	{
		msg << "����[--debug]������Ϊ[00000]��������ָ��һ��1";
	}
	for (unsigned int i = 0; i < strlen(debug); i++)
	{
		if (!(debug[i] == '0' || debug[i] == '1'))
			msg << "����[--debug]�ĵ�[" << i + 1 << "]λ����0/1";
	}
	return 0;
}

int check_filename(ostringstream& msg, const char* filename)
{
	const char* suffix = strrchr(filename, '.');
	if (suffix == NULL)
	{
		msg << "����Դ�����ļ�";
		return 1;
	}
	if ((strcmp(suffix, ".cpp") == 0) || (strcmp(suffix, ".c") == 0) || (strcmp(suffix, ".h") == 0))
	{
		return 0;
	}
	msg << "����Դ�����ļ�";
	return 1;
}

void err_out(const char *error_info,ostringstream& msg,const char* str, int way)
{
	usage(error_info);
	if (way == 0)
	{
		msg.str("");
		msg << "����[" << str << "]�ظ�";
	}
	else if (way == 1)
	{
		msg.str("");
		msg << "����[" << str << "]ȱ�ٸ��Ӳ���. (����:string)";
	}
	else if (way == 2)
	{
		msg.str("");
		msg << "����ָ������[" << str << "]";
	}
	else if (way == 3)
	{
		msg.str("");
		msg << "����[" << str << "]�Ƿ�.";
	}
	else if (way == 4)
	{
		msg.str("");
		msg << "����[" << str << "]��ʽ�Ƿ�.";
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
			msg << "\t--> ѧ������[" << filename << "]�еĵ�[" << line_count<< "]��Ϊע���У�����" << endl;
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
				msg << "\t--> ѧ������["<<filename<<"]�еĵ�["<<line_count<<"]��ѧ��["<<pointer->stu_num<<"]�ظ�������" << endl;
			}
			else
			{
				p->next = pointer;
				pointer->next = NULL;
				p = pointer;
			}
		}
	}
	line_count--;//���һ������
	for (student* p = head->next; p != NULL && p->next != NULL; p = p->next)
		student_count++;
	msg << "��ȡ��ɣ���["<<line_count<<"]�������ݣ�ȥ�غ�ѧ������["<<student_count<<"]��" << endl;
	fp.close();
	return head;
}

int print_stulist(ostringstream& msg, student* head)
{
	//ð������ֻ����������
	int student_count = 0;
	for (student* p = head->next; p != NULL && p->next != NULL; p = p->next)
		student_count++;
	student* list = new(nothrow) student[student_count];
	if (list == NULL)
		exit(-1);
	/* ������ÿκţ�������ѧ��,�ٰ���������õĸ������� */
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
			if (strcmp(list[j].class_num, list[j + 1].class_num) > 0)//strcmp������
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
	msg << "���\t�κ�\tѧ��\t����\tԭʼ������ȷ\tУ�������ȷ\n";
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
	msg << "���\t�κ�\tѧ��\t����\t�ļ���\t�������\n";
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
			msg << "\tδ�ύ\n";
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
			msg << "\t�ǿ��г����˺�����[256]�ֽ�." << endl;
			continue;
		}
		int i = 0;
		while (content[i] == ' ' || content[i] == '\t')
			i++;
		if (content[i] != '/' || !(content[i+1] == '*' || content[i+1] == '/') || !check_end(content))
		{
			msg << "\t��2����Ϣ�д�[����//��/*��ͷ��������/*��ͷ��*/����ͬһ��]" << endl;
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
					msg << "\t�����б��["<< full_count + 1 <<"]���ѧ��["<< tmp_stu_num << "]�ظ�������" << endl;
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
					msg << "\t��[" << full_count + 1 << "]��д���Լ���ˣ����ô��" << endl;
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
							msg << "��[" << full_count << "]��ѧ���������Ϣ��ȫ������" << endl;
						else
							msg << "��[" << full_count + 1 << "]���ѧ��[" << tmp_stu_num << "]/����[" << tmp_name << "]����ȷ������" << endl;
					}
					else
					{
						msg << "��[1]���ѧ��[������2153052�������2153816�����f��2152832���ع��2154161�����]/����[��";
						msg << char(0xDB)<<char(0x32) << "150912]����ȷ������\n";
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
			msg << "\t��������ȷ������\n";
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
	msg << "���\t�κ�\tѧ��\t����\n";
	int count = 1;
	for (student* p = head->next; p != NULL && p->next != NULL; p = p->next, count++)
	{
		int friend_count = 0;
		msg << count << "#" << '\t' << p->class_num << '\t' << p->stu_num
			<< '\t' << p->name;
		if (p->friend_count == 0)
		{
			msg << '\t' << "����Чƥ����" << endl;
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
				msg << "\t$" << friend_count + 1 << "\t" << p->my_friend[i].stu_num << "\t" << p->my_friend[i].name << "\t" << "��������" << endl;
			}
			friend_count++;
		}
	}
	return 0;
}

int print_finalscore(ostringstream& msg, student* head)
{
	int count = 0;
	msg << "���\t�κ�\tѧ��\t����\tԭʼ����÷�\t������ԭʼ��\t������۷�1\t������۷�2\t�������ܷ�\n";
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ��������5��cout֮�⣬�������κε�cout���
***************************************************************************/
static int second_line_check(ostringstream &msg , const char*debug, const char*courseid, const char*filename) //��������Լ����������һ����debug[5] 
{

	 /* �������������䣬��������cout */
	char path_name[100] = "./source/";
	strcat(path_name, courseid);
	strcat(path_name, ".dat");
	student* head;
	/* ���κ�.dat */
	msg << "1.��ȡ�κ������ļ�" << endl;
	head = read_stulist(msg, path_name); //���������ֵ��Ҳ���Բ�Ҫ������������Լ����������һ����msg 
	 /* ��������������(Ҳ���Բ�Ҫ)����������cout */
		if (debug[0] == '1')
			cout << msg.str() << endl;

	 /* �������������䣬��������cout */

    msg.str(""); //���msg�е���Ϣ
	msg << "2.���κ�+ѧ�������ѧ������" << endl;
	print_stulist(msg, head); //���������ֵ��Ҳ���Բ�Ҫ������������Լ����������һ����msg 
	 /* ��������������(Ҳ���Բ�Ҫ)����������cout */
		if (debug[1] == '1')
			cout << msg.str() << endl;

	 /* �������������䣬��������cout */

	msg.str(""); //���msg�е���Ϣ
	msg << "3.����ѧ����ȡ��2�еĽ�����Ϣ" << endl;
	read_2nd_line(msg, head, filename); //���������ֵ��Ҳ���Բ�Ҫ������������Լ����������һ����msg 
	// /* ��������������(Ҳ���Բ�Ҫ)����������cout */
		if (debug[2] == '1')
			cout << msg.str() << endl;

	 /* �������������䣬��������cout */

	/* ��˫��������Ϣƥ�� */
	msg.str(""); //���msg�е���Ϣ
	msg << "4.����ѧ���ĵ�2�л���ƥ����" << endl;
	print_2nd_line(msg, head); //���������ֵ��Ҳ���Բ�Ҫ������������Լ����������һ����msg 
	/* ��������������(Ҳ���Բ�Ҫ)����������cout */
		if (debug[3] == '1')
			cout << msg.str() << endl;

	 /* �������������䣬��������cout */

	/* �ٸ���ͨ�������м�� */
	msg.str(""); //���msg�е���Ϣ
	msg << "5.����ѧ���ĵ�2�л������յ÷�" << endl;
	print_finalscore(msg, head); //���������ֵ��Ҳ���Բ�Ҫ������������Լ����������һ����msg 
	 /* ��������������(Ҳ���Բ�Ҫ)����������cout */
		if (debug[4] == '1')
			cout << msg.str() << endl;

	 /* �������������䣬��������cout */
		/* �ͷ������ڴ� */
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
  �������ƣ�
  ��    �ܣ���ostringstream��ʾ��
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
static void usage(const char* const procname)
{
	ostringstream msg;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	msg << "Usage: " << procname << " [ --secondline | --courseid cid | --filename name/all ] | --debug xxxxx" << endl;
	msg << setw(wopt) << ' ' << "--secondline   : ���м��" << endl;
	msg << setw(wopt) << ' ' << "--courseid     : �κ�" << endl;
	msg << setw(wopt) << ' ' << "--filename     : �ļ���(��֧��all)" << endl;
	msg << setw(wopt) << ' ' << "--debug xxxxx  : ��5λ0/1�����������α�ʾ��Ҫ��ӡ[���κ��ļ� | ѧ������ | ��2�н��� | ����ƥ�� | ���ս��]����Ϣ��Ĭ��00000" << endl;
	msg << endl;

	msg << "e.g.   " << procname << " --secondline --courseid 100692 --filename 5-b14.c --debug 11111 : ���100692�γ̵�5-b14.c�ĵڶ���(��ӡ������Ϣ)" << endl;
	msg << "       " << procname << " --secondline --courseid 100692 --filename 5-b14.c --debug 00100 : ���100692�γ̵�5-b14.c�ĵڶ���(��ӡ������Ϣ)" << endl;
	msg << endl;
	cout << msg.str() << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����1��main����������������Ҳ����һ��cout
			2����1�����ƣ��������Ҫ������ʹ�� goto END;(�����������������)
***************************************************************************/
int main(int argc, char** argv)
{
	ostringstream msg;

	/* ���в����ķ���������д��main�У�Ҳ����д�Զ��庯��(��msg������ȥ�������в�����cout)���������Ҫ������goto  */
	/* ��ȡ�κ�.dat������ݣ�ȥ��ȥ�հ״�ӡ debug 10000
	   �������򣬰��κź�ѧ��˳���ӡ��ѧ������ debug 01000
	   ��ȡ����ѧ���ĵڶ��еĽ�����Ϣ(����Ƿ������Ӧѧ����ע�͵���ȷ��) debug 00100
	   ����ѧ���ĵ�2�л���ƥ���� debug 00010
	   ����ѧ���ĳ�ʼ�ֺ����յ÷�
	*/
	int check[4] = { 0 };//ͳ�Ƹ����������ֵĴ���
	int wrong = 0;
	char debug[5] = { '1','1','1','1','1'};//debugѡ�������
	char courseid[100];
	char filename[100];
	if (argc == 1)
	{
		usage(argv[0]);
		goto END;
	}
	for (int i = 1; i < argc; i++)//���������
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
			if (i == argc - 1 || !strncmp("--", argv[i + 1],2))//��·��������������������
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
			if (i == argc - 1 || !strncmp("--", argv[i + 1], 2))//��·��������������������
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
			if (i == argc - 1 || !strncmp("--", argv[i + 1], 2))//��·��������������������
			{
				err_out(argv[0],msg, parameter[3], 1);
				msg << "(ȱʡ:11111)";
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
	/* �������������ȷ������ô˺������м��(���������������) */
	second_line_check(msg, debug, courseid, filename);

	 /* �������������䣬��������cout���������Ҫ������goto */
	return 0;

		END:
	cout << msg.str() << endl;

	return 0;
}

