/* 2152041 计科 王浩 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
//根据需要可加入其它头文件
using namespace std;

//此处为示例，允许修改结构体名称，允许修改结构体中的成员内容，要求sizeof必须是64
struct game {
    char name[16] = {0};
    unsigned short life_value;
    unsigned short power_value;
    unsigned short health;
    unsigned short deft;
    unsigned int wealth;
    unsigned int fame;
    unsigned int charm;
    unsigned char move_speed;
    unsigned char attack_speed;
    unsigned char attack_range;
    unsigned char occupy;
    unsigned short attack_power;
    unsigned short defend_power;
    unsigned char agile;
    unsigned char wisdom;
    unsigned char experience;
    unsigned char level;
    unsigned short magic_num;
    unsigned char consume_magic_num;
    unsigned char magic_attack_power;
    unsigned char hit_rate;
    unsigned char magic_defend_power;
    unsigned char critical_strike_rate;//暴击率
    unsigned char stamina;//耐力
    unsigned long long total_time;
};

/* 此处允许新增函数，数量不限
   1、所有新增的函数，均不允许定义新的 fstream / ifstream / ofstream 流对象，并进行打开/读/写/关闭等操作
   2、所有新增的函数，均不允许用C方式进行文件处理
   3、上述两个限制同样适用于main函数
*/
template <typename T>
void trans_hex(char* buffer, T num, const int location, const int byte_num)
{
    for (int i = 0; i < byte_num; i++)
    {
        buffer[location + i] = (num >> (8 * i)) & 0xff;
    }
}

int check_range(int num, int min, int max)
{
    if (num >= min && num <= max)
        return 0;
    else
        return 1;
    return 0;
}

