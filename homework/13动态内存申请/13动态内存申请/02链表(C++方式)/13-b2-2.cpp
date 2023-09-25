/* 2152041 计科 王浩 */
#include<iostream>
#include<fstream>
using namespace std;

struct student
{
	int no;
	char name[9];
	int score;
	struct student* next;
};

int insert(struct student* head, int no, char name[], int score)
{
	struct student* tmp = new(nothrow) struct student;
	if (tmp == NULL)
		return -1;
	tmp->no = no;
	for (int i = 0; i < 8; i++)
		tmp->name[i] = name[i];
	tmp->score = score;
	struct student* p = head;
	while (p->next != NULL)
		p = p->next;
	p->next = tmp;
	tmp->next = NULL;
	return 0;
}


int main()
{
	struct student* head = new(nothrow) struct student;
	if (head == NULL)
		return -1;
	head->next = NULL;
	struct student* p = head;
	int no, score;
	char name[9];
	ifstream fin;
	fin.open("list.txt", ios::in);
	if (!fin.is_open())
	{
		printf("打开文件失败\n");
		return -1;
	}
	fin >> no >> name >> score;
	struct student* tmp = new(nothrow) struct student;
	if (tmp == NULL)
		return -1;
	tmp->no = no;
	for (int i = 0; i < 8; i++)
		tmp->name[i] = name[i];
	tmp->score = score;
	head = tmp;
	tmp->next = NULL;
	while (1)
	{
		fin >> no >> name >> score;
		if (no == 9999999)
			break;
		insert(head, no, name, score);
	}
	for (p = head; p != NULL; p = p->next)
	{
		cout << p->no << " " << p->name << " " << p->score << endl;
	}
	fin.close();
	//释放内存
	struct student* q;
	p = head;
	while (p != NULL)
	{
		q = p->next;
		delete p;
		p = q;
	}
	return 0;
}