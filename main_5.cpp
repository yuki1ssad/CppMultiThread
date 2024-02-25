/*
    unique_lock 详解
    1、unique_lock 取代 lock_guard
        1.1 

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


class A 
{
public:
    void inMsgRecvQueue()
    {
        for (int i = 0; i < 100000; i++) 
        {
            std::cout << "\ninMsgRecvQueue insert an element " << std::endl;
            std::lock_guard<std::mutex> sbguard(my_mutex);
            // my_mutex.lock();
            msgRecvQueue.push_back(i);
            // my_mutex.unlock();
        }
    }

    void outMsgRecvQueue()
    {
        for (int i = 0; i < 100000; i++) 
        {
            std::lock_guard<std::mutex> sbguard(my_mutex); // 局部变量。 1. lock_guard 构造函数里执行了 mutex::lock() 2. lock_guard 析构函数里执行了 mutex::unlock()
            // my_mutex.lock();
            if (!msgRecvQueue.empty())
            {
                int command = msgRecvQueue.front(); // 返回第一个元素，但不检查第一个元素是否存在
                msgRecvQueue.pop_front();
                std::cout << "\noutMsgRecvQueue run, successfully get an element" << std::endl;
            } 
            else 
            {
                std::cout << "\noutMsgRecvQueue run, but inMsgRecvQueue is empty" << std::endl;
            }
            // my_mutex.unlock();
        }
        std::cout << "\noutMsgRecvQueue finish run" << std::endl;
    }

private:
    std::list<int> msgRecvQueue;
    std::mutex my_mutex;
    // std::mutex my_mutex_1;
};

int main()
{
    A aobj;
    std::thread myOutMsgObj(&A::outMsgRecvQueue, &aobj);
    std::thread myInMsgObj(&A::inMsgRecvQueue, &aobj);
    myOutMsgObj.join();
    myInMsgObj.join();

    // 互斥量



    std::cout << "hhh" << std::endl;
}