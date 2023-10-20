#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

void GetMemory(char * &p);

int main()
{
    char *str = NULL;
    GetMemory(str);
    strcpy(str, "hello world");
    printf("%s\n", str);

    return 0;
}

void GetMemory(char * &p)
{
    p = (char *)malloc(100);
}

