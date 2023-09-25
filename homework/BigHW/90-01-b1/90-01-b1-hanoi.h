/* 信07 2152041 王浩 */
#pragma once

/* ------------------------------------------------------------------------------------------------------

     本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ------------------------------------------------------------------------------------------------------ */
/* 菜单函数 */
int menu();

/* 通过调用其他函数来实现相应功能的函数 */
void move(int n, char x, char y, int _1 = 0, int _2 = 0, int _3 = 0, int _4 = 0, int _8 = 0,int _9 = 0);

/* 与延时有关的函数 */
void sleep1(int speed);
void sleep2(int speed);

/* 与打印数组有关的函数 */
void print_horizontal();
void print_vertical();

/* 与图形化的实现有关的函数 */
void print_column();
void print_disk(int num, char start_column);
void move_disk(int num, char start_column, char end_column);

/* 唯一的递归函数，通过调用move函数来实现功能 */
void hanoi(int n, char src, char tmp, char dst, int _1 = 0, int _2 = 0, int _3 = 0, int _4 = 0, int _8 = 0, int _9 = 0);

/* 与实现游戏版本有关的函数 */
void play_game(int num,char goal_column);

/* 用来实现输入各项参数的函数 */
void in_put(int num, int* x, char* f, char* g, char* h, int* speed);
/* 通过相应参数来决定实现对应功能的函数 */
void act_honoi(int num);

