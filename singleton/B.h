#pragma once
#include <iostream>
using namespace std;

#include "Singleton.h"
using namespace yazi::utility;

class B
{
    friend class Singleton<B>;
public:
    void show()
    {
        cout << m_name << endl;
    }
    
private:
    B() : m_name("B") {}
    B(const B &) {}
    ~B() {}
    B & operator = (const B &);

private:
    string m_name;
};
