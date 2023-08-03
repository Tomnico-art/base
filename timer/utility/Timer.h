#pragma once

#include <thread>
#include <iostream>

namespace yazi 
{
    namespace utility
    {
        class Timer
        {
        public:
            Timer();
            Timer(int repeat);
            ~Timer();

            template <typename F, typename... Args>
            void start(int millisecond, F && func, Args&&... args); //启动
            void stop();   //关闭

        private:
            std::thread m_thread;   //定时线程
            std::atomic<bool> m_active; //原子变量
            std::function<void()> m_func;
            int m_period;   //定时器精度
            int m_repeat;   //触发次数，-1表示无限周期触发
        };   
        
    } // namespace utility
    
}