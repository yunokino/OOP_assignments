#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include "lib_mto10_net_tools.h"
using namespace std;

#define		MAX_ROW_NUM		8
#define		MAX_COL_NUM		10
void best_solve(int matrix_num[][10], int output_line, int output_row, int* best_x, int* best_y);
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ���������������ο������������������Ĳ�����Ҳ�����Լ�ȫ���Ʒ���д
***************************************************************************/
int game_progress(mto10_net_tools &client)
{
	char svrpack[RECVBUF_LEN];	//��Ŵ�Server���յ�������
	char row;
	int col;

	while (1) {
		/* -------------------
			Client=>Server
		   ------------------- */
		/* ���ݷ���˷����ĵ�ͼ������һ�������꣨ĿǰΪ�ֹ�������ʽ����Ҫ��Ϊ�Զ�����ѽ����꣩
		   ��ʾ�����Խ�client.get_map()�ķ���ֵ���Ƶ��ַ������У��ٻ�ԭΪ���Լ��Ķ�ά��������
		*/
		client.print_map(); //��������Ϊʾ�⣬ͼ�ν����в��ܵ��ã�Ҫ�Լ�дת������

		/* ��Ϸ�ѽ������ٶ���*/
		if (client.is_gameover())
			break;

		cout << "��������(A-J)��(0-9)���� : ";
		int matrix_num[8][10] = { 0 };
		char map_num[81];
		int best_x = 0, best_y = 0;
		int output_line = client.get_col(), output_row = client.get_row();
		strcpy(map_num, client.get_map());
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
		cout << endl<<row << " " << col;

		client.send_coordinate(row, col);

		/* -------------------
			Server=>Client
		   ------------------- */
	   /* �ȴ�Server�˵�gameprogress */
		if (client.get_gameprogress_string(svrpack) < 0) {
			return -1;
		}

		/* ��ӡ�� svrpack �����ݣ����д�������Server�˼�������
		   ���� Content �����ݣ��������£�
			"InvalidCoordinate" : �Ƿ�����
				GameID		��������ϷID
				Step		��Ŀǰ����
				Score		��Ŀǰ����
				MaxValue	��Ŀǰ�ϳɵ����ֵ
			"MergeFailed" : ѡ���������Χ�޿ɺϳ���
				GameID		��������ϷID
				Step		��Ŀǰ����
				Score		��Ŀǰ����
				MaxValue	��Ŀǰ�ϳɵ����ֵ
			"MergeSucceeded" : ���κϳɳɹ�
				GameID		��������ϷID
				Step		��Ŀǰ����
				Score		��Ŀǰ����
				MaxValue	��Ŀǰ�ϳɵ����ֵ
				OldMap		������ѡ�������ĵ�ͼ
				NewMap		������ѡ��������ٴ����ĵ�ͼ
			"GameOver" : ��ͼ�����������Ϸ����
				GameID			��������ϷID
				FinalStep		�����ղ���
				FinalScore		�����շ���
				FinalMaxValue	�����պϳɵ����ֵ
			"GameFinished" : �Ѻϳɵ��������ޣ�16������Ϸ���
				GameID			��������ϷID
				FinalStep		�����ղ���
				FinalScore		�����շ���
				FinalMaxValue	�����պϳɵ����ֵ */

		/* ��ӡ�յ���ԭʼ�ַ��� */
		cout << "ServerӦ�� : " << endl << svrpack << endl;
	}//end of while(1)

	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	const char *my_no = "2152041";		//����ѧ��
	const char *my_pwd = "10yue26ri.";	//��������

	int wanted_row, wanted_col, wanted_id, wanted_delay;

#if 1 //�������룬�˴���Ϊ #if 0 ���ʾ�������� #else �е����
	wanted_row = 6;			//�˴������޸�Ϊ�����������ʽ
	wanted_col = 6;			//�˴������޸�Ϊ�����������ʽ
	wanted_id = -1;		//idΪ�����������Ϸ��ţ������-1����ʾ���������������[0..2^31-1]���ʾ��̶���ţ���Ź̶�����ÿ�θ����ĳ�ʼ���󼰺���������ͬ��������ԣ�
	wanted_delay = 60 * 1000;	//delayΪ�����ÿ��Ӧ����ʱ�ӣ���λms
#else
	wanted_row = -1;
	wanted_col = -1;
	wanted_id = -1;
	wanted_delay = -1;
#endif
	mto10_net_tools client;

	/* ��client������е�debug���أ�����ʱ�ɴ򿪣���ͼ�ν���ʱ��رգ� */
	client.set_debug_switch(true);

	/* ���ӷ����� */
	if (client.connect() < 0) {
		/* ����ʧ����Ϣ����û��debug_switch����ӡ */
		cout << "���ӷ�����ʧ��!" << endl;
		return -1;
		}

	/* ��Server�˷�����֤��Ϣ������ */
	if (client.send_parameter(my_no, '*', my_pwd, wanted_row, wanted_col, wanted_id, wanted_delay) < 0) {
		cout << "������֤��������Ϣʧ��!" << endl;
		return -1;
		}

	/* �ȴ�Server���·���������Ϸ��ʼ��*/
	if (client.wait_for_game_start() < 0) {
		cout << "�ȴ�GameStartʧ��!" << endl;
		return -1;
		}

	/* ��ӡ�ӷ������յ��Ĳ�����������Ϸ�Դ˲���Ϊ׼����������6��6�У�����8��10�У��򱾴���Ϸ��8��10��Ϊ׼��
	   �����ӡ����Ϣ��ͼ�λ������������ȥ�� */
	cout << "������������Ϣ : " << endl;
	cout << "  ���� : " << client.get_row() << endl;
	cout << "  ���� : " << client.get_col() << endl;
	cout << "  ID�� : " << client.get_gameid() << endl;
	cout << "  ��ʱ : " << client.get_delay()/1000.0 << "(��)" << endl;
	cout << "  ��ͼ : " << client.get_map() << endl;
	/* ��ͼ���е�ֵΪ1-9��A-F���ֱ��ʾ1-15��ֵ��
		   ���磺
		     ������������=3
			 ������������=4
			 ���������ص�ͼ=123A85CF2123
		   ���ʾ��ǰ��ͼΪ(����������ʾ��)
		     1 2 3  10
			 8 5 12 15
			 2 1 2  3
			��Ϸ����������Ϊ���ϳɵ�16�����κοɺϳ�Ԫ�� */

	/* ������Ϸ��������
	   1���յ�Server��GameOver�򷵻�0����Ϸ����
	   2���������������-1��������Ϣ����ȷ�ȴ��󣩣��������ٴ��ظ�	*/

	if (game_progress(client) < 0) {
		client.close();
		return -1;
		}

	client.close();
	cout << "��Ϸ����" << endl;

	return 0;
}


void best_solve(int matrix_num[][10], int output_line, int output_row, int* best_x, int* best_y)
{
	int grade = 0, old_grade = grade;
	int mark_same[8][10];
	for (int p = 0; p <= output_line - 1; p++)
		for (int q = 0; q <= output_row - 1; q++)
		{
			int store[80][2] = { 0 };//����������
			int next[4][2] = { {0,1},{1,0},{0, -1},{ -1,0} };//����ƶ�����
			mark_same[p][1] = 1;
			store[0][0] = p;
			store[0][1] = q;
			int start = 0, end = 1;
			while (start < end)
			{
				for (int k = 0; k <= 3; k++)
				{
					int i = store[start][0], j = store[start][1];//��¼���
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
			if (end == 1)
			{
				for (int i = 0; i <= 7; i++)
					for (int j = 0; j <= 9; j++)
						mark_same[i][j] = 0;
				continue;
			}
			else
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
				continue;
			}
			for (int i = 0; i <= output_line - 1; i++)
				for (int j = 0; j <= output_row - 1; j++)
					mark_same[i][j] = 0;
		}
}
