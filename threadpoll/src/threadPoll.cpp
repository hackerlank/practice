#include "threadPoll.h"
#include <string.h>
#include <sstream>
#include <unistd.h>

ThreadPoll* ThreadPoll::inst = NULL;
ThreadPoll::ThreadPoll()
{
}

ThreadPoll& ThreadPoll::getInst()
{
    if(!inst)
    {
        inst = new ThreadPoll();
    }
    return *inst;
}

ThreadPoll::~ThreadPoll()
{
    for(auto iter = m_thread.begin();iter != m_thread.end();++iter)
    {
        Thread *thread = iter->second;
        if(thread)
        {
            thread->setComplete();
        }
    }
}

bool ThreadPoll::createThread()
{
    bool ret = false;
    do
    {
        size_t key = m_thread.size() + 1;
        bool join = key % 2 == 0 ? true : false;
        std::ostringstream oss;
        oss << "[测试" << key << "]";
        Thread *thread = new Thread(oss.str(),join);
        if(!thread)
        {
            break;
        }
        if(!thread->start())
        {
            break;
        }
        m_thread.insert(std::make_pair(thread->id(),thread));
        ret = true;
    }while(false);
    return ret;
}

void ThreadPoll::loop()
{
    for(int i = 0;i < 5;++i)
    {
        createThread();
    }
    int task = 1;
    while(true)
    {
        for(auto iter = m_thread.begin();iter != m_thread.end();++iter)
        {
            Thread *thread= iter->second;
            if(thread)
            {
                thread->add(task);
            }
        }
        task++;
        sleep(2);
    }
}
       


int main()
{
    ThreadPoll &poll = ThreadPoll::getInst();
    poll.loop();
    return 0;
}
