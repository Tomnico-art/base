#pragma once

#include<string>
#include<map>
using namespace std;

class Value
{
public:
    //构造函数
    Value();
    ~Value();
    Value(bool value);
    Value(int value);
    Value(double value);
    Value(const char * value);
    Value(const string & value);

    //运算符重载
    Value & operator = (bool value);
    Value & operator = (int value);
    Value & operator = (double value);
    Value & operator = (const char * value);
    Value & operator = (const string & value);

    //类型转换
    operator bool();
    operator int();
    operator double();
    operator string();
private:
    string m_value;
};

typedef std::map<string, Value> Section;

class IniFile
{
public:
    IniFile();
    ~IniFile();
    bool load(const string & filename);

    Value & get(const string &section, const string &key);
    void set(const string &section, const string &key, const Value & value);


    Section & operator [] (const string & section)
    {
        return m_sections[section];
    }

private:
    string trim(string s);

private:
    string m_filename;
    std::map<string, Section> m_sections;
};

