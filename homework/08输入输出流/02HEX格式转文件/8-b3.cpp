/* 2152041 ���� ��07 */
/* 2152359 ��֥�� 2151412 ����� 2153048 ������ 2152586 ���º� 2150258 ���ٷ� */
#include <iostream>
#include<iomanip>
#include<cstring>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
    cerr << "�ļ���������ʽ������:" << endl;
    cerr << "    a.txt : ����·����ʽ" << endl;
    cerr << "    ..\\data\\b.dat          : ���·����ʽ" << endl;
    cerr << "    C : \\Windows\\System32\\c.dat : �������·����ʽ" << endl;
    cerr << "������Ҫת����hex��ʽ�ļ��� : ";

    char input_name[100];
    char output_name[100];
    char* in_name = input_name;
    char* out_name = output_name;
    unsigned char content[1000000];
    int offset_num = 0;
    ifstream infile;
    ofstream outfile;

    cin >> input_name;
    cerr << "������ת������ļ���        : ";
    cin >> output_name;
    infile.open((const char*)(in_name), ios::in | ios::binary);
    outfile.open((const char*)(out_name), ios::out | ios::binary);
    if (!infile.is_open())
    {
        infile.close();
        outfile.close();
        cout << "�����ļ�" << input_name << "��ʧ��" << endl;
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
            cout << "������ƫ����0x" << setw(8) << hex << setfill('0') << offset_num << "��������ֵ0x" << setw(8) << hex << setfill('0') << (line * 16) << endl;
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
