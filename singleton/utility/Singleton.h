#pragma once

namespace yazi
{
namespace utility
{

template <typename T>
class Singleton
{
public:
    static T * instance()
    {
        if (m_instance == NULL)
        {
            m_instance = new A();
        }
        return m_instance;
    }
private:
    Singleton() {}
    Singleton(const Singleton<T> &);
    ~Singleton() {}
    Singleton<T> & operator = (const Singleton<T>);
private:
    static T * m_instance;

};

template <typename T>
T * Singleton<T>::m_instance = NULL;

}
}