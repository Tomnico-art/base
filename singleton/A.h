#pragma once
#include <iostream>
using namespace std;

#include "Singleton.h"
using namespace yazi::utility;

class A
{
    friend class Singleton<B>;
public:
    void show()
    {
        cout << m_name << endl;
    }
    
private:
    A() : m_name("A") {}
    A(const A &) {}
    ~A() {}
    A & operator = (const A &);

private:
    string m_name;
};
