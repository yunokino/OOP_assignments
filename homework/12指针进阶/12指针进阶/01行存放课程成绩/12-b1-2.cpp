/*2152041 计科 王浩*/
#include <iostream>
#include <iomanip>
using namespace std;

#define STUDENT_NUM	4
#define SCORE_NUM	5

/* --- 不允许定义任何形式的全局变量 --- */

/***************************************************************************
  函数名称：
  功    能：求第一门课的平均分
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void average(int(*score)[STUDENT_NUM])
{
    /* 函数定义语句部分：
       1、本函数中仅允许定义 1个简单变量 + 1个指针变量 */

       /* 函数执行语句部分：
          1、不允许再定义任何类型的变量，包括 for (int i=0;...）等形式定义变量
          2、循环变量必须是指针变量，后续语句中不允许出现[]形式访问数组
             不允许：int a[10], i;
                     for(i=0; i<10; i++)
                         cout << a[i];
             允许  ：int a[10], p;
                     for(p=a; p<a+10; p++)
                         cout << *p;          */

    double total = 0;
    int *p;
    for (p = *score; p < *score + 4; p++)
    {
        total += *p;
    }
    cout << "第1门课平均分：" << total / STUDENT_NUM << endl;

}

/***************************************************************************
  函数名称：
  功    能：找出有两门以上课程不及格的学生
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void fail(int(*score)[STUDENT_NUM])
{
    /* 函数定义语句部分：
       1、本函数中仅允许定义 3个简单变量 + 1个行指针变量 + 1个简单指针变量 */

       /* 函数执行语句部分（要求同average）*/
    double count = 0, total = 0;
    int i = 0;
    int(*p_line)[STUDENT_NUM],* p;
    cout << "2门以上不及格的学生：" << endl;
    for (i = 0; i < STUDENT_NUM; i++)
    {
        count = 0;
        total = 0;
        for (p_line = score; p_line < score + 5; p_line++)
        {
            p = *p_line + i;
            total += *p;
            if (*p < 60)
                count++;
        }
        if (count >= 2)
        {
            cout << "No：" << i + 1 << " ";
            for (p_line = score; p_line < score + 5; p_line++)
            {
                p = *p_line + i;
                cout << *p << " ";
            }
            cout << "平均：" << total / SCORE_NUM << endl;
        }
    }
}

/***************************************************************************
  函数名称：
  功    能：找出平均成绩在90分以上或全部成绩在85分以上的学生
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void good(int(*score)[STUDENT_NUM])
{
    /* 函数定义语句部分：
       1、本函数中仅允许定义 3个简单变量 + 1个行指针变量 + 1个简单指针变量 */

       /* 函数执行语句部分（要求同average）*/
    double count = 0, total = 0;
    int i = 0;
    int(*p_line)[STUDENT_NUM], * p;
    cout << "平均90以上或全部85以上的学生：" << endl;
    for (i = 0; i < STUDENT_NUM; i++)
    {
        count = 0;
        total = 0;
        for (p_line = score; p_line < score + 5; p_line++)
        {
            p = *p_line + i;
            total += *p;
            if (*p >= 85)
                count++;
        }
        if (count == SCORE_NUM || (total / SCORE_NUM) >= 90)
        {
            cout << "No：" << i + 1<< " ";
            for (p_line = score; p_line < score + 5; p_line++)
            {
                p = *p_line + i;
                cout << *p << " ";
            }
            cout << "平均：" << total / SCORE_NUM << endl;
        }
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
    int a[SCORE_NUM][STUDENT_NUM] = {
        {91,92,93,97},  //第1-4个学生的第1门课成绩
        {81,82,83,85},  //第1-4个学生的第2门课成绩
        {71,72,99,87},  //第1-4个学生的第3门课成绩
        {61,32,80,91},  //第1-4个学生的第4门课成绩
        {51,52,95,88} };//第1-4个学生的第5门课成绩
    /* 除上面的预置数组外，本函数中仅允许定义 1个行指针变量 + 1个简单指针变量 */

    /* 函数执行语句部分（要求同average）*/
    int(*p_line)[STUDENT_NUM], * p;
    cout << "初始信息：" << endl;
    for (p_line = a; p_line < a + 5; p_line++)
    {
        cout << "No.1-4学生的第" << p_line - a + 1 << "门课的成绩：";
        for (p = *p_line; p < *p_line + 4; p++)
        {
            cout << *p << " ";
        }
        cout << endl;
    }
    cout << endl;
    average(a);
    cout << endl;
    fail(a);
    cout << endl;
    good(a);

    return 0;
}
