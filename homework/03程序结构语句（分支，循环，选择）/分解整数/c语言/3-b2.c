/*���� ��07 2152041*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int i;
    printf("������һ��[1..30000]�������\n");
    scanf ("%d", &i);
    printf("��λ : %d\n",i/10000);
    printf("ǧλ : %d\n",(i/1000)%10);
    printf("��λ : %d\n",i/10/10%10);
    printf("ʮλ : %d\n",i/10%10);
    printf("��λ : %d\n",i%10);
    return 0;
}

