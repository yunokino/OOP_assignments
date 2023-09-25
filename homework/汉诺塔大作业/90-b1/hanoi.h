/* ��07 2152041 ���� */
#pragma once

/* ------------------------------------------------------------------------------------------------------

     ���ļ����ܣ�
	1��Ϊ�˱�֤ hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp ���໥���ʺ����ĺ�������
	2��һ�����ϵ�cpp���õ��ĺ궨�壨#define����ȫ��ֻ����const����������������
	3�����Բο� cmd_console_tools.h ��д���������Ķ�����ᣩ
   ------------------------------------------------------------------------------------------------------ */
/* �˵����� */
int menu();

/* ͨ����������������ʵ����Ӧ���ܵĺ��� */
void move(int n, char x, char y, int _1 = 0, int _2 = 0, int _3 = 0, int _4 = 0, int _8 = 0,int _9 = 0);

/* ����ʱ�йصĺ��� */
void sleep1(int speed);
void sleep2(int speed);

/* ���ӡ�����йصĺ��� */
void print_horizontal();
void print_vertical();

/* ��ͼ�λ���ʵ���йصĺ��� */
void print_column();
void print_disk(int num, char start_column);
void move_disk(int num, char start_column, char end_column);

/* Ψһ�ĵݹ麯����ͨ������move������ʵ�ֹ��� */
void hanoi(int n, char src, char tmp, char dst, int _1 = 0, int _2 = 0, int _3 = 0, int _4 = 0, int _8 = 0, int _9 = 0);

/* ��ʵ����Ϸ�汾�йصĺ��� */
void play_game(int num,char goal_column);

/* ����ʵ�������������ĺ��� */
void in_put(int num, int* x, char* f, char* g, char* h, int* speed);
/* ͨ����Ӧ����������ʵ�ֶ�Ӧ���ܵĺ��� */
void act_honoi(int num);

