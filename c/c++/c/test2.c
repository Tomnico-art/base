#include <stdio.h>
char *get_str(void);

int main()
{
    char *p = get_str();
    printf("%s\n", p);

    return 0;
}

char *get_str()
{
    //char str[] = {"abcd"};
    //static char str[] = {"abcd"};
    char *str = "abcd";
    return str;
}