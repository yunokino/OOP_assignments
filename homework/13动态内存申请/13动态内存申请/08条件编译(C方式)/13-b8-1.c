/* 2152041 �ƿ� ���� */
#include <stdio.h>

int main()
{
    /* ��������������໥λ�ÿɻ���������Ŀǰ#if���������VS2022�������Ȼ�ΪLinux��*/
#if (defined __linux)
    printf("Linux\n");
#elif (defined __GNUC__)
    printf("Dev\n");
#elif (defined _MSC_VER)
    printf("VS2022\n");
#endif

    return 0;
}
