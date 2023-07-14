#include<iostream>
using namespace std;

#include "A.h"
#include "B.h"

#include "Singleton.h"
using namespace yazi::utility;

int main()
{
    //主线程
    Singleton<A>::instance()->show();
    Singleton<B>::instance()->show();

    // //子线程
    // Singleton<A>::instance->show();
    // Singleton<B>::instance->show();
    
    return 0;
}
