/* 2152041 王浩 信07 */
/* 2152359 陈芝杨 2151412 杨智皓 2153048 周振堂 2152586 赵新浩 2150258 金屹峰 */
#include <iostream>
#include<iomanip>
#include<cstring>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
    cerr << "文件名以下形式均可以:" << endl;
    cerr << "    a.txt : 不带路径形式" << endl;
    cerr << "    ..\\data\\b.dat          : 相对路径形式" << endl;
    cerr << "    C : \\Windows\\System32\\c.dat : 绝对相对路径形式" << endl;
    cerr << "请输入要转换的hex格式文件名 : ";

    char input_name[100];
    char output_name[100];
    char* in_name = input_name;
    char* out_name = output_name;
    unsigned char content[1000000];
    int offset_num = 0;
    ifstream infile;
    ofstream outfile;

    cin >> input_name;
    cerr << "请输入转换后的文件名        : ";
    cin >> output_name;
    infile.open((const char*)(in_name), ios::in | ios::binary);
    outfile.open((const char*)(out_name), ios::out | ios::binary);
    if (!infile.is_open())
    {
        infile.close();
        outfile.close();
        cout << "输入文件" << input_name << "打开失败" << endl;
        return -1;
    }
    int i = 0, j = 0, line = 0;
    while (!infile.eof())
    {
        content[i] = infile.get();
        i++;
        j++;
    }
    i = 0;
    j = 0;
    bool is_end = 0;
    while (1)
    {
        j = i;
        offset_num = 0;
        for (; content[i] == '0'; i++)
            ;
        if(line==0)
            i--;
        offset_num = (content[i] >= '0' && content[i] <= '9'? content[i]-'0' : content[i] - 'a'+10);
        while (i < line * 82 + 7)
        {
            i++;
            offset_num = offset_num * 16+ (content[i] >= '0' && content[i] <= '9' ? content[i] - '0' : content[i] - 'a' + 10);
        }
        if (offset_num != line * 16)
        {
            cout << "最左侧的偏移量0x" << setw(8) << hex << setfill('0') << offset_num << "不是期望值0x" << setw(8) << hex << setfill('0') << (line * 16) << endl;
            break;
        }
        i = j;
        i += 10;
        for (; i <= 31 + line * 82; i += 3)
        {
            if (content[i] >= '0' && content[i] <= '9')
                outfile << (char)((content[i] - '0') * 16 + (content[i + 1] >= '0' && content[i + 1] <= '9' ? (content[i + 1] - '0') : (content[i + 1] - 'a' + 10)));
            else if (content[i] >= 'a' && content[i] <= 'f')
                outfile << (char)(((content[i] - 'a' + 10)) * 16 + (content[i + 1] >= '0' && content[i + 1] <= '9' ? (content[i + 1] - '0') : (content[i + 1] - 'a' + 10)));
            else
            {
                is_end = 1;
                break;
            }
        }
        if (is_end)
            break;
        i += 2;
        for (; i <= 57 + line * 82; i += 3)
        {
            if (content[i] >= '0' && content[i] <= '9')
                outfile << (char)((content[i] - '0') * 16 + (content[i + 1] >= '0' && content[i + 1] <= '9' ? (content[i + 1] - '0') : (content[i + 1] - 'a' + 10)));
            else if (content[i] >= 'a' && content[i] <= 'f')
                outfile << (char)(((content[i] - 'a' + 10)) * 16 + (content[i + 1] >= '0' && content[i + 1] <= '9' ? (content[i + 1] - '0') : (content[i + 1] - 'a' + 10)));
            else
            {
                is_end = 1;
                break;
            }
        }
        if (is_end)
            break;
        i += 22;
        line++;
    }
    infile.close();
    outfile.close();
    return 0;
}
