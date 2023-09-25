/* 2152041 计科 王浩 */
#include <stdio.h>

int main()
{
    /* 三个条件编译的相互位置可互换（例：目前#if满足是输出VS2022，允许先换为Linux）*/
#if (defined __linux)
    printf("Linux\n");
#elif (defined __GNUC__)
    printf("Dev\n");
#elif (defined _MSC_VER)
    printf("VS2022\n");
#endif

    return 0;
}
