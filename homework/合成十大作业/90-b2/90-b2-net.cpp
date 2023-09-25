/* 2152041 王浩 信07 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include"90-b2.h"
#include"cmd_console_tools.h"
#include "lib_mto10_net_tools.h"
#include<windows.h>
using namespace std;

#define		MAX_ROW_NUM		8
#define		MAX_COL_NUM		10
void best_solve(int matrix_num[][10], int output_line, int output_row, int* best_x, int* best_y);
void print_move(int matrix_num[][10], int line, int row);
void print_auto_square(int matrix_num[][10], int line, int row, int x, int y);
void except_auto_zero(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row, int x, int y);
void fall_auto_zero(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row, int y);


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：本函数仅供参考，允许增减本函数的参数，也可以自己全部推翻重写
***************************************************************************/
int game_progress(mto10_net_tools& client, int _b)
{
	char svrpack[RECVBUF_LEN];	//存放从Server端收到的数据
	char row;
	int col;

	while (1) {
		/* -------------------
			Client=>Server
		   ------------------- */
		   /* 根据服务端发来的地图，返回一个解坐标（目前为手工输入形式，需要改为自动求最佳解坐标）
			  提示：可以将client.get_map()的返回值复制到字符数组中，再还原为你自己的二维数组后求解
		   */
		if(!_b)
			client.print_map(); //本函数仅为示意，图形界面中不能调用，要自己写转换函数
		/* 游戏已结束则不再读键*/
		if (client.is_gameover())
		{
			break;
		}
		int matrix_num[8][10] = { 0 };
		int mark_same[8][10] = { 0 };
		char map_num[81];
		int best_x = 0, best_y = 0;
		int output_line = client.get_row(), output_row = client.get_col();
		strcpy(map_num, client.get_map());
		cout << "请输入行(A-J)列(0-9)坐标 : ";
		int k = 0;
		for (int i = 0; i <= output_line - 1; i++)
			for (int j = 0; j <= output_row - 1; j++)
			{
				matrix_num[i][j] = ((map_num[k] >= '0' && map_num[k] <= '9') ? map_num[k] - '0' : map_num[k] - 'A' + 10);
				k++;
			}
		best_solve(matrix_num, output_line, output_row, &best_x, &best_y);
		row = char(best_x + 'A');
		col = best_y;
		if (_b)
		{
			cout << row << " " << col << endl;
			int x, y,old_x,old_y;
			int next[4][2] = { {0,1},{1,0},{0, -1},{ -1,0} };//标记移动方向
			cct_getxy(x, y);
			old_x = x;
			old_y = y;
			x += 4;
			y += 2;
			print_move(matrix_num, output_line, output_row);
			print_auto_square(matrix_num, output_line, output_row, x, y);
			Sleep(700);
			for (int k = 0; k <= 3; k++)
			{
				int i = best_x, j = best_y;//记录起点
				mark_same[i][j] = 1;
				while (1)
				{
					int old_i = i, old_j = j;
					i += next[k][0];
					j += next[k][1];
					if (i<0 || j<0 || i>output_line - 1 || j>output_row - 1)
						break;
					else
					{
						if (matrix_num[i][j] == matrix_num[old_i][old_j])
							mark_same[i][j] = 1;
						else
							break;
					}
				}
			}
			cct_setcursor(CURSOR_INVISIBLE);
			except_auto_zero(matrix_num, mark_same, row - 'A', col, output_line, output_row,old_x,old_y);
			fall_auto_zero(matrix_num, mark_same, row - 'A', col, output_line, output_row, old_y);
			cout << "移动完成" << endl;;
			cct_setcursor(CURSOR_VISIBLE_NORMAL);
			cct_setcolor();
		}
		client.send_coordinate(row, col);

		/* -------------------
			Server=>Client
		   ------------------- */
		   /* 等待Server端的gameprogress */
		if (client.get_gameprogress_string(svrpack) < 0) {
			return -1;
		}

		/* 打印出 svrpack 的内容，自行处理，并向Server端继续反馈
		   根据 Content 的内容，解释如下：
			"InvalidCoordinate" : 非法坐标
				GameID		：本次游戏ID
				Step		：目前步数
				Score		：目前分数
				MaxValue	：目前合成的最大值
			"MergeFailed" : 选择的坐标周围无可合成项
				GameID		：本次游戏ID
				Step		：目前步数
				Score		：目前分数
				MaxValue	：目前合成的最大值
			"MergeSucceeded" : 本次合成成功
				GameID		：本次游戏ID
				Step		：目前步数
				Score		：目前分数
				MaxValue	：目前合成的最大值
				OldMap		：消除选择坐标后的地图
				NewMap		：消除选择坐标后再次填充的地图
			"GameOver" : 地图上无消除项，游戏结束
				GameID			：本次游戏ID
				FinalStep		：最终步数
				FinalScore		：最终分数
				FinalMaxValue	：最终合成的最大值
			"GameFinished" : 已合成到设置上限（16），游戏完成
				GameID			：本次游戏ID
				FinalStep		：最终步数
				FinalScore		：最终分数
				FinalMaxValue	：最终合成的最大值 */

				/* 打印收到的原始字符串 */
		cout << "Server应答 : " << endl << svrpack << endl;
	}//end of while(1)
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int network(int _b)
{
	const char* my_no = "2152041";		//本人学号
	const char* my_pwd = "10yue26ri.";	//本人密码

	int wanted_row, wanted_col, wanted_id, wanted_delay;

#if 1 //条件编译，此处改为 #if 0 则表示启用下面 #else 中的语句
	wanted_row = 5;			//此处按需修改为键盘输入等形式
	wanted_col = 5;			//此处按需修改为键盘输入等形式
	wanted_id = -1;		//id为本次请求的游戏序号，如果置-1，表示服务器随机产生，[0..2^31-1]则表示想固定序号（序号固定，则每次给出的初始矩阵及后续填充均相同，方便调试）
	wanted_delay = 60 * 1000;	//delay为请求的每步应答的最长时延，单位ms
#else
	wanted_row = -1;
	wanted_col = -1;
	wanted_id = -1;
	wanted_delay = -1;
#endif
	mto10_net_tools client;

	/* 打开client类对象中的debug开关（调试时可打开，到图形界面时需关闭） */
	if(!_b)
		client.set_debug_switch(true);
	else
		client.set_debug_switch(false);

	/* 连接服务器 */
	if (client.connect() < 0) {
		/* 连接失败信息，有没有debug_switch都打印 */
		cout << "连接服务器失败!" << endl;
		return -1;
	}

	/* 向Server端发送认证信息及参数 */
	if (client.send_parameter(my_no, '*', my_pwd, wanted_row, wanted_col, wanted_id, wanted_delay) < 0) {
		cout << "发送认证及参数信息失败!" << endl;
		return -1;
	}

	/* 等待Server端下发参数（游戏开始）*/
	if (client.wait_for_game_start() < 0) {
		cout << "等待GameStart失败!" << endl;
		return -1;
	}

	/* 打印从服务器收到的参数，本次游戏以此参数为准（例：发送6行6列，返回8行10列，则本次游戏以8行10列为准）
	   下面打印的信息，图形化界面可以自行去除 */
	cout << "服务器返回信息 : " << endl;
	cout << "  行数 : " << client.get_row() << endl;
	cout << "  列数 : " << client.get_col() << endl;
	cout << "  ID号 : " << client.get_gameid() << endl;
	cout << "  超时 : " << client.get_delay() / 1000.0 << "(秒)" << endl;
	cout << "  地图 : " << client.get_map() << endl;
	/* 地图串中的值为1-9，A-F，分别表示1-15的值，
		   例如：
			 服务器返回行=3
			 服务器返回列=4
			 服务器返回地图=123A85CF2123
		   则表示当前地图为(本例仅仅是示例)
			 1 2 3  10
			 8 5 12 15
			 2 1 2  3
			游戏结束的条件为：合成到16或无任何可合成元素 */

			/* 进入游戏交互环节
			   1、收到Server的GameOver则返回0，游戏结束
			   2、其它错误均返回-1（报文信息不正确等错误），重连，再次重复	*/

	if (game_progress(client, _b) < 0) {
		client.close();
		return -1;
	}

	client.close();
	cout << "游戏结束" << endl;

	return 0;
}

void best_solve(int matrix_num[][10], int output_line, int output_row, int* best_x, int* best_y)
{
	int grade = 0, old_grade = grade;
	int mark_same[8][10];
	for (int p = 0; p <= output_line - 1; p++)
		for (int q = 0; q <= output_row - 1; q++)
		{
			int store[80][2] = { 0 };//储存标记坐标
			int next[4][2] = { {0,1},{1,0},{0, -1},{ -1,0} };//标记移动方向
			mark_same[p][1] = 1;
			store[0][0] = p;
			store[0][1] = q;
			int start = 0, end = 1;
			while (start < end)
			{
				for (int k = 0; k <= 3; k++)
				{
					int i = store[start][0], j = store[start][1];//记录起点
					while (1)
					{
						int old_i = i, old_j = j;
						i += next[k][0];
						j += next[k][1];
						if (i<0 || j<0 || i>output_line - 1 || j>output_row - 1)
							break;
						else
						{
							if (matrix_num[i][j] == matrix_num[old_i][old_j])
							{
								if (!mark_same[i][j])
								{
									store[end][0] = i;
									store[end][1] = j;
									end++;
								}
								mark_same[i][j] = 1;
							}
							else
								break;
						}
					}
				}
				start++;
			}
			if (end != 1)
			{
				int k = 0;
				for (int i = 0; i <= 7; i++)
					for (int j = 0; j <= 9; j++)
						if (mark_same[i][j] == 1)
							k++;
				grade = k * matrix_num[p][q] * 3;
				if (grade > old_grade)
				{
					old_grade = grade;
					(*best_x) = p;
					(*best_y) = q;
				}
			}
			for (int i = 0; i <= output_line - 1; i++)
				for (int j = 0; j <= output_row - 1; j++)
					mark_same[i][j] = 0;
			start = 0;
			end = 1;
		}
}

void print_auto_square(int matrix_num[][10], int line, int row, int x, int y)
{
	int old_x = x, old_y = y;
	int i = 0, j = 0;
	for (int m = 0; m <= line - 1; m++)
	{
		x = old_x;
		y = old_y;
		for (int n = 0; n <= row - 1; n++)
		{
			cct_gotoxy(x, y);
			cct_setcolor(matrix_num[i][j], 0);
			cout << "┏━┓";
			cct_gotoxy(x, y + 1);
			cout << "┃" << matrix_num[i][j] << " ┃";
			cct_gotoxy(x, y + 2);
			cout << "┗━┛";
			cct_setcolor();
			y = old_y;
			x += 8;
			j++;
		}
		old_y += 4;
		i++;
		j = 0;
	}
	cout << endl;
}

void fall_auto_zero(int matrix_num[][10], int mark_same[][10], int line, int row, int output_line, int output_row,int y)
{
	int count[8][10] = { 0 };
	for (int j = 0; j <= output_row - 1; j++)
		for (int i = 0; i <= output_line - 1; i++)
		{
			if (matrix_num[i][j] != 0)
			{
				for (int m = i; m <= output_line - 1; m++)
				{
					if (matrix_num[m][j] == 0)
						count[i][j]++;
				}
			}
		}
	for (int j = 0; j <= output_row - 1; j++)
	{
		for (int i = output_line - 2; i >= 0; i--)
		{
			int y_location = 2 + i * 4 + y;
			if (count[i][j] != 0)
			{
				for (; y_location <= 1 + y + (i + count[i][j]) * 4; y_location++)
				{
					cct_gotoxy(4 + j * 8, y_location);
					cct_setcolor(15, 15);
					cout << "      ";
					cct_gotoxy(4 + j * 8, y_location + 1);
					cout << "      ";
					cct_gotoxy(4 + j * 8, y_location + 2);
					cout << "      ";
					cct_setcolor();
					cct_setcolor(matrix_num[i][j], 0);
					cct_gotoxy(4 + j * 8, y_location + 1);
					cout << "┏━┓";
					cct_gotoxy(4 + j * 8, y_location + 2);
					cout << "┃" << matrix_num[i][j] << " ┃";
					cct_gotoxy(4 + j * 8, y_location + 3);
					cout << "┗━┛";
					cct_setcolor();
					Sleep(5);
					if ((y_location - y - 2) % 4 == 0)
					{
						cct_setcolor(15, 0);
						cct_gotoxy(4 + j * 8, y_location - 1);
						cout << "━━━";
						cct_setcolor();
					}
				}
			}
			if ((y_location - y - 2) % 4 == 0)
			{
				cct_setcolor(15, 0);
				cct_gotoxy(4 + j * 8, y_location - 1);
				cout << "━━━";
				cct_setcolor();
			}
		}
	}
	cct_gotoxy(0, y + 2+output_line * 4);
}

void except_auto_zero(int matrix_num[][10], int mark_same[][10],int line, int row, int output_line, int output_row,int x,int y)
{

	for (int i = 0; i <= output_line - 1; i++)
		for (int j = 0; j <= output_row - 1; j++)
		{
			if (mark_same[i][j] == 1 && (i != line || j != row))
			{
				cct_setcolor(15, 15);
				cct_gotoxy(4 + x + j * 8, 2 + y + i * 4);
				cout << "      ";
				cct_gotoxy(4 + x + j * 8, 3 + y + i * 4);
				cout << "      ";
				cct_gotoxy(4 + x + j * 8, 4 + y + i * 4);
				cout << "      ";
				cct_setcolor();
				matrix_num[i][j] = 0;
			}
			if (i == line && j == row)
			{
				matrix_num[i][j]++;
				cct_setcolor(matrix_num[i][j], 0);
				cct_gotoxy(4 + x + j * 8, 2 + y + i * 4);
				cout << "┏━┓";
				cct_gotoxy(4 + x + j * 8, 3 + y + i * 4);
				cout << "┃" << matrix_num[i][j]<<setw(3)<< "┃";
				cct_gotoxy(4 + x + j * 8, 4 + y + i * 4);
				cout << "┗━┛";
				cct_setcolor();
			}
		}
}

void print_move(int matrix_num[][10], int line, int row)
{
	int m = 0;
	int x_location, y_location;
	cout << "      ";
	for (int i = 0; i <= row - 1; i++)
		cout << i << "       ";
	cout << " " << endl << "  ";
	cct_setcolor(15, 0);
	cout << "┏";
	for (int j = 1; j <= row * 4 - 1; j++)
	{
		if (j == row * 4 - 1)
			cout << "━┓";
		else if (j % 4 == 0)
			cout << "┳";
		else
			cout << "━";
	}
	cct_setcolor();
	cout << endl;
	cct_getxy(x_location, y_location);
	x_location += 4;
	for (int i = 1; i <= line * 4 - 1; i++)
	{
		if (i % 4 == 1 || i % 4 == 3)
		{
			cout << "  ";
			cct_setcolor(15, 0);
			cout << "┃";
			for (int j = 1; j <= row; j++)
				cout << "      ┃";
			cct_setcolor();
			cout << endl;
		}
		else if (i % 4 == 2)
		{
			cout << char(m + 'A') << " ";
			m++;
			cct_setcolor(15, 0);
			cout << "┃";
			for (int j = 1; j <= row; j++)
				cout << "      ┃";
			cct_setcolor();
			cout << endl;
		}
		else if (i % 4 == 0)
		{
			cout << "  ";
			cct_setcolor(15, 0);
			cout << "┣";
			for (int j = 1; j <= row * 4 - 1; j++)
			{
				if (j == row * 4 - 1)
					cout << "━┫";
				else if (j % 4 == 0)
					cout << "╋";
				else
					cout << "━";
			}
			cct_setcolor();
			cout << endl;
		}
		else;
	}
	cout << "  ";
	cct_setcolor(15, 0);
	cout << "┗";
	for (int j = 1; j <= row * 4 - 1; j++)
	{
		if (j == row * 4 - 1)
			cout << "━┛";
		else if (j % 4 == 0)
			cout << "┻";
		else
			cout << "━";
	}
	cct_setcolor();
	cout << endl;
}

