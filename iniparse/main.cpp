#include <iostream>
using namespace std;

#include "IniFile.h"

int main()
{
    // Value v1(true);
    // Value v2(123);
    // Value v3(1.23);
    // Value v4("hello");

    // Value v1;
    // v1 = true;
    // Value v2;
    // v2 = 123;
    // Value v3;
    // v2 = 1.23;
    // Value v4;
    // v4 = "hello world";

    // Value v1(true);
    // bool b = v1;

    // Value v2(123);
    // int i = v2;

    // Value v3(1.23);
    // double f = v3;

    // Value v4("hello");
    // const string & s = v4;

    IniFile ini;
    ini.load("./main.ini");

    const string & ip = ini["server"]["ip"];
    int port = ini["server"]["port"];

    ini.set("server", "timeout", 1000);
    ini.set("server", "flag", true);

    return 0;
}