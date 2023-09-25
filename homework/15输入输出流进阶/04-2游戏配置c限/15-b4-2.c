/* 2152041 计科 王浩 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
//根据需要可加入其它头文件


//此处为示例，允许修改结构体名称，允许修改结构体中的成员内容，要求sizeof必须是64
struct game {
    char name[16];
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
   1、所有新增的函数，均不允许定义新的 FILE* 并进行打开/读/写/关闭等操作
   2、上述限制同样适用于main函数
*/
//template <typename T>
//void trans_hex(char* buffer, T num, const int location, const int byte_num)
//{
//    for (int i = 0; i < byte_num; i++)
//    {
//        buffer[location + i] = (num >> (8 * i)) & 0xff;
//    }
//}
void trans_hex_int(char* buffer, unsigned int num, const int location)
{
    for (int i = 0; i < 4; i++)
    {
        buffer[location + i] = (num >> (8 * i)) & 0xff;
    }
}

void trans_hex_long(char* buffer, unsigned long long num, const int location)
{
    for (int i = 0; i < 8; i++)
    {
        buffer[location + i] = (num >> (8 * i)) & 0xff;
    }
}
void trans_hex_short(char* buffer, unsigned short num, const int location)
{
    for (int i = 0; i < 2; i++)
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

void change_content(struct game* mygame, char* buffer)
{
    unsigned int tmp;
    for (int i = 0; i <= 15; i++)
        mygame->name[i] = buffer[i];

    tmp = (int)(unsigned char)buffer[17] * 16 * 16 + (int)(unsigned char)buffer[16];
    mygame->life_value = tmp;
    tmp = (int)(unsigned char)buffer[19] * 16 * 16 + (int)(unsigned char)buffer[18];
    mygame->power_value = tmp;
    tmp = (int)(unsigned char)buffer[21] * 16 * 16 + (int)(unsigned char)buffer[20];
    mygame->health = tmp;
    tmp = (int)(unsigned char)buffer[23] * 16 * 16 + (int)(unsigned char)buffer[22];
    mygame->deft = tmp;
    for (int i = 3; i >= 0; i--)
        tmp = tmp * 16 * 16 + (int)(unsigned char)buffer[24 + i];
    mygame->wealth = tmp;
    for (int i = 3; i >= 0; i--)
        tmp = tmp * 16 * 16 + (int)(unsigned char)buffer[28 + i];
    mygame->fame = tmp;
    for (int i = 3; i >= 0; i--)
        tmp = tmp * 16 * 16 + (int)(unsigned char)buffer[32 + i];
    mygame->charm = tmp;

    for (int i = 7; i >= 0; i--)
        mygame->total_time = mygame->total_time * 16 * 16 + (unsigned long long)(unsigned char)buffer[36 + i];

    tmp = buffer[44];
    mygame->move_speed = tmp;
    tmp = buffer[45];
    mygame->attack_speed = tmp;
    tmp = buffer[46];
    mygame->attack_range = tmp;
    tmp = (int)(unsigned char)buffer[49] * 16 * 16 + (int)(unsigned char)buffer[48];
    mygame->attack_power = tmp;
    tmp = ((int)(unsigned char)buffer[51]) * 16 * 16 + (int)(unsigned char)buffer[50];
    mygame->defend_power = tmp;
    mygame->agile = buffer[52];
    mygame->wisdom = buffer[53];
    mygame->experience = buffer[54];
    mygame->level = buffer[55];
    tmp = (int)(unsigned char)buffer[57] * 16 * 16 + (int)(unsigned char)buffer[56];
    mygame->magic_num = tmp;
    mygame->consume_magic_num = buffer[58];
    mygame->magic_attack_power = buffer[59];
    mygame->hit_rate = buffer[60];
    mygame->magic_defend_power = buffer[61];
    mygame->critical_strike_rate = buffer[62];
    mygame->stamina = buffer[63];
}



/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：整个函数，只允许出现一次fopen、一次fread（因为包含错误处理，允许多次fclose）
***************************************************************************/
int read(struct game* mygame)
{
    /* 本函数中只允许定义一个 FILE* */
    FILE* fp;

    /* 文件打开，具体要求为：
       1、要求以读方式打开，打开方式***自行指定
       2、除本次fopen外，本函数其它地方不允许再出现fopen/freopen  */
    fp = fopen("game.dat", "rb");

    /* 进行后续操作，包括错误处理、读文件、显示各游戏项的值、关闭文件等，允许调用函数
       其中：只允许用一次性读取64字节的方法将game.dat的内容读入***（缓冲区名称、结构体名称自行指定）
                 fread(***, 1, sizeof(demo), fp);
    */
    if (fp == NULL)
    {
        printf("文件打开失败\n");
        return -1;
    }
    char buffer[64];
    fread(buffer, 64, 1, fp);
    change_content(mygame, buffer);
    printf("          玩家昵称：%s\n", mygame->name);
    printf("            生命值：%u\n", mygame->life_value);
    printf("            力量值：%u\n", mygame->power_value);
    printf("            体质值：%u\n", mygame->health);
    printf("            灵巧值：%u\n", mygame->deft);
    printf("            金钱值：%u\n", mygame->wealth);
    printf("            名声值：%u\n", mygame->fame);
    printf("            魅力值：%u\n", mygame->charm);
    printf("游戏累计时间(us)值：%lld\n", mygame->total_time);
    printf("        移动速度值：%u\n", mygame->move_speed);
    printf("        攻击速度值：%u\n", mygame->attack_speed);
    printf("        攻击范围值：%u\n", mygame->attack_range);
    mygame->occupy = 0;
    printf("          攻击力值：%u\n", mygame->attack_power);
    printf("          防御力值：%u\n", mygame->defend_power);
    printf("          敏捷度值：%u\n", mygame->agile);
    printf("            智力值：%u\n", mygame->wisdom);
    printf("            经验值：%u\n", mygame->experience);
    printf("            等级值：%u\n", mygame->level);
    printf("            魔法值：%u\n", mygame->magic_num);
    printf("        消耗魔法值：%u\n", mygame->consume_magic_num);
    printf("      魔法伤害力值：%u\n", mygame->magic_attack_power);
    printf("          命中率值：%u\n", mygame->hit_rate);
    printf("      魔法防御力值：%u\n", mygame->magic_defend_power);
    printf("          暴击率值：%u\n", mygame->critical_strike_rate);
    printf("            耐力值：%u\n", mygame->stamina);
    fclose(fp);

    return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：整个函数，只允许出现一次open、一次read、一次write（因为包含错误处理，允许多次fclose）
***************************************************************************/
int modify(struct game* mygame)
{
    /* 本函数中只允许定义一个 FILE* */
    FILE* fp;

    /* 文件打开，具体要求为：
       1、要求以读写方式打开，打开方式***自行指定
       2、除本次fopen外，本函数其它地方不允许再出现fopen/freopen  */
    fp = fopen("game.dat", "rb+");

    /* 进行后续操作，包括错误处理、读文件、显示各游戏项的值、关闭文件等，允许调用函数
       其中：只允许用一次性读取64字节的方法将game.dat的内容读入***（缓冲区名称、结构体名称自行指定）
                 fread(***, 1, sizeof(struct demo), fp);
             只允许用一次性写入64字节的方法将***的内容写入game.dat中（缓冲区名称、结构体名称自行指定）
                 fwrite(***, 1, sizeof(struct demo), fp);
    */
    if (fp == NULL)
    {
        printf("文件打开失败\n");
        return -1;
    }
    char buffer[64];
    fread(buffer, 64, 1, fp);
    change_content(mygame, buffer);
    while (1)
    {
        printf("--------------------------------------\n");
        printf("  游戏存档文件修改工具\n");
        printf("--------------------------------------\n");
        printf("  a.玩家昵称    (%s)\n", mygame->name);
        printf("  b.生命        (%u)\n", mygame->life_value);
        printf("  c.力量        (%u)\n", mygame->power_value);
        printf("  d.体质        (%u)\n", mygame->health);
        printf("  e.灵巧        (%u)\n", mygame->deft);
        printf("  f.金钱        (%u)\n", mygame->wealth);
        printf("  g.名声        (%u)\n", mygame->fame);
        printf("  h.魅力        (%u)\n", mygame->charm);
        printf("  i.游戏累计时间(%lld)\n", mygame->total_time);
        printf("  j.移动速度    (%u)\n", mygame->move_speed);
        printf("  k.攻击速度    (%u)\n", mygame->attack_speed);
        printf("  l.攻击范围    (%u)\n", mygame->attack_range);
        printf("  m.攻击力      (%u)\n", mygame->attack_power);
        printf("  n.防御力      (%u)\n", mygame->defend_power);
        printf("  o.敏捷度      (%u)\n", mygame->agile);
        printf("  p.智力        (%u)\n", mygame->wisdom);
        printf("  q.经验        (%u)\n", mygame->experience);
        printf("  r.等级        (%u)\n", mygame->level);
        printf("  s.魔法值      (%u)\n", mygame->magic_num);
        printf("  t.消耗魔法值  (%u)\n", mygame->consume_magic_num);
        printf("  u.魔法伤害力  (%u)\n", mygame->magic_attack_power);
        printf("  v.魔法命中率  (%u)\n", mygame->hit_rate);
        printf("  w.魔法防御力  (%u)\n", mygame->magic_defend_power);
        printf("  x.暴击率      (%u)\n", mygame->critical_strike_rate);
        printf("  y.耐力        (%u)\n", mygame->stamina);

        printf("--------------------------------------\n");
        printf("0.放弃修改\n");
        printf("1.存盘退出\n");
        printf("--------------------------------------\n");
        printf("请选择[a..y, 0..1] ");
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
                printf("\n");
                unsigned int input;
                unsigned long long time_tmp = 0;
                char tmp_name[20] = { 0 };
                switch (ch)
                {
                case 'a':
                    while (1)
                    {
                        printf("玩家昵称，当前值=%s,请输入 :", mygame->name);
                        scanf("%s", tmp_name);
                        if (strlen(tmp_name) <= 15)
                            break;
                        else
                            printf("非法的玩家昵称：%s\n", mygame->name);
                    }
                    for (int i = 0; i < 16; i++)
                    {
                        mygame->name[i] = tmp_name[i];
                    }
                    break;
                case 'b':
                    while (1)
                    {
                        printf("生命，当前值=%u，范围[0..10000]，请输入 :",  mygame->life_value );
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 10000) || !status)
                        {
                            while(getchar()!='\n');
                          
                            printf("非法的生命值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->life_value = input;
                    break;
                case 'c':
                    printf("力量，当前值=%u，范围[0..10000]，请输入 :", mygame->power_value);
                    while (1)
                    {
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 10000) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的力量值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->power_value = input;
                    break;
                case 'd':
                    while (1)
                    {
                        printf("体质，当前值=%u，范围[0..8192]，请输入 :", mygame->health);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 8192) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的体质值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->health = input;
                    break;
                case 'e':

                    while (1)
                    {
                        printf("灵巧，当前值=%u，范围[0..1024]，请输入 :", mygame->deft);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 1024) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的灵巧值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->deft = input;
                    break;
                case 'f':

                    while (1)
                    {
                        printf("金钱，当前值=%u，范围[0..100000000]，请输入 :", mygame->wealth);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100000000) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的金钱值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->wealth = input;
                    break;
                case 'g':

                    while (1)
                    {
                        printf("名声，当前值=%u，范围[0..1000000]，请输入 :", mygame->fame);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 1000000) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的名声值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->fame = input;
                    break;
                case 'h':

                    while (1)
                    {
                        printf("魅力，当前值=%u，范围[0..1000000]，请输入 :", mygame->charm);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 1000000) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的魅力值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->charm = input;
                    break;
                case 'i':

                    while (1)
                    {
                        printf("游戏累计时间，当前值=%lld，范围[0..10000000000000000]，请输入 :", mygame->total_time);
                        int status = scanf("%llu",& time_tmp);
                        if (time_tmp < 0 || time_tmp > 10000000000000000 || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的游戏累计时间值：%lld\n", time_tmp);
                        }
                        else
                            break;
                    }
                    mygame->total_time = time_tmp;
                    break;
                case 'j':

                    while (1)
                    {
                        printf("移动速度，当前值=%u，范围[0..100]，请输入 :", mygame->move_speed);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的移动速度值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->move_speed = input;
                    break;
                case 'k':

                    while (1)
                    {
                        printf("攻击速度，当前值=%u，范围[0..100]，请输入 :", mygame->attack_speed);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的攻击速度值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->attack_speed = input;
                    break;
                case 'l':

                    while (1)
                    {
                        printf("攻击范围，当前值=%u，范围[0..100]，请输入 :", mygame->attack_range);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');
                            printf("非法的攻击范围值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->attack_range = input;
                    break;
                case 'm':

                    while (1)
                    {
                        printf("攻击力，当前值=%u，范围[0..2000]，请输入 :", mygame->attack_power);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 2000) || !status)
                        {
                            while(getchar()!='\n');
                            printf("非法的攻击力值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->attack_power = input;
                    break;
                case 'n':

                    while (1)
                    {
                        printf("防御力，当前值=%u，范围[0..2000]，请输入 :", mygame->defend_power);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 2000) || !status)
                        {
                            while(getchar()!='\n');
                            printf("非法的防御力值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->defend_power = input;
                    break;
                case 'o':

                    while (1)
                    {
                        printf("敏捷度，当前值=%u，范围[0..100]，请输入 :", mygame->agile);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的敏捷度值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->agile = input;
                    break;
                case 'p':

                    while (1)
                    {
                        printf("智力，当前值=%u，范围[0..100]，请输入 :", mygame->wisdom);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的智力值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->wisdom = input;
                    break;
                case 'q':

                    while (1)
                    {
                        printf("经验，当前值=%u，范围[0..100]，请输入 :", mygame->experience);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的经验值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->experience = input;
                    break;
                case 'r':

                    while (1)
                    {
                        printf("等级，当前值=%u，范围[0..100]，请输入 :", mygame->level);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的等级值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->level = input;
                    break;
                case 's':

                    while (1)
                    {
                        printf("魔法值，当前值=%u，范围[0..10000]，请输入 :", mygame->magic_num);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 10000) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的魔法值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->magic_num = input;
                    break;
                case 't':

                    while (1)
                    {
                        printf("消耗魔法值，当前值=%u，范围[0..100]，请输入 :", mygame->consume_magic_num);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的消耗魔法值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->consume_magic_num = input;
                    break;
                case 'u':

                    while (1)
                    {
                        printf("魔法伤害力，当前值=%u，范围[0..100]，请输入 :", mygame->consume_magic_num);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的魔法伤害力值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->consume_magic_num = input;
                    break;
                case 'v':

                    while (1)
                    {
                        printf("魔法命中率，当前值=%u，范围[0..100]，请输入 :", mygame->hit_rate);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的魔法命中率值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->hit_rate = input;
                    break;
                case 'w':

                    while (1)
                    {
                        printf("魔法防御力，当前值=%u，范围[0..100]，请输入 :", mygame->magic_defend_power);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的魔法防御力值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->magic_defend_power = input;
                    break;
                case 'x':
                    while (1)
                    {
                        printf("暴击率，当前值=%u，范围[0..100]，请输入 :", mygame->critical_strike_rate);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的暴击率值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->critical_strike_rate = input;
                    break;
                case 'y':
                    while (1)
                    {
                        printf("耐力，当前值=%u，范围[0..100]，请输入 :", mygame->stamina);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("非法的耐力值：%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->stamina = input;
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
                buffer[i] = mygame->name[i];
            trans_hex_short(buffer, mygame->life_value, 16);
            trans_hex_short(buffer, mygame->power_value, 18);
            trans_hex_short(buffer, mygame->health, 20);
            trans_hex_short(buffer, mygame->deft, 22);
            trans_hex_int(buffer, mygame->wealth, 24);
            trans_hex_int(buffer, mygame->fame, 28);
            trans_hex_int(buffer, mygame->charm, 32);
            trans_hex_long(buffer, mygame->total_time, 36);
            buffer[44] = mygame->move_speed;
            buffer[45] = mygame->attack_speed;
            buffer[46] = mygame->attack_range;
            trans_hex_short(buffer, mygame->attack_power, 48);
            trans_hex_short(buffer, mygame->defend_power, 50);
            buffer[52] = mygame->agile;
            buffer[53] = mygame->wisdom;
            buffer[54] = mygame->experience;
            buffer[55] = mygame->level;
            trans_hex_short(buffer, mygame->magic_num, 56);
            buffer[58] = mygame->consume_magic_num;
            buffer[59] = mygame->magic_attack_power;
            buffer[60] = mygame->hit_rate;
            buffer[61] = mygame->magic_defend_power;
            buffer[62] = mygame->critical_strike_rate;
            buffer[63] = mygame->stamina; 
            rewind(fp);
            fwrite(buffer, 64, 1, fp);
            break;
        }
        else
        {
            printf("\n");
        }
    }

    fclose(fp);
    return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数允许带参数，不允许进行文件读写
***************************************************************************/
int main(int argc, char* argv[])
{ 
    if (argc != 2)
    {
        printf("usage : %s --modify | --read", argv[0]);
        return -1;
    }
    struct game mygame;
    for (int i = 0; i < 16; i++)
        mygame.name[i] = 0;
    if (!strcmp(argv[1], "--read"))
        read(&mygame);
    else
        modify(&mygame);

    return 0;
}
