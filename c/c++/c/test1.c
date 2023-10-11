#include <stdio.h>

int main()
{
    char *pt = "AAA";   //字符串常量存放在只读区域，不能修改值，智能修改指针指向。
    printf("%s\n", pt);

    // *pt = 'B';       //段错误
    // printf("%s\n", pt);

    pt = "B";           //正确
    printf("%s\n", pt);

    return 0;
}