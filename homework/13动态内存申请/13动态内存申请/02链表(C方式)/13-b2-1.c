/* 2152041 计科 王浩 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct student
{
	int no;
	char name[9];
	int score;
	struct student* next;
};

int insert(struct student* head, int no, char name[], int score)
{
	struct student* tmp = malloc(sizeof(struct student));
	if (tmp == NULL)
		return -1;
	tmp->no = no;
	for (int i=0;i < 8;i++)
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
	struct student* head = malloc(sizeof(struct student));
	if (head == NULL)
		return -1;
	head->next = NULL;
	struct student* p = head;
	int no, score;
	char name[9];
	FILE* infile;
	infile = fopen("list.txt", "r");
	if (infile == NULL)
	{
		printf("打开文件失败\n");
		return -1;
	}
	fscanf(infile, "%d %s %d", &no, &name, &score);
	struct student* tmp = malloc(sizeof(struct student));
	if (tmp == NULL)
		return -1;
	tmp->no = no;
	for (int i = 0; i < 8; i++)
		tmp->name[i] = name[i];
	tmp->score = score;
	head = tmp;
	tmp->next = NULL;
	while(1)
	{
		fscanf(infile, "%d %s %d",&no,&name,&score);
		if (no == 9999999)
			break;
		insert(head, no, name, score);
	}
	for (p = head; p != NULL; p = p->next)
	{
		printf("%d %s %d\n", p->no, p->name, p->score);
	}
	fclose(infile);
	//释放内存
	struct student* q;
	p = head;
	while (p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	return 0;
}