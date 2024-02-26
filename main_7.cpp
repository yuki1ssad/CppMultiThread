/*
    condition_variable、wait、notify_one、notify_all
    1、

    2、
*/
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <thread>
#include <unistd.h>
#include <list>
#include <mutex>

std::mutex resource_mutex;
std::once_flag g_flag;

class MyCAS
{
    static void CreateInstance()
    {
        std::cout << "CreateInstance run" << std::endl;
        sleep(10);
        m_instance = new MyCAS();
        static CGarhuishou cl;
    }
private:
    MyCAS(/* args */){}; // 私有化构造函数
private:
    static MyCAS *m_instance;
public:
    static MyCAS *GetInstance()
    {
        // if (m_instance == nullptr) // 双重锁定（双重检查）-> 提高效率
        // {
        //     std::unique_lock<std::mutex> mymutex(resource_mutex);
        //     if (m_instance == nullptr) {
        //         m_instance = new MyCAS();
        //         static CGarhuishou cl;
        //     }
        // }
        std::cout << "call_once start" << std::endl;
        std::call_once(g_flag, CreateInstance);
        std::cout << "call_once finish" << std::endl;
        return m_instance;
    }

    class CGarhuishou
    {
    public:
        ~CGarhuishou()
        {
            if (MyCAS::m_instance)
            {
                delete MyCAS::m_instance;
                MyCAS::m_instance = nullptr;
            }
        }
    };
};

// 类静态变量初始化
MyCAS *MyCAS::m_instance = nullptr;

void mythread()
{
    std::cout << "My thread start." << std::endl;
    MyCAS *p_a = MyCAS::GetInstance();
    std::cout << "thread_" << std::this_thread::get_id() << " p_a: " << p_a << std::endl;
    std::cout << "My thread finish." << std::endl;
}

int main()
{
    MyCAS *p_a = MyCAS::GetInstance();
    MyCAS *p_b = MyCAS::GetInstance();
    std::cout << "p_a: " << p_a << "\np_b: " << p_b << std::endl;

    // 这两个线程会异步执行 MyCAS::GetInstance()
    std::thread mytobj1(mythread);
    std::thread mytobj2(mythread);
    mytobj1.join();
    mytobj2.join();

    // std::call_once() 
}