/* 2152041 王浩 信07 */
#include <iostream>
#include<iomanip>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
    cerr << "文件名以下形式均可以:" << endl;
    cerr << "    a.txt : 不带路径形式" << endl;
    cerr << "    ..\\data\\b.dat          : 相对路径形式" << endl;
    cerr << "    C : \\Windows\\System32\\c.dat : 绝对相对路径形式" << endl;
    cerr << "请输入文件名 : ";
    unsigned char content[1000000];
    char input_name[100];
    char* name = input_name;
    ifstream infile;

    cin >> input_name;
    infile.open((const char*)(name), ios::in | ios::binary);
    if (!infile.is_open())
    {
        infile.close();
        cout << "输入文件" << input_name << "打开失败" << endl;
        return -1;
    }
    int i = 0;
    while (!infile.eof())
    {
        content[i] = infile.get();
        i++;
    }
    infile.close();
    i--;
    int k = i;
    content[i] = EOF;
    i = 0;
    while (k != 0)
    {
        if ((i + 1) % 16 == 1)
            cout << setw(8) << hex << setfill('0') << i << "  ";
        cout << hex << setw(2) << setfill('0') << (int)(content[i]) << " ";
        if (((i + 1) % 8 == 0) && ((i + 1) % 16 != 0) && (k != 1))
            cout << "- ";
        else if (((i + 1) % 16 == 0) || k == 1)
        {
            if (k == 1)
            {
                int j = i;
                for (; (j + 1) % 16 != 0; j++)
                {
                    if ((j + 1) % 8 == 0)
                        cout << "     ";
                    else
                        cout << "   ";
                }
            }
            cout << "    ";
            int j = i - 15;
            for (; (j + 1) % 16 != 1; j++);
            for (; j <= i; j++)
            {
                if (content[j] >= '!' && content[j] <= '~')
                    cout << content[j];
                else
                    cout << ".";
            }
            cout << endl;
        }
        i++;
        k--;
    }

    return 0;
}
