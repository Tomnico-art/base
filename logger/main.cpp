#include <iostream>
using namespace std;

#include "Logger.h"
using namespace yazi::utility;

int main()
{
    Logger::instance()->open("./test.log");
    Logger::instance()->max(100);
    // Logger::instance()->log(Logger::DEBUG, __FILE__, __LINE__, "hello");
    debug("hello world");
    info("info message");
    info("warn message");
    info("error message");

    return 0;
}