/* 2152041 王浩 信07 */
#include <iostream>
using namespace std;

int repeat(int hang, int lie, int sudoku[][9])
{
	bool _1 = 0, _2 = 0, _3 = 0, _4 = 0, _5 = 0, _6 = 0, _7 = 0, _8 = 0, _9 = 0;
	for (int i = hang - 3; i <= hang - 1; i++)
		for (int j = lie - 3; j <= lie - 1; j++)
			switch (sudoku[i][j])
			{
				case 1:
					_1 = 1;
					break;
				case 2:
					_2 = 1;
					break;
				case 3:
					_3 = 1;
					break;
				case 4:
					_4 = 1;
					break;
				case 5:
					_5 = 1;
					break;
				case 6:
					_6 = 1;
					break;
				case 7:
					_7 = 1;
					break;
				case 8:
					_8 = 1;
					break;
				case 9:
					_9 = 1;
					break;
				default:
					break;
			}
	return _1 && _2 && _3 && _4 && _5 && _6 && _7 && _8 && _9;
}

int main()
{
	int sudoku[9][9];
	cout << "请输入9*9的矩阵，值为1-9之间\n";
	for (int i = 0; i <= 8; i++)
		for (int j = 0; j <= 8; j++)
		{
			while (1)
			{
				cin >> sudoku[i][j];
				if (cin.fail() || sudoku[i][j] < 1 || sudoku[i][j]>9)
				{
					cout << "请重新输入第" << i + 1 << "行" << j + 1 << "列(行列均从1开始计数)的值\n";
					cin.clear();
					cin.ignore(65536, '\n');
					continue;
				}
				else
					break;
			}
		}
	bool _heng, _shu;
	bool _1 = 0, _2 = 0, _3 = 0, _4 = 0, _5 = 0, _6 = 0, _7 = 0, _8 = 0, _9 = 0;
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
			switch (sudoku[i][j])
			{
				case 1:
					_1 = 1;
					break;
				case 2:
					_2 = 1;
					break;
				case 3:
					_3 = 1;
					break;
				case 4:
					_4 = 1;
					break;
				case 5:
					_5 = 1;
					break;
				case 6:
					_6 = 1;
					break;
				case 7:
					_7 = 1;
					break;
				case 8:
					_8 = 1;
					break;
				case 9:
					_9 = 1;
					break;
				default:
					break;
			}
		_heng= _1 && _2 && _3 && _4 && _5 && _6 && _7 && _8 && _9;
		if (_heng == 0)
			break;
	}
	for (int j = 0; j <= 8; j++)
	{
		for (int i = 0; i <= 8; i++)
			switch (sudoku[i][j])
			{
				case 1:
					_1 = 1;
					break;
				case 2:
					_2 = 1;
					break;
				case 3:
					_3 = 1;
					break;
				case 4:
					_4 = 1;
					break;
				case 5:
					_5 = 1;
					break;
				case 6:
					_6 = 1;
					break;
				case 7:
					_7 = 1;
					break;
				case 8:
					_8 = 1;
					break;
				case 9:
					_9 = 1;
					break;
				default:
					break;
			}
		_shu = _1 && _2 && _3 && _4 && _5 && _6 && _7 && _8 && _9;
		if (_shu == 0)
			break;
	}

	if (repeat(3, 3, sudoku) && repeat(6, 3, sudoku) && repeat(9, 3, sudoku) && repeat(3, 6, sudoku) && repeat(3, 9, sudoku) && repeat(6, 6, sudoku) && repeat(6, 9, sudoku) && repeat(9, 6, sudoku) && repeat(9, 9, sudoku)&&_heng&&_shu)
		cout << "是数独的解";
	else
		cout << "不是数独的解";
	cout << endl;
	return 0;
}