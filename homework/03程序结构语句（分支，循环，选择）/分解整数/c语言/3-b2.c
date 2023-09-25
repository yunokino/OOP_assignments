/*王浩 信07 2152041*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int i;
    printf("请输入一个[1..30000]间的整数\n");
    scanf ("%d", &i);
    printf("万位 : %d\n",i/10000);
    printf("千位 : %d\n",(i/1000)%10);
    printf("百位 : %d\n",i/10/10%10);
    printf("十位 : %d\n",i/10%10);
    printf("个位 : %d\n",i%10);
    return 0;
}

