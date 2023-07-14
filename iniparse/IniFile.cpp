#include "IniFile.h"
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

Value::Value()
{
}

Value::~Value()
{
}

Value::Value(bool value)
{
    *this = value;
}

Value::Value(int value)
{
    *this = value;
}

Value::Value(double value)
{
    *this = value;
}

Value::Value(const char *value)
{
    *this = value;
}

Value::Value(const string &value)
{
    *this = value;
}

Value &Value::operator=(bool value)
{
    m_value = value ? "true" : "false";
    return *this;
}

Value &Value::operator=(int value)
{
    stringstream ss;
    ss << value;
    m_value = ss.str();
    return *this;
}

Value &Value::operator=(double value)
{
    stringstream ss;
    ss << value;
    m_value = ss.str();
    return *this;
}

Value &Value::operator=(const char *value)
{
    m_value = value;
    return *this;
}

Value &Value::operator=(const string &value)
{
    m_value = value;
    return *this;
}

Value::operator bool()
{
    return m_value == "true";
}

Value::operator int()
{
    return atoi(m_value.c_str());
}

Value::operator double()
{
    return atof(m_value.c_str());
}

Value::operator string()
{
    return m_value;
}

IniFile::IniFile()
{
}

IniFile::~IniFile()
{
}

bool IniFile::load(const string &filename)
{
    ifstream fin(filename);
    if (fin.fail())
    {
        return false;
    }

    string line;
    string section;
    while (getline(fin, line))
    {
        line = trim(line);
        if (line == "")
        {
            continue;
        }
        if (line[0] == '[')
        {
            int pos = line.find_first_of(']');
            string section = line.substr(1, pos-1);
            section = trim(section);
            m_sections[section] = Section();
        }
        else 
        {
            int pos = line.find_first_of('=');
            string key = line.substr(0, pos);
            key = trim(key);
            string value = line.substr(pos + 1, line.length() - pos);
            value = trim(value);
            m_sections[section][key] = value;
        }
    }
    return true;

}

Value &IniFile::get(const string &section, const string &key)
{
    return m_sections[section][key];
}

void IniFile::set(const string &section, const string &key, const Value & value)
{
    m_sections[section][key] = value;
}

string IniFile::trim(string s)
{
    if (s.empty())
    {
        return s;
    }
    s.erase(0, s.find_first_not_of(" \n\r"));
    s.erase(s.find_last_not_of(" \n\r") + 1);
    return s;
}