void change_content(struct game &mygame,char *buffer)
{
    unsigned int tmp;
    for (int i = 0; i <= 15; i++)
        mygame.name[i] = buffer[i];
    
    tmp = (int)(unsigned char)buffer[17] * 16 * 16 + (int)(unsigned char)buffer[16];
    mygame.life_value = tmp;
    tmp = (int)(unsigned char)buffer[19] * 16 * 16 + (int)(unsigned char)buffer[18];
    mygame.power_value = tmp;
    tmp = (int)(unsigned char)buffer[21] * 16 * 16 + (int)(unsigned char)buffer[20];
    mygame.health = tmp;
    tmp = (int)(unsigned char)buffer[23] * 16 * 16 + (int)(unsigned char)buffer[22];
    mygame.deft = tmp;
    for (int i = 3; i >= 0; i--)
        tmp = tmp * 16 * 16 + (int)(unsigned char)buffer[24 + i];
    mygame.wealth = tmp;
    for (int i = 3; i >= 0; i--)
        tmp = tmp * 16 * 16 + (int)(unsigned char)buffer[28 + i];
    mygame.fame = tmp;
    for (int i = 3; i >= 0; i--)
        tmp = tmp * 16 * 16 + (int)(unsigned char)buffer[32 + i];
    mygame.charm = tmp;
    
    for (int i = 7; i >= 0; i--)
        mygame.total_time = mygame.total_time * 16 * 16 + (unsigned long long)(unsigned char)buffer[36 + i];

    tmp = buffer[44];
    mygame.move_speed = tmp;
    tmp = buffer[45];
    mygame.attack_speed = tmp;
    tmp = buffer[46];
    mygame.attack_range = tmp;
    tmp = (int)(unsigned char)buffer[49] * 16 * 16 + (int)(unsigned char)buffer[48];
    mygame.attack_power = tmp;
    tmp = ((int)(unsigned char)buffer[51]) * 16 * 16 + (int)(unsigned char)buffer[50];
    mygame.defend_power = tmp;
    mygame.agile = buffer[52];
    mygame.wisdom = buffer[53];
    mygame.experience = buffer[54];
    mygame.level = buffer[55];
    tmp = (int)(unsigned char)buffer[57] * 16 * 16 + (int)(unsigned char)buffer[56];
    mygame.magic_num = tmp;
    mygame.consume_magic_num = buffer[58];
    mygame.magic_attack_power = buffer[59];
    mygame.hit_rate = buffer[60];
    mygame.magic_defend_power = buffer[61];
    mygame.critical_strike_rate = buffer[62];
    mygame.stamina = buffer[63];
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：整个函数，只允许出现一次open、一次read（因为包含错误处理，允许多次close）
***************************************************************************/
int read(struct game &mygame)
{
    /* 本函数中只允许定义一个 ifstream流对象，不再允许定义任何形式的fstream/ifstream/ofstream流对象，也不允许使用C方式的文件处理 */
    ifstream gfile;

    /* 文件打开，具体要求为：
       1、要求以读方式打开，打开方式***自行指定
       2、除本次open外，本函数其它地方不允许再出现open  */
    gfile.open("game.dat", ios::in | ios::binary);

    /* 进行后续操作，包括错误处理、读文件、显示各游戏项的值、关闭文件等，允许调用函数
       其中：只允许用一次性读取64字节的方法将game.dat的内容读入***（缓冲区名称、结构体名称自行指定）
                 gfile.read(***, sizeof(demo));
    */
    if (!gfile)
    {
        cout << "文件打开失败" << endl;
        return -1;
    }
    char buffer[64];
    gfile.read(buffer, sizeof(game));
    change_content(mygame, buffer);
    cout << setw(18) << right << "玩家昵称" << "：" << mygame.name << endl;
    cout << setw(18) << right << "生命值" << "：" << mygame.life_value << endl;
    cout << setw(18) << right << "力量值" << "：" << mygame.power_value << endl;
    cout << setw(18) << right << "体质值" << "：" << mygame.health << endl;
    cout << setw(18) << right << "灵巧值" << "：" << mygame.deft << endl;
    cout << setw(18) << right << "金钱值" << "：" << mygame.wealth << endl;
    cout << setw(18) << right << "名声值" << "：" << mygame.fame << endl;
    cout << setw(18) << right << "魅力值" << "：" << mygame.charm << endl;
    cout << setw(18) << right << "游戏累计时间(us)值" << "：" << mygame.total_time << endl;
    cout << setw(18) << right << "移动速度值" << "：" << (int)mygame.move_speed << endl;
    cout << setw(18) << right << "攻击速度值" << "：" << (int)mygame.attack_speed << endl;
    cout << setw(18) << right << "攻击范围值" << "：" << (int)mygame.attack_range << endl;
    mygame.occupy = 0;
    cout << setw(18) << right << "攻击力值" << "：" << mygame.attack_power << endl;
    cout << setw(18) << right << "防御力值" << "：" << mygame.defend_power << endl;
    cout << setw(18) << right << "敏捷度值" << "：" << (int)mygame.agile << endl;
    cout << setw(18) << right << "智力值" << "：" << (int)mygame.wisdom << endl;
    cout << setw(18) << right << "经验值" << "：" << (int)mygame.experience << endl;
    cout << setw(18) << right << "等级值" << "：" << (int)mygame.level << endl;
    cout << setw(18) << right << "魔法值" << "：" << mygame.magic_num << endl;
    cout << setw(18) << right << "消耗魔法值" << "：" << (int)mygame.consume_magic_num << endl;
    cout << setw(18) << right << "魔法伤害力值" << "：" << (int)mygame.magic_attack_power << endl;
    cout << setw(18) << right << "命中率值" << "：" << (int)mygame.hit_rate << endl;
    cout << setw(18) << right << "魔法防御力值" << "：" << (int)mygame.magic_defend_power << endl;
    cout << setw(18) << right << "暴击率值" << "：" << (int)mygame.critical_strike_rate << endl;
    cout << setw(18) << right << "耐力值" << "：" << (int)mygame.stamina << endl;
    gfile.close();
    return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：整个函数，只允许出现一次open、一次read、一次write（因为包含错误处理，允许多次close）
***************************************************************************/
int modify(struct game &mygame)
{
    /* 本函数中只允许定义一个 fstream流对象，不再允许定义任何形式的fstream/ifstream/ofstream流对象，也不允许使用C方式的文件处理 */
    fstream gfile;
    /* 文件打开，具体要求为：
       1、要求以读写方式打开，打开方式***自行指定
       2、除本次open外，本函数其它地方不允许再出现open  */
    gfile.open("game.dat", ios::in|ios::out|ios::binary);

    /* 进行后续操作，包括错误处理、读文件、显示各游戏项的值、关闭文件等，允许调用函数
       其中：只允许用一次性读取64字节的方法将game.dat的内容读入***（缓冲区名称、结构体名称自行指定）
                 gfile.read(***, sizeof(demo));
             只允许用一次性写入64字节的方法将***的内容写入game.dat中（缓冲区名称、结构体名称自行指定）
                 gfile.write(***, sizeof(demo));
    */
    if (!gfile)
    {
        cout << "文件打开失败" << endl;
        return -1;
    }
    char buffer[64];
    gfile.read(buffer, sizeof(game));
    change_content(mygame, buffer);

    while (1)
    {
        cout << "--------------------------------------" << endl;
        cout << "  游戏存档文件修改工具" << endl;
        cout << "--------------------------------------" << endl;
        cout << "  a." << setw(12) << left << "玩家昵称    (" << mygame.name <<")"<< endl;
        cout << "  b." << setw(12) << left << "生命        (" << mygame.life_value <<")"<< endl;
        cout << "  c." << setw(12) << left << "力量        (" << mygame.power_value <<")"<< endl;
        cout << "  d." << setw(12) << left << "体质        (" << mygame.health <<")"<< endl;
        cout << "  e." << setw(12) << left << "灵巧        (" << mygame.deft <<")"<< endl;
        cout << "  f." << setw(12) << left << "金钱        (" << mygame.wealth <<")"<< endl;
        cout << "  g." << setw(12) << left << "名声        (" << mygame.fame <<")"<< endl;
        cout << "  h." << setw(12) << left << "魅力        (" << mygame.charm <<")"<< endl;
        cout << "  i." << setw(12) << left << "游戏累计时间(" << mygame.total_time <<")"<< endl;
        cout << "  j." << setw(12) << left << "移动速度    (" << (int)mygame.move_speed <<")"<< endl;
        cout << "  k." << setw(12) << left << "攻击速度    (" << (int)mygame.attack_speed <<")"<< endl;
        cout << "  l." << setw(12) << left << "攻击范围    (" << (int)mygame.attack_range <<")"<< endl;
        cout << "  m." << setw(12) << left << "攻击力      (" << mygame.attack_power <<")"<< endl;
        cout << "  n." << setw(12) << left << "防御力      (" << mygame.defend_power <<")"<< endl;
        cout << "  o." << setw(12) << left << "敏捷度      (" << (int)mygame.agile <<")"<< endl;
        cout << "  p." << setw(12) << left << "智力        (" << (int)mygame.wisdom <<")"<< endl;
        cout << "  q." << setw(12) << left << "经验        (" << (int)mygame.experience <<")"<< endl;
        cout << "  r." << setw(12) << left << "等级        (" << (int)mygame.level <<")"<< endl;
        cout << "  s." << setw(12) << left << "魔法值      (" << mygame.magic_num <<")"<< endl;
        cout << "  t." << setw(12) << left << "消耗魔法值  (" << (int)mygame.consume_magic_num <<")"<< endl;
        cout << "  u." << setw(12) << left << "魔法伤害力  (" << (int)mygame.magic_attack_power <<")"<< endl;
        cout << "  v." << setw(12) << left << "魔法命中率  (" << (int)mygame.hit_rate <<")"<< endl;
        cout << "  w." << setw(12) << left << "魔法防御力  (" << (int)mygame.magic_defend_power <<")"<< endl;
        cout << "  x." << setw(12) << left << "暴击率      (" << (int)mygame.critical_strike_rate <<")"<< endl;
        cout << "  y." << setw(12) << left << "耐力        (" << (int)mygame.stamina <<")"<< endl;

        cout << "--------------------------------------" << endl;
        cout << "0.放弃修改" << endl;
        cout << "1.存盘退出" << endl;
        cout << "--------------------------------------" << endl;
        cout << "请选择[a..y, 0..1] ";
        char ch;
        while ((ch = getchar()))
        {
            if (ch == '\n')
                continue;
            int valid = 0;
            if (ch == '0' || ch == '1')
            {
                break;
            }
            if (ch >= 'a' || ch <= 'y')
            {
                valid = 1;
                cout << endl;
                unsigned int input;
                unsigned long long time_tmp;
                char tmp_name[20] = { 0 };
                switch (ch)
                {
                case 'a':
                    while (1)
                    {
                        cout << "玩家昵称，当前值=" << mygame.name << ",请输入 :";
                        cin >> tmp_name;
                        if (strlen(tmp_name) <= 15)
                            break;
                        else
                            cout << "非法的玩家昵称：" << tmp_name << endl;
                    }
                    for (int i = 0; i < 16; i++)
                    {
                        mygame.name[i] = tmp_name[i];
                    }
                    break;
                case 'b':
                    while (1)
                    {
                        cout << "生命，当前值=" << mygame.life_value << "，范围[0..10000]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 10000) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的生命值：" << input <<"" << endl;
                        }
                        else
                            break;
                    }
                    mygame.life_value = input;
                    break;
                case 'c':
                    cout << "力量，当前值=" << mygame.power_value << "，范围[0..10000]，" << "请输入 :";
                    while (1)
                    {
                        cin >> input;
                        if (check_range(input, 0, 10000) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的力量值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.power_value = input;
                    break;
                case 'd':
                    while (1)
                    {
                        cout << "体质，当前值=" << mygame.health << "，范围[0..8192]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 8192) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的体质值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.health = input;
                    break;
                case 'e':

                    while (1)
                    {
                        cout << "灵巧，当前值=" << mygame.deft << "，范围[0..1024]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 1024) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的灵巧值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.deft = input;
                    break;
                case 'f':

                    while (1)
                    {
                        cout << "金钱，当前值=" << mygame.wealth << "，范围[0..100000000]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 100000000) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的金钱值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.wealth = input;
                    break;
                case 'g':

                    while (1)
                    {
                        cout << "名声，当前值=" << mygame.fame << "，范围[0..1000000]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 1000000) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的名声值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.fame = input;
                    break;
                case 'h':

                    while (1)
                    {
                        cout << "魅力，当前值=" << mygame.charm << "，范围[0..1000000]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 1000000) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的魅力值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.charm = input;
                    break;
                case 'i':

                    while (1)
                    {
                        cout << "游戏累计时间，当前值=" << mygame.total_time << "，范围[0..10000000000000000]，" << "请输入 :";
                        cin >> time_tmp;
                        if (time_tmp < 0 || time_tmp > 10000000000000000 || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的游戏累计时间值：" << time_tmp << endl;
                        }
                        else
                            break;
                    }
                    mygame.total_time = time_tmp;
                    break;
                case 'j':

                    while (1)
                    {
                        cout << "移动速度，当前值=" << (int)mygame.move_speed << "，范围[0..100]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 100) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的移动速度值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.move_speed = input;
                    break;
                case 'k':

                    while (1)
                    {
                        cout << "攻击速度，当前值=" <<(int) mygame.attack_speed << "，范围[0..100]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 100) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的攻击速度值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.attack_speed = input;
                    break;
                case 'l':

                    while (1)
                    {
                        cout << "攻击范围，当前值=" << (int)mygame.attack_range << "，范围[0..100]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 100) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的攻击范围值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.attack_range = input;
                    break;
                case 'm':

                    while (1)
                    {
                        cout << "攻击力，当前值=" << mygame.attack_power << "，范围[0..2000]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 2000) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的攻击力值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.attack_power = input;
                    break;
                case 'n':

                    while (1)
                    {
                        cout << "防御力，当前值=" << mygame.defend_power << "，范围[0..2000]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 2000) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的防御力值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.defend_power = input;
                    break;
                case 'o':

                    while (1)
                    {
                        cout << "敏捷度，当前值=" << (int)mygame.agile << "，范围[0..100]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 100) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的敏捷度值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.agile = input;
                    break;
                case 'p':

                    while (1)
                    {
                        cout << "智力，当前值=" << (int)mygame.wisdom << "，范围[0..100]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 100) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的智力值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.wisdom = input;
                    break;
                case 'q':

                    while (1)
                    {
                        cout << "经验，当前值=" << (int)mygame.experience << "，范围[0..100]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 100) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的经验值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.experience = input;
                    break;
                case 'r':

                    while (1)
                    {
                        cout << "等级，当前值=" << (int)mygame.level << "，范围[0..100]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 100) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的等级值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.level = input;
                    break;
                case 's':

                    while (1)
                    {
                        cout << "魔法值，当前值=" << mygame.magic_num << "，范围[0..10000]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 10000) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的魔法值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.magic_num = input;
                    break;
                case 't':

                    while (1)
                    {
                        cout << "消耗魔法值，当前值=" << (int)mygame.consume_magic_num << "，范围[0..100]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 100) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的消耗魔法值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.consume_magic_num = input;
                    break;
                case 'u':

                    while (1)
                    {
                        cout << "魔法伤害力，当前值=" << (int)mygame.consume_magic_num << "，范围[0..100]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 100) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的魔法伤害力值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.consume_magic_num = input;
                    break;
                case 'v':

                    while (1)
                    {
                        cout << "魔法命中率，当前值=" << (int)mygame.hit_rate << "，范围[0..100]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 100) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的魔法命中率值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.hit_rate = input;
                    break;
                case 'w':

                    while (1)
                    {
                        cout << "魔法防御力，当前值=" <<(int) mygame.magic_defend_power << "，范围[0..100]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 100) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的魔法防御力值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.magic_defend_power = input;
                    break;
                case 'x':

                    while (1)
                    {
                        cout << "暴击率，当前值=" << (int)mygame.critical_strike_rate << "，范围[0..100]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 100) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的暴击率值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.critical_strike_rate = input;
                    break;
                case 'y':

                    while (1)
                    {
                        cout << "耐力，当前值=" <<(int) mygame.stamina << "，范围[0..100]，" << "请输入 :";
                        cin >> input;
                        if (check_range(input, 0, 100) || cin.fail())
                        {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            cout << "非法的耐力值：" << input << endl;
                        }
                        else
                            break;
                    }
                    mygame.stamina = input;
                    break;
                default:
                    break;
                }
            }
            if (valid)
                break;
        }
        if (ch == '0')
        {
            break;
        }
        else if (ch == '1')
        {
            /* 将此时已有的值转换为相应字节 */
            for (int i = 0; i < 16; i++)
                buffer[i] = mygame.name[i];
            trans_hex(buffer, mygame.life_value, 16, 2);
            trans_hex(buffer, mygame.power_value, 18, 2);
            trans_hex(buffer, mygame.health, 20, 2);
            trans_hex(buffer, mygame.deft, 22, 2);
            trans_hex(buffer, mygame.wealth, 24, 4);
            trans_hex(buffer, mygame.fame, 28, 4);
            trans_hex(buffer, mygame.charm, 32, 4);
            trans_hex(buffer, mygame.total_time, 36, 8);
            buffer[44] = mygame.move_speed;
            buffer[45] = mygame.attack_speed;
            buffer[46] = mygame.attack_range;
            trans_hex(buffer, mygame.attack_power, 48, 2);
            trans_hex(buffer, mygame.defend_power, 50, 2);
            buffer[52]  =mygame.agile;
            buffer[53]  =mygame.wisdom;
            buffer[54]  =mygame.experience;
            buffer[55]  =mygame.level;
            trans_hex(buffer, mygame.magic_num, 56, 4);
            buffer[58] = mygame.consume_magic_num;
            buffer[59] = mygame.magic_attack_power;
            buffer[60] = mygame.hit_rate;
            buffer[61] = mygame.magic_defend_power;
            buffer[62] = mygame.critical_strike_rate;
            buffer[63] = mygame.stamina;
            gfile.seekp(ios::beg);
            gfile.write(buffer, sizeof(game));
            break;
        }
        else
        {
            cout << endl;
        }
    }
    gfile.close();
    return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数允许带参数，不允许进行文件读写
***************************************************************************/
int main(int argc, char*argv[])
{
    if (argc != 2)
    {
        cout << "usage : "<<argv[0]<<" --modify | --read" << endl;
        return -1;
    }
    struct game mygame;
    if (!strcmp(argv[1], "--read"))
        read(mygame);
    else
        modify(mygame);

    return 0;
}
