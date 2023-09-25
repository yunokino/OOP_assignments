/* 2152041 �ƿ� ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
//������Ҫ�ɼ�������ͷ�ļ�


//�˴�Ϊʾ���������޸Ľṹ�����ƣ������޸Ľṹ���еĳ�Ա���ݣ�Ҫ��sizeof������64
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
    unsigned char critical_strike_rate;//������
    unsigned char stamina;//����
    unsigned long long total_time;
};

/* �˴�����������������������
   1�����������ĺ����������������µ� FILE* �����д�/��/д/�رյȲ���
   2����������ͬ��������main����
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ��������������ֻ�������һ��fopen��һ��fread����Ϊ����������������fclose��
***************************************************************************/
int read(struct game* mygame)
{
    /* ��������ֻ������һ�� FILE* */
    FILE* fp;

    /* �ļ��򿪣�����Ҫ��Ϊ��
       1��Ҫ���Զ���ʽ�򿪣��򿪷�ʽ***����ָ��
       2��������fopen�⣬�����������ط��������ٳ���fopen/freopen  */
    fp = fopen("game.dat", "rb");

    /* ���к����������������������ļ�����ʾ����Ϸ���ֵ���ر��ļ��ȣ�������ú���
       ���У�ֻ������һ���Զ�ȡ64�ֽڵķ�����game.dat�����ݶ���***�����������ơ��ṹ����������ָ����
                 fread(***, 1, sizeof(demo), fp);
    */
    if (fp == NULL)
    {
        printf("�ļ���ʧ��\n");
        return -1;
    }
    char buffer[64];
    fread(buffer, 64, 1, fp);
    change_content(mygame, buffer);
    printf("          ����ǳƣ�%s\n", mygame->name);
    printf("            ����ֵ��%u\n", mygame->life_value);
    printf("            ����ֵ��%u\n", mygame->power_value);
    printf("            ����ֵ��%u\n", mygame->health);
    printf("            ����ֵ��%u\n", mygame->deft);
    printf("            ��Ǯֵ��%u\n", mygame->wealth);
    printf("            ����ֵ��%u\n", mygame->fame);
    printf("            ����ֵ��%u\n", mygame->charm);
    printf("��Ϸ�ۼ�ʱ��(us)ֵ��%lld\n", mygame->total_time);
    printf("        �ƶ��ٶ�ֵ��%u\n", mygame->move_speed);
    printf("        �����ٶ�ֵ��%u\n", mygame->attack_speed);
    printf("        ������Χֵ��%u\n", mygame->attack_range);
    mygame->occupy = 0;
    printf("          ������ֵ��%u\n", mygame->attack_power);
    printf("          ������ֵ��%u\n", mygame->defend_power);
    printf("          ���ݶ�ֵ��%u\n", mygame->agile);
    printf("            ����ֵ��%u\n", mygame->wisdom);
    printf("            ����ֵ��%u\n", mygame->experience);
    printf("            �ȼ�ֵ��%u\n", mygame->level);
    printf("            ħ��ֵ��%u\n", mygame->magic_num);
    printf("        ����ħ��ֵ��%u\n", mygame->consume_magic_num);
    printf("      ħ���˺���ֵ��%u\n", mygame->magic_attack_power);
    printf("          ������ֵ��%u\n", mygame->hit_rate);
    printf("      ħ��������ֵ��%u\n", mygame->magic_defend_power);
    printf("          ������ֵ��%u\n", mygame->critical_strike_rate);
    printf("            ����ֵ��%u\n", mygame->stamina);
    fclose(fp);

    return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ��������������ֻ�������һ��open��һ��read��һ��write����Ϊ����������������fclose��
***************************************************************************/
int modify(struct game* mygame)
{
    /* ��������ֻ������һ�� FILE* */
    FILE* fp;

    /* �ļ��򿪣�����Ҫ��Ϊ��
       1��Ҫ���Զ�д��ʽ�򿪣��򿪷�ʽ***����ָ��
       2��������fopen�⣬�����������ط��������ٳ���fopen/freopen  */
    fp = fopen("game.dat", "rb+");

    /* ���к����������������������ļ�����ʾ����Ϸ���ֵ���ر��ļ��ȣ�������ú���
       ���У�ֻ������һ���Զ�ȡ64�ֽڵķ�����game.dat�����ݶ���***�����������ơ��ṹ����������ָ����
                 fread(***, 1, sizeof(struct demo), fp);
             ֻ������һ����д��64�ֽڵķ�����***������д��game.dat�У����������ơ��ṹ����������ָ����
                 fwrite(***, 1, sizeof(struct demo), fp);
    */
    if (fp == NULL)
    {
        printf("�ļ���ʧ��\n");
        return -1;
    }
    char buffer[64];
    fread(buffer, 64, 1, fp);
    change_content(mygame, buffer);
    while (1)
    {
        printf("--------------------------------------\n");
        printf("  ��Ϸ�浵�ļ��޸Ĺ���\n");
        printf("--------------------------------------\n");
        printf("  a.����ǳ�    (%s)\n", mygame->name);
        printf("  b.����        (%u)\n", mygame->life_value);
        printf("  c.����        (%u)\n", mygame->power_value);
        printf("  d.����        (%u)\n", mygame->health);
        printf("  e.����        (%u)\n", mygame->deft);
        printf("  f.��Ǯ        (%u)\n", mygame->wealth);
        printf("  g.����        (%u)\n", mygame->fame);
        printf("  h.����        (%u)\n", mygame->charm);
        printf("  i.��Ϸ�ۼ�ʱ��(%lld)\n", mygame->total_time);
        printf("  j.�ƶ��ٶ�    (%u)\n", mygame->move_speed);
        printf("  k.�����ٶ�    (%u)\n", mygame->attack_speed);
        printf("  l.������Χ    (%u)\n", mygame->attack_range);
        printf("  m.������      (%u)\n", mygame->attack_power);
        printf("  n.������      (%u)\n", mygame->defend_power);
        printf("  o.���ݶ�      (%u)\n", mygame->agile);
        printf("  p.����        (%u)\n", mygame->wisdom);
        printf("  q.����        (%u)\n", mygame->experience);
        printf("  r.�ȼ�        (%u)\n", mygame->level);
        printf("  s.ħ��ֵ      (%u)\n", mygame->magic_num);
        printf("  t.����ħ��ֵ  (%u)\n", mygame->consume_magic_num);
        printf("  u.ħ���˺���  (%u)\n", mygame->magic_attack_power);
        printf("  v.ħ��������  (%u)\n", mygame->hit_rate);
        printf("  w.ħ��������  (%u)\n", mygame->magic_defend_power);
        printf("  x.������      (%u)\n", mygame->critical_strike_rate);
        printf("  y.����        (%u)\n", mygame->stamina);

        printf("--------------------------------------\n");
        printf("0.�����޸�\n");
        printf("1.�����˳�\n");
        printf("--------------------------------------\n");
        printf("��ѡ��[a..y, 0..1] ");
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
                        printf("����ǳƣ���ǰֵ=%s,������ :", mygame->name);
                        scanf("%s", tmp_name);
                        if (strlen(tmp_name) <= 15)
                            break;
                        else
                            printf("�Ƿ�������ǳƣ�%s\n", mygame->name);
                    }
                    for (int i = 0; i < 16; i++)
                    {
                        mygame->name[i] = tmp_name[i];
                    }
                    break;
                case 'b':
                    while (1)
                    {
                        printf("��������ǰֵ=%u����Χ[0..10000]�������� :",  mygame->life_value );
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 10000) || !status)
                        {
                            while(getchar()!='\n');
                          
                            printf("�Ƿ�������ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->life_value = input;
                    break;
                case 'c':
                    printf("��������ǰֵ=%u����Χ[0..10000]�������� :", mygame->power_value);
                    while (1)
                    {
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 10000) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ�������ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->power_value = input;
                    break;
                case 'd':
                    while (1)
                    {
                        printf("���ʣ���ǰֵ=%u����Χ[0..8192]�������� :", mygame->health);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 8192) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ�������ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->health = input;
                    break;
                case 'e':

                    while (1)
                    {
                        printf("���ɣ���ǰֵ=%u����Χ[0..1024]�������� :", mygame->deft);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 1024) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ�������ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->deft = input;
                    break;
                case 'f':

                    while (1)
                    {
                        printf("��Ǯ����ǰֵ=%u����Χ[0..100000000]�������� :", mygame->wealth);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100000000) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ��Ľ�Ǯֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->wealth = input;
                    break;
                case 'g':

                    while (1)
                    {
                        printf("��������ǰֵ=%u����Χ[0..1000000]�������� :", mygame->fame);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 1000000) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ�������ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->fame = input;
                    break;
                case 'h':

                    while (1)
                    {
                        printf("��������ǰֵ=%u����Χ[0..1000000]�������� :", mygame->charm);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 1000000) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ�������ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->charm = input;
                    break;
                case 'i':

                    while (1)
                    {
                        printf("��Ϸ�ۼ�ʱ�䣬��ǰֵ=%lld����Χ[0..10000000000000000]�������� :", mygame->total_time);
                        int status = scanf("%llu",& time_tmp);
                        if (time_tmp < 0 || time_tmp > 10000000000000000 || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ�����Ϸ�ۼ�ʱ��ֵ��%lld\n", time_tmp);
                        }
                        else
                            break;
                    }
                    mygame->total_time = time_tmp;
                    break;
                case 'j':

                    while (1)
                    {
                        printf("�ƶ��ٶȣ���ǰֵ=%u����Χ[0..100]�������� :", mygame->move_speed);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ����ƶ��ٶ�ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->move_speed = input;
                    break;
                case 'k':

                    while (1)
                    {
                        printf("�����ٶȣ���ǰֵ=%u����Χ[0..100]�������� :", mygame->attack_speed);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ��Ĺ����ٶ�ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->attack_speed = input;
                    break;
                case 'l':

                    while (1)
                    {
                        printf("������Χ����ǰֵ=%u����Χ[0..100]�������� :", mygame->attack_range);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');
                            printf("�Ƿ��Ĺ�����Χֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->attack_range = input;
                    break;
                case 'm':

                    while (1)
                    {
                        printf("����������ǰֵ=%u����Χ[0..2000]�������� :", mygame->attack_power);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 2000) || !status)
                        {
                            while(getchar()!='\n');
                            printf("�Ƿ��Ĺ�����ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->attack_power = input;
                    break;
                case 'n':

                    while (1)
                    {
                        printf("����������ǰֵ=%u����Χ[0..2000]�������� :", mygame->defend_power);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 2000) || !status)
                        {
                            while(getchar()!='\n');
                            printf("�Ƿ��ķ�����ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->defend_power = input;
                    break;
                case 'o':

                    while (1)
                    {
                        printf("���ݶȣ���ǰֵ=%u����Χ[0..100]�������� :", mygame->agile);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ������ݶ�ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->agile = input;
                    break;
                case 'p':

                    while (1)
                    {
                        printf("��������ǰֵ=%u����Χ[0..100]�������� :", mygame->wisdom);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ�������ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->wisdom = input;
                    break;
                case 'q':

                    while (1)
                    {
                        printf("���飬��ǰֵ=%u����Χ[0..100]�������� :", mygame->experience);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ��ľ���ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->experience = input;
                    break;
                case 'r':

                    while (1)
                    {
                        printf("�ȼ�����ǰֵ=%u����Χ[0..100]�������� :", mygame->level);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ��ĵȼ�ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->level = input;
                    break;
                case 's':

                    while (1)
                    {
                        printf("ħ��ֵ����ǰֵ=%u����Χ[0..10000]�������� :", mygame->magic_num);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 10000) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ���ħ��ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->magic_num = input;
                    break;
                case 't':

                    while (1)
                    {
                        printf("����ħ��ֵ����ǰֵ=%u����Χ[0..100]�������� :", mygame->consume_magic_num);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ�������ħ��ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->consume_magic_num = input;
                    break;
                case 'u':

                    while (1)
                    {
                        printf("ħ���˺�������ǰֵ=%u����Χ[0..100]�������� :", mygame->consume_magic_num);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ���ħ���˺���ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->consume_magic_num = input;
                    break;
                case 'v':

                    while (1)
                    {
                        printf("ħ�������ʣ���ǰֵ=%u����Χ[0..100]�������� :", mygame->hit_rate);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ���ħ��������ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->hit_rate = input;
                    break;
                case 'w':

                    while (1)
                    {
                        printf("ħ������������ǰֵ=%u����Χ[0..100]�������� :", mygame->magic_defend_power);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ���ħ��������ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->magic_defend_power = input;
                    break;
                case 'x':
                    while (1)
                    {
                        printf("�����ʣ���ǰֵ=%u����Χ[0..100]�������� :", mygame->critical_strike_rate);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ��ı�����ֵ��%u\n", input);
                        }
                        else
                            break;
                    }
                    mygame->critical_strike_rate = input;
                    break;
                case 'y':
                    while (1)
                    {
                        printf("��������ǰֵ=%u����Χ[0..100]�������� :", mygame->stamina);
                        int status = scanf("%u", &input);
                        if (check_range(input, 0, 100) || !status)
                        {
                            while(getchar()!='\n');

                            printf("�Ƿ�������ֵ��%u\n", input);
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
            /* ����ʱ���е�ֵת��Ϊ��Ӧ�ֽ� */
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main�������������������������ļ���д
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
