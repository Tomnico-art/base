#include "Logger.h"
using namespace yazi::utility;

#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <stdexcept>

const char *Logger::s_level[LEVEL_COUNT] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};

Logger *Logger::m_instance = NULL;

Logger::Logger() : m_level(DEBUG), m_max(0), m_len(0)
{
}

Logger::~Logger()
{
}

Logger *Logger::instance()
{
    if (m_instance == nullptr)
    {
        m_instance = new Logger();
    }
    return m_instance ;
}

void Logger::open(const string &filename)
{
    m_filename = filename;
    m_fout.open(filename, ios::app);
    if (m_fout.fail())
    {
        throw logic_error("open file failed" + filename);
    }
    m_fout.seekp(0, ios::end);
    m_len = m_fout.tellp();
}

void Logger::close()
{
    m_fout.close();
}

void Logger::log(Level level, const char *file, int line, const char *format, ...)
{
    if (m_level > level)
    {
        return;
    }
    if (m_fout.fail())
    {
        throw logic_error("open file failed" + m_filename);
    }

    time_t ticks = time(NULL);
    struct tm * ptm = localtime(&ticks);
    char timestamp[32];
    memset(timestamp, 0, sizeof(timestamp));
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", ptm);

    int len = 0;
    const char *fmt = "%s %s %s:%d ";
    len = snprintf(NULL, 0, fmt, timestamp, s_level[level], file, line);
    if(len > 0)
    {
        char * buffer = new char[len + 1];
        snprintf(buffer, len + 1, fmt, timestamp, s_level[level], file, line);
        buffer[len] = 0;
        cout << buffer << endl;
        m_fout << buffer;
        delete buffer;
        m_len += len;
    }

    va_list arg_ptr;
    va_start(arg_ptr, format);
    len = vsnprintf(NULL, 0, format, arg_ptr);
    va_end(arg_ptr);
    if (len > 0)
    {
        char *content = new char[len + 1];
        va_start(arg_ptr, format);
        vsnprintf(content, len + 1, format, arg_ptr);
        va_end(arg_ptr);
        cout << content << endl;
        m_fout << content;
        delete content;
        m_len += len;
    }
    m_fout << "\n";

    m_fout.flush();


}

void Logger::level(int level)
{
    m_level = level;
}

void Logger::max(int bytes)
{
    m_max = bytes;
}

void Logger::rotate()
{
    close();
    time_t ticks = time(NULL);
    struct tm* ptm = localtime(&ticks);
    char timestamp[32];
    memset(timestamp, 0, sizeof(timestamp));
    strftime(timestamp, sizeof(timestamp), ".%Y-%m-%d_%H-%M-%S", ptm);
    string filename = m_filename + timestamp;
    if (rename(m_filename.c_str(), filename.c_str()) != 0)
    {
        throw std::logic_error("rename log file failed: " + string(strerror(errno)));
    }
    open(m_filename);
}
